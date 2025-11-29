;Viewer for Text with grafix. (c) Capry/STALL
;------------------------------
MainColor       EQU 5
IM2_TABLE       EQU #82
StartCode       EQU #8400
PG_Muz          EQU 6
PGGfx0          EQU 1
PGGfx1          EQU 3
PGGfx2          EQU 7
PGGfx3          EQU #41 ;4
PGTxt           EQU 7

strings         EQU 21  ;кол-во строк на экране (снизу)

CheatPatch      EQU #6237

id              EQU 0

STKBUFF         EQU 64

;DEBUG

        P20=#40
        P23=#43
        P24=#44
        P25=#45

;------------------------------
        MACRO EXRAM
        CALL exramsp
        DB :0
        ENDM 

        MACRO DK
        DB :0
        DW :1
        ENDM 

        _stradr=0

        MACRO DT
        DW _stradr
        _stradr=$-2
        IFN 0+:0
        DB :0
        IFN 0+:1
        DB :1
        IFN 0+:2
        DB :2
        IFN 0+:3
        DB :3
        IFN 0+:4
        DB :4
        IFN 0+:5
        DB :5
        ENDIF 
        ENDIF 
        ENDIF 
        ENDIF 
        ENDIF 
        ENDIF 
        ENDM 

;SPRITE Name,addr,len,hgt,atrs

        MACRO SPRITE
        :0addr=:1
        :0len=:2
        :0hgt=:3
        :0atrs=:4
        ENDM 

;SPRLINE Name,line

        MACRO SPRLINE
        DB 9
        DW :0addr
        IFN :0atrs
        DW 8*:0len*:1
        ELSE 
        DW 9*:0len*:1
        ENDIF 
        ENDM 

        MACRO STD
        IFN ?SAVEOBJ-2
        DISPLAY "STD breakpoint at ",$
        CALL std
        ENDIF 
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
        ORG #6000,#07
        DISPLAY "Clearing fucking memory for saver:"
        NULL 7,#C000,#4000
        NULL 1,#C000,#4000
        NULL 2,#8000,#4000
        NULL 3,#C000,#4000
        DISPLAY "Final is near... very-very near..."
        DISPLAY /L," 8(<o=;"
        DISPLAY 
        ENDIF 

        passbuff=#FE00
        PASSBUFF=passbuff

        MACRO PASSWORD
        saveadr=$
        crc=0
        ORG passbuff
        DW :1

        tstadr=$
        DB :0
        lnpsw=$-tstadr
        ORG tstadr
        DB lnpsw,:0
        passbuff=$
        DW 0

        ORG saveadr
        DB lnpsw:N
        DUP lnpsw
        crc=crc!":C":N
        EDUP 

        DB crc
        DW :1
        ENDM 

;------------------------------
        ;ORG #C000,PG_Muz
        ;INCLUDE "PT35play",P23
;------------------------------
                ORG StartCode,PGTxt
FNT0            INCBIN "fontintr.f",#800
FNT1            EQU FNT0+#800

;Заголовок вьювера. (top)
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

                ORG FNT1+#800,PGTxt

Start           JP START

I_STACK         DS STKBUFF ;стек для инта
                ORG '$+1*256
KEYSBUFF        DS 256   ;буфер для пароля :)
ANIGFXBUFF      DS 256   ;буфер информации для анимации
                         ;DW SCRADR,^SPR,PLUS


;-------------------------

START   CALL INIT
ST_PAGE CALL PAGE

WaitKey RES 5,(IY+1)
WaitK1  HALT 

        CALL #1F54
        JP NC,EXIT

WK1     LD A,50
        DEC A
        JR NZ,WK2
        LD HL,KEYSBUFF
        LD (KBU1+1),HL
        ;оч. буфер пароля
        INC A
WK2     LD (WK1+1),A

        BIT 5,(IY+1)
        JR Z,WaitK1

        LD A,(IY-50)
KBU1    LD HL,KEYSBUFF
        LD (HL),A
        INC L
        LD (KBU1+1),HL
WYK1    LD A,50
        LD (WK1+1),A
        LD A,(IY-50)
        LD HL,KEYTAB
SEARK1  BIT 7,(HL)
        JP NZ,WPU1
        CP (HL)
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        JR NZ,SEARK1
        EX DE,HL
        JP (HL)

WPU1    RES 5,(IY+1)
        HALT 
        BIT 5,(IY+1)
        JR NZ,WPU1
        JP WaitKey

