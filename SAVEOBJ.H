;--------- Object Saver v2.1 (ц) ЦаПрЮгА 02.06.2001 -----------
;  * Перед использованием настройте параметры!!! (см ниже!) *
;  Здесь содержится макрос SAVEOBJ:
;       SAVEOBJ "filenameE",start,len[,page]
;  Е - расширение, по умолЧаниЮ - "C"
;  Главный файл проекта должен находиться в странице MAIN_PAGE.
;Для записи проект должен содержать вызов макроса SAVEOBJ:
;
;       IF ?SAVEOBJ-2
;       SAVEOBJ "имяфайла1",старт,длина[,страница]
;       ...
;       SAVEOBJ "имяфайлаN",старт,длина[,страница]
;       ENDIF
;
;  Таких вызовов может быть несколько.
;  Для компиляции в память необходимо компилировать с главного
;файла проекта, для записи на диск - с файла SAVEOBJ. Признак
;компиляции на диск - определенность SAVEOBJ как макроса
; (?SAVEOBJ=2).
;
;WARNING! Макрос изменяет текущую страницу компиляции на нулевую
;
;Отличия от версии 2.0:
; + Уменьшил сэйвер на 2 байта
; + Сэйвер тепереча располагается с адреса #5B00 (можно сменить)
; + Сэйвер можно настроить, чтобы запускался из вашей
;   проги (в переменную JP_BEFORE_SAVE поместите адрес запуска
;   проги, а там в нужном месте CALL _SAVER)

        MAIN "SAVEOBJ"  ; Чтобы не было Wrong MAIN Place

        DISPLAY "*** OBJECT SAVER ***"
        DISPLAY 

;--------------- Настраиваемые параметры ----------------------
MAIN_PAGE       EQU #C0    ;Главная страница проекта
_SVTBL          EQU #5B00  ;адрес размещения записывалки :)
_ERASE_FILES    EQU 1      ;1-удалять файл перед записью, 0-нет
;--------------------------------------------------------------

_SVREC  EQU _SVTBL

        MACRO SAVEOBJ

        _SVs=:1         ;для того, чтобы можно было использовать
        _SVl=:2         ;выражения с $
        _SVorg=$

        IF _SVl
        DISPLAY "Warning! ",:0," empty!"
        ELSE 

        ORG _SVREC
        DEFS 8," "
        DEFB "C"
        ORG _SVREC
        DEFB :0
        ORG _SVREC+9
        DEFW _SVs,_SVl

        IF "  "-"  :3"  ;если страницу не ввели
        DEFB #10
        DISPLAY "SAVEOBJ ",:0,"=",_SVs,",",_SVl
        ELSE 
        DEFB :3|#10
 DISPLAY "SAVEOBJ ",:0,"=",_SVs,",",_SVl,",:3"
        ENDIF 

        _SVREC=$

        ORG _SVorg      ;страница компиляции=0

        ENDIF 

        ENDM ;SAVEOBJ


        INCLUDE "",MAIN_PAGE    ;оттранслируем проект

        ORG _SVREC
        DEFB 0
_SAVER  LD HL,_SVTBL
_SVNEXT LD A,(HL)
        OR A
        RET Z
        LD DE,#5CDD     ;имя кинем
        LD BC,9
        LDIR 
        LD E,(HL)       ;старт
        INC HL
        LD D,(HL)
        INC HL
        PUSH DE
        LD E,(HL)       ;длина
        INC HL
        LD D,(HL)
        INC HL
        LD A,(HL)       ;страница
        INC HL
        LD BC,#7FFD
        OUT (C),A
        EX (SP),HL

        IFN _ERASE_FILES
        PUSH HL
        PUSH DE         ;на всякий пожарный
        LD C,#0A
        CALL #3D13      ;файл есть?
        INC C
;       JR Z,_noDEL
        LD C,#12
        CALL NZ,#3D13   ;kill'em all!
;_noDEL
        POP DE
        POP HL
        ENDIF 

        LD C,#0B
        CALL #3D13
        POP HL
        JR _SVNEXT

        DISPLAY "Saver: ",_SVTBL,"-",$

        IFN ?JP_BEFORE_SAVE
        ORG _SVREC+1
        DISPLAY "RUN program for save!!!"
        ELSE 
        ORG JP_BEFORE_SAVE
        ENDIF 

