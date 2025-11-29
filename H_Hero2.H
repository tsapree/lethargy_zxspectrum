; Герой. Монстры.

        MAIN "",#C0

KickL
        FZS 0,#00FE,fgkick+192,#0103,HeroClr
        FZS 0,#FFFE,fgkick+144,#0203,HeroClr
        FZS srcbrkL,#FFFE,fgkick+96,#0203,HeroClr
        FZS 0,#FFFE,fgkick+48,#0203,HeroClr
        FZS StLL22,#FFFE,fgkick,#0203,HeroClr

KickR   FZM 0,#00FE,fgkick+192,#0103,HeroClr
        FZM 0,#00FE,fgkick+144,#0203,HeroClr
        FZM srcbrkR,#00FE,fgkick+96,#0203,HeroClr
        FZM 0,#00FE,fgkick+48,#0203,HeroClr
        FZM StRL22,#00FE,fgkick,#0203,HeroClr

PunchL
        FZS 0,#00FE,fgpunch+120,#0103,HeroClr
        FZS 0,#00FE,fgpunch+96,#0103,HeroClr
        FZS srcpncL,#FFFE,fgpunch+48,#0203,HeroClr
        FZS StLL22,#FFFE,fgpunch,#0203,HeroClr

PunchR  FZM 0,#00FE,fgpunch+120,#0103,HeroClr
        FZM 0,#00FE,fgpunch+96,#0103,HeroClr
        FZM srcpncR,#00FE,fgpunch+48,#0203,HeroClr
        FZM StRL22,#00FE,fgpunch,#0203,HeroClr

BowL
        FZS 0,#00FE,fgbow+312,#0103,HeroClr
        FZS 0,#FFFE,fgbow+264,#0203,HeroClr
        FZS 0,#FFFE,fgbow+216,#0203,HeroClr
        FZS 0,#FFFE,fgbow+168,#0203,HeroClr
        FZS W2unhF,#FFFE,fgbow+120,#0203,HeroClr
        FZS FirStrL,#FFFE,fgbow+72,#0203,HeroClr
        FZS 0,#FFFE,fgbow+24,#0203,HeroClr
        FZS StLL22,#00FE,fgbow,#0103,HeroClr

BowR    FZM 0,#00FE,fgbow+312,#0103,HeroClr
        FZM 0,#00FE,fgbow+264,#0203,HeroClr
        FZM 0,#00FE,fgbow+216,#0203,HeroClr
        FZM 0,#00FE,fgbow+168,#0203,HeroClr
        FZM W2unhF,#00FE,fgbow+120,#0203,HeroClr
        FZM FirStrR,#00FE,fgbow+72,#0203,HeroClr
        FZM 0,#00FE,fgbow+24,#0203,HeroClr
        FZM StRL22,#00FE,fgbow,#0103,HeroClr

W2unhF  AND #10
        JP Z,arr1snd
repfaz1 JP RepFaze

FirStrL LD HL,OutStrL
        LD BC,#FFFF ;слева из живота
        JP flyadd

FirStrR LD HL,OutStrR
        LD BC,#01FF
        JP flyadd

OutStrL
        FZS FStrL,#00FF,strelkL,#0102,7

OutStrR FZS FStrR,#00FF,strelkR,#0102,7

FStrR   CALL WlkAdr
        INC HL
        LD A,(HL)
        OR A
        JR NZ,FStrRF
        INC (IY+1)
        INC HL
        LD A,(HL)
        OR A
        JR NZ,FStrRF
        INC (IY+1)
        JR repfaz1

FStrL   CALL WlkAdr
        DEC HL
        LD A,(HL)
        OR A
        JR NZ,FStrLF
        DEC (IY+1)
        DEC HL
        LD A,(HL)
        OR A
        JR NZ,FStrLF
        DEC (IY+1)
        JR repfaz1

FStrLF
        INC HL
        CALL FStrLF1
FStrLF2 CALL NZ,_AddItmStr
FStrLF3 JP KillFly