ST_PAGE1 CALL PAGE
WaitKey1 RES 5,(IY+1)
        HALT 
        BIT 5,(IY+1)
        JR Z,WaitK1
        JR WYK1

KEYTAB  DK "Q",UP
        DK "9",UP
        DK 11,UP
        DK "A",DOWN
        DK "8",DOWN
        DK 10,DOWN
        DK "O",LEFT
        DK "6",LEFT
        DK 4,LEFT
        DK 8,LEFT
        DK "P",RIGHT
        DK "7",RIGHT
        DK 5,RIGHT
        DK 9,RIGHT
        DK 7,EXIT
        DK 14,EXIT
        DK 13,SRC_PAROL
        DB #80

UP      LD HL,(FRSTRNG)
        LD A,(HL)
        INC HL
        OR (HL)
        JP Z,WaitKey1
        CALL DwnAni
        LD HL,#50C0
        LD DE,#50E0
        LD B,strings-1 ;21
SCRLDW1 CALL SCRLIN
        LD A,L
        SUB 32
        LD L,A
        JR NC,$+6
        LD A,H
        SUB 8
        LD H,A
        LD A,E
        SUB 32
        LD E,A
        JR NC,$+6
        LD A,D
        SUB 8
        LD D,A
        DJNZ SCRLDW1
        EX DE,HL
        LD (Adress1+1),HL
        LD (Adress+1),HL
        LD HL,(FRSTRNG)
        LD E,(HL)
        INC HL
        LD D,(HL)
        EX DE,HL
        LD (FRSTRNG),HL
        CALL String
        LD HL,(NXSTRNG)
        LD E,(HL)
        INC HL
        LD D,(HL)
        LD (NXSTRNG),DE
noafa   ;LD A,2
        ;LD (scrl+1),A
        JP WaitKey1

DOWN    LD HL,(NXSTRNG)
        INC HL
        INC HL
        LD A,(HL)
        OR A
        JP Z,WaitKey1
        LD HL,(FRSTRNG)
        CALL EmulStr
        LD (FRSTRNG),HL
        CALL UpAni
                         ;DW SCRADR,^SPR,PLUS
        LD HL,24-strings*32+#4020
        LD DE,24-strings*32+#4000
        LD B,strings-1
SCRLUP1 CALL SCRLIN
        LD A,L
        ADD A,32
        LD L,A
        JR NC,$+6
        LD A,H
        ADD A,8
        LD H,A
        LD A,E
        ADD A,32
        LD E,A
        JR NC,$+6
        LD A,D
        ADD A,8
        LD D,A
        DJNZ SCRLUP1
        EX DE,HL
        LD (Adress1+1),HL
        LD (Adress+1),HL
        LD HL,(NXSTRNG)
        CALL String
        LD (NXSTRNG),HL
        JR noafa

UpAni
        LD HL,ANIGFXBUFF
        LD DE,ANIGFXBUFF
UpA2    LD A,(HL)
        INC HL
        OR (HL)
        DEC HL
        JP NZ,UpA3
        LDI 
        LDI 
        LDI 
        LDI 
        RET 

UpA3    LD A,(HL)
        SUB 32
        LD (HL),A
        INC HL
        LD C,A
        LD A,(HL)
        JR NC,UpA1
        SUB 8
        LD (HL),A
UpA1    CP #40
        DEC HL
        JR NZ,UpA4
        LD A,C
        AND #E0
        CP #20
        JR NZ,UpA4
        LD BC,6
        ADD HL,BC
        JR UpA2

UpA4    LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        JR UpA2

DwnAni  LD HL,ANIGFXBUFF
        LD DE,ANIGFXBUFF
DwnA2   LD A,(HL)
        INC HL
        OR (HL)
        DEC HL
        JP NZ,DwnA3
        LDI 
        LDI 
        LDI 
        LDI 
        RET 

DwnA3   LD A,(HL)
        ADD A,32
        LD (HL),A
        LD C,A
        JR NC,DwnA1
        INC HL
        LD A,(HL)
        ADD A,8
        LD (HL),A
        DEC HL
        CP #58
        JR NZ,DwnA1
        LD BC,6
        ADD HL,BC
        JR DwnA2

DwnA1   LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        JR DwnA2

Rgh2    DEC HL
        DEC HL
        JR Rgh3

