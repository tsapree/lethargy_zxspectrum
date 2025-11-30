;процы фонтанов, предметов и пр.

        MAIN "",#C0

;Big Monsters!!!
OutLeaf
        FZS OLeafWH,#FF,leaf1,#0702,4
        FZS 0,#FE,leaf2,#0703,4
        FZS 0,#FD,leaf3,#0704,4
        FZS 0,0,leaf47d,#0701,4
         FZSP #FC,leaf4u,#0704,4
OutLeaf1 FZS NHerSr,0,leaf47d,#0701,4
         FZSP #02FC,leaf5u,#0304,4
        FZS 0,0,leaf47d,#0701,4
         FZSP #02FC,leaf6u,#0304,4
        FZS FOutLeaf1,0,leaf47d,#0701,4
         FZSP #02FC,leaf7u,#0304,4
        FZS FOutLeaf2,0,leaf47d,#0701,4
         FZSP #02FC,leaf6u,#0304,4
OutLeaf2 FZS M1W,0,leaf47d,#0701,4
         FZSP #02FC,leaf5u,#0304,4
        FZS M1W,0,leaf47d,#0701,4
         FZSP #FC,leaf4u,#0704,4
        FZS M1W,#FD,leaf3,#0704,4
        FZS 0,#FE,leaf2,#0703,4
        FZS FOutLeaf,#FE,leaf2,#0703,4

OLeafWH LD HL,RepFaze
        PUSH HL
        CALL OLeWH1
        RET NZ
        POP HL
        CALL stndmode
        JP lavasnd

FullDmg CALL damage_sr
        DB -32

OLeWH1  LD A,(HERO)
        INC A
        INC A
        CP (IY)
        RET NZ
        LD A,(HERO+1)
        SUB 3
        CP (IY+1)
        RET 

FOutLeaf LD HL,OutLeaf
        JP LDIYHL

FOuLea1 LD HL,OutLeaf2
        LD (IY-10),#FE  ;! сделать цветок "прозрачным"
        JP LDIYHL

FOutLeaf1 LD HL,FOuLea1
        PUSH HL
        CALL OLeWH1
        RET NZ
        POP HL
        RET 

FOutLeaf2 LD HL,OutLeaf1
        JP LDIYHL

NHerSr  CALL NoHeroSr
        CALL damage_sr
        DB -7



;при-при-п-привидение!!!!
OutGhost
        FZS M1W,#00FB,ghost1,#0604,7
         FZSP #02FF,ghost2,#0302,7
        FZS 0,#00FB,ghost1+192,#0604,7
         FZSP #02FF,ghost2+48,#0302,7
        FZS 0,#00FB,ghost1+384,#0604,7
         FZSP #02FF,ghost2+96,#0302,7
        FZS 0,#00FB,ghost1+576,#0604,7
         FZSP #02FF,ghost2+144,#0302,7
        FZS M1W,#00FB,ghost1+768,#0604,7
         FZSP #02FF,ghost2+192,#0302,7
        FZS 0,#00FB,ghost1+576,#0604,7
         FZSP #02FF,ghost2+144,#0302,7
        FZS 0,#00FB,ghost1+384,#0604,7
         FZSP #02FF,ghost2+96,#0302,7
        FZS FOGh1,#00FB,ghost1+192,#0604,7
         FZSP #02FF,ghost2+48,#0302,7

FOGh1   LD HL,OutGhost
        JP LDIYHL

BegShit1 FZS W4RSh1
        FZS M1W,#00FE,Shit1,#0103,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit1,#0103,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit1,#0103,ShuClr
        FZS ClrIY9