FStrRF
        DEC HL
        CALL FStrLF1
        JR Z,FStrLF3
        DEC (IY+1)
        JR FStrLF2

FStrLF1 PUSH HL
        LD HL,strela_shitl*256+Estrela
        LD DE,0
        LD A,1
        CALL srcitmf
        POP HL
        DEC B
        RET NZ
        LD (HL),#FF
        RET 

_AddItmStr
        LD C,MaxRunes
        LD IX,RUNEBUFF
        LD DE,8
_AIS1   LD A,(IX)
        INC A
        JR Z,_AIS2
        INC A
        JR Z,_AIS2
        DEC C
        RET Z
        ADD IX,DE
        JR _AIS1

_AIS2
        LD HL,OutArrUzd
        LD A,(IY)
        DEC A
        LD (IX),A
        LD A,(IY+1)
        LD (IX+1),A
        LD (IX+2),L
        LD (IX+3),H
        LD (IX+7),1
        RET 

ElecL
        FZS 0,#00FE,fgelec+96,#0203,HeroClr
        FZS elecdmg,#00FE,fgelec+48,#0203,HeroClr
        FZS 0,#00FE,fgelec,#0203,HeroClr
        FZS elecdmg,#00FE,fgelec+48,#0203,HeroClr
        FZS 0,#00FE,fgelec,#0203,HeroClr
        FZS elecdmg,#00FE,fgelec+48,#0203,HeroClr
        FZS 0,#00FE,fgelec,#0203,HeroClr
        FZS elecdmg,#00FE,fgelec+48,#0203,HeroClr
        FZS nulelec,#00FE,fgelec,#0203,HeroClr
        FZS StLL22,#00FE,fgelec+96,#0203,HeroClr

ElecR   FZM 0,#FFFE,fgelec+96,#0203,HeroClr
        FZM elecdmg,#FFFE,fgelec+48,#0203,HeroClr
        FZM 0,#FFFE,fgelec,#0203,HeroClr
        FZM elecdmg,#FFFE,fgelec+48,#0203,HeroClr
        FZM 0,#FFFE,fgelec,#0203,HeroClr
        FZM elecdmg,#FFFE,fgelec+48,#0203,HeroClr
        FZM 0,#FFFE,fgelec,#0203,HeroClr
        FZM elecdmg,#FFFE,fgelec+48,#0203,HeroClr
        FZM nulelec,#FFFE,fgelec,#0203,HeroClr
        FZM StRL22,#FFFE,fgelec+96,#0203,HeroClr

nulelec
        LD (IY+9),0
        RET 

elecdmg CALL damage_sr
elecdmg1 DB dmg_elec

JmpRight
        FZM      0,#00FE,jlRD1+#168,#0103,HeroClr ;1
        FZM      0,#00FE,jlRD1+#138,#0203,HeroClr ;2
        FZM JmpRpm,#00FE,jlRD1+#108,#0203,HeroClr ;3 x+ y-
        FZM  JmpRp,#00FE,jlRD1+#D8,#0203,HeroClr  ;4 x+
        FZM JmpRpm,#00FD,jlRD2+#60,#0204,HeroClr  ;5 x+ y-
        FZM JmpRs6,#00FE,jlRD1+#A8,#0203,HeroClr  ;6 x+
        FZM JmpRpp,#00FE,jlRD1+#78,#0203,HeroClr  ;7 x+ y+
        FZM  JmpRp,#00FD,jlRD2+#20,#0204,HeroClr  ;8 x+
        FZM  JmpRc,#00FE,jlRD1+#60,#0103,HeroClr  ;9 x+
        FZM  JmpRd,#00FE,jlRD2,#0104,HeroClr      ;a y+
JmpR1p  FZM  JmpRe,#00FE,jlRD1+#30,#0203,HeroClr  ;b x+
JmpREnd FZM      0,#00FE,jlRD1+#18,#0103,HeroClr  ;c
        FZM StRL21,#00FE,jlRD1,#0103,HeroClr      ;d

