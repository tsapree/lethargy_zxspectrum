;процы фонтанов, предметов и пр.

        MAIN "",#C0

;--Fire----
OutFire2NoRune
        FZS W4Rune

        FZS 0,#00FF,fire29-12,#0204,7
        FZS 0,#00FF,fire29-9,#0204,6
        FZS 0,#00FF,fire29-6,#0204,3
        FZS 0,#00FF,fire29-3,#0204,2

OutFire2
        FZS r_flash,#00FF,fire21,#0202,2
        FZS r_flash,#00FF,fire22,#0202,2
        FZS r_flash,#00FF,fire23,#0202,2
        FZS r_flash,#00FF,fire24,#0202,2
        FZS r_flash,#00FF,fire25,#0202,2
        FZS r_flash,#00FF,fire26,#0202,2
        FZS r_flash,#00FF,fire27,#0202,2
        FZS FOutFire2,#00FF,fire28,#0202,2

FOutFire2
        LD HL,OutFire2
        JP LDIYHL

W4Rune  LD A,-2
        LD BC,#0206
        CALL check_hero
        JP NC,RepFaze
        LD E,(IY+8)
        LD D,0
        LD HL,RuneXtaken
        ADD HL,DE
        INC (HL)
        JP viz_runes

r_flash CALL RND_A
        AND 15
        CP 12
        RET NC
        RRA 
        LD D,(IY+1)
        JR C,$+5
        INC D
        INC D
        INC D
        DEC D
        ADD A,(IY)
        INC A
        LD E,A
        LD HL,FLSBUFF
        LD BC,4
r_f1    LD A,(HL)
        INC A
        JR Z,r_f2
        INC A
        JR Z,r_f2
        ADD HL,BC
        JP r_f1

r_f2    LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        LD (HL),.FLASH
        INC HL
        LD (HL),'FLASH
        RET 


OutLUp  FZS M1W,0,Lavaup1,#0201,2
        FZS M1W,0,Lavaup1+16,#0201,2
        FZS M1W,0,Lavaup1+32,#0201,2
        FZS M1W,0,Lavaup1+48,#0201,2
        FZS M1W,0,Lavaup1+64,#0201,2
        FZS M1W,0,Lavaup1+80,#0201,2
        FZS M1W,0,Lavaup1+96,#0201,2
        FZS M1W,0,Lavaup1+112,#0201,2

        FZS M1W,0,Lavau23,#0201,2
        FZS M1W,0,Lavau23+16,#0201,2
        FZS M1W,0,Lavau23+32,#0201,2
        FZS M1W,0,Lavau23+48,#0201,2
        FZS M1W,0,Lavau23+64,#0201,2
        FZS M1W,0,Lavau23+80,#0201,2
        FZS M1W,0,Lavau23+96,#0201,2
        FZS M1W,0,Lavau23+112,#0201,2

        FZS M1W,0,Lavau23,#0201,2
        FZS M1W,0,Lavau23+16,#0201,2
        FZS M1W,0,Lavau23+32,#0201,2
        FZS M1W,0,Lavau23+48,#0201,2
        FZS M1W,0,Lavau23+64,#0201,2
        FZS M1W,0,Lavau23+80,#0201,2
        FZS M1W,0,Lavau23+96,#0201,2
        FZS M1W,0,Lavau23+112,#0201,2

        FZS M1W,0,Lavaup4,#0201,2
        FZS M1W,0,Lavaup4+16,#0201,2
        FZS M1W,0,Lavaup4+32,#0201,2
        FZS M1W,0,Lavaup4+48,#0201,2
        FZS M1W,0,Lavaup4+64,#0201,2
        FZS M1W,0,Lavaup4+80,#0201,2
        FZS M1W,0,Lavaup4+96,#0201,2
        FZS FOutLUp,0,Lavaup4+112,#0201,2

FOutLUp CALL M1W
        RET NZ
        LD HL,OutLUp
        JP LDIYHL

OutLDw  FZS OLDCp,0,Lavadw,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+16,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+32,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+48,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+64,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+80,#0201,Lav_clr
        FZS OLDCp,0,Lavadw+96,#0201,Lav_clr
        FZS FOutLDw,0,Lavadw+112,#0201,Lav_clr