;шупальца
OutShit1
        FZS Sh1sr,#00FE,Shit1,#0103,ShuClr
        FZS Sh1sr,#00FE,Shit1+24,#0203,ShuClr
        FZS Sh1sr,#00FE,Shit1+72,#0203,ShuClr
        FZS Sh1sr,#00FE,Shit1+120,#0203,ShuClr
        FZS Sh1sr,#00FE,Shit1+168,#0203,ShuClr
        FZS Sh1sr,#00FE,Shit1+216,#0103,ShuClr
        FZS Sh1sr,#00FE,Shit1+240,#0103,ShuClr
        FZS FOSh1,#00FE,Shit1+264,#0103,ShuClr

W4RSh1  DEC (IY+6)
        LD A,(IY+6)
        OR A
        JP NZ,RepFaze
        RET 

ClrIY9  LD (IY+9),0
        RET 

Sh4sr   LD HL,BegShit4
        JR Sh1sr+3
Sh3sr   LD HL,BegShit3
        JR Sh1sr+3
Sh2sr   LD HL,BegShit2
        JR Sh1sr+3
Sh1sr   LD HL,BegShit1
        LD IX,HERO+1
        LD A,(IY+1)
        SUB (IX)
        JR Z,ShDmg
        INC A
        JR Z,ShDmg
        LD A,(IY+9)
        OR A
        JP Z,M1W
        LD (IY+9),0
        LD (IY+6),TimeNoShit
        CALL LDIYHL
        JP xpehbsnd

FOSh1   CALL M1W
        RET NZ
FOSh11  LD HL,OutShit1
        JP LDIYHL

ShDmg   CALL damage_sr
        DB dmg_shit

BegShit2 FZS W4RSh1
        FZS M1W,#00FE,Shit2,#0203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit2,#0203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit2,#0203,ShuClr
        FZS ClrIY9

OutShit2 FZS Sh2sr,#00FE,Shit2,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+48,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+96,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+144,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+192,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+240,#0203,ShuClr
        FZS Sh2sr,#00FE,Shit2+288,#0203,ShuClr
        FZS FOSh2,#00FE,Shit2+336,#0203,ShuClr

FOSh2   CALL M1W
        RET NZ
FOSh21  LD HL,OutShit2
        JP LDIYHL

BegShit3 FZS W4RSh1
        FZS M1W,#00FE,Shit3,#0203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit3,#0203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit3,#0203,ShuClr
        FZS ClrIY9

OutShit3 FZS Sh3sr,#00FE,Shit3,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+48,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+96,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+144,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+192,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+240,#0203,ShuClr
        FZS Sh3sr,#00FE,Shit3+288,#0203,ShuClr
        FZS FOSh3,#00FE,Shit3+336,#0203,ShuClr

FOSh3   CALL M1W
        RET NZ
FOSh31  LD HL,OutShit3
        JP LDIYHL

BegShit4 FZS W4RSh1
        FZS M1W,#00FE,Shit4,#203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit4,#203,ShuClr
        FZS M1W
        FZS M1W,#00FE,Shit4,#203,ShuClr
        FZS ClrIY9

OutShit4 FZS Sh4sr,#FE,Shit4,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+48,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+96,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+144,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+192,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+240,#203,ShuClr
        FZS Sh4sr,#FE,Shit4+288,#203,ShuClr
        FZS FOSh4,#FE,Shit4+336,#203,ShuClr

FOSh4   CALL M1W
        RET NZ
FOSh41  LD HL,OutShit4
        JP LDIYHL

;Паук

OutUppSpd FZS RepFaze,#00FD,wweb,#0302,7

OutSpiderW
        FZS OSW4hero,#00FD,Spider+480,#0304,7
        FZS 0,#00FE,Spider+576,#0304,7
        FZS 0,#00FF,Spider+1,#0304,7

OutSpider FZS M1W,#00FF,Spider,#0304,7
        FZS M1W,#00FF,Spider+96,#0304,7
        FZS M1W,#00FF,Spider+192,#0304,7
        FZS M1W,#00FF,Spider+288,#0304,7
        FZS M1W,#00FF,Spider+384,#0304,7
        FZS M1W,#00FF,Spider+480,#0304,7
        FZS FOutSpid1,#00FF,Spider+576,#0304,7

