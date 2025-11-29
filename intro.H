;Intro For Lethargy. Text reader.

IM2_TABLE       EQU #82
StartCode       EQU #8400

STKBUFF         EQU 64

        IFN ?SAVEOBJ-2
PG_Muz  EQU #81
        ELSE 
PG_Muz  EQU #4
        ENDIF 

        MACRO ORGXX00
        ORG $+255&#FF00
        ENDM 

        MACRO HALTT
        IF 1
        DS 7,#76
        ENDIF 
        HALT 
        ENDM 

        MACRO EXRAM
        CALL exramsp
        DB :0
        ENDM 

        MACRO NULL
        DISPLAY "page :0: "
        ORG :1,:0
        DUP :2/#400
        DS #400
        DISPLAY /L,"."
        EDUP 
        DONE
        ENDM 

        MACRO DONE
        DISPLAY /L," Done"
        ENDM 

        IF ?SAVEOBJ-2
        ORG #6000,#00
        DISPLAY "Clearing fucking memory for saver:"
        NULL 0,#6000,#A000
        DISPLAY "Final is near... very-very near..."
        DISPLAY /L," 8(<o=;"
        DISPLAY 
        ENDIF 

;-------------------------------

                ORG #6000
_start
TB_Y            DS #400
pixtbl

clock   INCBIN "clock"
clock1  EQU clock+#0B64
clock2  EQU clock+#0BDC
clock3  EQU clock+#0C54
clock4  EQU clock+#0CCC

;-------------------------------

                ORG StartCode