FOutLDw CALL OLDCp
        LD HL,OutLDw
        JP LDIYHL

OLDCp   LD A,(HERO)
        CP (IY)
        RET NZ
        LD A,(HERO+1)
        SUB (IY+1)
        JR Z,$+4
        DEC A
        RET NZ
        LD A,by_lava
        LD (HERO+9),A
        JP lavasnd
        ;RET

;--Fontan--
OutFontan
        FZS 0,#00FF,fontan1,#0202,5
        FZS 0,#00FF,fontan2,#0202,5
        FZS 0,#00FF,fontan3,#0202,5
        FZS 0,#00FF,fontan4,#0202,5
        FZS 0,#00FF,fontan5,#0202,5
        FZS 0,#00FF,fontan6,#0202,5
        FZS 0,#00FF,fontan7,#0202,5
        FZS FOutFontan,#00FF,fontan8,#0202,5

FOutFontan
        LD HL,OutFontan
        JP LDIYHL

OutRuchej
        FZS 0,#00FE,Ruchej,#0203,5
        FZS 0,#00FE,Ruchej+48,#0203,5
        FZS 0,#00FE,Ruchej+96,#0203,5
        FZS 0,#00FE,Ruchej+144,#0203,5
        FZS 0,#00FE,Ruchej+192,#0203,5
        FZS 0,#00FE,Ruchej+240,#0203,5
        FZS 0,#00FE,Ruchej+288,#0203,5
        FZS FOutRuchej,#00FE,Ruchej+336,#0203,5

FOutRuchej
        LD HL,OutRuchej
        JP LDIYHL

OutDropWater
        FZS wtODWx
        FZS 0,0,drpbgn1+3,#0101,5
        FZS wtODW1,0,drpbgn1+2,#0101,5
        FZS 0,0,drpbgn1+1,#0101,5
        FZS 0,0,drpbgn1,#0101,5
        FZS 0,0,drp1+8,#0101,5
lpODW2  FZS vrODW1,0,drp1+6,#0101,5
        FZS lpODW1,0,drp1+2,#0102,5
enODW1  FZS kapsfx,0,drpend1,#0101,5
        FZS bgODW1,0,drpend2,#0101,5

vrODW1  CALL verdwnm
        RET Z
        LD HL,enODW1
        JP LDIYHL

lpODW1  INC (IY)
        CALL WlkAdr
        LD HL,lpODW2
        JP LDIYHL

bgODW1  LD A,(IY+6)
        LD (IY),A
        CALL WlkAdr

bgODWb  LD C,15
        CALL bgODWf
        LD HL,OutDropWater
        JP LDIYHL

bgODWf  CALL RND_A
        AND #1F
        ADD A,C
        LD (IY+6),A
        RET 

wtODWx  LD A,(IY+6)
        OR A
        LD C,5
        JP Z,bgODWf
        DEC (IY+6)
        JP RepFaze

wtODW1  LD A,(IY+6)
        OR A
        JR Z,wtODW2
        DEC (IY+6)
        JP RepFaze

wtODW2  LD A,(IY)
        LD (IY+6),A
        RET 

;---
OutKapkan
        FZS wtOKp
        FZS 0,0,kapkan2,#0201,7
        FZS wtCKp,0,kapkan4,#0201,7
        FZS 0,0,kapkan3,#0201,7
        FZS 0,0,kapkan2,#0201,7
        FZS enOKp,0,kapkan1,#0201,7

wtOKp   CALL cpkpc
        JP Z,nozhsnd
wtCKp1  LD (IY+6),Kap_Wait4Close
wtCKp2  JP RepFaze

wtCKp   CALL cpkpc
        JR Z,wtCKp1
        DEC (IY+6)
        RET Z
        JR wtCKp2

enOKp   LD HL,OutKapkan
        JP LDIYHL

cpkpc   LD A,(HERO)
        CP (IY)
        RET NZ
        LD A,(HERO+1)
        SUB (IY+1)
        JR Z,stKpdmg
        DEC A
        RET NZ
stKpdmg CALL damage_sr  ;повреждения от капкана
        DB dmg_kapkan