FOutSpid1 CALL M1W
        RET NZ

FOutSpider LD HL,OutSpider
        JP LDIYHL

OSW4hero
        LD A,(HERO+1)
        DEC A
        CP (IY+1)
        JP Z,OSW42
        SBC A,A
        LD (OSW41+1),A
        JP RepFaze

OSW42   LD A,(HERO)
        SUB 3
        CP (IY)
        JR C,OSW41
        LD A,(RuneXtaken+6-1)
        AND #80
        JP Z,RepFaze

OSW41   LD A,0
        OR A
        LD HL,HerInSpidL
        JR Z,$+5
        LD HL,HerInSpidR
        LD (HERO+2),HL
        LD A,(IY)
        ADD A,3
        LD (HERO),A
        LD A,#FF
        LD (noinvent+1),A
FDm1    LD A,1
        LD (tpyn_1+1),A
        RET 

;---
OSetPut
        FZS OSetPsr

OSetPsr LD A,#FE
OSetP1  LD (OORLD),A
        JP RepFaze

OSetOr
        FZS OSetOsr

OSetOsr LD A,#28
        JR OSetP1


;тифон
OTycSleep
        FZS RepFaze,#00FD,tydead3,#0904,0
;       FZS M1W,#00FC,tydead2,#0905,0
;       FZS M1W,#00FB,tydead1,#0906,0

OutTycBody
        FZS TycPrep,#02FA,ty_1,#0503,4
         FZSP #00FD,ty_2,#0603,4
         FZSP 0,ty_3,#0801,4

TycPrep LD A,(IY+6)
        OR A
        JP NZ,RepFaze
        LD HL,OutTycHead
        LD BC,0
        CALL admnst
        LD (IX+6),0
        LD HL,OutTycTail
        LD BC,0
        CALL admnst
        INC (IY+6)
        CALL WlkAdr
        LD C,9
        CALL BlkWay
        JP RepFaze

OutTycHead
        FZS OTHw,#07FA,tyh_,#0203,4
        FZS M1W,#07FA,tyh_+48,#0203,4
        FZS OTHe,#07FA,tyh_+96,#0203,4

OTHw    LD A,(IY+6)
        OR A
        JR Z,OTHw1
        DEC (IY+6)
        RET Z
        JP RepFaze

OTHw1   CALL RND_A
        RLCA 
        AND 15
        CP 6
        JR NC,$+3
        ADD A,A
        LD (IY+6),A
        JP RepFaze

OTHe    CALL M1W
        RET NZ
        CALL OTHe0
FOTHe   LD HL,OutTycHead
        JP LDIYHL

OTHe0   CALL RND_A
        AND 15
        LD B,1
        SUB 9
        JR C,OTHe1
        INC B
OTHe1   PUSH BC
        LD HL,OFireT
        LD BC,#07FB
        CALL admnst
        POP AF
        LD (IX+6),A
        JP fbal2snd

OutTycTail
        FZS M1W,#00FA,tyt_+192,#0203,4
        FZS M1W,#00FA,tyt_+144,#0203,4
        FZS M1W,#00FA,tyt_+96,#0203,4
        FZS M1W,#00FA,tyt_+48,#0203,4
        FZS M1W,#00FA,tyt_,#0203,4
        FZS M1W,#00FA,tyt_,#0203,4
        FZS M1W,#00FA,tyt_+48,#0203,4
        FZS M1W,#00FA,tyt_+96,#0203,4
        FZS M1W,#00FA,tyt_+144,#0203,4
        FZS OTTa,#00FA,tyt_+192,#0203,4
OTTa    CALL M1W
        RET NZ
FOTTa   LD HL,OutTycTail
        JP LDIYHL