LEFT    LD HL,(FRSTRNG)
Rgh3    LD B,strings
Rgh4    LD E,(HL)
        INC HL
        LD D,(HL)
        DEC HL
        LD A,D
        OR E
        JR Z,$+5
        EX DE,HL
        DJNZ Rgh4
        LD (FRSTRNG),HL
        JP ST_PAGE1

RIGHT
        LD HL,(NXSTRNG)
        LD B,strings
Rgh1    INC HL
        INC HL
        LD A,(HL)
        OR A
        JR Z,Rgh2
        CALL EmulStr
        DJNZ Rgh1
        LD HL,(NXSTRNG)
        LD (FRSTRNG),HL
        JP ST_PAGE1

;VARS

FRSTRNG DW TEXT
NXSTRNG DW 0

SRC_PAROL
        CALL SRC_1
        LD HL,KEYSBUFF
        LD (KBU1+1),HL
        JP ST_PAGE

SRC_1   LD A,(KBU1+1)
        DEC A
        RET Z
        LD HL,prl_buff
SRC_2   CP (HL)
        INC HL
        LD C,(HL)
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        PUSH AF
        PUSH HL
        CALL Z,SRC_CRC
        POP HL
        POP AF
        INC (HL)
        DEC (HL)
        RET Z
        JR SRC_2

SRC_CRC LD B,A
        LD HL,(KBU1+1)
        LD A,C
        DEC HL
        DEC HL
        XOR (HL)
        DJNZ $-2
        RET NZ
        EX DE,HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        LD (SRCJP+1),HL
        PUSH HL
        PUSH BC
        CALL DEXOR
SRCJP   LD HL,0
        LD A,(HL)
        CP id
        PUSH AF
        CALL Z,jhl
        POP AF
        POP BC
        POP HL
        RET Z
DEXOR   LD DE,KEYSBUFF
DEXOR1  LD A,(DE)
        CP 13
        JR Z,DEXOR
        XOR (HL)
        XOR L
        XOR E
        LD (HL),A
        INC HL
        INC E
        DEC BC
        LD A,B
        OR C
        JR NZ,DEXOR1
        RET 

jhl     JP (HL)


;-------------------
prl_buff
        DB 0