FLASH   FZR 0,flashs,#41
        FZR 0,flashs+8,#42
        FZR 0,flashs+16,#43
        FZR 0,flashs+24,#44
        FZR 0,flashs+32,#45
        FZR 0,flashs+40,#46
        FZR EObj,flashs+48,#47

; двуголовые мы :)

thstpL
        FZS VthsL,#FE,_2heads,#0103,THClr
        FZS V2dead,#FFFE,_2heads+24,#0203,THClr
        FZS 0,#FFFE,_2heads+72,#0203,THClr
        FZS HdGL,#FFFE,_2heads+120,#0203,THClr
        FZS 0,#FE,_2heads+168,#0203,THClr
        FZS V2dead,#FE,_2heads+216,#0203,THClr
        FZS V2dead,#FE,_2heads+264,#0203,THClr
        FZS EthsL,#FE,_2heads+312,#0203,THClr

VthsL   CALL V2dead1
        CALL VHeY
        JR NC,VtL1
        CALL VHeR
        JR NC,EthsR
        INC A
        JR NZ,VtL1
        LD HL,Ou2HdFL
        JP LDIYHL

VtL1    LD DE,WLKLEN-1
        CALL a_exm4bl
        CP 8
        RET Z
EthsR   LD HL,thstpR
        JP LDIYHL

VthsR   CALL V2dead1
        CALL VHeY
        JR NC,VtR1
        CALL VHeR
        JR Z,VtR1
        JR C,EthsL
        CP 4
        JR C,VtR2
        CALL RND_A
        AND #C
        JR NZ,VtR1
VtR2    LD HL,Ou2HdFR
        JP LDIYHL

VtR1    LD DE,WLKLEN+1
        CALL a_exm4bl
        CP 8
        RET Z
EthsL   LD HL,thstpL
        JP LDIYHL

VHeY    LD A,(HERO)
        SUB (IY)
        INC A
        CP 3
        RET 

VHeR    LD A,(HERO+1)
        SUB (IY+1)
        RET 

thstpR  FZS VthsR,#FE,_2heads,#0103,THClr
        FZS 0,#00FE,_2heads+312,#0203,THClr
        FZS 0,#00FE,_2heads+264,#0203,THClr
        FZS HdGR,#00FE,_2heads+216,#0203,THClr
        FZS 0,#FFFE,_2heads+168,#0203,THClr
        FZS 0,#FFFE,_2heads+120,#0203,THClr
        FZS V2dead,#FFFE,_2heads+72,#0203,THClr
        FZS EthsR,#FFFE,_2heads+24,#0203,THClr

Ou2Hdead
        FZS 0,#00FE,hed2ead,#0203,7
        FZS 0,#00FE,hed2ead+48,#0203,7
        FZS 0,#00FE,hed2ead+96,#0203,7
        FZS DeadMonster,#00FE,hed2ead+144,#0203,7
        FZS RepFze,#00FE,hed2ead+192,#0203,7

V2dead1 CALL V2dead
        RET C
        POP HL
        RET 

V2deadS
V2dead  LD A,(IY+9)
        CP 3            ;умирает после 3х выстрелов
        RET C
        LD HL,Ou2Hdead
        JP LDIYHL

Ou2HdFL ;удар головой
;       FZS 0,#FFFE,hed2fgt,#0203,7
        FZS O2HDBit,#FFFE,hed2fgt+48,#0203,7
        FZS 0,#FFFE,hed2fgt+96,#0203,7
        FZS 0,#FFFE,hed2fgt+48,#0203,7
        FZS EthsL,#FFFE,hed2fgt,#0203,7

O2HDBit
        CALL hlftsnd
        CALL damage_sr
        DB dmg_bit

Ou2HdFR ;бросание ножей
        FZS knifsnd,#FE,hed2fgt+144,#0203,7
        FZS 0,#FE,hed2fgt+192,#0203,7
        FZS V2deadS,#FE,hed2fgt+240,#0203,7
        FZS 0,#FE,hed2fgt+288,#0203,7
        FZS EO2HFR,#FE,hed2fgt+336,#0203,7