OFireT  FZS OFi3sr,0,FireF,#0303,0
        FZS OFi2sr,0,Fires1,#0202,0
        FZS OFi3sr,0,Fire1,#0303,0
        FZS OFi2sr,0,Fires2,#0202,0
        FZS OFi3sr,0,Fire2,#0303,0
        FZS OFi2sr,0,Fires1,#0202,0
        FZS OFi3sr,0,Fire3,#0303,0
        FZS OFi2sr,0,Fires2,#0202,0
        FZS OFi3sr,0,Fire4,#0303,0
        FZS OFi2sr,0,Fires1,#0202,0
        FZS OFi3sr,0,Fire1,#0303,0
        FZS FOFireT

FOFireT LD (IY),#FE
        RET 

OFi3sr  CALL OFi3s1
        INC (IY+1)
        INC (IY)
        RET 

OFi3s1  LD DE,#0205
        LD BC,#0306
        CALL TstZoneH
        RET NC
OFi3s2  CALL damage_sr
        DB dmg_typhon

OFi2s1  LD DE,#0104
        LD BC,#0205
        CALL TstZoneH
        RET NC
        JR OFi3s2

OFi2sr  CALL OFi2s1
        LD A,(IY+6)
        DEC A
        RET Z
        INC (IY+1)
        RET 


;тученька :)
OutTy4KA
        FZS RepFaze,#00FF,tu4ka,#0A02,7