JmpRightSmall
        FZM      0,#00FE,jlRD1+#168,#0103,HeroClr ;1
        FZM      0,#00FE,jlRD1+#138,#0203,HeroClr ;2
        FZM JmpRpm,#00FE,jsRD1+168,#0203,HeroClr  ;3 x+ y-
        FZM JmpRpm,#00FE,jsRD1+120,#0203,HeroClr  ;4 x+ y-
        FZM JmpRs6,#00FE,jsRD2+64,#0104,HeroClr   ;5 x+
        FZM      0,#00FE,jsRD1+96,#0103,HeroClr   ;6
        FZM JmpRpp,#00FE,jsRD1+48,#0203,HeroClr    ;7 x+ y+
        FZM  JmpRc,#00FE,jsRD1,#0203,HeroClr       ;8 x+
        FZM  JmpRd,#00FE,jsRD2,#0204,HeroClr       ;9 y+

JmpOn4R FZM 0,#00FE,jsRU+24,#0203,HeroClr
        FZM StRL21,#00FE,jsRU,#0103,HeroClr

JmpRs6  INC (IY+1)
        CALL WlkAdr
        CALL exm4bl
        JR Z,JR81
        CP 8
        LD HL,JmpOn4R
        JP Z,LDIYHL

FRLpE   CALL verdwn
        JP Z,FallRLp
FRLpE1  LD HL,JmpREnd
        JP LDIYHL

JmpRc   INC (IY+1)
        CALL WlkAdr
        INC E
        CALL exm3blE
        DEC (IY+1)
        CP 4
        LD HL,JmpR1p
        JP Z,LDIYHL
        INC (IY+1)
        JR JmpRfv1

JmpRe   INC (IY+1)
        CALL WlkAdr
        CALL exm3blE
        JR Z,FRLpE
        RET 

JmpRd   INC (IY)
        LD HL,JmpR1p
        CALL LDIYHL
        JR JmpRfiv

JR81    LD DE,WLKLEN+1
        CALL exm4bl
        RET Z
JR82    JR FRLpE

JmpRpp  INC (IY)
        JR JmpRp

JmpRpm  DEC (IY)
JmpRp   INC (IY+1)

JmpRfiv CALL WlkAdr
JmpRfv1 LD E,1
        CALL exm3blE
        RET Z
        JR JR82

;---

JmpLeft
        FZS      0,#00FE,jlRD1+#168,#0103,HeroClr ;1
        FZS      0,#FFFE,jlRD1+#138,#0203,HeroClr ;2
        FZS JmpLpm,#FFFE,jlRD1+#108,#0203,HeroClr ;3 x+ y-
        FZS  JmpLp,#FFFE,jlRD1+#D8,#0203,HeroClr  ;4 x+
        FZS JmpLpm,#FFFD,jlRD2+#60,#0204,HeroClr  ;5 x+ y-
        FZS JmpLs6,#FFFE,jlRD1+#A8,#0203,HeroClr  ;6 x+
        FZS JmpLpp,#FFFE,jlRD1+#78,#0203,HeroClr  ;7 x+ y+
        FZS  JmpLp,#FFFD,jlRD2+#20,#0204,HeroClr  ;8 x+
        FZS  JmpLc,#00FE,jlRD1+#60,#0103,HeroClr  ;9 x+
        FZS  JmpLd,#00FE,jlRD2,#0104,HeroClr      ;a y+
JmpL1p  FZS  JmpLe,#FFFE,jlRD1+#30,#0203,HeroClr  ;b x+
JmpLEnd FZS      0,#00FE,jlRD1+#18,#0103,HeroClr  ;c
        FZS StLL21,#00FE,jlRD1,#0103,HeroClr      ;d