EO2HFR
        LD B,(IY+1)
        LD C,(IY)
        DEC C
        INC B
        LD HL,OutNdlzD
        CALL flybfy
        LD HL,OutNdlzM
        CALL flybfy
        INC B
        LD HL,OutNdlzU
        CALL flybfy
        JP EthsR

;ножи летят
OutNdlzU ;FZS VPopadN,0,Nedlz+4,#101,7
        ;FZS NdlRgt,0,Nedlz+12,#101,7
        FZS VPopadN,0,Nedlz+20,#101,7
        FZS NdlRgt,0,Nedlz+28,#101,7
        FZS EONdl,0,Nedlz+36,#101,7

OutNdlzM ;FZS VPopadN,0,Nedlz+2,#101,7
        FZS NdlRgt,0,Nedlz+10,#101,7
        FZS VPopadN,0,Nedlz+18,#101,7
        FZS NdlRgt,0,Nedlz+26,#101,7
        FZS EONdl,0,Nedlz+34,#101,7

OutNdlzD FZS VPopadN,0,Nedlz,#101,7
        FZS NdlRgt,0,Nedlz+8,#101,7
        FZS VPopadN,0,Nedlz+16,#101,7
        FZS NdlRgt,0,Nedlz+24,#101,7
        FZS EONdl,0,Nedlz+32,#101,7

EONdl   CALL RepFaze

NdlRgt  INC (IY+1)
        CALL WlkAdr
        LD A,(HL)
        OR A
        JP NZ,KillFly   ;врезалась

VPopadN ;проверка на попадание
        LD DE,#0002
        LD BC,#0103
        CALL TstZoneH
        RET NC
        CALL KillFly
        CALL damage_sr
        DB dmg_strelka

;Mummy
muR
        FZS FmR1,#FFFE,mumR2,#0303,mumclr
        FZS FmuR2,#FFFE,mumR2+#48,#0303,mumclr
        FZS FmR1,#FFFE,mumR1,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#30,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#60,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#90,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#C0,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#F0,#0303,mumclr
        FZS Fm1,#FFFE,mumR1+#138,#0303,mumclr
        FZS FmuR2,#FFFE,mumR1+#180,#0303,mumclr
        FZS FmR2,#FEFE,mumR1+#1C8,#0303,mumclr
        FZS Fm1,#FEFE,mumR1+#210,#0303,mumclr
        FZS Fm1,#FFFE,mumR1+#258,#0203,mumclr
        FZS Fm1,#FFFE,mumR1+#288,#0203,mumclr
        FZS FmuR1,#FFFE,mumR1+#2B8,#0203,mumclr

muD     FZS DeadMonster
        FZS RepFaze

FmuR2   LD A,(IY+9)
        OR A
        JR NZ,Fm1
        CALL M1W
        RET NZ
        CALL HdGR
        LD DE,WLKLEN+1
        CALL a_exm4bl
        CP 8
        RET Z
        LD HL,muL
        JP LDIYHL

FmL1    LD HL,mudL1
        JR FmL21
FmL2    LD HL,mudL2
        JR FmL21
FmR1    LD HL,mudR1
        JR FmL21
FmR2    LD HL,mudR2
FmL21   LD (Fmde1+1),HL
Fm1     LD A,(IY+9)
        SUB holdmumm
        JR NC,Fm11
        CALL M1W
mumtdmg LD DE,#0002 ;?
        LD BC,#0304 ;?
        CALL TstZoneH
        RET NC
        CALL damage_sr
        DB dmg_mummy

Fm11    JP Z,RepFaze
        DEC A
        JP NZ,M1W
Fmde1   LD HL,muD
        JP LDIYHL

FmuR1   CALL M1W
        RET NZ
FmuR    LD HL,muR
        JP LDIYHL

