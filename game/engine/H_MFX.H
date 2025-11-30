;Звуки, распакеры, музыка...

        MAIN "",#C0

        IFN ?GAMEOVER
;первый проход - код в основном теле проги

AtrBuff EQU ATRS_BUFF

GAMEOVER
        DI 
        LD A,mus_pg
        CALL ONPAGE
        CALL INIT
        XOR A
        CALL ini_nrgline
        LD A,gfx_pg
        CALL ONPAGE
        CALL outnrg
        LD A,#CD
        LD (i_plmuz),A
        LD A,#21
        LD (i_game),A
        LD (i_plsnd),A
        LD B,50
eoga1   EI 
        HALT 
        XOR A
        LD (intcntr+1),A
        PUSH BC
        CALL SHWSPZ
        POP BC
        DJNZ eoga1

        EI 

        CALL ClrScrF7

        CALL ONPAGE_mus
        LD HL,go_xor
        LD DE,ATRS_BUFF ;еле-еле влазит!
        CALL DEHRUST

        LD HL,ATRS_BUFF ;прорисовка скелетокровати ;#8000
        CALL goSAll

        ;д.б. тушение кровати

        CALL CleAtr

        LD HL,go_scr
        CALL DECOMPR

        HALT 

        LD HL,#5800+#200
        LD DE,ATRS_BUFF+#200
        LD BC,#FF47
        LD A,C
        CALL LPATR1

        LD B,50
        HALT 
        DJNZ $-1

        LD A,8