;---------------------------
INIT    DI 
        XOR A
        OUT (#FE),A
        LD HL,#5AFF
        LD DE,#5AFE
        LD BC,#1B00
        LD (HL),A
        LDDR 
        LD HL,Header
        LD E,A
ouhed1  LD D,#40
ouhed2  PUSH DE
        LD BC,32
        LDIR 
        POP DE
        INC D
        LD A,D
        AND 7
        JR NZ,ouhed2
        LD A,E
        ADD A,#20
        LD E,A
        CP 24-strings*32
        JR C,ouhed1
        LD DE,#5800
        LD C,64+32
        LDIR 

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
;       EXRAM PG_Muz
;       LD HL,vie_music
;       LD DE,module
;       LD BC,v_mus_len
;       LDIR
;       CALL #C000
;       EXRAM 0
        LD A,IM2_TABLE
        LD I,A
        IM 2
        EI 
INIT1   LD BC,#0FF0
        LD HL,FNT0
        LD DE,FNT1
prpfnt1 LD A,(HL)
        AND B
        LD (DE),A
        LD A,(HL)
        AND C
        LD (HL),A
        INC DE
        INC L
        JR NZ,prpfnt1
        INC H
        LD A,H
        CP 'FNT1
        JR NZ,prpfnt1
        LD A,#C9
        LD (INIT1),A
        RET 

EXIT    DI 
        CALL #1F54
        JR NC,EXIT
;       EXRAM PG_Muz
;       CALL AY_OFF
;       EXRAM 0
        IM 1
        LD A,#3E
        LD I,A
        LD HL,#0123
        LD (#5C09),HL
        RES 3,(IY+48)
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
shwscr  OR #10
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
        EXRAM 7

m_lp1   ;EXRAM PG_Muz
        ;CALL #C005
        ;CALL SND_PLR   ;звуки
        ;CALL OUTPUT    ;вывод на AY

        LD IY,#5C3A
        CALL #38

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

;--------------------------
PAGE    LD HL,24-strings*32+#4000
        LD (Adress+1),HL
        LD (Adress1+1),HL
        LD HL,ANIGFXBUFF
        LD (HL),0
        INC L
        JR NZ,$-3
        LD HL,(FRSTRNG)
        LD B,strings
PG1     PUSH BC
        CALL String
        POP BC
        DJNZ PG1
        LD (NXSTRNG),HL
        RET 

;DB 1,2,3,4,5,6,7 - Colors
;   8,num - двупробелы...
;   9,^InfSpr,Plus
;InfSpr: DW AdrSpr
;        DB Len
;        DB Type (Attrs Y/N)

EmulStr LD D,13
        INC HL
        LD A,D
        INC HL
EmStr1  CP (HL)
        JP C,$-2
        LD A,(HL)
        INC HL
        RET Z
        CP 8
        JP Z,EmulStr+3
        CP 9
        LD A,13
        JR NZ,EmStr1
        INC HL
        INC HL
        JR EmulStr+2

String
        INC HL ;ADDR OF PREVIOUS STRING
        INC HL
        LD A,MainColor
        LD (Color+1),A
        CALL Str1
        PUSH HL
        LD HL,(Adress+1)
Adress1 LD DE,0
        LD A,L
        SUB E
        NEG 
        ADD A,32
        CALL NZ,FlSmB
        LD HL,(Adress1+1)
        LD A,L
        ADD A,32
        LD L,A
        JR NC,$+6
        LD A,H
        ADD A,8
        LD H,A
        LD (Adress1+1),HL
        LD (Adress+1),HL
        POP HL
        RET 

Str2    POP HL
Str1    LD A,(HL)
        INC HL
        CP #0E
        JP NC,PrS1
        CP #0D
        RET Z
        CP #09
        JP Z,PutSprLine
        CP #08
        JP Z,PutSpaces
        LD (Color+1),A
        JR Str1

PrS1    LD B,A
PrS3    LD A,(HL)
        CP #0E
        JP NC,PrS2
        CP #0D
        JP Z,PrS5
        CP #09
        JP Z,PrS5
        CP #08
        JP Z,PrS5
        LD (NxtSymCol+1),A
        LD A,#AF
        LD (PrS6),A
        INC HL
        JP PrS3

PrS5    LD A," "
        JR PrS4

PrS2    INC HL
PrS4    PUSH HL
        LD DE,Str2
        PUSH DE
        LD L,A
        LD E,B
        LD D,'FNT0
        LD H,'FNT1
Adress  LD BC,0
        LD A,C
        INC A
        LD (Adress+1),A
        DUP 7
        LD A,(DE)
        OR (HL)
        LD (BC),A
        INC H
        INC D
        INC B
        EDUP 
        LD A,(DE)
        OR (HL)
        LD (BC),A
        LD A,B
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
        LD L,C
Color   LD (HL),0
PrS6    RET 

NxtSymCol
        LD A,0
        LD (Color+1),A
        LD A,#C9
        LD (PrS6),A
        RET 

PutSprLine
        XOR A
        LD (PSL6+1),A
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        PUSH HL
        LD HL,ANIGFXBUFF
PSLAGB1 LD A,(HL)
        INC L
        OR (HL)
        JR Z,PSLAGB2
        LD A,L
        ADD A,5
        LD L,A
        JR PSLAGB1

PSLAGB2 DEC L
        LD (PSLAGB3+2),HL
        INC L
        INC L
        LD (HL),E
        INC L
        LD (HL),D
        INC L
        LD (HL),C
        INC L
        LD (HL),B
        INC L
        LD (HL),A
        INC L
        LD (HL),A
        INC L
        LD (HL),A
        INC L
        LD (HL),A
        EX DE,HL
PSL4Ani LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL

        PUSH BC
        LD A,D
        RLCA 
        RLCA 
        AND 3
        LD C,PGGfx0
        JR Z,slpG1
        DEC A
        LD C,PGGfx1
        JR Z,slpG1
        DEC A
        LD C,PGGfx2
        JR Z,slpG1
        LD C,PGGfx3
slpG1   LD A,C
        CALL exram
        POP BC

        SET 7,D
        SET 6,D

        LD A,(HL) ;64-(LEN*2)
        INC HL
        LD (PSL5+1),A
        LD (PSL7+1),A
        NEG 
        ADD A,32
        ADD A,A
        LD (PSL2+1),A
        LD A,(HL)
        LD (PSL4+1),A
        EX DE,HL
        ADD HL,BC
        LD DE,(Adress+1)
PSLAGB3 LD (0),DE
        PUSH DE
        LD A,8
PSL1    PUSH DE
PSL2    JR $
        DUP 32
        LDI 
        EDUP 
        POP DE
        INC D
        DEC A
        JR NZ,PSL1
        EX DE,HL
        POP HL
PSL7    LD A,0
        LD B,A
        ADD A,L
        LD (Adress+1),A
        LD A,H
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
PSL4    LD A,0
        OR A
        JR Z,PSL5
        LD (HL),A
        INC HL
        DJNZ $-2
        JR PSL61

PSL5    LD BC,0
        EX DE,HL
        LDIR 
PSL61   EXRAM PGTxt
PSL6    POP HL
        NOP 
        LD A,#C9
        LD (PSL6+1),A
        JP Str1

PutSpaces
        LD A,(HL)
        INC HL
        CALL FlSmB
        JP Str1

FlSmB   PUSH HL
        LD C,A
        NEG 
        ADD A,32
        ADD A,A
        LD (PSs1+1),A
        LD HL,(Adress+1)
        LD A,L
        ADD A,C
        LD (Adress+1),A
        LD B,8
        LD E,L
        XOR A
PSs1    JR $
        DUP 32
        LD (HL),A
        INC L
        EDUP 
        LD L,E
        INC H
        DJNZ PSs1
        LD A,H
        DEC A
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
        LD B,C
        LD (HL),0
        INC L
        DJNZ $-3
        POP HL
        RET 

;-------------------------
;-------------------------)
SCRLIN  PUSH HL
        PUSH DE
        PUSH BC
        LD A,8
SCSLOP1 PUSH HL
        PUSH DE
        DUP 32
        LDI 
        EDUP 
        POP DE
        POP HL
        INC H
        INC D
        DEC A
        JP NZ,SCSLOP1
        DEC H
        DEC D
        LD A,H
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
        LD A,D
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD D,A
        DUP 32
        LDI 
        EDUP 
        POP BC
        POP DE
        POP HL
        RET 

        ;INCLUDE "ViewGFX",#82

        DISPLAY "BEGIN TEXT: ",$

        _stradr=0
TEXT

        MACRO MDOT
DT 13
DT 8,24 ;25
DB 7," [",1,"многоточие",7,"]",13
DT 13
        ENDM 

DT 13
DT 7," Шаг...",13
DT 7," Второй...",13
DT 7," Третий...",13
MDOT
DT " Мелкая пыль секунд на ботинках...",13
DT " Тонкая стрелка пробежала круг и начала второй...",13
MDOT
DT 7," Еще один год сверху.",13
     ;112233445566778899001122334455
DT 7," Нет, не  очередной  день рожд"
DB "ения.  Он был давно.  Просто, как",13
DT 7," факт, - очередное повзросление,"
DB " возмужание и постарение.",13
DT 7," Очередной шаг.",13
DT 7," Шаг влево, шаг вправо. Везде"
DB " успеем.",13
DT 7," Везде были, везде будем.",13
DT 7," Кругом наши следы.",13
DT 7," Шаг   назад  -  оглянуться   и"
DB "   снова   загрустить   по  мимо",13
DT 7," промчавшимся дням. Дням,  когда"
DB "  все  было просто и интересно.",13
DT 7," Когда каждый день придумывалось новое.",13
DT 7," Новое было стимулом жить.",13
DT 7," Новое было стимулом творить.",13
DT 7," Знать, уметь, искать и находить.",13
MDOT
DT " Новое умерло.",13
DT " Ну, может быть, и не умерло...",13
DT " Но потеряло всякую ценность. Для нас.",13
DT " Для  меня.  Для  каждого,   кто"
DB " познал новое.  Не принимал его",13
DT " как  есть, а именно   познал. Е"
DB "л  его ложками, до сытой икоты.",13
DT " Запивал им. Каждый день начинал"
DB " с нового и заканчивал новым.",13
MDOT
DT 7," Апатия.",13
DT 7," Медленно, с  темнотой в руках"
DB "  и пустотой в голове  подкралось",13
DT 7," это слово.",13
DT 7," Апатия.",13
DT 7," Не депрессия. Это мы уже прошли.",13
DT 7," Мимо прошли.",13
DT 7," Пробежали  в ужасе.  В  стра"
DB "хе,  что  депрессия  поймает  нас.",13
DT 7," Заточит  в   свою  золотую  кл"
DB "етку.   Клетку  лени  и  плохого",13
DT 7," настроения. Клетку отвращения к"
DB "о всему. Мы были в этой клетке.",13
DT 7," Мы зубами грызли золото.  И про"
DB "грызли. Оставив после себя лишь",13
DT 7," следы зубов на ткани реальности.",13
DT 7," Апатия.",13
DT 7," Если  часто  повторять  слово"
DB ",  думать о нем,  о его значении,",13
DT 7," можно потерять всю соль слова, "
DB "его смысл и жизнь.",13
DT 7," Апатия.",13
DT 7," Апатия с корнем вросла в мой мозг.",13
DT 7," Она опутала меня. Опутала нас.",13
DT 7," Раскинулась  океаном  вокруг"
DB "  нас,   превращая  все  вокруг  в",13
DT 7," черную воду равнодушия.  Наши д"
DB "уши стали равны. Равны нулю. Мы",13
DT 7," утеряли что-то важное.",13
DT 7," Жизнь.",13
MDOT
DT " И потому я пошел другим путем.",13
DT " Шаг...",13
DT " Второй...",13
DT " Третий...",13
MDOT
DT 7," Я уснул.",13
DT 7," Я пожелал оказаться  там, "
DB "откуда  нет выхода. Я оказался.",13
DT 7," Где - не знаю...",13
DT 7," Но выход, по-моему, есть всегда.",13
DT 7," Я заснул.",13
DT 7," Я хотел спать долго. Очень долго.",13
DT 7," Больше, чем длится моя жизнь.",13
DT 7," Вечно.",13
DT 7," Я заснул.",13
DT 7," Апатия.",13
DT 7," Я заснул.",13
DT 7," Апатия.",13
DT 7," Я за...",13
MDOT
DT " Другой мир. Не страшный, просто другой.",13
DT " Жадный.  Живой и красочный.  Д"
DB "аже  местами смешной  и нелепый.",13
DT " Он стал моей жизнью.",13
DT " Я, может быть, и сплю...",13
DT " Апатия.",13
DT " Апатия...",13
DT " А апатия куда-то ушла.",13
DT " Медленно  побрела  прочь  от"
DB "  нехорошего   меня,  променявшего",13
DT " апатию на сон. Ушла и скрылась за поворотом.",13
DT " Бросила мне  на  прощание перч"
DB "атку  в лицо  и знание - что это",13
DT " сон.",13
DT " Ушла.",13
MDOT
DT 7," Шаг...",13
DT 7," Второй...",13
DT 7," Третий...",13
MDOT
DT " ...",13
MDOT
DT 7," Четвертый...",13
DT 7," Пятый...",13
DT 7," Я считаю...",13
MDOT
DT " Мне безразлично все...",13
DT " Я считаю...",13
MDOT
DT " Апатия...",13
DT " Сон...",13
MDOT
DT 7," Летаргический сон...",13
DT 7," Апатичный сон...",13
DT 7," Lethargy: the apathetic dream...",13
DT 13
DT 8,24 ;25
DB 7," [",1,"многоточие",7,"]",13

DT
DB 0
DW 0


        DISPLAY "END OF TEXT: ",$

        IFN ?SAVEOBJ-2
        IF ?std-1
std     PUSH AF
        LD A,9
        OUT (0),A
        POP AF
        JP #66
        ENDIF 
        ENDIF 

        EFFFF=$

        IF ?SAVEOBJ-2
        SAVEOBJ "infa01",#C000,Egfx0-#C000,PGGfx0
        SAVEOBJ "infa03",#C000,Egfx1-#C000,PGGfx1
        SAVEOBJ "infa07",FNT0,EFFFF-FNT0,PGTxt
        ENDIF 

        ORG #F000
JP_BEFORE_SAVE
        LD HL,PASSBUFF
JBS1    LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,D
        OR E
        JR Z,noxormore
        LD C,(HL)
        INC HL
        LD B,0
        PUSH DE
        LD DE,KEYSBUFF
        LDIR 
        LD A,13
        LD (DE),A
        EX (SP),HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        CALL DEXOR
        POP HL
        JR JBS1

noxormore
        LD HL,KEYSBUFF
        LD DE,KEYSBUFF+1
        LD BC,255
        LD (HL),L
        LDIR 

        IF ?SAVEOBJ-2
        JP _SAVER
        ELSE 
        JP Start
        ENDIF 

;       ORG Start