muL
        FZS FmL1,#FEFE,mumL2+#48,#0303,mumclr
        FZS FmuL2,#FEFE,mumL2,#0303,mumclr
        FZS FmL1,#FFFE,mumL1+#2B8,#0203,mumclr
        FZS Fm1,#FFFE,mumL1+#288,#0203,mumclr
        FZS Fm1,#FFFE,mumL1+#258,#0203,mumclr
        FZS Fm1,#FFFE,mumL1+#228,#0203,mumclr
        FZS Fm1,#FFFE,mumL1+#1F8,#0203,mumclr
        FZS Fm1,#FEFE,mumL1+#1B0,#0303,mumclr
        FZS Fm1,#FEFE,mumL1+#168,#0303,mumclr
        FZS FmuL2,#FEFE,mumL1+#120,#0303,mumclr
        FZS FmL2,#FFFE,mumL1+#D8,#0303,mumclr
        FZS Fm1,#FFFE,mumL1+#90,#0303,mumclr
        FZS Fm1,#FFFE,mumL1+#60,#0203,mumclr
        FZS Fm1,#FFFE,mumL1+#30,#0203,mumclr
        FZS FmuL1,#FFFE,mumL1,#0203,mumclr

mudL1   FZS 0,#FFFE,mumLd,#0203,mumclr
        FZS muD1,#FFFE,mumLd+120,#0303,mumclr

mudL2   FZS 0,#FFFE,mumLd+48,#0303,mumclr
        FZS muD1,#FFFE,mumLd+120,#0303,mumclr

mudR1   FZS 0,#FFFE,mumRd+144,#0203,mumclr
        FZS muD1,#FEFE,mumRd,#0303,mumclr

mudR2   FZS 0,#FEFE,mumRd+72,#0303,mumclr
        FZS muD1,#FEFE,mumRd,#0303,mumclr

muD1    LD HL,muD
        JP LDIYHL

FmuL2   LD A,(IY+9)
        OR A
        JP NZ,Fm1
        CALL M1W
        RET NZ
        CALL HdGL
        LD DE,WLKLEN-1
        CALL a_exm4bl
        CP 8
        RET Z
        LD HL,muR
        JP LDIYHL

FmuL1   CALL M1W
        RET NZ
FmuL    LD HL,muL
        JP LDIYHL

;--- П-п-р-ивидение!

SPEED=1

        IF SPEED-1
gh2up2
gh2up   FZS g2utst,#00FE,ghst2ud,#304,7
        FZS g2tdmg,#00FE,ghst2ud-6,#304,7
        FZS g2tdmg,#00FE,ghst2ud-4,#304,7
        FZS g2ue,#00FE,ghst2ud-2,#304,7
        ELSE 
gh2up2
gh2up   FZS g2utst,#00FE,ghst2ud,#304,7
        FZS g2ue,#00FE,ghst2ud-4,#304,7
        ENDIF 

g2utst  LD A,(IY+6)
        DEC A
        JR Z,eg2ud
        LD (IY+6),A
        CALL g2vfire
        CALL WlkAdr
        LD DE,-(3*WLKLEN)
        CALL exm2bl
        LD HL,gh2dw2
        JP NZ,LDIYHL
        CALL g2tdmg
        DEC (IY)
        JP WlkAdr

g2ue
        CALL g2tdmg
        LD HL,gh2up
        JP LDIYHL

g2tdmg  LD DE,#0202
        LD BC,#0305
        CALL TstZoneH
        RET NC
        CALL damage_sr
        DB dmg_ghost2

        IF SPEED-1
gh2dw2
gh2dw   FZS g2dtst,#00FE,ghst2ud+96,#304,7
        FZS g2tdmg,#00FD,ghst2ud+94,#304,7
        FZS g2tdmg,#00FD,ghst2ud+92,#304,7
        FZS g2de,#00FD,ghst2ud+90,#304,7
        ELSE 
gh2dw2
gh2dw   FZS g2dtst,#00FE,ghst2ud+96,#304,7
        FZS g2de,#00FD,ghst2ud+92,#304,7
        ENDIF 

g2dtst  LD A,(IY+6)
        DEC A
        LD (IY+6),A
eg2ud   LD HL,gh2ud1
        JP Z,LDIYHL
        CALL g2vfire
        CALL WlkAdr
        LD DE,2*WLKLEN
        CALL exm2bl
        LD HL,gh2up2
        JP NZ,LDIYHL
        CALL g2tdmg
        INC (IY)
        JP WlkAdr

g2de    CALL g2tdmg
        LD HL,gh2dw
        JP LDIYHL