LPATR4  PUSH AF
        CALL CreateDecTable
        HALT 
        LD HL,#5820
        LD DE,ATRS_BUFF+32
        LD BC,#5AE0
        CALL CngAtrsCP
        POP AF
        DEC A
        CP #FF
        JR NZ,LPATR4

        LD B,50
        HALT 
        DJNZ $-1

        LD HL,#5800
        LD BC,#1400
        LD A,6
        CALL TXATR

        PUSH BC
        LD B,100
        HALT 
        DJNZ $-1
        POP BC
        CALL TXATRFD

        LD HL,#5814
        LD BC,#0C00
        CALL TXATR

        PUSH BC
        LD B,100
        HALT 
        DJNZ $-1
        POP BC
        CALL TXATRFD

        LD HL,#5AE0
        LD BC,#2000
        CALL TXATR

        PUSH BC
        LD B,100
        HALT 
        DJNZ $-1
        POP BC
        CALL TXATRFD

        XOR A
        IN A,(#FE)
        CPL 
        AND 31
        JR Z,$-6

        LD A,#21
        LD (i_plmuz),A

        CALL INIT
        DI 
        JP RESTART

ClrScrF7 LD A,7
ClrScrF
        PUSH AF
        CALL FadeScr
        POP AF

ClrScrA LD HL,#4000
        LD DE,#4001
        LD BC,#1800
        LD (HL),L
        LDIR 
        LD BC,#2FF
        LD (HL),A
        LDIR 
        RET 

TXATR   CALL TXATR1
        INC C
        CP C
        JR NZ,TXATR
        RET 

TXATRFD
        DEC C
        PUSH AF
        CALL TXATR1
        POP AF
        RET Z
        JR TXATRFD

TXATR1  PUSH HL
        PUSH BC
        LD (HL),C
        INC L
        DJNZ $-2
        POP BC
        POP HL
        HALT 
        HALT 
        HALT 
        RET 


LPATR1  LD (LPATR12+1),A
        PUSH AF
        PUSH HL
        PUSH DE
        PUSH BC
LPATR11 LD A,(DE)
        CP C
        JR NZ,$+4
LPATR12 LD (HL),0
        INC HL
        INC DE
        DJNZ LPATR11
        POP BC
        POP DE
        POP HL
        POP AF
        RET 

DecTbl  EQU TBL_SCOMS

FadeScr
        LD A,1
        CALL CreateDecTable
        LD B,8
FadeScr1 PUSH BC
        EI 
        HALT 
        LD HL,#5800
        LD D,H
        LD E,L
        LD BC,#5B00
        CALL CngAtrsOR
        POP BC
        DJNZ FadeScr1
        RET 

CreateDecTable
        LD HL,DecTbl
        OR A
        JR NZ,CDecTb1
        LD (HL),L
        INC L
        JR NZ,$-2
        RET 

CDecTb1 LD C,A
        RLCA 
        RLCA 
        RLCA 
        LD B,A
CDecTbl LD A,L
        AND 7
        SUB C
        JR NC,$+3
        XOR A
        LD E,A
        LD A,L
        AND 7*8
        SUB B
        JR NC,$+3
        XOR A
        OR E
        LD (HL),A
        INC L
        JR NZ,CDecTbl
        RET 

CngAtrsOR
        LD A,#B7
        JR $+4

CngAtrsCP
        LD A,#BE
        LD (CAS4),A

CngAtrs LD A,B
        LD (CAS3+1),A
        LD A,C
        LD (CAS2+1),A
        LD B,'DecTbl
CAS1    LD A,(DE)
CAS4    CP (HL)         ;#BE - CP (HL), #B7 - OR A
        JR Z,$+5
        LD C,A
        LD A,(BC)
        LD (HL),A
        INC HL
        INC DE
        LD A,L
CAS2    CP 0
        JR NZ,CAS1
        LD A,H
CAS3    CP #5B
        JR NZ,CAS1
        RET 

goSAll  LD (goS9+1),HL
        CALL goS9
        LD B,50
        CALL PAUSE

        CALL goS9
        LD B,50
        CALL PAUSE

        LD B,4
        CALL goS9
        HALT 
        HALT 
        HALT 
        HALT 
        DJNZ $-7

        LD B,30
        CALL PAUSE

        LD B,5
        CALL goS9
        HALT 
        HALT 
        HALT 
        DJNZ $-6

        LD B,100
        CALL PAUSE

        RET 

PAUSE   HALT 
        DJNZ $-1
        RET 

go_sm=2

goS9    LD HL,#8000
        LD DE,#4089+go_sm
        PUSH BC
        LD A,12*14/8
goS8    EX AF,AF'
        LD C,(HL)
        INC HL
        EX DE,HL
        LD B,8
goS5    RL C
        PUSH BC
        JR C,goS6
        LD B,8
        LD A,(DE)
        XOR (HL)
        LD (HL),A
        INC DE
        INC H
        DJNZ $-5
        LD A,H
        SUB 8
        LD H,A

goS6    INC L
        LD A,L
        AND 31
        CP 16+5+go_sm
        JR C,goS7
        LD A,L
        ADD A,32-12
        LD L,A
        JR NC,goS7
        LD A,H
        ADD A,8
        LD H,A
goS7    POP BC
        DJNZ goS5
        EX DE,HL
        EX AF,AF'
        DEC A
        JR NZ,goS8
        POP BC
        LD (goS9+1),HL
        RET 

;Распаковщик файлов, упакованных методом
;Hrust1:  (программы Hrust1.0, Hrust1.1)
;
;Не использует регистр SP,  поэтому рас-
;паковку  можно проводить и при включен-
;ных прерываниях. Длина #121(289) байт.
;         !!!Неперемещаемый!!!
;
;Можно использовать "стандартный", пере-
;мещаемый распаковщик длиной 256 байт.
;Однако он использует регистр SP.
;
;формат файла:
;+0(2):"HR" - признак принадлежности
;+2(2) - длина исходного файла
;+4(2) - длина упакованного файла
;
;Для распаковки файла надо задать в:
;HL - откуда распаковывать
;DE - куда распаковывать
;и вызвать депакер (CALL DEHRUST).
;Области откуда/куда распаковывать могут
;пересекаться, депакер это учитывает.
;Если эти области не пересекаются, то
;распаковать файл можно несколько раз.
;Больше депакер не использует никаких
;областей (исключая 6 байт в стеке).
;
;Example:
;1) LD HL,#8000:LD DE,#8000:CALL DEHRUST
;2) LD HL,#C000:LD DE,#8000:CALL DEHRUST
;
;            Есть вопросы ?
;
;**************************************
;*    E-mail: dp@fmf.gasu.gorny.ru    *
;*    tel:(38822) 244-21. Дмитрий.    *
;*     Россия. г.Горно - Алтайск.     *
;*         01.03.97 - 28.12.98        *
;**************************************

DEHRUST PUSH DE
        PUSH HL
        INC HL
        INC HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        DEC BC
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        DEC BC
        POP HL
        ADD HL,BC
        SBC HL,DE
        ADD HL,DE
        JR C,LL4019
        LD D,H
        LD E,L
LL4019  LDDR 
        EX DE,HL
        POP DE
        LD C,#0C
        ADD HL,BC
        PUSH HL
        POP IX
        LD A,#03
LL4025  DEC HL
        LD B,(HL)
        DEC HL
        LD C,(HL)
        PUSH BC
        DEC A
        JR NZ,LL4025
        LD B,A
        EXX 
        LD D,#BF
        LD C,#10
        CALL LL4115
