;-- BASIC MONOLOADER GENERATOR ---------- (c) 2001 Evg/STALL --
; Cоздает на диске BASIC-файл, содержащий в себе строку:
;
;1 CLEAR 0 [RamTop]: INK USR 0 [#5D53]: REM <исполняемый блок>
;--------------------------------------------------------------
RamTop  EQU #5FFF
        MACRO ProgName
        DEFB "Lethargy"
        ;     ^^^^^^^^ Здесь установите имя файла
        ENDM 
;Исполняемый блок оформляется макросом ExeBLK:
        MACRO ExeBLK
;--------------------------
        XOR A
        OUT (#FE),A
        LD SP,#5FFF
        LD HL,#4000
        LD DE,#4001
        LD BC,#1AFF
        LD (HL),A
        LDIR 
        LD HL,#6000
        LD DE,#4910
        CALL ldpg1
        CALL #6000
        LD DE,#2911
        CALL ldpg
        LD DE,#2B13
        CALL ldpg
        LD HL,#DE00
        LD DE,#2014
        CALL ldpg1
        LD DE,#2716
        CALL ldpg
        LD DE,#1B17
        CALL ldpg
        LD HL,#6000
        LD DE,#4210
        CALL ldpg1
        CALL #6000
        LD DE,#2811
        CALL ldpg
        JP #8500

ldpg    LD HL,#C000
ldpg1   LD BC,#7FFD
        OUT (C),E
        LD B,D
        LD C,5
        LD DE,(#5CF4)
        JP #3D13

;--------------------------
        ENDM 
;Этот макрос может содержать текст, который будет помещен в
;свободном месте файла. Далее хвост заполняется 0
        MACRO TailText
        DB "'Lethargy. The Apatetic dream.'",13
        DB "Basic Loader (c) 22-o8-2oo3 tSap rEe stall"
        DB 0
        ENDM 
;--------------------------------------------------------------
;Внимание! Бейсик не должен залезать на RamTop. Должно оста-
;ваться место и для стека, а при использовании операций ТР-ДОС,
;работающих с каталогом, необходимо место под буфер 257 байт.
;
;Буфер сдвигает область начиная с первой строки бейсика до дна
;стека включительно.
;
;PS: Кстати, BestView 2.9 пишет содержимое хвоста basic
;только если есть присоединенный блок (файл в секторах длиннее,
;чем бейсик-часть)...
;--------------------------------------------------------------
        ORG #6000
PROG    EQU #5C53       ;начало BASIC программы
VARS    EQU #5C4B       ;конец программы, начало переменных
E_LINE  EQU #5C59       ;конец переменных (начало буфера строки)
ARUN    EQU #5CD1       ;Здесь TR-DOS хранит номер строки старта
MSKSZ   EQU #5D06       ;Количество символов поиска имени

        LD HL,FNAME
        LD C,#13        ;УСТАНОВИМ ИМЯ ФАЙЛА
        CALL #3D13

        LD A,9          ;ПОИСК ПО 8+1 СИМВОЛАМ
        LD (MSKSZ),A
        LD C,#0A        ;ФАЙЛ СУЩЕСТВУЕТ?
        CALL #3D13      ;НЕТ -> C=#FF
        INC C
        JR Z,NODEL      ;ЕСЛИ ЕГО НЕТ, ТО И УДАЛЯТЬ НЕ НАДО
        LD C,#12        ;ИНАЧЕ ПРИБЪЕМ ;)
        CALL #3D13
NODEL

;СОХРАНЯЕМ СИСТЕМНЫЕ УКАЗАТЕЛИ

        LD HL,(VARS)
        PUSH HL
        LD HL,(PROG)
        PUSH HL
        LD HL,(E_LINE)
        PUSH HL

;ПЕРЕИНИЦИАЛИЗИРУЕМ ИХ ТАКИМ ОБРАЗОМ, ЧТОБЫ ПОСЛЕ ТОГО,
;КАК ТР-ДОС СОЗДАСТ БУФЕР ДЛЯ ОПЕРАЦИЙ С КАТАЛОГОМ,
;ОНИ УКАЗЫВАЛИ НА НАШУ ПРОГУ, КОТОРУЮ МЫ ЗАПИСЫВАЕМ.
        LD HL,TSTBAS+BASLEN-257
        LD (VARS),HL
        LD HL,TSTBAS-257
        LD (PROG),HL
        LD HL,TSTBAS+BSVLEN-257
        LD (E_LINE),HL

;ОНА БУДЕТ СТАРТОВАТЬ СО СТРОКИ 1
        LD HL,1
        LD (ARUN),HL

;ТЕПЕРЬ ЗАПИШЕМ ЕЕ.
        LD C,#0C
        CALL #3D13

;ВОССТАНОВИМ УКАЗАТЕЛИ НА СТАРУЮ ПРОГРАММУ
        POP HL
        LD (E_LINE),HL
        POP HL
        LD (PROG),HL
        POP HL
        LD (VARS),HL

        RET 

FNAME
        ProgName
        DEFB "B"
;--------------------------------------------------------------
;Это наша программа загрузчика

TSTBAS:
        DISP #5D3B
BAS
        DEFB 0,1          ;STRING #
        DEFW STRLEN
STR     DEFB #FD          ;CLEAR
        DEFB "0"          ;0
        DEFB #0E,0,0      ;\
        DEFW RamTop       ;| NUMBER #5FFF
        DEFB 0            ;/
        DEFB #3A,#D9,#C0  ;:INK USR
        DEFB "0"          ;0
        DEFB #0E,0,0      ;\
        DEFW EXERUN       ;| NUMBER #5D53
        DEFB 0            ;/
        DEFB #3A,#EA      ;:REM
        ;===============
EXERUN:
        ExeBLK
        ;===============
        DEFB #0D
STRLEN  EQU $-STR
BASLEN  EQU $-BAS
        DEFB #80
BSVLEN  EQU $-BAS
BSFREE  EQU RamTop-#5D3B-BSVLEN-401
        DEFB #AA
        DEFW 0
        DISPLAY "Basic program len:",BSVLEN
        DISPLAY "Basic Top addres: ",$-3
        DISPLAY "RamTop:           ",RamTop
        IFN BSFREE&#8000
   DISPLAY "RamTop no good for TRDOS CAT operations: ",BSFREE
        ENDIF 
        TailText
        DISPLAY "Last tail byte   :",$-BAS
        DEFS 256,0
        ;===============
        ENT 