Start           XOR A
                OUT (#FE),A
                EXX 
                PUSH HL
                LD (EXIT+1),SP
                JP START

I_STACK         DS STKBUFF ;стек для инта
                ORG '$+1*256

;---------------------------
INIT
        LD HL,#0101
        LD (#5C09),HL
        SET 3,(IY+48)   ;CAPS LOCK
        LD IY,#5C3A
        DEC L
        LD A,IM2_TABLE+1
        LD H,A
        LD (HL),A
        DEC H
        LD (HL),A
        INC L
        JR NZ,$-2
        LD H,A
        LD L,A
        LD (HL),#C3
        INC L
        LD (HL),.INT
        INC L
        LD (HL),'INT

        LD A,IM2_TABLE
        LD I,A
        IM 2

        EXRAM PG_Muz
        LD HL,PLYER
        LD DE,#C000
        LD BC,PLYERSIZE
        LDIR 

        EI 
        RET 

STARTPLAY
        EXRAM PG_Muz
        CALL #C000
        EXRAM 0
        LD A,#CD
        LD (PLMUS),A
        RET 

TESTEXIT
        XOR A
        IN A,(#FE)
        CPL 
        AND 31
        RET Z
        DI 
        JR EXIT

EXITT   CALL fadescr

EXIT    LD SP,0
        EXRAM PG_Muz
        CALL #C000
        EXRAM 0
        DI 
        LD A,#C9
        LD (INT),A
        XOR A
        CALL ClrAtr
        CALL gamescr
EXIT1   DI 
        CALL #1F54
        JR NC,EXIT1
        POP HL
        EXX 
        LD IY,#5C3A
        IM 1
        LD A,#3E
        LD I,A
        LD HL,#0123
        LD (#5C09),HL
        RES 3,(IY+48)
        EI 
        RET 

;------------------------

page    DB 0

exramsp EX (SP),HL
        LD A,(HL)
        INC HL
        EX (SP),HL
exram   PUSH BC
        AND #F7
        LD (page),A
        OR #10
        LD BC,#7FFD
        OUT (C),A
        POP BC
        RET 

;-------------------------

INT     LD (INT_SP+1),SP
        LD SP,I_STACK+STKBUFF
        PUSH HL
        PUSH DE
        PUSH BC
        PUSH AF
        EXX 
        EX AF,AF'
        PUSH HL
        PUSH DE
        PUSH BC
        PUSH AF
        PUSH IX
        PUSH IY
        LD A,(page)
        PUSH AF

m_lp1   EXRAM PG_Muz
PLMUS   LD HL,PLAY

        LD IY,#5C3A
        CALL #38

        CALL TESTEXIT

        POP AF
        CALL exram
        POP IY
        POP IX
        POP AF
        POP BC
        POP DE
        POP HL
        EXX 
        EX AF,AF'
        POP AF
        POP BC
        POP DE
        POP HL
INT_SP  LD SP,0
        EI 
        RET 

PLAY    LD HL,0
        LD A,0
        INC A
        CP 3
        JR NZ,$+4
        XOR A
        INC HL
        LD (PLAY+1),HL
        LD (PLAY+4),A
        JP #C006

NPatPLAY
        CALL NPPLAY
        RET Z
        HALT 
        JR NPatPLAY

NPPLAY  LD A,(PLAY+1)
        AND 63
        RET 

VVPLAY  CALL VPLAY
        RET Z
        HALT 
        JR VVPLAY

VPLAY   LD HL,(PLAY+1)
        OR A
        SBC HL,DE
        RET 

START   CALL INIT
SHOW    CALL init
        XOR A
        CALL ClrScr
        LD HL,#4047
        LD DE,clock
        LD BC,#1290
        CALL outspr
        LD HL,#5847
        LD C,18
        CALL outatr

        CALL second2
        CALL second
        CALL STARTPLAY

        LD A,#47
        CALL ClrScr

        LD DE,128
        CALL NPPLAY

        LD IX,tblL
        EXX 
        LD C,#42
        LD DE,32-5
        EXX 

        XOR A
        LD HL,#4053
        LD DE,letterL
        LD B,4
        PUSH DE
        CALL drwlett ;dl2
        POP DE
        CALL nso2
        CALL scrLe
        CALL scrLe
        CALL scrLe
        CALL scrLe

        CALL scrlse

        XOR A
        CALL ClrScr
        LD HL,#4000
        LD DE,lscr
        LD BC,#20C0
        CALL outspr
        HALT 
        EX DE,HL
        LD BC,#300
        LDIR 

        CALL NPPLAY
        CP 59
        JR NZ,$-5

        CALL fadescr
        CALL NPatPLAY
        JP START_READER

ClrScr  LD HL,#4000
        LD DE,#4001
        LD BC,#1800
        LD (HL),L
        LDIR 
ClSc1   LD BC,#2FF
        LD (HL),A
        LDIR 
        RET 

ClrAtr  LD HL,#5800
        LD DE,#5801
        JR ClSc1

second  CALL second1
second1 CALL second0
second0 LD HL,#480B
        LD BC,#0518
        CALL xorspr
second2 LD B,50
        HALT 
        DJNZ $-1
        RET 

fadescr LD B,8
fadescr0 LD HL,#5800
fadescr1 LD A,(HL)
        AND 7
        LD C,A
        JR Z,$+3
        DEC C
        LD A,(HL)
        AND #38
        JR Z,$+4
        SUB 8
        OR C
        LD (HL),A
        INC L
        JP NZ,fadescr1
        INC H
        LD A,H
        CP #5B
        JR NZ,fadescr1
        HALT 
        DJNZ fadescr0
        RET 

gamescr LD HL,#4000
        LD DE,lscr
        LD BC,#20C0
        CALL outspr
        EX DE,HL
        LD BC,#300
        LDIR 
        RET 

scrLe
        LD C,4 ;11,7,3
sLe1    CALL dll1
        LD A,C
        HALTT
        DEC C
        JR NZ,$-2
        DEC A
        LD C,A
        JR NZ,sLe1

        CALL sLe21

        LD C,(IX)
        INC IX
sLe3    EXX 
        LD C,(IX)
        INC IX
        EXX 
        CALL dll1
        HALTT
        DEC C
        JR NZ,sLe3

        CALL sLe21

        PUSH DE
        CALL dl1
        POP AF
        HALT 

        LD A,(IX)
        INC IX
        ADD A,L
        LD L,A
        LD B,(IX)
        INC IX
        LD C,(IX)
        INC IX
stts1   LD A,1
        CALL drwlett
        HALTT
        CALL dll1
        HALTT
        DEC C
        JR NZ,stts1
        CALL sLe21
        LD C,1 ;13,9,5,1
sLe4    CALL dll1
        LD A,C
        HALTT
        DEC C
        JR NZ,$-2
        INC A
        LD C,A
        CP 6
        JR C,sLe4

        PUSH HL
        PUSH DE
        PUSH BC
recatr  LD HL,#5840
        LD D,H
        LD E,L
        INC DE
        LD BC,#0080
        LD (HL),#47
        LDIR 
        LD (recatr+1),HL
        JR nso21

nso2
        PUSH HL
        PUSH DE
        PUSH BC
nso21   EXX 
        PUSH HL
        PUSH DE
        PUSH BC

        LD A,#41
        CALL nsocolor

        LD B,8
        JR $+4
nso1    POP IX
        PUSH IX
        PUSH BC
        CALL scrnam
        HALT 
        HALT 
        POP BC
        DJNZ nso1
        POP DE

        CALL outbokow
        CALL nsocolorrep

        LD B,24
        HALT 
        DJNZ $-1

        CALL s2crds
        CALL s2crds+3
        LD (HL),.endpix
        INC HL
        LD (HL),'endpix

        CALL showpixs

        CALL NPPLAY
        CP 32
        JR NZ,$-5

        POP BC
        POP DE
        POP HL
        EXX 
        POP BC
        POP DE
        POP HL
        RET 

sLe21   LD C,(IX)
        INC IX
sLe2    CALL dll1
        HALTT
        DEC C
        JR NZ,sLe2
        RET 

dll1    PUSH DE
        CALL dl1
        POP DE
        RET 

drwlett
        OR A
        JR Z,dl2
dl1     PUSH BC
        PUSH HL
        LD (HL),0
        INC L
        DJNZ $-3
        POP HL
        POP BC
        CALL dwnhl
dl2     LD (drwp1+1),HL
        LD (drwp1+4),DE
        LD (drwp1+7),BC
        PUSH HL
        PUSH BC
        LD C,32
        CALL outspr
        POP BC
        POP HL

        PUSH HL
        EXX 
        POP HL
        CALL scratr
        LD B,5
dl3     LD (HL),C
        INC L
        LD (HL),C
        INC L
        LD (HL),C
        INC L
        LD (HL),C
        INC L
        LD (HL),C
        INC L
        LD (HL),C
        ADD HL,DE
        DJNZ dl3
        EXX 
        RET 

drwprevlett
drwp1   LD HL,0
        LD DE,0
        LD BC,0
        LD C,32

outspr  PUSH HL
        PUSH BC
        LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4
        POP BC
        POP HL
        CALL dwnhl
        DEC C
        JR NZ,outspr
        RET 

outatr  PUSH BC
        LD C,L
        LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4
        LD L,C
        LD C,32
        ADD HL,BC
        POP BC
        DEC C
        JR NZ,outatr
        RET 

xorspr  PUSH HL
        PUSH BC
        LD A,(DE)
        XOR (HL)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-5
        POP BC
        POP HL
        CALL dwnhl
        DEC C
        JR NZ,xorspr
        RET 

scrlse  LD A,#45
        CALL ClrAtr

        LD B,16
scsp3   PUSH BC
        CALL scrlspr
        HALT 
        POP BC
        DJNZ scsp3
        RET 

scrlspr LD DE,#57F2
scsp1   LD HL,#57F2
        CALL uphl
        LD (scsp1+1),HL
        LD BC,#0638

scsp2   PUSH HL
        PUSH DE
        PUSH BC
        LD A,(HL)
        LD (DE),A
        INC E
        INC L
        DJNZ $-4
        POP BC
        POP HL
        CALL uphl
        EX DE,HL
        POP HL
        CALL uphl
        DEC C
        JR NZ,scsp2
        RET 

scrnam  LD B,(IX)
        INC IX
        LD A,(IX)
        LD (ouML4+1),A
        INC IX
        LD C,(IX)
        INC IX
        LD D,(IX)
        INC IX
        LD A,(IX)
        INC IX
        LD H,(IX)
        INC IX

ouML1   PUSH DE
        PUSH BC
        LD B,4
        LD L,A
ouML4   JR $
       DUP 4
        RL (HL)
        DEC L
       EDUP 
        EX DE,HL
        LD L,C
       DUP 4
        RL (HL)
        DEC L
       EDUP 
        DEC H
        EX DE,HL
        DJNZ ouML4
        POP BC
        POP DE
        DJNZ ouML1
        LD B,(IX)
        INC IX
        LD A,(IX)
        LD (ouMR4+1),A
        INC IX
        LD C,(IX)
        INC IX
        LD D,(IX)
        INC IX
        LD A,(IX)
        INC IX
        LD H,(IX)
        INC IX

ouMR1   PUSH DE
        PUSH BC
        LD B,4
        LD L,A
ouMR4   JR $
       DUP 4
        RR (HL)
        INC L
       EDUP 
        EX DE,HL
        LD L,C
       DUP 4
        RR (HL)
        INC L
       EDUP 
        INC H
        EX DE,HL
        DJNZ ouMR4
        POP BC
        POP DE
        DJNZ ouMR1
        RET 

nsocolorrep
        PUSH IX
        LD A,#47
ncr1    LD IX,0
        CALL nsocolor
        POP IX
        RET 

nsocolor
        LD (nso6+1),A
        LD (ncr1+2),IX
        LD L,(IX)
        INC IX
        LD H,(IX)
        INC IX
        LD E,(IX)
        INC IX
        LD D,(IX)
        INC IX
        LD C,(IX)
        INC IX
        LD B,(IX)
        INC IX
nso3    PUSH BC
        LD C,L
nso5    LD A,(DE)
        CP #41
        JR NZ,$+4
nso6    LD A,#41
nso4    LD (HL),A
        INC L
        INC DE
        DJNZ nso5
        LD L,C
        LD C,32
        ADD HL,BC
        POP BC
        DEC C
        JR NZ,nso3
        RET 

outbokow

        LD B,32
outboko1
        PUSH BC
        PUSH IX
        CALL oxspr3
        HALT 
        CALL oxspr3
        HALT 
        HALT 
        POP IX
        POP BC
        DJNZ outboko1

outboko2 PUSH IX
        CALL oxspr3
        HALT 
        CALL oxspr3
        HALT 
        HALT 
        POP IX
        CALL NPPLAY
        JR NZ,outboko2

        CALL oxspr5
        HALT 
oxspr5  LD HL,#4000 ;empty
        CALL oxspr4
        RET 

oxspr3
RND     LD HL,12345
        LD A,H
        ADD A,#77
        LD H,A
        RLC L
        ADD A,L
        LD L,A
        LD (RND+1),HL
        LD A,H
        AND 7
        LD H,A
        LD DE,lscr+256+1280
        ADD HL,DE

oxspr4  LD C,(IX)
        INC IX
        LD B,(IX)
        INC IX
        LD E,(IX)
        INC IX
        LD D,(IX)
        INC IX
        EXX 
        LD C,(IX)
        INC IX
        LD B,(IX)
        INC IX
        EXX 
oxspr2  PUSH BC
        PUSH HL
        EXX 
        PUSH BC
oxspr1  EXX 
        LD A,(BC)
        XOR (HL)
        EX DE,HL
        AND (HL)
        EX DE,HL
        XOR (HL)
        LD (BC),A
        INC C
        INC DE
        INC HL
        EXX 
        DJNZ oxspr1
        POP BC
        EXX 
        POP HL
        LD BC,32
        ADD HL,BC
        POP BC
        INC B
        LD A,B
        AND 7
        JR NZ,oxspr2
        LD A,C
        ADD A,32
        LD C,A
        JR C,$+6
        LD A,B
        SUB 8
        LD B,A
        EXX 
        DEC C
        RET Z
        EXX 
        JR oxspr2

scratr  LD A,H
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
        RET 

dwnhl   INC H
        LD A,H
        AND 7
        RET NZ
dwnhl1  LD A,L
        ADD A,32
        LD L,A
        RET C
        LD A,H
        SUB 8
        LD H,A
        RET 

uphl    DEC H
        LD A,H
        AND 7
        CP 7
        RET NZ
        LD A,L
        SUB 32
        LD L,A
        RET C
        LD A,H
        ADD A,8
        LD H,A
        RET 

;XY->adr
;DE->HL

A2SA    LD A,E
        RRCA 
        RRCA 
        RRCA 
        AND #E0
        ADD A,D
        LD L,A
        LD A,E
        AND #18
        OR #40
        LD H,A
        RET 


showpixs
        XOR A
        LD (isx2),A
        LD (isy2),A
        EI 
        HALT 

ppp1    DI 
        CALL outpix
        PUSH HL
        PUSH DE
        PUSH BC
        CALL drwprevlett
        POP BC
        POP DE
        POP HL
        EI 
        HALT 
        LD HL,clrpixs
        LD (ppix1+1),HL
        XOR A
        CALL clrpixs
ppp2    LD A,96
        INC A
        LD (ppp2+1),A
        JR NZ,ppp1
        LD A,96
        LD (ppp2+1),A
        RET 

outpix  DI 
        LD (endpix+1),SP
        LD SP,pixtbl
        RET 

endpix  LD SP,0
        LD HL,(ppix1+1)
        LD (HL),#C9
        RET 

;stanly
;   setop_stan,#852A,19
;
setop_stan
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 14
        LD BC,#0050
        LD DE,#0009
        JP C,attraction
        CP 20
        LD B,#80
        LD D,#09
        JP C,attraction
        CP 80
        LD BC,#C048
        JP C,attraction
        CP 110
        LD BC,#9060
        JP C,attraction
        LD BC,#FFC0
        JP attraction

;stanly
;   setop_y,#B92A,4
;
setop_y
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 10
        LD BC,#0000
        LD DE,#0009
        JP C,repulsion
        CP 15
        LD BC,#C000
        LD DE,#0909
        JP C,repulsion
        CP 95
        LD BC,#6550
        JP C,attraction
        LD BC,#60C0
        JR attraction

;capry
;   setop_c,#934A,4
;   setop_pry,#B84A,14
;
setop_c
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 25
        LD BC,#8000
        LD DE,#0900
        JR C,attraction
        CP 100
        LD BC,#8060
        LD DE,#0909
        JR C,attraction
        LD BC,#C0C0
        JR attraction
setop_pry
        JR setop_y

;fatal snipe
;   setop_stan,#7B6A,24
;   setop_y,#B96A,19
;
setop_fatal
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 25
        LD BC,#A066
        LD DE,#0909
        JR C,repulsion
        CP 50
        LD BC,#A040
        JR C,attraction
        CP 125
        LD BC,#9038
        JR C,attraction
        LD BC,#B0C0
        JR attraction

setop_nipe
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 25
        LD BC,#A070
        LD DE,#0909
        JR C,repulsion
        CP 50
        LD BC,#A094
        JR C,attraction
        CP 125
        LD BC,#9070
        JR C,attraction
        LD BC,#B0C0
        JR attraction

;притяжение
attraction
        LD HL,isy1
        LD (HL),#3E ;LD A,n
        INC HL
        LD (HL),C
        INC HL
        LD (HL),#94 ;SUB H
        LD HL,isy2
        LD (HL),E ;ADD HL,BC
        LD HL,isx1
        LD (HL),#3E ;LD A,n
        INC HL
        LD (HL),B
        INC HL
        LD (HL),#94 ;SUB H
        LD HL,isx2
        LD (HL),D ;ADD HL,BC
        RET 

;отталкивание
repulsion
        LD HL,isy1
        LD (HL),#7C ;LD A,H
        INC HL
        LD (HL),#D6 ;SUB n
        INC HL
        LD (HL),C
        LD HL,isy2
        LD (HL),E ;ADD HL,BC
        LD HL,isx1
        LD (HL),#7C ;LD A,H
        INC HL
        LD (HL),#D6 ;SUB n
        INC HL
        LD (HL),B
        LD HL,isx2
        LD (HL),D ;ADD HL,BC
        RET 


;presentz
;   setop_stan,#838A,29
;   setop_y,#B18A,4
;
setop_presen
        JP setop_stan
setop_s
        JP setop__

;game
;   setop_stan,#82AA,14
;   setop_y,#C1AA,5
;
setop_the
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 50
        LD BC,#80A0
        LD DE,#0909
        JR C,attraction
        CP 130
        LD BC,#A080
        JR C,attraction
        CP 160
        LD BC,#9000
        JR C,attraction
        LD BC,#C0C0
        JR attraction
setop__
        POP AF
        INC A
        PUSH AF
        POP AF
        CP 25
        LD BC,#A080
        LD DE,#0909
        JR C,attraction
        CP 110
        LD BC,#8080
        JR C,attraction
        CP 160
        LD BC,#40C0
        JR C,attraction
        LD BC,#C0C0
        JP attraction

outpix1
        POP HL          ;10
        LD A,H
        CP 192
        JR NC,nocpix
        POP DE          ;10
        ADD HL,DE       ;11

isy1    LD A,70         ;7
        SUB H           ;4
        EX DE,HL        ;4
        LD C,A          ;4
        SBC A,A         ;4
        LD B,A          ;4
isy2    ADD HL,BC       ;11
        EXX             ;4

        POP HL          ;10
        POP DE          ;10
        ADD HL,DE       ;11
isx1    LD A,48         ;7
        SUB H           ;4      X
        EX DE,HL        ;4
        LD C,A          ;4
        SBC A,A         ;4
        LD B,A          ;4
isx2    ADD HL,BC       ;11
        PUSH HL         ;11
        PUSH DE         ;11
        LD A,D          ;4
        EXX             ;4
        PUSH HL         ;11
        PUSH DE         ;11
        LD HL,8         ;10
        ADD HL,SP       ;11
        LD SP,HL        ;6

opix    LD L,D          ;4
        LD H,'TB_Y      ;7
        LD B,(HL)       ;7
        INC H           ;4
        LD C,(HL)       ;7
        INC H           ;4
        LD L,A          ;4
        LD A,(HL)       ;7
        INC H           ;4
        OR C            ;4
        LD C,A          ;4
        LD A,(BC)       ;7
        OR (HL)         ;7
        LD (BC),A       ;7

ppix1   LD HL,clrpixs   ;10
        LD (HL),#32     ;10    LD (##),A
        INC HL          ;6
        LD (HL),C       ;7
        INC HL          ;6
        LD (HL),B       ;7
        INC HL          ;6
        LD (ppix1+1),HL ;20
        ;380

        RET             ;10

nocpix  POP DE
        POP DE
        POP DE
        RET 

init    LD HL,TB_Y
        LD DE,#4000
iin1    LD (HL),D
        INC H
        LD (HL),E
        DEC H
        INC L
        INC D
        LD A,D
        AND 7
        JR NZ,iin1
        LD A,E
        ADD A,32
        LD E,A
        JR C,$+6
        LD A,D
        SUB 8
        LD D,A
        LD A,D
        CP #58
        JR C,iin1
        LD (HL),0
        INC L
        JR NZ,$-3
        LD H,'TB_Y+2
        LD C,#80
        XOR A
iin2    LD (HL),A
        INC H
        LD (HL),C
        RRC C
        ADC A,0
        DEC H
        INC L
        JR NZ,iin2
        RET 

s2crds
        LD HL,pixtbl
        XOR A
        LD (s2c7+1),A
        LD A,(IX)
        INC IX
        LD (s2c5+1),A
        LD A,(IX)
        INC IX
        LD (s2c51+1),A
        LD E,(IX)
        INC IX
        LD D,(IX)
        INC IX
        LD B,(IX)
        INC IX

        PUSH DE
        EXX 
        POP DE
        LD L,E
        LD A,D
        LD H,'TB_Y
        LD D,(HL)
        INC H
        LD E,(HL)
        INC H
        LD L,A
        LD A,(HL)
        INC H
        OR E
        LD E,A
        LD C,(HL)
        EX DE,HL
        EXX 
s2c5    LD (HL),0 ;.setops
        INC HL
s2c51   LD (HL),0 ;'setops
        INC HL
        LD (HL),0
        INC HL
s2c7    LD A,0
        LD (HL),A ;!
        ADD A,4
        LD (s2c7+1),A
        INC HL
s2c3    EXX 
        LD B,0
s2c2    LD A,(HL)
        AND C
        JR Z,s2c1
        INC B
        EXX 
        LD (HL),.outpix1
        INC HL
        LD (HL),'outpix1
        INC HL
        LD (HL),0 ;
        INC HL    ; Y
        LD (HL),E ;
        INC HL
        LD A,R
        AND 127
        LD (HL),0 ;A ;
        INC HL    ; vY
        LD (HL),0 ;
        INC HL
        LD (HL),0 ;
        INC HL    ; X
        LD (HL),D ;
        INC HL
        LD A,R
        AND 127
        SET 7,A
        LD (HL),0 ;A ;
        INC HL    ; vX
        LD (HL),0 ;#FF ;
        INC HL
        EXX 
s2c1    EXX 
        INC E
        EXX 
        INC H
        LD A,H
        AND 7
        CP 6
        JR NZ,s2c2
        LD A,H
        SUB 4
        LD H,A
        RRC C
        JR NC,$+3
        INC L
        EXX 
        LD A,E
        SUB 4
        LD E,A
        INC D
        EXX 
        INC B
        DEC B
        EXX 
        JR NZ,s2c4
        DJNZ s2c5
        JR s2c6
s2c4    DJNZ s2c3
s2c6    RET 

;------------------------------------------
        ORGXX00
it_stan   DD #01BCC902112D0091EB071129
it_y      DD #48782020
it_c      DD #1E10101E
it_pry    DD #F7A4943CF4108410
it_fatal  DD #1E6799001092250018F23D00109225E0
it_nipe   DD #4BDCF06912E0591C804BD0F0
it_presen DD #1CF78DE9128711CD1C84050B1087B9E9
it_s      DD #18200870
it_the    DD #3D2F112E11E8112F
it____    DD #00000054

;       DB 0 ;scrolldwn
;       DB 0 ;scrolldwn+ChangeColor
;       DB 0,0,0 ;color,color,color... для пред. пункта
;       DB 0 ;scrolldwn
;       DB 0 ;ADD HL,A
;       DB 0 ;sx
;       DB 0 ;scrolldwn+morph
;       DB 0 ;scrolldwn


tblL
;stanly
        DW #582E,stanatr,#0C06
        DW 4-3*3*256+3,#45B2,it_stan+(3*4-1)
        DW 4-1*3*256+1,#42B7,it_y
        DW #402D,stnL,#0706
        DW #402D+7,stnR,#0606
;pixs flying
        DW setop_stan,#852A
        DB 19
        DW setop_y,#B92A
        DB 4
;slide down
        DB 2
        DB 4,#43,#44,#45,#46
        DB 1
        DB 0
        DB 4,7
        DB 1

;capry
        DW #58CF,capratr,#0C05
        DW 4-1*3*256+1,#4D32,it_c+(1*4-1)
        DW 4-2*3*256+2,#4A37,it_pry
        DW #40CF,capL,#0405
        DW #40F7,capR,#0504
;pixs flying
        DW setop_c,#934A
        DB 4
        DW setop_pry,#B84A
        DB 14
;slide down
        DB 2
        DB 4,#45,#44,#43,#44
        DB 2
        DB 0
        DB 4,6
        DB 2

;fatal snipe
        DW #594D,fasnatr,#0F05
        DW 4-4*3*256+4,#4DB2,it_fatal+(4*4-1)
        DW 4-3*3*256+3,#4AB7,it_nipe
        DW #486C,fatL,#0704
        DW #4877,fatR,#0503
;pixs flying
        DW setop_fatal,#7B6A
        DB 24
        DW setop_nipe,#B96A
        DB 19
;slide down
        DB 2
        DB 4,#43,#44,#45,#46
        DB 2
        DB 0
        DB 4,6
        DB 2

;presentz
        DW #59CD,prezatr,#0E05
        DW 4-4*3*256+4,#5533,it_presen+(4*4-1)
        DW 4-1*3*256+1,#5236,it_s
        DW #48CD,przL,#0705
        DW #48CD+9,przR,#0604
;pixs flying
        DW setop_presen,#838A
        DB 29
        DW setop_s,#B18A
        DB 4
;slide down
        DB 2
        DB 4,#45,#44,#43,#45
        DB 1
        DB #FF
        DB 6,7
        DB 1

;game
        DW #5A2E,gameatr,#0D06
        DW 4-2*3*256+2,#55B1,it_the+(4*2-1)
        DW 4-1*3*256+1,#52B8,it____
        DW #506E,gamL,#0504
        DW #502E+8,gamR,#0506
;pixs flying
        DW setop_the,#82AA
        DB 14
        DW setop__,#C1AA
        DB 5

        INCLUDE "intro1",#C1

PLYER   INCBIN "PTPLAYER.C",#A2F
        INCBIN "DARKNESS.M",#1346
        PLYERSIZE=$-PLYER
        DISPLAY "End of music: ",$

clrpixs EQU PLYER       ;все равно нафиг не надо...

        ;DS 4000,#C9
        ;стирание:
        ;LD (#0),A      ;13
        ;LD (#0),A
        ;RET

letterL INCBIN "intrmrph.C"
letterA EQU letterL+#0400
letterS EQU letterL+#0780
letterT EQU letterL+#0B00
GAME    EQU letterL+#10C0
;End L+#1180

stanatr DD #414141414141414141414141414141414142424141414141
        DD #414141414142424141414141414141414142424242414141
        DD #414147474742424202474141414141414141414141414141
capratr DD #414141414646464641414141414141414646464641414141
        DD #414141414646464641414141414141470646464647474141
        DD #414141414141414141414141
fasnatr DD #414141414141444444444141414141414141414141444444
        DD #444141414141414141414141444444444141414141414147
        DD #474747444444044747474141414141414141414141414141
        DD #414141
prezatr DD #41414141414146464646414141414141
        DD #414141414646464641414141414141414141414646414141
        DD #414141414147474747460647414141414141414141414141
        DD #414141414141
gameatr DD #414141414141414141414141414141414145454545454541
        DD #414141414141454545454545414141414141414545454545
        DD #454141414141474745454545454547414141414141414141
        DD #414141414141

        ORGXX00

FNT0            INCBIN "fontintr.f",#800
FNT1            EQU FNT0+#800

Header
leth    DD #D5000000000000AA8000000000000AAAFE7D540000000000
        DD #000000001001103CAAAA0000000000440000000000000014
        DD #79E8000000000000000000001001103C50000AAAAAA82AAA
        DD #AAAA8280000102AB67555000000000000000000010011024
        DD #AA900000000000577540000000000016CA80000000000000
        DD #000000001001F0271EA00AAAAAA82AEAAAA8820000012AAC
        DD #D555000000000000000000001001503FA8000000000000D4
        DD #400000000000005998000000000000000000000010015039
        DD #08400A00000000FEEA00028000040AA39555400000000000
        DD #000000001FFF5FE972800000000000FF400000000000001F
        DD #C0000000000000000000000000F0438F0005FF00F4000001
        DD #7F00FF4000002F00FD000002FF0000AAEFFF000000F07F8F
        DD #00007F00FFA00017FF00FE00005BFF00FFF400002F000005
        DD #555D0000009FC0F8805BFFFFFE00FF009781FFB4FF00FFFF
        DD #D200FF0BFF810AABBBFF000000800000800097E0FFE8105F
        DD #FFFFF40081000B81FFD080017FFF00155555000000800000
        DD #8002FF80E8001005FF81FFD0FF017FFFFE008700051000AA
        DD #EEFFFFFFFF800000FF002FFFFE8010002F81FFA081000784
        DD #FFFAFF01FF100001555575F801000000005FFF00F800002D
        DD #FF00D000000B7F00F40000002F00000AA22BFFF801000000
        DD #00017F00FF6800001700FD0000002F00FF40002FFF000000
        DD #154557780100000000000A0000FEABAAA0000280000001FF
        DD #C40000000000000000000000000000000000000000FFD544
        DD #000000000000157E2AA80000000002200000220220020000
        DD #AAAA0AAAAAEAAAA8A0000080000002B950000000000003BB
        DD #83BBBBBB8E0EDDDF0000000000FD011040000000000455B6
        DD #AA8000000000022B80A8A2BA280A9C55AAAA0AAAAAAAAA00
        DD #A00002000000032C000000000000022A03ABA2A2280A91D5
        DD #0000000000DD0400000000000055566AA80002208AAAAA2B
        DD #83BBA2BA2E0E9DD50000000000AA800000000000000029F4
        DD #000000000000000000200000000000000000000000F40000
        DD #000000000000000000000000000000000000000000000000
        DD #48484F4F4F4F4F4141010101070105050505050707070707
        DD #07071818181818184F4B4B5F4B4B4F4B4B5F43434705052F
        DD #05054703031F181818181818181818184F4F4F4F4F414141
        DD #410701010705050505054747470604040404040404181818
stnL    INCBIN "fig4intr"
stnR    EQU stnL+#0150
capL    EQU stnL+#0270
capR    EQU stnL+#0310
fatL    EQU stnL+#03B0
fatR    EQU stnL+#0490
przL    EQU stnL+#0508
przR    EQU stnL+#0620
gamL    EQU stnL+#06E0
gamR    EQU stnL+#0780

lscr    INCBIN "lethscr"

        DISPLAY "expecting end of all: ",$

_size=$-_start

        IF ?SAVEOBJ-2
        SAVEOBJ "l_intro0",_start,_size
        ENDIF 

        ORG Start