LL4036  LD A,(IX+#00)
        INC IX
        EXX 
LL403C  LD (DE),A
        INC DE
LL403E  EXX 
LL403F  ADD HL,HL
        DJNZ LL4045
        CALL LL4115
LL4045  JR C,LL4036
        LD E,#01
LL4049  LD A,#80
LL404B  ADD HL,HL
        DJNZ LL4051
        CALL LL4115
LL4051  RLA 
        JR C,LL404B
        CP #03
        JR C,LL405D
        ADD A,E
        LD E,A
        XOR C
        JR NZ,LL4049
LL405D  ADD A,E
        CP #04
        JR Z,LL40C4
        ADC A,#FF
        CP #02
        EXX 
LL4067  LD C,A
LL4068  EXX 
        LD A,#BF
        JR C,LL4082
LL406D  ADD HL,HL
        DJNZ LL4073
        CALL LL4115
LL4073  RLA 
        JR C,LL406D
        JR Z,LL407D
        INC A
        ADD A,D
        JR NC,LL4084
        SUB D
LL407D  INC A
        JR NZ,LL408D
        LD A,#EF
LL4082  RRCA 
        CP A
LL4084  ADD HL,HL
        DJNZ LL408A
        CALL LL4115
LL408A  RLA 
        JR C,LL4084
LL408D  EXX 
        LD H,#FF
        JR Z,LL409B
        LD H,A
        INC A
        LD A,(IX+#00)
        INC IX
        JR Z,LL40A6
LL409B  LD L,A
        ADD HL,DE
        LDIR 
LL409F  JR LL403E
LL40A1  EXX 
        RRC D
        JR LL403F
LL40A6  CP #E0
        JR C,LL409B
        RLCA 
        XOR C
        INC A
        JR Z,LL40A1
        SUB #10
LL40B1  LD L,A
        LD C,A
        LD H,#FF
        ADD HL,DE
        LDI 
        LD A,(IX+#00)
        INC IX
        LD (DE),A
        INC HL
        INC DE
        LD A,(HL)
        JP LL403C
LL40C4  LD A,#80
LL40C6  ADD HL,HL
        DJNZ LL40CC
        CALL LL4115
LL40CC  ADC A,A
        JR NZ,LL40F3
        JR C,LL40C6
        LD A,#FC
        JR LL40F6
LL40D5  LD B,A
        LD C,(IX+#00)
        INC IX
        CCF 
        JR LL4068
LL40DE  CP #0F
        JR C,LL40D5
        JR NZ,LL4067
        LD B,#03
        EX DE,HL
LL40E7  POP DE
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        DJNZ LL40E7
        LD HL,#2758
        EXX 
        RET 
LL40F3  SBC A,A
        LD A,#EF
LL40F6  ADD HL,HL
        DJNZ LL40FC
        CALL LL4115
LL40FC  RLA 
        JR C,LL40F6
        EXX 
        JR NZ,LL40B1
        BIT 7,A
        JR Z,LL40DE
        SUB #EA
        ADD A,A
        LD B,A
LL410A  LD A,(IX+#00)
        INC IX
        LD (DE),A
        INC DE
        DJNZ LL410A
        JR LL409F
LL4115  LD B,C
        LD L,(IX+#00)
        INC IX
        LD H,(IX+#00)
        INC IX
        RET 
LCODE   EQU $-DEHRUST

;---------------------------------------
; Depacker Laser Compact 5.2
; +0(5): "LCMP5"
; +5(2): Length screen without header
; +7(1): Additional info length:
;-------
; 11 byte - File name
; N byte - Comment.
;-------
;(C) Hrumer. 06.12.99. Hrumer@inbox.ru
;
; IN: HL - Address of compressed screen
;---------------------------------------

ADR     EQU #4000;#8000;#C000

DECOMPR
        LD DE,7 ;SKIP "LCMP5" & LENGTH
        ADD HL,DE

        LD A,(HL)
        INC HL
        LD E,A
        ADD HL,DE

        LD A,(HL)
        LD E,A;РАЗРЫВ

        AND 3
        RLCA 
        RLCA 
        RLCA 
        OR ADR/256

        EXX 
        LD D,A;НАЧАЛО
        LD E,0
        EXX 

        LD A,(HL)
        INC HL
        XOR ADR/256+#18
        AND #FC
        LD HX,A;КОНЕЦ Ч. ИЗО.

DLC1    LD A,(HL)
        INC HL
        LD LX,#FF
DLC2
        EXX 
        JR NZ,DLC10
        LD B,1

DLC3    EXA 
        SLA D
        JR NZ,$+6
        LD D,(HL)
        INC HL
        SLI D

        DJNZ DLC7

        JR C,DLC1

        INC B
;-----------
DLC4    LD C,%01010110
        LD A,#FE
DLC5    SLA D
        JR NZ,$+6
        LD D,(HL)
        INC HL
        RL D
        RLA 
        SLA C
        JR Z,DLC6
        JR C,DLC5
        RRCA 
        JR NC,DLC5
        SUB 8
DLC6    ADD A,9
;---------
        DJNZ DLC3

        CP 0-8+1
        JR NZ,$+4
        LD A,(HL)
        INC HL

        ADC A,#FF
        LD LX,A
        JR C,DLC4
        LD HL,#2758
        EXX 
        RET 
;-------------
DLC7    LD A,(HL)
        INC HL

        EXX 
        LD L,A
        EXA 
        LD H,A
        ADD HL,DE

        CP #FF-2
        JR NC,DLC8
        DEC LX
DLC8
        LD A,H
        CP HX
        JR NC,DLC13
        XOR L
        AND #F8
        XOR L
        LD B,A
        XOR L
        XOR H
        RLCA 
        RLCA 
        LD C,A

DLC9    EXA 
        LD A,(BC)
DLC10   EXA 
        LD A,D
        CP HX
        JR NC,DLC14
        XOR E
        AND #F8
        XOR E
        LD B,A
        XOR E
        XOR D
        RLCA 
        RLCA 
        LD C,A

DLC11   EXA 
        LD (BC),A

        INC DE
        JR NC,$+4
        DEC HL
        DEC HL
        INC HL
        EXA 
        INC LX
        JR NZ,DLC8
        JR DLC2

DLC13   SCF 
DLC14   PUSH AF

        CP 'AtrBuff             ;
        JR NC,$+4               ; бу ми. атрибудтты в AtrBuff'е
        ADD A,'AtrBuff-#58      ;

        EXX 
        ADD A,E
        EXX 
        LD B,A
        POP AF
        LD C,E
        JR NC,DLC11
        LD C,L
        JR DLC9
LENGDEC EQU $-DECOMPR

        ELSE 

;докомпиляция - звуки в странице

tab_vol DD #00000000000000000000000000000000
        DD #00000000000000000101010101010101
        DD #00000000010101010101010102020202
        DD #00000001010101010202020202030303
        DD #00000101010102020202030303030404
        DD #00000101010202020303030404040505
        DD #00000101020202030304040405050606
        DD #00000101020203030404050506060707
        DD #00010102020303040405050606070708
        DD #00010102020304040505060707080809
        DD #0001010203030405050607070809090A
        DD #000101020304040506070708090A0A0B
        DD #0001020203040506060708090A0A0B0C
        DD #00010203030405060708090A0A0B0C0D
        DD #00010203040506070708090A0B0C0D0E
        DD #000102030405060708090A0B0C0D0E0F

frq_A   DW 0
frq_B   DW 0
frq_C   DW 0
frq_N   DB 0
mix     DB 0
vol_A   DB 0
vol_B   DB 0
vol_C   DB 0
frq_E   DW 0
form_E  DB 0

chnfaze EQU 12

ShutSmp LD HL,0
        LD (SND_A+1),HL
        LD (SND_B+1),HL
        LD (SND_C+1),HL
        RET 

IniSmpNmb
        PUSH HL
        PUSH DE
        PUSH BC
        LD A,B
        LD B,0
        LD HL,sndtbl
        ADD HL,BC
        ADD HL,BC
        LD E,(HL)
        INC HL
        LD D,(HL)
        EX DE,HL
        CP 10+16
        LD C,0
        JR C,ISN1
        INC C
        CP 22+16
        JR C,ISN1
        INC C
ISN1    CALL Ini_Smp
        POP BC
        POP DE
        POP HL
        RET 

;HL = SAMPLE ADDRES
;C=chanel
Ini_Smp
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        EX DE,HL
        ADD HL,DE
        XOR A
        DEC C
        JR Z,IS_B
        DEC C
        JR Z,IS_C
        LD (NoSmF_A),A
        LD (REP_A+1),HL
        LD (SND_A+1),DE
        RET 

IS_B    LD (NoSmF_B),A
        LD (REP_B+1),HL
        LD (SND_B+1),DE
        RET 

IS_C    LD (NoSmF_C),A
        LD (REP_C+1),HL
        LD (SND_C+1),DE
        RET 

OUTSOUNDS
        CALL SND_PLR
        CALL OUTPUT
        RET 

SND_PLR
        LD A,(mix)
        LD C,A
        CALL SND_A
        CALL SND_B
        CALL SND_C
        LD A,C
        LD (mix),A
        RET 

;--- канал A ---
SND_A   LD HL,0
        LD A,H
        AND A
        JR NZ,SmpA_ON

NoSmF_A RET 
        LD (vol_A),A   ; A=0 !!!
        LD A,%001001 ;0*3+2/2*9
        OR C
        LD C,A
        LD A,#C9
        LD (NoSmF_A),A
        RET 

SmpA_ON
        LD A,%001001
        OR C
        LD C,A
        LD A,(HL)
        INC HL
        RRCA 
        JR NC,no_nseA
        EXA 
        LD A,(HL)
        INC HL
        LD (frq_N),A
        EXA 
        RES 3,C
no_nseA RRCA 
        JR NC,no_tneA
        LD D,(HL)
        INC HL
        LD E,(HL)
        INC HL
        PUSH HL         ;
        LD HL,chnfaze   ;
        ADD HL,DE       ;
        LD (frq_A),HL   ;DE
        POP HL          ;
        RES 0,C
no_tneA RRCA 
        JR NC,$+5
REP_A   LD HL,0
        RRCA 
        JR NC,$+4
        LD H,0
        AND #0F
        LD (SND_A+1),HL
SndAVol OR #F0
        LD L,A
        LD H,'tab_vol
        LD A,(HL)
        LD (vol_A),A
        RET 

;--- канал B ---
SND_B   LD HL,0
        LD A,H
        AND A
        JR NZ,SmpB_ON

NoSmF_B RET 
        LD (vol_B),A   ; A=0
        LD A,1*3+2/2*9
        OR C
        LD C,A
        LD A,#C9
        LD (NoSmF_B),A
        RET 

SmpB_ON LD A,C
        OR %010010
        LD C,A
        LD A,(HL)
        INC HL
        RRCA 
        JR NC,no_nseB
        EXA 
        LD A,(HL)
        INC HL
        LD (frq_N),A
        EXA 
        RES 4,C
no_nseB RRCA 
        JR NC,no_tneB
        LD D,(HL)
        INC HL
        LD E,(HL)
        INC HL
        LD (frq_B),DE
        RES 1,C
no_tneB RRCA 
        JR NC,$+5
REP_B   LD HL,0
        RRCA 
        JR NC,$+4
        LD H,0
        AND #0F
        LD (SND_B+1),HL
SndBVol OR #F0
        LD L,A
        LD H,'tab_vol
        LD A,(HL)
        LD (vol_B),A
        RET 

;--- канал C ---
SND_C   LD HL,0
        LD A,H
        AND A
        JR NZ,SmpC_ON

NoSmF_C RET 
        LD (vol_C),A   ;0
        LD A,%100100
        OR C
        LD C,A
        LD A,#C9
        LD (NoSmF_C),A
        RET 

SmpC_ON
        LD A,%100100
        OR C
        LD C,A
        LD A,(HL)
        INC HL
        RRCA 
        JR NC,no_nseC
        EXA 
        LD A,(HL)
        INC HL
        LD (frq_N),A
        EXA 
        RES 5,C
no_nseC RRCA 
        JR NC,no_tneC
        LD D,(HL)
        INC HL
        LD E,(HL)
        INC HL
        PUSH HL         ;
        LD HL,-chnfaze  ;
        ADD HL,DE       ;
        LD (frq_C),HL   ;DE
        POP HL          ;
        RES 2,C
no_tneC RRCA 
        JR NC,$+5
REP_C   LD HL,0
        RRCA 
        JR NC,$+4
        LD H,0
        AND #0F
        LD (SND_C+1),HL
SndCVol OR #F0
        LD L,A
        LD H,'tab_vol
        LD A,(HL)
        LD (vol_C),A
        RET 

AY_OFF  LD HL,vol_C
        XOR A
        LD (HL),A
        DEC L
        LD (HL),A
        DEC L
        LD (HL),A
        DEC L
        CPL 
        LD (HL),A

OUTPUT  LD DE,#FFBF
        LD BC,#FFFD
        LD HL,frq_A
        OUT (C),L
        LD B,E
        OUTI 

        DUP 12
        LD B,D
        OUT (C),L
        LD B,E
        OUTI 
        EDUP 

        LD A,(HL)
        OR A
        RET Z
        LD B,D
        OUT (C),L
        LD B,E
        OUT (C),A
        XOR A
        LD (HL),A
        RET 

        ENDIF 
