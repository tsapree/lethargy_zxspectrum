; Графический движок. Вывод уровней, анимация энкаунтеров,
; сист проц упр, вывода и проч.

        MAIN "",#C0

        ORG #8000
INTBUF  DS 257,#81

        ORG #8181
INT     DI 
        ;LD (),SP
        ;LD SP,
        PUSH HL
        PUSH DE
        PUSH BC
        PUSH AF
        EX AF,AF'
        EXX 
        PUSH HL
        PUSH DE
        PUSH BC
        PUSH AF
        PUSH IX
        PUSH IY
        LD A,(page)
        PUSH AF
        LD HL,intcntr+1
        INC (HL)
i_game  LD HL,gameinterrupts
i_plmuz LD HL,playmusic
i_plsnd LD HL,playsounds
        POP AF
        CALL ONPAGE
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
        EI 
        RET 

gameinterrupts
;не демо!!!
        CALL ONPAGE_main
        CALL viz_dig    ;!!! слишком часто!
wspflg1 LD A,0
        OR A
        CALL NZ,wspsr1 ;возникновение предмета в инвентаре.
virflg1 LD A,1
        DEC A
        CALL NZ,viz_runes_1
        RET 

playmusic
        CALL ONPAGE_mus
        JP PLAY

playsounds
        CALL ONPAGE_mus
        JP OUTSOUNDS

        VER_EDGE INT

        ORG #8200 ;#00!
OUTPROCS40

ONoSpr  POP HL          ;10
        POP HL          ;10
        RET             ;10 =30 t

OOutSpr
        LD HL,OCleSpr   ;10
        PUSH HL         ;11
        POP HL          ;10
OOOSPR  POP HL          ;10
        POP DE          ;10
OOSa1   LD (OOS1+1),SP  ;20
        LD SP,HL        ;6   /77

        EX DE,HL        ;4
        LD C,H          ;4
OOSG    LD H,#40        ;7   /15

        POP DE          ;10
        LD (HL),E       ;7
        INC H           ;4
        LD (HL),D       ;7
        INC H           ;4   /32

        POP DE          ;10
        LD (HL),E       ;7
        INC H           ;4
        LD (HL),D       ;7
        INC H           ;4   /32

        POP DE          ;10
        LD (HL),E       ;7
        INC H           ;4
        LD (HL),D       ;7
        INC H           ;4   /32

        POP DE          ;10
        LD (HL),E       ;7
        INC H           ;4
        LD (HL),D       ;7   /28

OOSA1   LD H,#58        ;7
        LD (HL),C       ;7   /14

OOS1    LD SP,0         ;10
        RET             ;10  /20  =250

OCleSpr LD DE,ONoSpr    ;10
        PUSH DE         ;11
        POP DE          ;10
        POP HL          ;10
        POP HL          ;10
OOSA2   LD H,#58        ;7
        LD (HL),E       ;7
        RET             ;10 =75 t

OLVDATA POP HL          ;10
        POP HL          ;10
        RET             ;10 =30 t
EOSPR

OStart  DI 
        LD (OEnd+1),SP