JmpLeftSmall
        FZS      0,#00FE,jlRD1+#168,#0103,HeroClr ;1
        FZS      0,#FFFE,jlRD1+#138,#0203,HeroClr ;2
        FZS JmpLpm,#FFFE,jsRD1+168,#0203,HeroClr  ;3 x+ y-
        FZS JmpLpm,#FFFE,jsRD1+120,#0203,HeroClr  ;4 x+ y-
        FZS JmpLs6,#00FE,jsRD2+64,#0104,HeroClr   ;5 x+
        FZS      0,#00FE,jsRD1+96,#0103,HeroClr   ;6
        FZS JmpLpp,#FFFE,jsRD1+48,#0203,HeroClr   ;7 x+ y+
        FZS  JmpLc,#FFFE,jsRD1,#0203,HeroClr      ;8 x+
        FZS  JmpLd,#FFFE,jsRD2,#0204,HeroClr      ;9 y+

JmpOn4L FZS 0,#FFFE,jsRU+24,#0203,HeroClr
        FZS StLL21,#00FE,jsRU,#0103,HeroClr

JmpLs6  DEC (IY+1)
        CALL WlkAdr
        ;LD DE,WLKLEN
        CALL exm4bl
        JR Z,JL81
        CP 8
        LD HL,JmpOn4L
        JP Z,LDIYHL

FLLpE   CALL verdwn
        JP Z,FallLLp
FLLpE1  LD HL,JmpLEnd
        JP LDIYHL

JmpLc   DEC (IY+1)
        CALL WlkAdr
        DEC E
        ;LD E,WLKLEN-1
        CALL exm3blE
        INC (IY+1)
        CP 4
        LD HL,JmpL1p
        JP Z,LDIYHL
        DEC (IY+1)
        JR JmpLfv1

JmpLe   DEC (IY+1)
        CALL WlkAdr
        ;LD E,WLKLEN
        CALL exm3blE
        JR Z,FLLpE
        RET 

JmpLd   INC (IY)
        LD HL,JmpL1p
        CALL LDIYHL
        JR JmpLfiv

JL81    LD DE,WLKLEN-1
        CALL exm4bl
        RET Z
JL82    JR FLLpE

JmpLpp  INC (IY)
        JR JmpLp

JmpLpm  DEC (IY)
JmpLp   DEC (IY+1)

JmpLfiv CALL WlkAdr
JmpLfv1 LD DE,-1
        CALL exm3bl
        RET Z
        JR JL82

PutKapL
        FZS 0,#FFFE,putkap2+144,#0203,HeroClr
        FZS 0,#FFFE,putkap2+96,#0203,HeroClr
        FZS 0,#FFFF,putkap1+192,#0202,HeroClr
        FZS M1W,#FFFF,putkap1+160,#0202,HeroClr
        FZS M1W,#FFFF,putkap1+128,#0202,HeroClr
        FZS M1W,#FFFF,putkap1+96,#0202,HeroClr
        FZS M1W,#FFFF,putkap1+64,#0202,HeroClr
        FZS 0,#FFFF,putkap1+32,#0202,HeroClr
        FZS 0,#FFFF,putkap1,#0202,HeroClr
        FZS 0,#FFFE,putkap2+48,#0203,HeroClr
        FZS PuKaL,#FFFE,putkap2,#0203,HeroClr

PutKapR FZM 0,#00FE,putkap2+144,#0203,HeroClr
        FZM 0,#00FE,putkap2+96,#0203,HeroClr
        FZM 0,#00FF,putkap1+192,#0202,HeroClr
        FZM M1W,#00FF,putkap1+160,#0202,HeroClr
        FZM M1W,#00FF,putkap1+128,#0202,HeroClr
        FZM M1W,#00FF,putkap1+96,#0202,HeroClr
        FZM M1W,#00FF,putkap1+64,#0202,HeroClr
        FZM 0,#00FF,putkap1+32,#0202,HeroClr
        FZM 0,#00FF,putkap1,#0202,HeroClr
        FZM 0,#00FE,putkap2+48,#0203,HeroClr
        FZM PuKaR,#00FE,putkap2,#0203,HeroClr