ghost   FZS ghdilp
gh2wbap FZS GWBefA
gh2ap   FZS 0,#00FE,ghst2ap,#303,7
        FZS 0,#00FE,ghst2ap+72,#303,7
        FZS 0,#00FE,ghst2ap+144,#303,7
        FZS 0,#00FE,ghst2ap+216,#303,7
        FZS 0,#00FE,ghst2ap+288,#303,7
        FZS 0,#00FE,ghst2ap+360,#303,7
        FZS 0,#00FE,ghst2ap+432,#303,7
        FZS 0,#00FE,ghst2ap+504,#303,7

        FZS g2ud1,#00FE,ghst2,#303,7
gh2ud1  FZS g2ud,#00FE,ghst2,#303,7

gh2di   FZS 0,#00FE,ghst2,#303,7

        FZS 0,#00FE,ghst2di,#303,7
        FZS 0,#00FE,ghst2di+72,#303,7
        FZS 0,#00FE,ghst2di+144,#303,7
        FZS 0,#00FE,ghst2di+216,#303,7
        FZS 0,#00FE,ghst2di+288,#303,7
        FZS 0,#00FE,ghst2di+360,#303,7
        FZS ghdilp,#00FE,ghst2di+432,#303,7

ghdilp  CALL RND_A
        AND %011110
        ADD A,25
        LD (IY+6),A
        LD HL,gh2wbap
        JP LDIYHL

GWBefA  LD A,(IY+6)
        OR A
        RET Z
        DEC A
        LD (IY+6),A
        JP RepFaze

g2ud1   CALL RND_A
        AND 30
        ADD A,15
        LD (IY+6),A
        LD HL,gh2up2
        JP LDIYHL

g2ud    CALL RND_A
        AND 15
        CP 12
        RET NC
        LD C,(IY+6)
        RLCA 
        ADD A,15
        LD (IY+6),A
        DEC C
        LD HL,gh2up2
        JR NZ,$+5
        LD HL,gh2dw2
        JP LDIYHL

g2vfire LD A,(HERO)
        ADD A,2
        SUB (IY)
        RET C
        CP 5
        RET NC
        ;гхост на уровне героя (+/- 2 знакоместа)
        CALL RND_A
        AND 15
        CP 13
        RET C
        LD HL,GHFL
        LD BC,#FF00
        CALL admnst
        LD (IX+6),8
        LD HL,GHFR
        LD BC,#0200
        CALL admnst
        LD (IX+6),8
        RET 

admnst  LD IX,MONSTRS
        LD DE,10
admnst1 LD A,(IX)
        INC A
        JR Z,admnst2
        INC A
        JR Z,admnst2
        ADD IX,DE
        JR admnst1

admnst2 LD A,(IY)
        ADD A,C
        LD (IX),A
        LD A,(IY+1)
        ADD A,B
        LD (IX+1),A
        LD (IX+2),L
        LD (IX+3),H
        LD (IX+7),#FF   ;не монстр.
        RET 



GHFL    FZS GHtdmg,#00FE,ghfl1,#203,7
        FZS GHL,#00FE,ghfl2,#203,7
        FZS GHtdmg,#00FE,ghfl3,#303,7
        FZS GHL,#00FE,ghfl4,#203,7
GHFL1   FZS GHtdmg,#00FE,ghfl5,#203,7
        FZS GHFLSR,#00FE,ghfl6,#203,7
        FZS GHtdmg,#00FE,ghflof1,#103,7
        FZS GHFLE,#00FE,ghflof2,#103,7

GHL     DEC (IY+1)
        RET 

GHFLE   LD (IY),#FE
        RET 

GHtdmg  LD DE,#0002
        LD BC,#0105
        CALL TstZoneH
        RET NC
        CALL damage_sr
        DB dmg_ghost2fire

GHFLSR
GHFLSR1 LD A,(IY+6)
        DEC A
        LD (IY+6),A
        RET Z
        DEC (IY+1)
        LD HL,GHFL1
        JP LDIYHL

GHFR    FZS 0,#00FE,ghfr1,#203,7
        FZS GHtdmg,#00FE,ghfr2,#203,7
        FZS GHR,#00FE,ghfr3,#303,7
        FZS GHR,#00FE,ghfr4,#203,7