OutLight
        FZS Wmolniq                             ;3+
        FZS 0,#FFFC,molnii,#0405,molniq1        ;8+
         FZSP #FEFB,Empty,#0701,uppmolniq       ;5+
         FZSP #03FA,Empty,#0101,uppmolniq       ;5=21
        FZS Wmolniq
        FZS 0,#FFFC,molnii+160,#0505,molniq2
         FZSP #00FB,Empty,#0601,uppmolniq
         FZSP #03FA,Empty,#0201,uppmolniq
        FZS Wmolniq
        FZS 0,#00FC,molnii+360,#0405,molniq1
         FZSP #FFFB,Empty,#0601,uppmolniq
         FZSP #00FA,Empty,#0301,uppmolniq
        FZS Wmolniq
        FZS 0,(#FFFC+#100),molnii+160,#0505,molniq2
         FZSP (#00FB+#100),Empty,#0601,uppmolniq
         FZSP (#03FA+#100),Empty,#0201,uppmolniq
        FZS Wmolniq
        FZS 0,(#FFFC+#200),molnii,#0405,molniq1
         FZSP (#FEFB+#200),Empty,#0701,uppmolniq
         FZSP (#03FA+#200),Empty,#0101,uppmolniq
        FZS Wmolniq
        FZS 0,(#FFFC+#200),molnii+160,#0505,molniq2
         FZSP (#00FB+#100),Empty,#0601,uppmolniq
         FZSP (#03FA+#100),Empty,#0201,uppmolniq
        FZS Wmolniq
        FZS 0,(#00FC+#200),molnii+360,#0405,molniq1
         FZSP (#FFFB+#FF00),Empty,#0601,uppmolniq
         FZSP (#00FA+#FF00),Empty,#0301,uppmolniq
        FZS Wmolniq
        FZS FOLigh,(#FFFC+#300),molnii+160,#0505,molniq2
         FZSP (#00FB+#FD00),Empty,#0601,uppmolniq
         FZSP (#03FA+#FF00),Empty,#0201,uppmolniq

FOLigh  LD HL,OutLight
        JP LDIYHL

Wmolniq DEC (IY+6)
        LD A,(IY+6)
        RET Z
        DEC A
        RET Z
        INC A
        INC A
        JP NZ,RepFaze
        LD A,(HERO+1)
        SUB (IY+1)
        JR C,Wmlq1
        CP 6
        JR NC,Wmlq1
        PUSH AF
        LD A,by_ty4ka
        LD (HERO+9),A
        CALL RND_A
        RLCA 
        AND 3
        POP BC
        ADD A,B
        DEC A
        LD (IY+6),2
        JR Wmlq2

Wmlq1   CALL RND_A
        RLCA 
        RLCA 
        RLCA 
        AND 15
        CP 10
        JR C,$+4
        SUB 10
        ADD A,2
        LD (IY+6),A
        CALL RND_A
        RLCA 
Wmlq2   AND 7
        LD L,A
        LD E,A
        ADD A,A
        ADD A,A
        ADD A,L
        LD L,A
        LD H,0
        LD D,H
        ADD HL,HL
        ADD HL,HL
        ADD HL,DE
        LD DE,OutLight
        ADD HL,DE
        JP LDIYHL

Outlights
        FZS VOli,0,mlights,#0201,7
        FZS lighsfx,0,mlights+16,#0201,7
        FZS VOli,0,mlights+32,#0201,7
        FZS FOli,0,mlights+48,#0201,7
        FZS VOli,0,mlights+64,#0201,7
        FZS lighsfx,0,mlights+80,#0201,7
        FZS VOli,0,mlights+96,#0201,7
        FZS FOli,0,mlights+112,#0201,7

VOli    LD A,(machinetbl)
        OR A
        RET Z
        LD (IY),#FE
        IF ?NoSound
        RET 
        ELSE 
        LD C,2
        JP Msound
        ENDIF 

FOli    LD DE,Outlights
        JP RndSprF

OutXakep
        FZS OXW4Her,#00FF,TABLE,#0302,0

OXW4Her LD HL,RepFaze
        PUSH HL
        LD A,(IY+9)
        OR A
        RET Z
        LD (IY+9),0
        CP givecoin
        JR Z,OXcoin
        RET 

OXcoin
        LD A,(LIVES)
        CP 7
        RET NC
        INC A
        LD (LIVES),A
        PUSH IY
        CALL AddLini
        POP IY
        LD HL,(LstItm)
        LD (HL),0
        CALL select_cross
        JP tlsr

OutExit
        FZS OExi1,#00FC,lift,#0105,eClr1
         FZSP #01FC,lift+40,#0105,7
         FZSP #02FC,lift+80,#0105,eClr3

        FZS OExi2,#00FC,lift,#0105,eClr1
         FZSP #01FC,lift+40,#0105,7
         FZSP #02FC,lift+80,#0105,eClr3
         FZSP #01FC,Empty,#0101,eClr2
LOExi=$-3

OutExit1
        FZS OE3,#00FC,lift,#0105,eClr1
         FZSP #01FC,lift+40,#0105,eClr2
         FZSP #02FC,lift+80,#0105,eClr3

        FZS OE3,#00FC,lift+120,#0105,eClr1
         FZSP #01FC,lift+160,#0105,eClr2
         FZSP #02FC,lift+200,#0105,eClr3

        FZS OE3,#00FC,lift+240,#0105,eClr1
         FZSP #01FC,lift+280,#0105,eClr2
         FZSP #02FC,lift+320,#0105,eClr3

        FZS OE3,#00FC,lift+360,#0105,eClr1
         FZSP #01FC,lift+400,#0105,eClr2
         FZSP #02FC,lift+440,#0105,eClr3

        FZS OE3,#00FC,lift+480,#0105,eClr1
         FZSP #01FC,lift+520,#0105,eClr2
         FZSP #02FC,lift+560,#0105,eClr3

        FZS OE3,#00FC,lift+600,#0105,eClr1
         FZSP #01FC,lift+640,#0105,eClr2
         FZSP #02FC,lift+680,#0105,eClr3

        FZS OE3,#00FC,lift+720,#0105,eClr1
         FZSP #01FC,lift+760,#0105,eClr2
         FZSP #02FC,lift+800,#0105,eClr3

        FZS OE3,#00FC,lift+840,#0105,eClr1
         FZSP #01FC,lift+880,#0105,eClr2
         FZSP #02FC,lift+920,#0105,eClr3

        FZS OOE3,#00FC,lift+960,#0105,eClr1
         FZSP #01FC,lift+1000,#0105,eClr2
         FZSP #02FC,lift+1040,#0105,eClr3

        FZS OTEx,#00FC,lift+1080,#0105,eClr1
         FZSP #01FC,lift+1120,#0105,eClr2
         FZSP #02FC,lift+1160,#0105,eClr3

OOE3    LD A,0
        INC A
        CP 15
        LD (OOE3+1),A
        JR NZ,OE3
        LD HL,DissapL
        LD (HERO+2),HL
OE3     LD A,(IY+6)
        INC A
OE4     CP 3
        JR C,OE6
OE5     LD A,0
        INC A
        CP 11
        LD (OE5+1),A
        JR C,OE7
        XOR A
        LD (OE5+1),A
        LD A,(OE4+1)
        DEC A
        JR Z,OE8
        LD (OE4+1),A
OE7     XOR A
OE6     LD (IY+6),A
        JP C,OExiRep
        RET 

OE8     LD A,7
        LD (OEWp3+1),A
        JR OE7

OTEx    CALL OE3
        RET NZ
FOTEx   LD HL,OutExit1
        JP LDIYHL

OExi1   LD DE,#01FF
        LD BC,#0101
        CALL TstZoneH
        JR NC,OExiRep
        JP stndmode

OExi2   LD A,(LOExi)
        CP 5
        JR NC,OExi3
        INC A
        LD (LOExi),A
OExiRep JP RepFaze

OExi3   XOR A
        LD (IY+6),A
        LD HL,OutExWspuhi
        LD BC,0
        CALL admnst
        LD (IX+6),0
        RET 

OutExWspuhi
        FZS OEWpause

        FZS 0,#00FC,razrq,#0105,eClr4
         FZSP #01FC,razrq+40,#0105,eClr5
         FZSP #02FC,razrq+80,#0105,eClr6

        FZS 0,#00FC,razrq+120,#0105,eClr4
         FZSP #01FC,razrq+160,#0105,eClr5
         FZSP #02FC,razrq+200,#0105,eClr6

        FZS OEWpause

        FZS 0,#00FC,razrq+240,#0105,eClr4
         FZSP #01FC,razrq+280,#0105,eClr5
         FZSP #02FC,razrq+320,#0105,eClr6

        FZS 0,#00FC,razrq+360,#0105,eClr4
         FZSP #01FC,razrq+400,#0105,eClr5
         FZSP #02FC,razrq+440,#0105,eClr6

        FZS OEWpause

        FZS 0,#00FC,razrq+480,#0105,eClr4
         FZSP #01FC,razrq+520,#0105,eClr5
         FZSP #02FC,razrq+560,#0105,eClr6

        FZS 0,#00FC,razrq+600,#0105,eClr4
         FZSP #01FC,razrq+640,#0105,eClr5
         FZSP #02FC,razrq+680,#0105,eClr6

        FZS OEWpause

        FZS 0,#00FC,razrq+720,#0105,eClr4
         FZSP #01FC,razrq+760,#0105,eClr5
         FZSP #02FC,razrq+800,#0105,eClr6

        FZS FOEWs1,#00FC,razrq+840,#0105,eClr4
         FZSP #01FC,razrq+880,#0105,eClr5
         FZSP #02FC,razrq+920,#0105,eClr6

FOEWs1  LD HL,OutExWspuhi
        JP LDIYHL

OEWpause
        LD A,(IY+6)
        OR A
        JR Z,OEWp1
        DEC A
        LD (IY+6),A
        JR NZ,OEWp2
        RET 

OEWp1   CALL RND_A
        RRCA 
OEWp3   AND 15
        INC A
OEWp2   LD (IY+6),A
        JP RepFaze

DissapL FZS 0,#00FE,app3,#0103,HeroClr
        FZS 0,#FFFE,app3+24,#0303,HeroClr
        FZS 0,#FFFF,app2,#0302,HeroClr
        FZS 0,#FFFF,app1,#0301,HeroClr
        FZS 0,#FFFF,app1+24,#0301,HeroClr
        FZS M1W,#00FF,app1+48,#0101,HeroClr
        FZS M1W,#00FF,app1+56,#0101,HeroClr
        FZS W4FCut

W4FCut  LD HL,RepFaze
        PUSH HL
        LD A,(IY+6)
        INC A
        AND 31
        LD (IY+6),A
        RET NZ
        CALL RunFiCut
        ;тут ничего нет - сюда не вернется

;-------
OutLuck FZS W2DLck,#0000,luck,#0201,6
OutLuckHid FZS RepFaze,#0000,doorhi2,#0201,2

W2DLck
        LD E,(IY+6)
        LD D,0
        LD HL,lucktbl
        ADD HL,DE
        LD A,(HL)
        OR A
        JP Z,RepFaze
        LD C,0
        CALL LuGost
EObj    LD (IY),#FE
        RET 

LuGost
        CALL WlkAdr
        LD (HL),C
        INC HL
        LD (HL),C
        ADD HL,DE
        LD (HL),C
        DEC HL
        LD (HL),C
        RET 

OutDoorHid FZS RepFaze,#00FE,doorhid,#0103,DoorHClr
OutWall FZS RepFaze,#00FE,Wall,#0103,6

OutRychR FZS ORysrR,#0000,rychR1,#0101,7
        FZS 0,#0000,rychR2,#0101,7
OutRyR1 FZS RepFaze,#0000,rychR3,#0101,7

OutRych FZS ORysr,#0000,rych1,#0101,7
        FZS 0,#0000,rych2,#0101,7
OutRy1  FZS RepFaze,#0000,rych3,#0101,7

ORysrR  LD HL,rychRtbl
        JR ORysr+3

ORysr
        LD HL,rychtbl
        IF ?AnyKey
        LD A,#BF
        IN A,(#FE)
        AND 4
        JR Z,OTRy1
        ENDIF 

        LD A,(IY+9)
        CP pushdown_r
        JP NZ,RepFaze
OTRy1   LD E,(IY+8)
        LD D,0
        ADD HL,DE
        LD E,(HL)
        SET 7,(HL)
        LD HL,doortbl
        ADD HL,DE
        LD (HL),1
        RET 

OutStrelaLW
        FZS W2EoS
        FZS 0,0,strelkL+16,#0101,7
        FZS 0,0,strelkL+24,#0101,7
OutStrelaL FZS RepFaze,0,strelkL+16,#0101,7

OutStrelaRW FZS W2EoS
        FZS 0,0,strelkR+16,#0101,7
        FZS 0,0,strelkR+24,#0101,7
OutStrelaR FZS RepFaze,0,strelkR+16,#0101,7

W2EoS
        LD A,(IY+9)
        SUB strela_shitl
        JP NZ,RepFaze
        LD HL,streltbl
        LD E,(IY+8)
        LD D,0
        ADD HL,DE
        INC (HL)
        JP arr2snd
        ;RET

OutDoor
        FZS ODoor_sr,#00FE,Ddoor,#0103,DoorClr
        FZS 0,#00FE,Ddoor+8,#0102,3
        FZS EDoor_sr,#00FE,Ddoor+16,#0101,2

ODoor_sr
        IF ?AnyKey
        LD A,#BF
        IN A,(#FE)
        AND 4
        LD E,(IY+8)
        JR Z,OTDoor
        ENDIF 
        LD A,(IY+9)
        OR A
        JP Z,RepFaze
        DEC A
        LD E,(IY+8)
        CP E
        JP NZ,RepFaze
        LD HL,(LstItm)
        DEC (HL)
        PUSH DE
        CALL select_cross
        POP DE
OTDoor  LD D,0
        LD HL,doortbl
        ADD HL,DE
        LD (HL),1
        RET 

EDoor_sr
        LD (IY),#FE
        LD BC,#300
door_way
        LD L,(IY+4)
        LD H,(IY+5)
d_way2  LD DE,-WLKLEN
d_way1  LD (HL),C
        ADD HL,DE
        DJNZ $-2
        RET 

;-------

begenc

;--Elementals
OutElmO FZS WEi1

        FZS 0,0,spix1,#0101,ElmClr
        FZS 0,0,spix1+8,#0101,ElmClr
        FZS 0,0,spix1+16,#0201,ElmClr
        FZS 0,#FF,spix2,#0202,ElmClr
        FZS 0,#FF,spix2+32,#0202,ElmClr
        FZS 0,#FF,spix2+64,#0202,ElmClr
        FZS 0,#FE,spix3,#0203,ElmClr
        FZS 0,#FE,spix3+48,#0203,ElmClr

OutElem
        FZS 0,#FE,fpix1,#0203,ElmClr
        FZS 0,#FE,fpix1+48,#0203,ElmClr
        FZS 0,#FE,fpix1+96,#0203,ElmClr
        FZS 0,#FE,fpix1+144,#0203,ElmClr
        FZS 0,#FF,fpix2,#0202,ElmClr
        FZS 0,#FF,fpix2+32,#0102,ElmClr
        FZS 0,#FF,fpix2+48,#0102,ElmClr
        FZS 0,#FF,fpix2+64,#0102,ElmClr
        FZS 0,#FE,fpix3,#0203,ElmClr
        FZS 0,#FE,fpix3+48,#0203,ElmClr
        FZS 0,#FE,fpix3+96,#0203,ElmClr
        FZS 0,#FE,fpix3+144,#0203,ElmClr
        FZS 0,#FE,fpix4,#0203,ElmClr
        FZS 0,#FE,fpix4+48,#0203,ElmClr
        FZS 0,#FE,fpix4+96,#0203,ElmClr
        FZS 0,#FE,fpix4+144,#0203,ElmClr
        FZS 0,#01FE,fpix5,#0103,ElmClr
        FZS EOEl,#FE,fpix5+24,#0203,ElmClr

EOEl    LD HL,OutElem
        JP LDIYHL

WEi1
        IF ?AnyKey
        LD A,#BF
        IN A,(#FE)
        AND 4
        LD E,(IY+8)
        JR Z,WEi2
        ENDIF 
        LD A,(IY+9)
        OR A
        JP Z,RepFaze
        DEC A
        LD E,(IY+8)
        CP E
        JP NZ,RepFaze
        CP 2    ;5th elem
WEi2    LD D,0
        EX DE,HL
        LD DE,ElmTbl
        ADD HL,DE
        LD A,1
        LD (HL),A
        JR Z,WEi3
        LD HL,(LstItm)
        DEC (HL)
        JP select_cross

WEi3    EX DE,HL        ;пятый ставится только пятым!
        LD B,5
        AND (HL)
        INC HL
        DJNZ $-2
        LD (doortbl+6),A
        RET NZ
        LD (DE),A
        JP RepFaze

;--Gazer-------------------------------------
OutGazer
        FZS Gaz_sr
        FZS 0,0,GAZ1,#201,3
        FZS GazDmg,#FF,GAZ2,#202,6
        FZS GazDmg,#FF,GAZ3,#202,7
        FZS GazDmg,#FF,GAZ4,#202,3
        FZS GazDmg,#FF,GAZ5,#202,7
        FZS GazDmg,#FE,GAZ6,#203,6
        FZS GazDmg,#FE,GAZ7,#203,3
        FZS GazDmg,#FE,GAZ8,#203,7
        FZS Gaz_end,#00FE,GAZ9,#0203,6

Gaz_sr  DEC (IY+4)
        RET Z
Gaz_sr1 CALL NewGazR
Gaz_end LD HL,OutGazer
        JP LDIYHL

NewGazR CALL RND_A
        AND 31
        INC A
        LD (IY+4),A
        RET 

GazDmg  LD DE,#0102
        LD BC,#0203
        CALL TstZoneH
        RET NC
        CALL damage_sr
        DB dmg_gazer