RasplL
        FZS FDm4,#00FE,rasplav+128,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+112,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+112,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+96,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+96,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+80,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+80,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+64,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+64,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+48,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+48,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+32,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+32,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+16,#0102,HeroClr
        FZS FDm3,#00FF,rasplav+16,#0102,HeroClr
        FZS FDm3,#00FF,rasplav,#0102,HeroClr
        FZS FDm2

RasplR  FZM FDm4,#00FE,rasplav+128,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+112,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+112,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+96,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+96,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+80,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+80,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+64,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+64,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+48,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+48,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+32,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+32,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+16,#0102,HeroClr
        FZM FDm3,#00FF,rasplav+16,#0102,HeroClr
        FZM FDm3,#00FF,rasplav,#0102,HeroClr
        FZS FDm2

FDm4    DEC (IY)
        RET 

O_TELO

        FZS 0,#FFFD,mysoul+192,#0304,HeroClr
        FZS 0,#FFFD,mysoul+192+1,#0304,HeroClr
        FZS 0,#FFFD,mysoul+192+2,#0304,HeroClr
        FZS 0,#FFFD,mysoul+96+3,#0304,HeroClr
        FZS 0,#FFFD,mysoul+96+4,#0304,HeroClr
        FZS 0,#FFFD,mysoul+96+5,#0304,HeroClr
        FZS 0,#FFFD,mysoul+0+6,#0304,HeroClr
        FZS 0,#FFFD,mysoul+0+7,#0304,HeroClr
O_TE1   FZS 0,#FFFC,mysoul+0,#0304,HeroClr
        FZS 0,#FFFC,mysoul+96,#0304,HeroClr
        FZS 0,#FFFC,mysoul+192,#0304,HeroClr
        FZS W2DIE,#FFFC,mysoul+96,#0304,HeroClr

W2DIE   DEC (IY+6)
        LD HL,O_TE1
        JP NZ,LDIYHL
        LD A,1
        LD (tpyn_1+1),A
        RET 

HerInSpidL
          FZS W2PKUP,#00FE,hernogi+72,#0103,HeroClr
          FZS W2PKUP1,#00FE,hernogi+48,#0103,HeroClr
          FZS FDm1,#00FE,hernogi+24,#0103,HeroClr
          FZS W2PKUP,#00FE,hernogi+24,#0103,HeroClr
          FZS FDm2,#00FE,hernogi,#0103,HeroClr

HerInSpidR
          FZM W2PKUP,#00FE,hernogi+72,#0103,HeroClr
          FZM W2PKUP1,#00FE,hernogi+48,#0103,HeroClr
          FZM FDm1,#00FE,hernogi+24,#0103,HeroClr
          FZM W2PKUP,#00FE,hernogi+24,#0103,HeroClr
          FZM FDm2,#00FE,hernogi,#0103,HeroClr

W2PKUP  LD A,(IY+6)
        INC A
        AND 15
W2PK1   LD (IY+6),A
        RET Z
        AND 1
        JP NZ,RepFaze
FDm2    LD HL,RepFaze
        PUSH HL
FDm3    CALL damage_sr
        DB -1

W2PKUP1 LD A,(IY+6)
        INC A
        AND 1
        JR W2PK1

AppearR FZS ApScW
        FZM 0,#00FF,app1+56,#0101,HeroClr
        FZM 0,#00FF,app1+48,#0101,HeroClr
        FZM 0,#FFFF,app1+24,#0301,HeroClr
        FZM 0,#FFFF,app1,#0301,HeroClr
        FZM 0,#FFFF,app2,#0302,HeroClr
        FZM 0,#FFFE,app3+24,#0303,HeroClr
        FZM ApScel,#00FE,app3,#0103,HeroClr

ApScel  LD HL,StandRight1
        JP LDIYHL

ApScW   LD A,(IY+6)
        INC A
        AND 15
        LD (IY+6),A
        RET Z
        JP RepFaze