GHFR1   FZS GHtdmg,#00FE,ghfr5,#203,7
        FZS GHFRSR,#00FE,ghfr6,#203,7
        FZS GHtdmg,#00FE,ghfrof1,#103,7
        FZS GHFLE,#00FE,ghfrof2,#103,7

GHR     INC (IY+1)
        RET 

GHFRSR  INC (IY+1)
        LD A,(IY+6)
        DEC A
        LD (IY+6),A
        RET Z
        LD HL,GHFR1
        JP LDIYHL

;--- WedIMa

wedfL   FZS Wb8L
        FZS gwl,#FE,wedl1,#203,7
        FZS DmgWedL,#FE,wedl1+48,#303,7
        FZS DmgWedL,#FE,wedl1+120,#303,7
        FZS DmgWedL,#FE,wedl1+192,#303,7
        FZS gwl,#FE,wedl1+264,#203,7
wedL1   FZS DmgWedL,#FE,wedl1+312,#303,7
        FZS gwle,#FE,wedl1+384,#303,7
        FZS DmgWedL,#FE,wedl1+456,#303,7
        FZS gwlp,#FE,wedl1+528,#203,7

wedLe   FZS DmgWedL,#FE,wedl2,#303,7
        FZS gwl,#FE,wedl2+72,#203,7
        FZS 0,#FE,wedl2+120,#303,7
        FZS 0,#FE,wedl2+192,#303,7
        FZS gwlen,#FE,wedl2+264,#203,7

Wb8L    CALL Wb8
        ADD A,C
        INC A
        LD (IY+1),A
        RET 

Wb8R    CALL Wb8
        SUB C
        NEG 
        LD (IY+1),A
        RET 

Wb8     DEC (IY+8)
        LD A,(IY+8)
        OR A
        POP HL
        JP NZ,RepFaze
        PUSH HL
        LD A,(IY+1)
        LD (IY+8),A
        LD C,A
        CALL RND_A
        AND 3
        SUB 2
        ADD A,C
        LD C,A
        CALL RND_A
        AND 3
        ADD A,3
        LD (IY+6),A
        RRA 
        RET 

gwlen   LD A,(IY+8)
        LD (IY+1),A
        CALL wed_lx
        LD HL,wedfR
        JP LDIYHL

wed_lx  PUSH AF
        CALL RND_A
        AND #3F
        ADD A,#20
        LD (IY+8),A
        POP AF
        RET 

gwlp    LD HL,wedL1
        CALL LDIYHL
gwl     DEC (IY+1)
        CALL WlkAdr ;?
DmgWedL;
DmgWed  LD DE,#0102
        LD BC,#0203
        CALL TstZoneH
        RET NC
        CALL damage_sr
        DB dmg_wedima

wedfR   FZS Wb8R
        FZS DmgWed,#FE,wedr1+528,#203,7
        FZS DmgWed,#FE,wedr1+456,#303,7
        FZS DmgWed,#FE,wedr1+384,#303,7
        FZS gwr,#FE,wedr1+312,#303,7
        FZS DmgWed,#FE,wedr1+264,#203,7
wedR1   FZS DmgWed,#FE,wedr1+192,#303,7
        FZS gwre,#FE,wedr1+120,#303,7
        FZS gwr,#FE,wedr1+48,#303,7
        FZS gwrp,#FE,wedr1,#203,7

wedRe   FZS gwr,#FE,wedr2+240,#303,7
        FZS DmgWed,#FE,wedr2+192,#203,7
        FZS DmgWed,#FE,wedr2+120,#303,7
        FZS gwr,#FE,wedr2+48,#303,7
        FZS gwren,#FE,wedr2,#203,7

gwren   LD A,(IY+8)
        LD (IY+1),A
        CALL wed_lx
        LD HL,wedfL
        JP LDIYHL

gwre    LD HL,wedRe
        JR gwle+3

gwle    LD HL,wedLe
        LD A,(IY+6)
        DEC A
        LD (IY+6),A
        RET NZ
        JP LDIYHL

gwrp    LD HL,wedR1
        CALL LDIYHL
        JP DmgWed

gwr     INC (IY+1)
        CALL WlkAdr
        JP DmgWed



