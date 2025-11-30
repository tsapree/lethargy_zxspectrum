;Оутро.
;начало: 08.08.2003
;конец:

        MAIN "",#C0

FNT     EQU ATRS_BUFF
prombuff EQU ATRS_BUFF+#600    ;DS 7*192

StrCode
_ocodestart
        DISP GGFX
morph   EQU 12
drmtbl  DB %00111111
        DB %00111111
        DB %00111111
        DB %00111111
        DB %00111111
        DB %00111111
        DB %00011111
        DB %00011111
        DB %00001111
        DB %00000111
        DB %00000001
        DB %00000000

OUTRO_TEXT
        CALL ONPAGE_lvl
        LD HL,outro_FNT
        LD DE,FNT
        LD BC,#600
        LDIR 
        CALL ONPAGE_lvl
        LD HL,endtext1
        LD DE,#4000
        CALL pradr
        LD HL,endtext2
        LD DE,#4006
        CALL pradr
        LD HL,endtext3
        LD DE,#400C
        CALL pradr
        LD HL,endtext4
        LD DE,#4012
        CALL pradr
        LD HL,endtext5
        LD DE,#4018
        CALL pradr

        LD HL,#5800
NVATr1  LD (HL),0
        INC HL
        LD B,5
        LD (HL),#3F
        INC HL
        DJNZ $-3
        LD A,L
        CP 30
        JR C,NVATr1
        LD (HL),0
        INC HL
        LD (HL),0
        INC HL
        EX DE,HL
        LD HL,#5800
        LD BC,#2E0
        LDIR 

        CALL ONPAGE_fzs
        LD HL,Logo1_scr_1
        CALL DECOMPR
        CALL ONPAGE_lvl
        LD HL,#4000
        LD DE,#C000
        LD BC,#1800
        LDIR 
        LD HL,ATRS_BUFF
        LD BC,#300
        LDIR 
        CALL ONPAGE_fzs
        LD HL,Logo2_scr_1
        CALL DECOMPR
        CALL ONPAGE_lvl
        LD HL,#4000
        LD DE,#C000
        LD BC,#1800
        LD A,(DE)
        XOR (HL)
        LD (HL),A
        INC HL
        INC DE
        DEC BC
        LD A,B
        OR C
        JR NZ,$-8

        LD A,1*8+1
        CALL BlinkAt
        HALT 
        HALT 
        HALT 
        HALT 
        XOR A
        OUT (#FE),A
        LD DE,#5800
        LD HL,ATRS_BUFF
        LD BC,#300
        LDIR 
        CALL PAUSE150
        LD A,6*8+6
        CALL BlinkAt
        HALT 
        CALL ONPAGE_lvl
        LD HL,#C000
        LD DE,#4000
        LD BC,#1800
        LDIR 
        HALT 
        HALT 
        XOR A
        OUT (#FE),A
        LD BC,#300
        LDIR 
        CALL PAUSE150
        CALL FadeScr

        LD HL,fcemukey
        LD (emukeys+1),HL
        LD A,#C3
        LD (emukeys),A
        LD HL,0
        LD (srcmgNO),HL
        CALL InitOSp
        CALL SHOWROOM
        CALL FCLp0
        EI 
        LD HL,#4000
        LD DE,#5800
clnez0  LD A,(DE)
        AND #3F
        JR NZ,clnez1
        LD C,H
        LD B,8
        LD (HL),A
        INC H
        DJNZ $-2
        LD H,C
        LD A,7
        LD (DE),A
clnez1  INC DE
        INC L
        JR NZ,clnez0
        LD A,H
        ADD A,8
        LD H,A
        CP #58
        JR NZ,clnez0

        CALL PAUSE150
        LD C,8
fdstr0  LD B,32
        LD HL,#59E0
fdstr1  LD A,(HL)
        AND 7
        JR Z,$+3
        DEC A
        LD (HL),A
        INC L
        DJNZ fdstr1
        HALT 
        DEC C
        JR NZ,fdstr0

        CALL ONPAGE_fzs
        CALL Magnify
FUCK
        LD A,7*8+7
        CALL BlinkAt

        LD HL,#4827
        LD DE,end2c_temp
        LD BC,#1206
        CALL outspr
        HALT 
        PUSH DE
        LD HL,ATRS_BUFF
        LD D,H
        LD E,L
        INC DE
        LD BC,#2FF
        LD (HL),L
        LDIR 
        POP DE
        LD BC,#1206
        LD HL,ATRS_BUFF+#127
        CALL outatr
        HALT 
        HALT 
        HALT 
        XOR A
        OUT (#FE),A
        LD HL,ATRS_BUFF
        LD DE,#5800
        LD BC,#300
        LDIR 

        IF ?SAVEOBJ-2
        JR $
        ELSE 
        XOR A
        IN A,(#FE)
        CPL 
        AND 31
        JR Z,$-5
        CALL ONPAGE_mus
        CALL INIT
        RET 
        ENDIF 

BlinkAt LD C,A
        HALT 
        AND 7
        OUT (#FE),A
        LD HL,#5800
        LD B,3
        LD (HL),C
        INC L
        JP NZ,$-2
        INC H
        DJNZ $-6
        RET 


PAUSE150
        LD B,150
        HALT 
        DJNZ $-1
        RET 

prnstr  EX DE,HL
        LD A,L
        AND #E0
prnstr1 ADD A,0
        LD L,A
        JR pradr2

pradr   LD (prtxt+1),HL
        LD (pradr1+1),DE
        LD (drmorph+1),DE
        LD A,E
        LD (prnstr1+1),A
pradr1  LD HL,#4000
pradr2  LD B,#0C
        LD C,#0F
prtxt   LD DE,0
        LD A,(DE)
        OR A
        JP Z,drmorph
        INC DE
        LD (prtxt+1),DE
        CP 32
        JR NC,prtxt1
        CP 13
        JR Z,prent
        ADD A,A
        ADD A,A
        DEC A
        HALT 
        JR NZ,$-2
        JR prtxt

prent   LD A," "
        LD B,1
prtxt1  LD E,A
        LD D,'FNT
        PUSH HL
        DUP 3
        LD A,(DE)
        XOR (HL)
        AND C
        XOR (HL)
        LD (HL),A
        INC D
        INC H
        LD A,(DE)
        XOR (HL)
        AND C
        XOR (HL)
        LD (HL),A
        INC D
        INC H
        LD A,H
        AND 7
        CALL Z,dwnhl1
        EDUP 
        EX DE,HL
        POP HL
        LD A,C
        CPL 
        LD C,A
        RLCA 
        JR NC,$+3
        INC HL
        DJNZ prtxt
        JP prnstr

dwnde   INC D
        LD A,D
        AND 7
        RET NZ
dwnde1  LD A,E
        ADD A,32
        LD E,A
        RET C
        LD A,D
        SUB 8
        LD D,A
        RET 

endtext1

DB "МЕДЛЕННО,",10,13
DB "КАК ПУГЛИВЫЙ",5
DB "   МАЛЕНЬКИЙ"
DB "   ЩЕНОК,",10,13
DB "НАПОЛЗАЕТ   "
DB "  ВОЛНА...  ",20
DB "   ОСТОРОЖНО"
DB "ПОДБИРАЕТСЯ,",10
DB "ЧТОБЫ ОДНИМ "
DB "      РЫВКОМ"
DB "УТЯНУТЬ ТЕБЯ"
DB "В ОКЕАН...  ",20
DB "    И ТЫ    "
DB "ОКАЗЫВАЕШЬСЯ",10
DB " В НОВОЙ",5," И",13
DB "ЧУЖОЙ ДЛЯ   "
DB "    ТЕБЯ    ",10
DB "   СТИХИИ...",20
DB "БАРАХТАЕШЬСЯ",10
DB "И ПЫТАЕШЬСЯ "
DB " ВЕРНУТЬСЯ В"
DB " ПРИВЫЧНЫЙ  ",10
DB "МИР...      ",20
DB " И ВДРУГ ТЫ "
DB "  ОСОЗНАЕШЬ,",15
DB "   ЧТО ЭТА  "
DB "ЧУЖАЯ СТИХИЯ"
DB "   СТАЛА    ",10
DB "   РОДНОЙ...",20
DB " ТЫ ДОМА... ",20
DB "            "
DB " ТЫ УМЕР... ",28
DB 0

endtext2

DB "БЕЖИШЬ...   ",10
DB "  ПОВОРОТ...",10
DB " ЕЩЕ ОДИН...",15
DB "  И ЕЩЕ...  ",10
DB "В ПОГОНЕ ЗА "
DB "   СВОЕЙ    "
DB "   МЫСЛЬЮ...",15
DB " БЕЖИШЬ ПО  "
DB "КОРИДОРАМ   "
DB " ИЗВИЛИН... ",20
DB "  И КАЖЕТСЯ,",10
DB " ЧТО ВОТ-ВОТ"
DB "НАСТИГНЕШЬ  "
DB "  ЕЕ,",15," НО... ",10
DB "   ОНА СНОВА"
DB "УСКОЛЬЗАЕТ..",10
DB "И СНОВА     "
DB "  БЕЖИШЬ... ",10
DB " ПОВОРОТЫ...",10
DB "ВЫБИВАЕШЬСЯ "
DB "ИЗ СИЛ...   ",10
DB "НО БЕЖИШЬ...",20
DB "  И КОГДА   "
DB "КАЖЕТСЯ,",5," ЧТО"
DB " ТЫ НИКОГДА "
DB "ЕЕ",10," НЕ",13
DB "  ПОЙМАЕШЬ, ",20
DB "         ОНА",10
DB "  ЗАМИРАЕТ. ",20
DB "ТЫ ПОЙМАЛ...",20
DB "            ",20
DB "ТЫ УМЕР...  ",28
DB 0

endtext3

DB "РАЗБЕГ...   ",20
DB "  ПОЛЕТ...  ",10
DB "  ВЕТЕР БЬЕТ"
DB "  ПО УШАМ,  ",10
DB "СВИСТИТ...  ",20
DB "   МИМО     "
DB "  ПРОНОСЯТСЯ",5
DB " ПТИЦЫ",5," И",5,13
DB "КАПЛИ ДОЖДЯ.",20
DB "  ПОЛЕТ...  ",15
DB "  ТЫ КРИЧИШЬ"
DB "ОТ ВОСТОРГА,",10
DB " И ГОНИШЬСЯ "
DB "  ЗА СВОИМ  "
DB "   КРИКОМ...",20
DB "КТО БЫСТРЕЕ?",10
DB "РАЗНОЦВЕТНЫЕ"
DB "  ПЯТНА...  ",15
DB "     ТЯЖЕСТЬ"
DB " СКОРОСТИ...",20
DB "ТЫ ГЛОТАЕШЬ "
DB "   ВОСТОРГ  "
DB "  ВПЕРЕМЕЖКУ"
DB " С КЛОЧКАМИ "
DB "ВОЗДУХА...  ",20
DB "НЕБО ВВЕРХУ.",10
DB "ЗЕМЛЯ СНИЗУ.",20
DB "   МЧИТСЯ   "
DB "НАВСТРЕЧУ...",15
DB "ТЫ СВОБОДЕН.",20
DB "            ",20
DB " ТЫ УМЕР... ",28
DB 0

endtext4

DB "ТЫ ПИШЕШЬ...",10
DB "  ПЛЮС...   ",15
DB "    МИНУС...",15
DB "  РАВНО...  ",20
DB "ТРИНАДЦАТЬ  ",5
DB " УМНОЖИТЬ НА"
DB "   ВОСЕМЬ...",20
DB " ПОСТРОИТЬ  "
DB "ТАБЛИЧКУ... ",20
DB " В ЦИКЛЕ... ",10
DB "  ЗНАКОМЕСТО"
DB " СПРАВА,",5," ДВА"
DB "СНИЗУ...    ",15
DB "  МОРФИНГ   ",5
DB "ПЛЮС",5," ЧАНКИ",5," И",5
DB "   НЕМНОГО  ",5
DB "МУЗЫКИ...   ",20
DB " СНОВА ПЛЮС.",15
DB "   ПОБИТОВОЕ"
DB " ДЕЛЕНИЕ... ",5
DB "НЕТ, ЛУЧШЕ  "
DB " ТАБЛИЧКУ...",15
DB "    ГЛЮКИ...",20
DB " ПОКСОРИТЬ? ",10
DB "МОЖНО И     "
DB "ПОКСОРИТЬ...",20
DB "  ПОСЧИТАТЬ "
DB " КОНТРОЛЬНУЮ"
DB "  СУММУ...  ",15
DB "ТЫ НАПИСАЛ. ",20
DB "            ",20
DB " ТЫ УМЕР... ",28
DB 0

endtext5

DB "СОН...      ",20
DB "КРАСОЧНЫЙ И "
DB "МРАЧНЫЙ...  ",15
DB "СТРАШНЫЙ И  "
DB "НЕМНОГО     "
DB "ЗАБАВНЫЙ... ",20
DB "ЛАБИРИНТ... ",10
DB "ВЫХОД ЕСТЬ. ",10
DB "ВЫХОД ВСЕГДА"
DB "ЕСТЬ...     ",20
DB "ТЫ СПИШЬ... ",5
DB "И ВИДИШЬ    "
DB "СОН...      ",10
DB "ТЫ ЖИВЕШЬ...",5
DB "ЖИВЕШЬ ЭТИМ "
DB "СНОМ...     ",15
DB "ХОЧЕШЬ      "
DB "ПРОСНУТЬСЯ..",5
DB "НЕ МОЖЕШЬ...",15
DB "ТЫ ЖИВЕШЬ",5," ВО"
DB "СНЕ...      ",10
DB "ТЫ СПИШЬ... ",15
DB "ЖИЗНЬ...    ",5
DB "НАСТОЯЩАЯ   "
DB "ЖИЗНЬ       "
DB "ПРОХОДИТ    "
DB "МИМО ТЕБЯ...",20
DB "ИЩЕШЬ ВЫХОД.",15
DB "ТЫ НАШЕЛ... ",10
DB "ТЫ ПРОСНУЛСЯ",20
DB "            "
DB "ТЫ УМЕР...  ",28
DB 0

rlrr    LD HL,prombuff
        LD E,192
rrbuff2 LD BC,#0700
rrbuff1 LD A,(HL)
        RR C
        RRA 
        RL C
        OR (HL)
        LD (HL),A
        INC HL
        DJNZ rrbuff1
        DEC E
        JR NZ,rrbuff2
        DEC HL
        LD E,192
rlbuff2 LD BC,#0700
        LD A,(HL)
rlbuff3 AND 0
        LD (HL),A
rlbuff1 LD A,(HL)
        RR C
        RLA 
        RL C
        OR (HL)
        LD (HL),A
        DEC HL
        DJNZ rlbuff1
        INC HL
        LD A,(HL)
rrbuff3 AND 0
        LD (HL),A
        DEC HL
        DEC E
        JR NZ,rlbuff2
        RET 

rurd    LD HL,prombuff
        LD DE,prombuff+7
        LD BC,7*191
rurd1   LD A,(DE)
        OR (HL)
        LD (HL),A
        INC DE
        CPI 
        JP PE,rurd1
        EX DE,HL
        DEC HL
        DEC DE
        LD BC,7*191
rurd2   LD A,(DE)
        OR (HL)
        LD (HL),A
        DEC DE
        CPD 
        JP PE,rurd2
        RET 

drmorph
        LD HL,#4000
        LD (outp0+1),HL
        LD DE,prombuff
inpu1   LD A,L
        LD BC,7
        LDIR 
        LD L,A
        CALL dwnhl
        LD A,H
        CP #58
        JR C,inpu1
        LD HL,#C000
        LD (ldr2m+1),HL
        XOR A
        CALL drm1+3
output  LD HL,#C000
        LD A,morph
outp0   LD DE,#4000
        PUSH AF
        HALT 
        HALT 
outp1   DUP 8
        LD A,E
        DUP 7
        LDI 
        EDUP 
        LD E,A
        INC D
        EDUP 
        CALL dwnde+1
        LD A,D
        CP #58
        JP C,outp1
        POP AF
        DEC A
        JP NZ,outp0
        RET 

drm1    LD A,0
        INC A
        LD (drm1+1),A
        CP morph
        RET Z
        LD C,A
        LD B,0
        LD HL,drmtbl
        ADD HL,BC
        LD A,(HL)
        LD (rrbuff3+1),A
        OR A
        JR Z,$+5
        RLCA 
        JR NC,$-1
        RRCA 
        LD (rlbuff3+1),A
        LD A,C
        CP 4
        CALL NC,rlrr
        CALL rurd
ldr2m   LD DE,#C000
        LD HL,prombuff
        LD BC,7*192
        LDIR 
        LD (ldr2m+1),DE
        JR drm1

Drawing FZS M1W,#00FE,sceldrw,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+24,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+48,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+72,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+96,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+120,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+144,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+168,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+192,#0203,HeroClr
        FZS M1W,#00FE,sceldrw+240,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+264,#0103,HeroClr
        FZS M1W,#00FE,sceldrw+288,#0203,HeroClr
        FZS M1W,#00FE,sceldrw+336,#0203,HeroClr
        FZS M1W,#00FE,sceldrw+384,#0203,HeroClr
        FZS M1W,#00FE,sceldrw+432,#0103,HeroClr
        FZS EDrw,#00FE,sceldrw+456,#0103,HeroClr

EDrw    PUSH IY
        LD BC,#0F05
        CALL mnstbfy
        LD HL,EEDrw
        CALL mnstbfehl
        POP IY
        JP StRL21

EEDrw   FZS RepFaze,0,endd,#0202,7

ScBye   FZS 0,#FEFE,sclbye,#0103,HeroClr ;1
        FZS 0,#FEFE,sclbye+24,#0103,HeroClr ;2
        FZS 0,#FDFE,sclbye+48,#0203,HeroClr ;3
        FZS 0,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+144,#0203,HeroClr ;5
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+192,#0203,HeroClr ;7
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+144,#0203,HeroClr ;5
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+192,#0203,HeroClr ;7
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+144,#0203,HeroClr ;5
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+192,#0203,HeroClr ;7
        FZS M1W,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS M1W,#FDFE,sclbye+144,#0203,HeroClr ;5
        FZS 0,#FDFE,sclbye+96,#0203,HeroClr ;4,6
        FZS 0,#FDFE,sclbye+48,#0203,HeroClr ;3
        FZS 0,#FEFE,sclbye+24,#0103,HeroClr ;2
        FZS 0,#FEFE,sclbye,#0103,HeroClr ;1
        FZS EndFC1

EndFC1  LD A,1
        LD (FCLp2+1),A
        JP RepFaze

        MACRO MMES
        aa=256-:0/2+:2
        bb=192-:1/2+:3
        cc=144*256/:0
        dd=48*256/:1
        MES aa,bb,cc,dd
        ENDM 

        MACRO MES
        ;%010YYyyy YYYXXXXX
 DB :1<2&#E0+(:0>3&63)
 DB :1&7+(:1&#C0>3)+#40
 DW 0
        lastadr=$
 DW 0
 DB 1<(:0&7)
 DW :2,:3
        ENDM 

;+01    DW adrscr
;+23    DW size
;+45    DW adrinmem
;+6     DB XinCELL
;+78    DW magnx
;+9A    DW magny

Magnify
        LD HL,#C000     ;адрес результата
        LD IX,MESTBL
mgude4  LD (IX+4),L
        LD (IX+5),H
        LD E,(IX+7)
        LD D,(IX+8)
        LD (mgdeX+1),DE
        LD E,(IX+9)
        LD D,(IX+10)
        LD (mgdeY+1),DE
        LD A,(IX+6)
        LD (mgude1+1),A
        LD DE,end2_temp ;адрес исходника
        CALL mgude0

        LD (IX+2),16*3
mgsY    EQU $-1
        LD (IX+3),0
mgsX    EQU $-1
        LD DE,11
        ADD IX,DE
        LD A,(IX)
        INC A
        JR NZ,mgude4

        LD HL,MESTBL
mgude3  LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        PUSH DE
        LD C,(HL)
        INC HL
        LD B,(HL)
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        EX (SP),HL
        EX DE,HL
mgude2  PUSH DE
        PUSH BC
        LD A,(HL)
        LD (DE),A
        INC HL
        INC DE
        DJNZ $-4
        POP BC
        POP DE
        CALL dwnde
        DEC C
        JR NZ,mgude2
        POP HL
        LD BC,11-6
        ADD HL,BC
        LD A,(HL)
        INC A
        RET Z
        HALT 
        JR mgude3

mgude0  XOR A
        LD (mgsY),A
        LD IY,0
mgdeY   LD BC,0
        LD A,HY
        ADD IY,BC
        SUB HY
        NEG 
        OR A
        JR Z,mgude5
        EX DE,HL
        LD BC,18
        ADD HL,BC
        DEC A
        JR NZ,$-2
        EX DE,HL
mgude5  LD A,HY
        CP 16*3
        RET NC
        PUSH BC
        LD C,#80        ;точка в знакоместе исходника
mgude1  LD (HL),#01     ;заполнять все первое знакоместо
        LD A,L
        PUSH AF
        CALL mgde0
        POP AF
        SUB L
        NEG 
        LD (mgsX),A
        LD A,(mgsY)
        INC A
        LD (mgsY),A
        POP BC
        JR mgdeY

mgde0   PUSH DE
        EXX 
        LD HL,#0000     ;координата в спрайте и дробная часть.
mgdeX   LD BC,#0100     ;смещение

mgde3   LD D,H
        ADD HL,BC
        LD A,H
        CP 18*8
        JR C,mgde4
        EXX 
        RL (HL)
        JR NC,$-2
        INC HL
        POP DE
        RET 

mgde4   SUB D
        EXX 
        JR Z,mgde2
mgde1   RRC C
        JR NC,$+3
        INC DE
        DEC A
        JR NZ,mgde1
mgde2   LD A,(DE)
        AND C
        DEC A ;0>#FF, #80>#7F
        CP #FF
        RL (HL)
        JR NC,$+5
        INC HL
        LD (HL),1
        EXX 
        JR mgde3

MESTBL
        MMES 9  , 3 ,0  ,8
        MMES 18 , 11,2  ,7
        MMES 27 , 20,4  ,5
        MMES 36 , 25,6  ,4
        MMES 45 , 28,8  ,3
        MMES 54 , 31,10 ,3
        MMES 63 , 33,9  ,2
        MMES 72 , 36,8  ,2
        MMES 81 , 38,7  ,1
        MMES 90 , 40,6  ,1
        MMES 99 , 42,5  ,1
        MMES 108, 44,4  ,0
        MMES 117, 45,3  ,0
        MMES 126, 46,2  ,0
        MMES 135, 47,1  ,0
        MMES 144, 48,0  ,0
        MES aa,bb,#00FF,#00FF
        DB #FF

        ENT 
_ocodesize=$-_ocodestart

        DISPLAY "Outro Code Size: ",$-StrCode

Logo2_scr       INCBIN "StalLog3.P"
Logo2_len       EQU $-Logo2_scr
Logo2_scr_1     EQU #E000

Logo1_scr       INCBIN "StalLogo.P"
Logo1_len       EQU $-Logo1_scr
Logo1_scr_1     EQU #E000+Logo2_len

outro_FNT       INCBIN "outrofnt.f",#600

end2_temp       EQU 0-#72C ;Logo1_scr_1+Logo1_len

end2    DD #1FFFFFFFFFF81FFFFFF80000
        DD #1FFFFFF800007FFFFFFFFFFE
        DD #7FFFFFFE00007FFFFFFE0000
        DD #7FFFFFFFFFFE7FFFFFFE0000
        DD #7FFFFFFE0000FFFFFFFFFFFF
        DD #7FFFFFFF0000FFFFFFFF0000
        DD #FFFFFFFFFFFF7FFFFFFF0000
        DD #FFFFFFFF0000FFFFFFFFFFFF
        DD #FFFFFFFF0000FFFFFFFF0000
        DD #FFFFFFFFFFFF7FFFFFFF0000
        DD #FFFFFFFF0000FFFFFFFFFFFF
        DD #FFFFFFFF0000FFFFFFFF0000
        DD #FFFFFFFFFFFFFFFFFFFF0000
        DD #FFFFFFFF0000FFFFFFFFFFFF
        DD #FFFFFFFF0000FFFFFFFF0000
        DD #FFFFFFFFFFFF7FFFFFFF0000
        DD #FFFFFFFF0000FFFFFFFFFFFF
        DD #FFFFFFFF0000FFFFFFFF0000
        DD #FFFFFFFFFFFF7FFFFFFF0000
        DD #FFFFFFFF0000FFFFFFFFFFFE
        DD #7FFFFFFF8000FFFFFFFE0000
        DD #FFFFFFFFFFFEFFFFFFFF8000
        DD #FFFFFFFE0000FFFF0003FFF8
        DD #FFFFFFFFE000FFFFFFF80000
        DD #FFFFFFF80000FFFF0007FFF8
        DD #FFFF00001FF8FFFFFFFE0000
        DD #FFFF0001FFFEFFFF00007FFE
        DD #FFFFFFFF0000FFFF0001FFFE
        DD #7FFF00007FFEFFFFFFFF0000
        DD #FFFF0000FFFF7FFF0000FFFF
        DD #FFFFFFFF0000FFFF0000FFFF
        DD #7FFF0000FFFFFFFFFFFF0000
        DD #FFFF0000FFFF7FFF0000FFFF
        DD #FFFFFFFF0000FFFF0000FFFF
        DD #7FFF0000FFFFFFFFFFFF0000
        DD #FFFF0000FFFF7FFF0000FFFF
        DD #FFFFFFFF0000FFFF0000FFFF
        DD #FFFF0000FFFFFFFFFFFF0000
        DD #FFFF0000FFFF7FFF0000FFFF
        DD #FFFFFFFF0000FFFF0000FFFF
        DD #FFFF0000FFFFFFFFFFFF0000
        DD #FFFF0000FFFFFFFF0000FFFF
        DD #FFFFFFFE0000FFFF0000FFFF
        DD #FFFF0000FFFFFFFFFFFE0000
        DD #FFFF0000FFFFFFFF0001FFFE
        DD #FFFFFFF80000FFFF0000FFFF
        DD #FFFF0001FFFEFFFF00000000
        DD #FFFF0000FFFFFFFF0007FFF8
        DD #FFFFFFFFFFF8FFFF0000FFFF
        DD #FFFFFFFFE000FFFFFFFFFFFE
        DD #FFFF0000FFFFFFFFFFFF8000
        DD #FFFFFFFFFFFE7FFF0000FFFF
        DD #FFFFFFFF8000FFFFFFFFFFFF
        DD #7FFF0000FFFFFFFFFFFF0000
        DD #FFFFFFFFFFFF7FFF0000FFFF
        DD #FFFFFFFF0000FFFFFFFFFFFF
        DD #FFFF0000FFFFFFFFFFFF0000
        DD #FFFFFFFFFFFF7FFF0000FFFF
        DD #7FFFFFFF0000FFFFFFFFFFFF
        DD #FFFF0000FFFFFFFFFFFF0000
        DD #FFFFFFFFFFFFFFFF0000FFFF
        DD #7FFFFFFF0000FFFFFFFFFFFF
        DD #7FFF0000FFFF7FFFFFFF0000
        DD #FFFFFFFFFFFFFFFF0000FFFF
        DD #7FFFFFFF0000FFFFFFFFFFFF
        DD #7FFF0000FFFF7FFFFFFF0000
        DD #FFFFFFFFFFFF7FFF0000FFFF
        DD #7FFFFFFF00007FFFFFFFFFFE
        DD #7FFE00007FFE7FFFFFFE0000
        DD #7FFFFFFFFFFE7FFE00007FFE
        DD #7FFFFFFE00001FFFFFFFFFF8
        DD #1FF800001FF81FFFFFF80000

end2c_temp      EQU $-end2+end2_temp

end2c   DD #0AAAFFFFFF541FFFFFF80000
        DD #FFFFFFFF0000011FFFFAEFEA
        DD #7FFFFFFEE000FFAAFFFAE000
        DD #2AAABFFFFB907FFFFFFE3C00
        DD #FFFEFFFC3C00047FFFFA7AC2
        DD #FFFFFFFF5700FEAAFEAA5700
        DD #AAABFFD7B5B8FFFFFFFF2A80
        DD #FFDCFFF62B80115FFFFEFE7C
        DD #FFFFFFFF0140FAAAFAAA7540
        DD #AAABFF57799EFFFFFFFF2AA0
        DD #FF76FFDC2EA007FFFFFD37CC
        DD #7FFFFFFF0050800080001550
        DD #AAAFFFFF5EAAFFFFFFFF00A8
        DD #FFFFFFFF28A8D7FFFBFFBFDC
        DD #FFFFFFFF0010FAFFF4FE1550
        DD #AABFFFFFD9A8FFFFFFFF00A8
        DD #FCFFFAFA1A08D7FFF7FF8EC4
        DD #7FFFFFFF0014AAFF54FE1554
        DD #AAFFFFFFF7AEFFFFF7FF0028
        DD #F6FFEEEA2A2277FFFFFFF6FA
        DD #5FFFFFFF8004EAFD54FC3054
        DD #AABFFFFFE6DCFFFFF5FF802A
        DD #FEFFBAAA6008FD7F000001BA
        DD #77FFFFFFE000808000808000
        DD #AAAFEAA800D4FFFF0007BBA8
        DD #7F5500011FF8F17FFF400068
        DD #5DDF0001FF762A8200007FFE
        DD #AA2FFAA80058FFFF0000AEAA
        DD #1F5400047FFEFD5FFD000048
        DD #557F0000FFDF0A800000FFFF
        DD #EAAAFAA00000FFFF0000AAAA
        DD #1F540000FFFFFC1FFF000008
        DD #555F0000FD7F0E880000FFFF
        DD #EAAAFAA00000EEFF0000AAAB
        DD #1F540000FFFFF705FF000000
        DD #55570000D57F1EA00000FFFF
        DD #AAAABE800000FBFF0000AAAB
        DD #00000000FFFFDD517F000000
        DD #555F000077FF3FEA0000FFFF
        DD #AAAABA800000FEFF0000AABF
        DD #75450000FFFF7FFC5F000000
        DD #55570000DFFF7EA00000FFFF
        DD #BEAAAAA00000FFBF0000ABFF
        DD #75550000FFFFFFFF7F000002
        DD #555F00007FFF7EE00001FFFE
        DD #BFFAAAA00054FEFF0000AFFF
        DD #7D550001ABFEFFFF00000020
        DD #55570000FFFF7EA80007FFF8
        DD #FFFFFEA8154E7ABF0000BFFF
        DD #00FFAABEA002FFF5DF95421F
        DD #555D0000FFFAA0FFFFFF802A
        DD #FFFFABEBB95E3EFF0000BFFF
        DD #00FFFEAA8010FFD776F57CB7
        DD #55570000FFFAA0FFFFFF0028
        DD #FFBFAE523D7B7FBF0000FFFD
        DD #40FFFFEA0044FF57F2F57A3C
        DD #55550000FFEAA8FFFFFF00A8
        DD #FC2EA0AB75783EEF0000FFFF
        DD #40FFFFFA0010F15F71F1AA6E
        DD #55550000FFFAA8FFFFFF00A8
        DD #7FDD5F2B2E1F6FBB0000FFFF
        DD #7FFFFFFE0000FABE9DD3559E
        DD #55550000FFFFFFFFFFFF02A0
        DD #FF3C4FE8AE673FEF0000FFFF
        DD #7EBFFFFE0400DF8EABC555AB
        DD #55550000FFFF7FFFFFFF2A80
        DD #BF96D4EBFAF46EFF0000FFFF
        DD #7FAABFFF11003FA9AB6535AE
        DD #555400007FFE7FFFFFFE2800
        DD #3F5F7E9B1E7A3BBE00007FFE
        DD #7FEEAAFE40001CBAAB5114A8
        DD #155000001FFC1FFFFFF80000
        DD #424242424242444444444242
        DD #464646464242424242424242
        DD #444444444442464646464242
        DD #024242424742444405444404
        DD #470707420707020242424707
        DD #044405070404470707070707
        DD #3A3A3A07070704440707043C
        DD #3C0707070742070707073A07
        DD #060607070404070707074242

end2_temp_size  EQU $-end2

FCMUZA  INCBIN "GALUCID.M"
        SIZE_FCMUZA=$-FCMUZA

        DISPLAY "End: ",$