OOOSt   LD SP,TBL_OMS   ;адрес в таблице, с которого необходимо
        IF ?Border
        LD A,3          ;выводить (можно пропустить несколько
        OUT (#FE),A     ;первых строк)
        ENDIF 
        RET 

OEnd    LD SP,0
        IF ?Border
        XOR A
        OUT (#FE),A
        ENDIF 
        LD HL,OR_SPRS_BUFF
        LD (OR_BUFF_ADR),HL
        LD HL,herosprbuff
        LD (HHMadr+1),HL
        RET 

;Формирование буфера для расчета координат в таблице:
;0-127 - адреса строк экрана, самая верхняя выводимая смещена
;        на NULL_Y_CELL строк вниз, не придется беспокоиться о
;        вылезающих спрайтах
;128-255 - смещения от начала строки, самое левое знакоместо
;        смещено на NULL_X_CELL знакомест вправо для более
;        простого отслеживания вылезающих спрайтов

InitOSp

        LD HL,XYTABLE
        XOR A

        LD (HL),A
        INC L
        JR NZ,$-2

        LD L,NULL_Y_CELL+19+16*2
        LD A,3
        LD BC,6*6
        LD DE,TBL_SCOMS

        LD (HL),E
        INC L
        LD (HL),D
        INC L
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        DEC A
        JR NZ,$-8

        LD L,NULL_Y_CELL*2
        LD A,24-HEAD_STRS
        LD C,6*32
        ;LD DE,TBL_OMS

        LD (HL),E
        INC L
        LD (HL),D
        INC L
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        DEC A
        JR NZ,$-8

        LD L,NULL_X_CELL+#80
        LD B,32
        LD (HL),A
        INC HL
        ADD A,6
        DJNZ $-4

;заполнение таблицы вывода необходимой инфой: адресом процы-
;затычки, адресом спрайта (пропускаю), смещением знакоместа
;относительно начала трети (0-255) и атрибутами (пропускаю)

        LD HL,TBL_SCOMS
        LD DE,ONoSpr ;+.OLVDATA

        LD A,#21
        EX AF,AF'
        LD A,3
IniOS3  LD B,6
        EX AF,AF'
IniOS2  LD (HL),E               ;заполнено графикой уровня
        INC HL
        LD (HL),D
        INC HL
        INC HL
        INC HL
        LD (HL),A
        INC HL
        INC HL
        INC A
        DJNZ IniOS2
        ADD A,32-6
        EX AF,AF'
        DEC A
        JR NZ,IniOS3

        LD B,3
        LD C,HEAD_STRS*32
IniOS1  LD (HL),E               ;заполнено графикой уровня
        INC HL
        LD (HL),D
        INC HL
        INC HL
        INC HL
        LD (HL),C
        INC HL
        INC HL
        INC C
        JR NZ,IniOS1
        INC D
        DJNZ IniOS1
        LD (HL),.OEnd
        INC HL
        LD (HL),'OEnd

        ;иниц дерьма.
        LD HL,mirr_tbl ;тбл поворота
        LD (HL),#80
        LD A,L
        RLCA 
        RR (HL)
        JR NC,$-3
        INC L
        JR NZ,$-9
        RET 


;Test: ДО 220 вывод одновр спрайтов,
;ДО 180 движущ спрайтов (с очисткой)

        ;Тут 256*2 - размноженная проца вывода спрайтов (на
        ;каждую треть), еще 256 байт - (начало) - табла расчета
        ;адреса в таблице вывода

        ORG OUTPROCS40+#100
OUTPROCS48;
ONoSpr48;
        POP HL
        POP HL
        RET 

OOutSpr48;
        LD HL,OCleSpr48
        PUSH HL
        POP HL
        POP HL
        POP DE
        LD (OOS148+1),SP
        LD SP,HL

        EX DE,HL
        LD C,H
        LD H,#48

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D

OOSA3   LD H,#59
        LD (HL),C

OOS148  LD SP,0
        RET 

OCleSpr48;
        LD DE,ONoSpr48
        PUSH DE
        POP DE
        POP HL
        POP HL
OOSA4   LD H,#59
        LD (HL),E
        RET 

OLVDATA48;
        POP HL
        POP HL
        RET 

        ORG OUTPROCS40+#200
OUTPROCS50;
ONoSpr50;
        POP HL
        POP HL
        RET 

OOutSpr50;
        LD HL,OCleSpr50
        PUSH HL
        POP HL
        POP HL
        POP DE
        LD (OOS150+1),SP
        LD SP,HL

        EX DE,HL
        LD C,H
        LD H,#50

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D
        INC H

        POP DE
        LD (HL),E
        INC H
        LD (HL),D

OOSA5   LD H,#5A
        LD (HL),C

OOS150  LD SP,0
        RET 

OCleSpr50;
        LD DE,ONoSpr50
        PUSH DE
        POP DE
        POP HL
        POP HL
OOSA6   LD H,#5A
        LD (HL),E
        RET 

OLVDATA50;
        POP HL
        POP HL
        RET 


        ORG ONoSpr+#300

;----------------------
START_DEPACK_GAME
        XOR A
        OUT (#FE),A
        LD (EXIT+1),SP
SDG_1   CALL depack_game

START
        EXX 
        LD (EX_HL+1),HL
        CALL IM2
RESTART CALL InitOSp
        JP M_MENU

S_GAME
        CALL GMInit
        CALL ewspsr1
        INC A
        LD (virflg1+1),A
        CALL ONPAGE_fzs
        CALL select_hand

StLp2
        CALL ONPAGE_fzs

        XOR A
        LD (HERO+9),A   ;после смерти
        LD (tpyn_1+1),A
        LD (tpyn+1),A

        CALL gomode
        CALL SHOWROOM

        LD A,32         ;засунуть дальше!
        LD (NRGpls),A   ;и в несколько мест
        LD A,"S"
        LD (NRG),A

StLp1   EI 

        IF ?SlowMotion
        DISPLAY "Slow motion ON (press Z)"
        LD A,#FE
        IN A,(#FE)
        RRCA 
        RRCA 
        LD B,1
        JR C,$+4
        LD B,40
        HALT 
        DJNZ $-1
        ELSE 
        HALT 
        ENDIF 
        XOR A
        LD (intcntr+1),A

noinvent
        LD A,0
        SUB #C3
        CCF 

        CALL NC,W4Enter ;Если ентер - надо выбирать предмет
        CALL NC,SelItem

tpyn    LD A,0
        OR A
        JR Z,tpyna_HET
tpyn_1  LD A,0
        OR A
        JR Z,tpyn_ECTb
        JP DIIIE

tpyna_HET

        LD IX,NRG-"T"
        LD HL,NRGpls
        LD C,(HL) ;взятие смещения энергии.
        LD A,C
        CP 127
        JR NC,$+4
        ADD A,7
        LD B,A
        SRA B
        SRA B
        SRA B
        LD A,C
        SUB B
        LD (HL),A
        INC HL
        SUB C
        SUB (IX+"T")
        NEG 
        CP (HL)
        JR C,$+3
        LD A,(HL)
        LD (IX+"T"),A
        INC HL
        SUB (HL)
        JR NC,$+3
        XOR A

        CALL Z,death    ;пока - так, потом - посмотрим

        CALL ini_nrgline
tpyn_ECTb
        CALL ONPAGE_gfx
        CALL outnrg
        CALL SHWSPZ

Exit2FiCut
        CALL QAOPSP
        CALL VerFir     ;в этой переменной одиночный файр
                     ;(опросил - декрементировал - жду)
        JP StLp1

EXITCS  DI 
        CALL ClrScrA
EXIT    LD SP,0
IM1     DI 
        LD A,#3F
        LD I,A
        IM 1
        EI 
EX_HL   LD HL,0
        EXX 
        LD IY,#5C3A
        RET 

IM2     DI 
        LD A,'INTBUF
        LD I,A
        IM 2
        RET 

SHWSPZ
        CALL SHWSPZ1

        EI 
intcntr LD A,0
        OR A
        JR NZ,$+3
        HALT 
        HALT 
        CALL OStart
        EI 
        CALL VerCngRoom
        CALL Colors
        RET 

SHWSPZ1 LD IX,0
        CALL ONPAGE_fzs

        LD A,.OOutSpr
        LD (OOOPRC+1),A
        LD IY,HERO
        CALL MONOUT
        LD IY,FLYBUFF
        CALL OBJOUT
        LD IY,HEROBUFF
        CALL MONOUT
        LD IY,FIREBUFF
        CALL OBJOUT
        LD IY,FLSBUFF
        CALL FLSOUT
        LD IY,RUNEBUFF
        CALL RUNEOUT

        LD A,.OOOSPR
        LD (OOOPRC+1),A
        LD A,6
        LD (OOOXb+1),A
        LD IY,ALIFEBUFF
        CALL OBJOUT
        LD A,.OOutSpr
        LD (OOOPRC+1),A
        LD A,#20
        LD (OOOXb+1),A

        CALL ONPAGE_main

        LD IY,#5C3A
        RET 

Colors  ;надо вместо A,(adr) сделать A,(HL)
        LD A,0
        INC A
        AND 1
        LD ($-4),A
        JR NZ,$+10
        LD A,(RuneClr)
        XOR 6!3
        LD (RuneClr),A
        LD A,(RichClr)
        XOR #47!#45
        LD (RichClr),A
        LD A,(MoneyClr)
        XOR #40
        LD (MoneyClr),A
        LD A,(BowClr)
        INC A
        AND 7
        LD (BowClr),A
        CALL RND_A
        AND 3
        ADD A,3
        LD (KeyClr),A
        LD A,(FBL_clr)
        LD (FBL_clr1),A
        XOR 4
        LD (FBL_clr),A
        RET 

;если #FF - конец, #FE - 'мертвый' элм

HERO    setcrds #09,#A,StandRight1,0
        DB #FF

ALIFEBUFF       DS 8+1,#FF

HEROBUFF

;---
MONSTRS         DS MaxMonstrs*10+1
FIREBUFF        DS MaxFires*8+1
FLYBUFF         DS MaxFlyers*8+1
RUNEBUFF        DS MaxRunes*8+1
FLSBUFF         DS MaxFlashes*4
E_MBUFFS
;---------------------

VerCngRoom
NoRoomChange LD A,0
        OR A
        RET NZ

        LD HL,(HERO)
        LD DE,(ROOMCRDSXY)
        LD BC,(ROOMCRDSSXSY)
        LD A,H
        SUB D
        SUB #10
        JR C,ToRoomL
        SUB B
        JR NC,ToRoomR
        LD A,L
        SUB E
        SUB #11
        JR C,ToRoomU
        SUB C
        RET C

ToRoomD LD A,(ROOMCRDSY)
        SUB L
        NEG 
        LD L,A
        INC L
        LD A,(ROOM_EXIT_DWN+1)
        SUB H
        NEG 
        LD H,A
        LD A,(ROOM_EXIT_DWN)
        JR TRoR2

ToRoomU LD BC,#00FF
        LD A,(ROOM_EXIT_UP+1)
        SUB H
        NEG 
        LD H,A
        DEC L
        LD A,(ROOM_EXIT_UP)
        JR TRoR1

ToRoomL LD BC,#FF00
        LD A,(ROOM_EXIT_LFT+1)
        SUB L
        NEG 
        LD L,A
        LD A,(ROOM_EXIT_LFT)
        JR TRoR1

ToRoomR LD A,(ROOMCRDSX)
        SUB H
        NEG 
        LD H,A
        LD A,(ROOM_EXIT_RGT+1)
        SUB L
        NEG 
        LD L,A
        LD A,(ROOM_EXIT_RGT)
TRoR2   LD BC,0
TRoR1   LD (ROOM),A             ;!!!
        OR A
        LD DE,(ROOMCRDSXY)
        SBC HL,DE
        LD (HRRC1+1),HL
        LD (HRRC2+1),BC
        LD HL,HRRCrd
        LD (SetCrdHero+1),HL
        JP SHOWROOMPLACE

HRRCrd
HRRC1   LD DE,0
HRRC2   LD BC,0
        LD HL,(ROOMCRDSXY)
        ADD HL,DE
        LD DE,(ROOMCRDSSXSY)
        LD A,D
        AND B
        ADD A,H
        LD H,A
        LD A,E
        AND C
        ADD A,L
        LD L,A
        LD (HERO),HL
        RET 

HeroCrds
        RET 


;-----------------------
;перейти в комнату, запомнив координаты восстановления
SHOWROOMPLACE
        LD HL,place_buff
        LD DE,place_reinc
        LD BC,4
        LDIR 

SHOWROOM
        LD HL,SHOWMMROOM
        CALL Remember_Coords

        XOR A
        LD (flybfycur),A
        LD (NoRoomChange+1),A
        LD A,#18
        LD (W4Enter),A

        CALL ONPAGE_main

        CALL viz_runes
        CALL viz_invent

SHROM2  LD HL,WALKONBUFF
        LD DE,WALKONBUFF+1
        LD BC,0+WLKHGT*WLKLEN-1
        LD (HL),#FF
        LDIR 

        LD A,(ROOM)
        LD E,A
        LD HL,megatbl
        LD BC,5
srcmg1  LD A,(HL)
        OR A
        JR Z,srcmg2
        CP E
        JR Z,srcmg2
        ADD HL,BC
        INC A
        JR NZ,srcmg1
        JR srcmge

srcmg2  CALL ONPAGE_agfx
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        EX DE,HL
        LD DE,GGFX
srcmgNO LDIR 

srcmge  LD A,(LVL_pg)
        CALL ONPAGE

        LD A,(ROOM)
        CALL FndRoom

        PUSH HL
        LD DE,ROOMCRDSXY
        LD BC,4
        LDIR 

        PUSH HL
        PUSH DE
        PUSH BC
        CALL fillATR
        CALL atrs2scr

        CALL ONPAGE_gfx
        CALL drawborders

        LD A,(LVL_pg)
        CALL ONPAGE

        POP BC
        POP DE
        POP HL

        CALL VizRoom

        POP HL
        LD A,(HL)
        ADD A,HEAD_STRS
        LD E,A
        INC HL

        LD D,(HL)
        INC HL
        PUSH HL
        CALL A2SA
        LD (FMSH1+1),HL
        LD (FMSH2+1),HL
        POP HL
        LD A,(HL)
        INC HL
        EXX 
        LD C,A
        EXX 
        LD A,(HL)
        INC HL
        EXX 
        LD D,A
        LD B,A
        PUSH BC
        EXX 
        POP BC
        PUSH BC
        PUSH HL

FMS1    POP HL
        LD A,(HL)
        INC HL
        OR A
        JR Z,FMEpty1
        PUSH HL
        DEC A
        JP Z,FMS3 ;Empty2
        LD L,A
        LD H,0
        LD E,A
        LD D,H
        ADD HL,HL
        ADD HL,DE
        LD DE,Land_Sprites_Table
        ADD HL,DE
        CALL ONPAGE_gfx
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,(HL)
        INC HL
        CP #11
        JR Z,FMSH1
        LD B,A
        AND #0F
        LD C,A
        LD A,B
        RRCA 
        RRCA 
        RRCA 
        RRCA 
        AND #0F
        LD B,A
        LD HL,(FMSH1+1)
        PUSH BC
        CALL FMSl1
        LD HL,(FMSH1+1)
        CALL scratrZ
        POP BC
FMSl2   PUSH BC
        LD C,L
FMSl21  LD A,(DE)
        LD (HL),A
        OR A
        CALL NZ,SetNoViz
        INC L
        INC DE
        DJNZ FMSl21
        LD L,C
        LD BC,32
        ADD HL,BC
        POP BC
        DEC C
        JR NZ,FMSl2
        JR FMS3

outspr
FMSl1   PUSH BC
        LD C,L
        LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4
        LD L,C
        POP BC
        INC H
        LD A,H
        AND 7
        JR NZ,FMSl1
        CALL dwnhl1
        DEC C
        JR NZ,FMSl1
        RET 

outatr  PUSH BC
        LD C,L
        LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4
        LD A,C
        ADD A,32
        LD L,A
        POP BC
        DEC C
        JR NZ,outatr
        RET 

FMEpty1 LD B,(HL)
        INC HL
        PUSH HL
        CALL FMnxtx
        DJNZ $-3
        JR FMS4

FMSH1   LD HL,0
        LD B,8
        LD A,(DE)
        LD (HL),A
        INC H
        INC DE
        DJNZ $-4

        DEC H
        CALL scratrZ
        LD A,(DE)
        LD (HL),A
        CALL SetNoViz

FMS3    LD A,(LVL_pg)
        CALL ONPAGE
        CALL FMnxtx
FMS4    JP NZ,FMS1
        POP DE
        POP BC

        CALL depack_walkable
        PUSH DE

        LD DE,WLKLERI*256+WLKUP
        CALL xywlkbuff

pwa2b1  PUSH BC
        PUSH HL
        LD A,(DE)
        LD (HL),A
        INC HL
        INC DE
        DJNZ $-4
        POP HL
        LD BC,WLKLEN
        ADD HL,BC
        POP BC
        DEC C
        JR NZ,pwa2b1
        POP DE

        ;зап выхов из комн:
        LD HL,ROOM_EXIT_LFT
        LD B,4
REL1    LD A,(DE)
        LD (HL),A
        INC HL
        INC DE
        INC A
        JR Z,$+5
        LD A,(DE)
        INC DE
        LD (HL),A
        INC HL
        DJNZ REL1
        PUSH DE
        CALL dpcklft
        CALL dpckrgt
        CALL dpckdwn
        CALL dpckup

SetCrdHero
        CALL HeroCrds
        LD IY,HERO
        CALL WlkAdr

        CALL cleMONSTRS

        CALL ONPAGE_fzs
        LD HL,MONSTRS
        LD (mnstbfy+2),HL
        LD HL,FIREBUFF
        LD (firebfy+2),HL
        LD HL,RUNEBUFF
        LD (runebfy+2),HL
        LD A,(LVL_pg)
        CALL ONPAGE
        POP HL
        CALL OE2b

        LD A,'ATRS_BUFF
        CALL cho2b
        CALL SHWSPZ1
        CALL OStart
        EI 
        LD A,#58
        CALL cho2b
        CALL atrs2scr
        JP ONPAGE_main

cho2b   LD (OOSA1+1),A
        LD (OOSA2+1),A
        INC A
        LD (OOSA3+1),A
        LD (OOSA4+1),A
        INC A
        LD (OOSA5+1),A
        LD (OOSA6+1),A
        RET 

atrs2scr
        LD HL,ATRS_BUFF+HEAD_CELLS
        LD DE,#5800+HEAD_CELLS
        LD BC,OUT_CELLS
        LDIR 
        RET 

cleMONSTRS
        LD HL,MONSTRS
        LD DE,MONSTRS+1
        LD BC,E_MBUFFS-MONSTRS-1
        LD (HL),#FF
        LDIR 
        RET 

;постановка одушевленных и неодушевленных энкантеров

OE2b    LD C,(HL)
        INC HL
        INC C
        RET Z
        DEC C
        LD B,(HL)
        INC HL  ;BC=xy
        LD E,(HL)
        INC HL
        LD D,0
        LD A,(HL)
        INC HL
        EX AF,AF'
        PUSH HL
        CALL ONPAGE_fzs
        LD HL,ENC_TABLE
        LD A,E
        ADD HL,DE
        ADD HL,DE
        LD E,(HL)
        INC HL
        LD D,(HL)
        EX DE,HL
        EX AF,AF'
        LD E,A
        LD D,0
        LD (nmbrmnst),A
        EX AF,AF'
        ;HL=proca
        ;A'=number or options
        ;A=number in enc_table
        ;BC=xy
        LD (typemnst),A
        CALL JHL
        POP HL
        LD A,(LVL_pg)
        CALL ONPAGE
        JR OE2b

JHL     JP (HL)

fillATR
        LD HL,(ROOMCRDSXY)
        LD DE,(ROOMCRDSSXSY)
        LD A,D
        LD (rpATR0+1),A
        SUB 33
        NEG 
        LD (rpATR1+1),A
        LD A,E
        LD (rpATR4+1),A
        LD A,H
        PUSH HL
        LD H,0
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD A,L
        LD L,A
        DEC HL
        LD (rpATR6+1),HL
        POP HL
        LD A,24-HEAD_STRS
        SUB L
        SUB E
        LD L,A
        LD A,32
        SUB H
        SUB D
        LD H,0
        LD D,H
        LD E,A
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,DE
        LD B,H
        LD C,L

        LD HL,ATRS_BUFF+OUT_CELLS+HEAD_CELLS-1
MMatr   LD DE,#0100
        CALL rpATRl
rpATR4  LD C,0
        JR rpATR0
rpATR1  LD B,0
        JR rpATR3
rpATR2  LD (HL),D
        DEC HL
rpATR3  DJNZ $-2
rpATR0  LD B,0
        LD (HL),E
        DEC HL
        DJNZ $-2
        DEC C
        JR NZ,rpATR1
rpATR6  LD BC,0
rpATRl  LD A,B
        OR C
        RET Z
        INC BC
        LD A,B
        OR C
        RET Z
        DEC BC
        LD (HL),D
        PUSH DE
        LD D,H
        LD E,L
        DEC DE
        LDDR 
        POP DE
        RET 

FndRoom ADD A,A
        LD HL,Rooms
        LD E,A
        LD D,0
        ADD HL,DE
        LD E,(HL)
        INC HL
        LD D,(HL)
        EX DE,HL
        RET 

;DE=смещение
xywlkbuff
        LD HL,(ROOMCRDSXY)
        ADD HL,DE

        IFN 36-WLKLEN
        DISPLAY "ошибка: умножение на 36!"
        ENDM 
        ENDIF 

        LD A,L
        ADD A,A
        ADD A,A
        ADD A,A
        ADD A,L ;*9
        LD L,A
        LD E,H
        LD H,0
        LD D,H
        ADD HL,HL
        ADD HL,HL
        ADD HL,DE
        LD DE,WALKONBUFF
        ADD HL,DE
        LD DE,WALKSERVBUFF
        RET 

dpcklft
        LD BC,(ROOM_EXIT_LFT)
        PUSH BC
        CALL skproom
        LD DE,0*256+WLKUP
        LD A,#FE ;CP
        JR tstdp1

dpckrgt
        LD BC,(ROOM_EXIT_RGT)
        PUSH BC
        ;C=numroom
        ;B=offset
        CALL skproom
        LD A,(ROOMCRDSX)
        INC A
        INC A
        LD D,A
        LD E,WLKUP
        LD A,#18 ;JR

tstdp1  LD (tstdpC),A
        LD A,B
        LD (pwlh21+1),A
        DEC A
        LD (pwlh2+1),A
        CALL xywlkbuff
        LD A,B;(ROOMCRDSX)
tstdpC  JR $+9
        SUB WLKLERI ;2
        ADD A,E
        LD E,A
        ADC A,D
        SUB E
        LD D,A
        LD A,(ROOMCRDSY)
        LD B,A
        POP AF
pwlh3   OR A
        JR Z,pwlh1
        ;C-hgt new room
        ;B-hgt cur room
        JP M,pwlh4
        PUSH DE
        LD DE,WLKLEN
        ADD HL,DE
        POP DE
        DEC A
        DJNZ pwlh3
        RET 

pwlh4   INC A
        PUSH HL
pwlh21  LD HL,32
        ADD HL,DE
        POP DE
        EX DE,HL
        DEC C
        JR NZ,pwlh3
        RET 

pwlh1   LD A,(DE)
        AND #FE
        LD (HL),A
        INC DE
        INC HL
        LD A,(DE)
        AND #FE
        LD (HL),A
        PUSH DE
        LD DE,35
        ADD HL,DE
        EX (SP),HL
pwlh2   LD E,31
        ADD HL,DE
        POP DE
        EX DE,HL
        ;BC=cycles
        DEC C
        JR Z,$+4
        DJNZ pwlh1
        RET 

dpckup  LD BC,(ROOM_EXIT_UP)
        PUSH BC
        CALL skproom
        LD DE,WLKLERI*256 ;#0200
        LD A,B
        LD (pwlv2+1),A
        LD (pwlv21+1),A
        CALL xywlkbuff
        LD A,C
        SUB WLKUP+1; +1 т.к. внахлест на одно знакоместо;2
        PUSH HL
        EX DE,HL
pwlv21  LD DE,0
        ADD HL,DE
        DEC A
        JR NZ,$-2
        EX DE,HL
        POP HL
        LD A,WLKUP
        JR dpckd1

dpckdwn
        LD BC,(ROOM_EXIT_DWN)
        PUSH BC
        CALL skproom
        LD A,(ROOMCRDSY)
        ADD A,WLKUP
        LD E,A
        LD D,WLKLERI

        LD A,B
        LD (pwlv2+1),A
        LD (pwlv2d+1),A
        CALL xywlkbuff
        PUSH HL
pwlv2d  LD HL,0
        ADD HL,DE
        EX DE,HL
        POP HL

        LD A,WLKDWN

dpckd1  LD (pwlvl2+1),A
        LD A,(ROOMCRDSX)
        LD C,A
        POP AF
pwlv31  OR A
        ;B-len new room
        ;C-len cur room
        JP M,pwlv4
pwlv3   JR Z,pwlv1
        INC HL
        DEC A
        DEC C
        JR NZ,pwlv31
        RET 

pwlv4   INC A
        INC DE
        DJNZ pwlv31
        RET 

pwlv1   PUSH BC
        PUSH HL
        PUSH DE
pwlvl2  LD B,2
pwlvl1  PUSH BC
        LD A,(DE)
        LD (HL),A
        LD BC,WLKLEN
        ADD HL,BC
        EX DE,HL
pwlv2   LD C,0
        ADD HL,BC
        EX DE,HL
        POP BC
        DJNZ pwlvl1
        POP DE
        POP HL
        POP BC
        INC HL
        INC DE
        DEC C
        RET Z
        DJNZ pwlv1
        RET 

;---
;>C=Room
;<DE=walk_packdata
;BC=SXSY
skproom
        LD A,C
        INC C
        JR NZ,$+5
        POP HL
        POP HL
        RET 

        CALL FndRoom
        INC HL
        INC HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        LD E,0
        PUSH BC
skprom4 PUSH BC
skprom1 INC E
        DEC E
        JR NZ,skprom3
        LD A,(HL)
        INC HL
        OR A
        JR NZ,skprom2
        LD E,(HL)
        INC HL
skprom3 DEC E
skprom2 DJNZ skprom1
        POP BC
        DEC C
        JR NZ,skprom4
        POP BC

        EX DE,HL
;на выходе: DE=адрес walk_packdata
;           BC=SXSY

;
; Распаковка проходимости
;
; DE=walk_packdata
; BC=SXSY
;
depack_walkable
        PUSH BC
        LD A,B
        LD (wobsf3+1),A
        LD HL,WALKSERVBUFF
        XOR A
        JR wobsf5

wobsf4  LD A,(wobsf2+1)
wobsf5  CPL 
        LD (wobsf2+1),A
        LD A,(DE)
        INC DE
        INC A
wobsf1  DEC A
        JR Z,wobsf4
wobsf2  LD (HL),#FF
        INC HL
        DJNZ wobsf1
wobsf3  LD B,0
        DEC C
        JR NZ,wobsf1
        POP BC
        RET 


FMnxtx  LD HL,FMSH1+1
        INC (HL)
        EXX 
        DEC B
        JR NZ,FMS2
FMSH2   LD HL,0
        LD A,L
        ADD A,32
        LD L,A
        JR NC,$+6
        LD A,H
        ADD A,8
        LD H,A
        LD (FMSH1+1),HL
        LD (FMSH2+1),HL
        LD B,D
        DEC C
FMS2    EXX 
        RET 

SetViz  XOR A
        JR SetNoViz+2

SetNoViz
        LD A,.OLVDATA
        PUSH HL
        PUSH DE
        PUSH BC
        LD DE,-ATRS_BUFF-HEAD_CELLS
        ADD HL,DE
        LD B,H
        LD C,L
        ADD HL,HL
        ADD HL,BC
        ADD HL,HL
        LD BC,TBL_OMS
        ADD HL,BC
        LD (HL),A
        POP BC
        POP DE
        POP HL
        RET 


VizRoom
        LD DE,(ROOMCRDSXY)
        LD BC,(ROOMCRDSSXSY)

OutFlashBox
        ;DE=xy
        ;BC=sxsy

        LD HL,ATRS_BUFF+HEAD_CELLS
        PUSH BC
        INC E
OFB2    DEC E
        JR Z,OFB3
        LD B,32
        CALL OFB1
        JR OFB2

OFB3    LD B,D
        INC B
        DEC B
        CALL NZ,OFB1

        POP BC
        PUSH BC
        LD A,32
        SUB B
        SUB D
OFB4    PUSH AF
        CALL SetViz
        POP AF
        INC HL
        DJNZ OFB4
        LD B,A
        CALL NZ,OFB1
        POP BC
        DEC C
        PUSH BC
        JR NZ,OFB3
        POP BC

OFB11   LD A,H
        CP 'ATRS_BUFF+3
        RET NC
        CALL SetNoViz
        INC HL
        JR OFB11

OFB1    CALL SetNoViz
        INC HL
        DJNZ OFB1
        RET 

;---------------------------
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

scratr  LD A,H
        AND #18
        RRCA 
        RRCA 
        RRCA 
        OR #58
        LD H,A
        RET 

scratrZ LD A,H
        AND #18
        RRCA 
        RRCA 
        RRCA 
        ADD A,'ATRS_BUFF
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

        IF 1

RND_A   PUSH HL
        LD HL,12345
        LD A,H
        ADD A,#77
        LD H,A
        RLC L
        ADD A,L
        LD L,A
        LD (RND_A+2),HL
        POP HL
        RET 

        ELSE 

RND_A   PUSH HL
        LD HL,1234
        INC HL
        LD A,H
        AND #1F
        LD H,A
        LD (RND_A+2),HL
        LD A,R
        XOR (HL)
        POP HL
        RET 

        ENDIF 

CleAtr
        XOR A
        LD HL,#5AFF
        LD (HL),A
        LD DE,#5AFE
        LD BC,#2FF
        LDDR 
        RET 

;--------------------------

;RUNE   DB X,Y
;       DW tst
;       ...
;tst    DW proga        ;прога обьекта
;       DW rune1        ;адрес спрайта обьекта
;       DB RuneClr      ;цвет обьекта

RUNEOUT
        LD A,#FE
        LD (OORLD),A
        CALL RUNOUT1
        LD A,#28
        LD (OORLD),A
        RET 

RUNOUT1
        LD A,(IY)
        INC A
        RET Z
        INC A
        CALL NZ,RUNESR
        LD DE,8 ;?
        ADD IY,DE
        JP RUNOUT1

RUNESR
        LD L,(IY+2)
        LD H,(IY+3)
        LD B,1
        LD E,(HL)
        INC HL
        LD D,(HL)
        DEC HL
        LD A,E
        OR D
        JR Z,$+3
        PUSH DE         ;прогу на стек
        PUSH BC
        PUSH HL
        INC HL
        INC HL
        LD C,(IY)
        LD B,(IY+1)
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,(HL)
        INC HL
        LD H,'COLORS
        LD L,A
        LD A,(HL)
        LD (OOAtr+1),A
        EX DE,HL
        LD DE,#0202
        JP HHR3

MONOUT
        LD A,#28
        LD (OORLD),A

MONOUT1 LD A,(IY)
        INC A
        RET Z
        INC A
        CALL NZ,OBJSR
        LD DE,10
        ADD IY,DE
        JP MONOUT1

OBJOUTOR
OBJOUT
        LD A,#28
        LD (OORLD),A

OBJOUT1
        LD A,(IY)
        INC A
        RET Z
        INC A
        CALL NZ,OBJSR
        LD DE,8
        ADD IY,DE
        JP OBJOUT1

FLSOUT
        LD A,(IY)
        INC A
        RET Z
        INC A
        CALL NZ,FLSSR
        LD DE,4
        ADD IY,DE
        JP FLSOUT

OBJSR
        LD L,(IY+2)
        LD H,(IY+3)
        LD (RepFze+1),HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,E
        OR D
        JR Z,$+3
        PUSH DE         ;прогу на стек
        LD B,(HL)       ;кол-во спрайтов
        INC B
        DEC B
        INC HL
        JR Z,HHR4
HHR1    PUSH BC
        LD A,(HL)
        AND #0F
        CP 8
        JR C,$+4
        OR #F0
        ADD A,(IY)
        LD C,A

        LD A,(HL)
        INC HL
        AND #F0
        JP P,$+5
        OR #0F
        RLCA 
        RLCA 
        RLCA 
        RLCA 
        ADD A,(IY+1)
        LD B,A

        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        PUSH DE
        LD A,(HL)
        AND #0F
        LD E,A
        XOR (HL)
        INC HL
        RLCA 
        RLCA 
        RLCA 
        RLCA 
        LD D,A
        ;INC HL

        LD A,(HL)
        INC HL
        EX (SP),HL
        PUSH HL
        OR A
        JR Z,HhRA

        LD H,'COLORS
        LD L,A
        LD A,(HL)
        LD (OOAtr+1),A
        POP HL
        BIT 7,H
        JR Z,HHM1
        CALL ONPAGE_main
HHR3    PUSH DE
        PUSH BC
HHR2    PUSH BC
        PUSH DE
        PUSH HL
        LD A,B
        SUB #10
        JR C,$+7
OOOXb   CP #20
        CALL C,OnceSpr
        POP HL
        LD DE,8
        ADD HL,DE
        POP DE
        POP BC
        INC C
        DEC E
        JR NZ,HHR2
        POP BC
        POP DE
        INC B
        DEC D
        JR NZ,HHR3
HHR5    CALL ONPAGE_fzs
        POP HL
        POP BC
        DJNZ HHR1
HHR4    LD (IY+2),L
        LD (IY+3),H
        LD A,(DIRECT)
        RET 

HhRA    POP HL
        CALL ONPAGE_main
HhR3    PUSH DE
        PUSH BC
HhR2    PUSH BC
        PUSH DE
        LD A,(HL)
        INC HL
        OR A
        JR Z,HhRz
        LD (OOAtr+1),A
        PUSH HL
        LD A,B
        SUB #10
        JR C,$+7
        CP #20
        CALL C,OnceSpr
        POP HL
        LD DE,8
        ADD HL,DE
HhRz    POP DE
        POP BC
        INC C
        DEC E
        JR NZ,HhR2
        POP BC
        POP DE
        INC B
        DEC D
        JR NZ,HhR3
        JP HHR5

;спрайт перевернуть :(

HHM1    CALL ONPAGE_main

        SET 7,H
        LD A,B
        ADD A,D
        DEC A
        LD B,A

HHM3    PUSH DE
        PUSH BC
HHM2    PUSH BC
        PUSH DE
        PUSH BC
HHMadr  LD BC,herosprbuff
        PUSH BC
        LD D,'mirr_tbl
        DUP 8
        LD E,(HL)
        LD A,(DE)
        LD (BC),A
        INC HL
        INC BC
        EDUP 
        LD (HHMadr+1),BC
        POP DE
        POP BC
        PUSH HL
        EX DE,HL
        LD A,B
        SUB #10
        JR C,$+7
        CP #20
        CALL C,OnceSpr
        POP HL
        POP DE
        POP BC
        INC C
        DEC E
        JR NZ,HHM2
        POP BC
        POP DE
        DEC B
        DEC D
        JR NZ,HHM3
        JP HHR5

FLSSR
        LD L,(IY+2)
        LD H,(IY+3)
        LD (RepFze+1),HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,E
        OR D
        JR Z,$+3
        PUSH DE
        LD C,(IY)
        LD B,(IY+1)
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,(HL)
        INC HL
        PUSH HL
        EX DE,HL
        LD (OOAtr+1),A
        CALL ONPAGE_main
        LD A,B
        SUB #10
        JR C,$+7
        CP #20
        CALL C,OnceSpr
        CALL ONPAGE_fzs
        POP HL
        LD (IY+2),L
        LD (IY+3),H
        RET 

WlkAdr
        LD A,(IY)
        SUB #10
        LD L,A
        ADD A,A
        ADD A,A
        ADD A,A
        ADD A,L
        LD L,A
        LD H,0
        LD D,H
        ADD HL,HL
        ADD HL,HL
        LD A,(IY+1)
        SUB #10
        LD E,A
        ADD HL,DE
        LD DE,WALKONBUFF+(WLKLEN*WLKUP)+WLKLERI
        ADD HL,DE
        LD (IY+4),L
        LD (IY+5),H
        LD DE,WLKLEN
        RET 

RepFaze
RepFze  LD HL,0
        LD (IY+2),L
        LD (IY+3),H
        RET 

outnrg  LD IX,f_ix
        LD E,0
        LD D,(IX+1)
        LD H,(IX+2)
        LD L,.nrgspr
        LD BC,#6E4
o_nrg2  PUSH DE
o_nrg1  CALL onrgline   ;менять вход в onrgline!
        POP DE
        INC D
        DJNZ o_nrg2
        DEC C           ; хрень :) никогда не выполнится
        JR Z,o_nrg2     ;
        LD A,D
        XOR #1F
        LD D,A
        LD E,(IX+4)     ;координата линии по Y
        LD A,(IX+5)     ;цвет
        DEC E
        LD (DE),A
        JR NZ,$-2
        RET 


ini_nrgline
        ;A=0
;lxand_tbl
        RLCA 
        LD C,A
        AND 7
        ADD A,.lxand_tbl
        LD H,'lxand_tbl
        LD L,A

        LD IX,onrgl1
        LD (IX-1),#7E
        LD A,#13
        LD (IX+5),A
        LD (IX+8),A
        LD (IX+11),A
        LD (IX+14),A
        LD (IX+17),A
        LD (IX+20),A
        LD (IX+23),A
        LD (IX+26),A

        LD A,(HL)
        LD (IX+1),A
        LD A,C
        RRCA 
        RRCA 
        RRCA 
        AND #0F
        SUB 8
        NEG 
        LD C,A
        LD B,0
        LD HL,onrgline
        ADD HL,BC
        ADD HL,BC
        LD (o_nrg1+1),HL
        OR A
        JR NZ,i_n_l1
        LD (IX-1),#C9
        RET 

i_n_l1  DEC A
        JR NZ,i_n_l2
        LD (IX+5),#C9
        RET 

i_n_l2  LD DE,3
        DEC A
        ADD IX,DE
        JR NZ,i_n_l2+3
        LD (IX+5),#C9
        RET 

onrgline
        LDI             ;) проца вывода энергии :)
        LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        LDI 
        RET ;LD A,(HL)  ;RET
onrgl1  AND 0
        LD (DE),A
        INC HL
        XOR A
        INC DE          ;RET
        DUP 7
        LD (DE),A
        INC HL
        INC DE          ;RET
        EDUP 
        LD (DE),A
        INC HL
        RET 

;постановка одиночного спрайта

;HL=adr of spr
;BC=xy
;(OOAtr+1)=Color

OnceSpr

        PUSH HL         ;11

        LD A,C          ;4
        ADD A,A         ;4
        LD L,A          ;4
        LD H,'XYTABLE   ;7
        LD E,(HL)       ;7
        INC L           ;4
        LD D,(HL)       ;7
        LD L,B          ;4
        SET 7,L         ;8
        LD L,(HL)       ;7
        LD H,0          ;7
        ADD HL,DE       ;10 =73

        LD A,(HL)       ;7
        CP .OOutSpr     ;7 спрайт будет выводиться
OORLD   JR Z,OOrSpr     ;7/12 - сюда поставить CP нн - для
                        ;неорных спрайтов
        CP .OLVDATA     ;7 стена
        POP BC          ;10
        RET Z           ;5/11  =43

OOOPRC  LD (HL),.OOutSpr ;10
        INC HL          ;6
        INC HL          ;6
        LD (HL),C       ;7 адрес спрайта
        INC HL          ;6
        LD (HL),B       ;7
OOAtr1  INC HL          ;6
        INC HL          ;6
OOAtr   LD (HL),0       ; цвет
        RET             ;10     =~75 /~206 (пересчитать пора)

OOrSpr  INC HL
        INC HL
        LD C,(HL)
        INC HL
        LD B,(HL)
        LD A,B
        CP LOW_POROG
        JR C,OOrS1
        LD DE,(OR_BUFF_ADR)
        LD (HL),D
        DEC HL
        LD (HL),E
        INC HL
        EX (SP),HL

OOrS2   LD A,(BC)
        OR (HL)
        LD (DE),A
        INC HL
        INC DE
        INC BC
        LD A,E
        AND 7
        JR NZ,OOrS2
        LD (OR_BUFF_ADR),DE
OOrS4   POP HL
        JR OOAtr1

OOrS1   EX (SP),HL
OOrS3   LD A,(BC)
        OR (HL)
        LD (BC),A
        INC HL
        INC C
        LD A,C
        AND 7
        JR NZ,OOrS3
        POP HL
        JR OOAtr1

