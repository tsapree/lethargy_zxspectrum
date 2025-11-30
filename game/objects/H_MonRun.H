;процы фонтанов, предметов и пр.

        MAIN "",#C0

;Таблица энкантеров:

EHrebet EQU 1

ENC_TABLE

;движущиеся обьекты - персонажи

                ENC spider1,spdr_sr

                ENC TothL,toth_sr
                ENC TothR,toth_sr
                ENC HeadL,head_sr
                ENC HeadR,head_sr
                ENC RebronL,rebronog_sr
                ENC RebronR,rebronog_sr
                ENC 2heads,_2head_sr
                ENC wedimaL,wed_sr
                ENC wedimaR,wed_sr
                ENC ghost2,gh2_sr
                ENC mummyR,mumR_sr
                ENC mummyL,mumL_sr

                ENC Leaf,leaf_sr
                ENC Spider,spider_sr
                ENC Typhon,tycon_sr
                ENC tu4kadw,ty4ka_sr
                ENC light,light_sr
                ENC Ghost,ghost_sr
                ENC Shit1,shit1_sr
                ENC Shit2,shit2_sr
                ENC Shit3,shit3_sr
                ENC Shit4,shit4_sr
                ENC table,xakep_sr
                ENC exit,exit_sr

                ENC Door,door_sr
                ENC doorhid,doorh_sr
                ENC doorhi2,luckh_sr
                ENC wall,wall_sr
                ENC Rychag,rych_sr
                ENC rychagR,rychR_sr
                ENC Luck,luck_sr
                ENC strela,strel_sr

;движущиеся, неодушивленные

                ENC gaser,gaz_sr
                ENC fire1,fir1_sr
                ENC fire2,fir2_sr
                ENC fontan,fontan_sr
                ENC drop,dropw_sr
                ENC lavaup1,lup1_sr
                ENC lavadw1,ldw1_sr
                ENC kolya,kap_sr
                ENC RuchejL,Ruchej_sr
                ENC Flypix,elemO_sr
                ENC lights1,lights_sr

;недвижущиеся, неодушивленные - не по ор, заслоняют все кроме
;карты. Хотя могут и двигаться...

                ENC rune1,rune_sr
                ENC rune2,rune_sr
                ENC rune3,rune_sr
                ENC rune4,rune_sr
                ENC rune5,rune_sr
                ENC rune6,rune_sr
                ENC rune7,rune_sr
                ENC rune8,rune_sr
                ENC rune9,rune_sr
                ENC rune0,rune_sr

                ENC Bow,bow_sr
                ENC arrow,arr_sr
                ENC Sword,sword_sr
                ENC Hammer,axe_sr
                ENC Firebal,fbal_sr
                ENC Kapkan,Kap_sr
                ENC life2,Life_sr

                ENC almaz,almaz_sr
                ENC krest,krest_sr
                ENC kolye,kolye_sr
                ENC money,money_sr
                ENC skript,skript_sr
                ENC elem1,elem_sr
                ENC elem2,elem_sr
                ENC elem3,elem_sr
                ENC elem4,elem_sr
                ENC elem5,elem_sr

                ENC key1,key_sr
                ENC key2,key_sr
                ENC key3,key_sr
                ENC key4,key_sr
                ENC key5,key_sr

spdr_sr
        CALL mnstbfy
        CALL bgspd1
        JP mnstbfe

wed_sr
        SUB EwedimaL
        CALL mnstbfy
        LD HL,wedfL
        LD DE,wedfR
        CALL wed_lx
        JR re_sr1

gh2_sr
        CALL mnstbfy
        CALL Recall_coords      ;!
        LD HL,ghost
        CALL NC,LDIYHL
        JP mnstbfe

rebronog_sr
        SUB ERebronL
        CALL mnstbfy
        CALL Recall_coords      ;!
        JR C,re_sr2
        LD HL,M1StepL
        LD DE,M1StepR
re_sr1  OR A
        JR Z,$+3
        EX DE,HL
        CALL LDIYHL
re_sr2  CALL WlkAdr
        JP mnstbfe

toth_sr
        SUB ETothL
        CALL mnstbfy
        CALL Recall_coords      ;!
        JR C,re_sr2
        LD HL,ttsL
        LD DE,ttsR
        JR re_sr1

head_sr
        SUB EHeadR
        CALL mnstbfy
        CALL Recall_coords      ;!
        JR C,re_sr2
        LD HL,HdStpL
        LD DE,HdStpR
        JR re_sr1

_2head_sr
        CALL mnstbfy
        CALL Recall_coords      ;!
        JR C,re_sr2
        CALL RND_A
        AND 1
        LD HL,thstpL
        LD DE,thstpR
        JR re_sr1

mumL_sr CALL mnstbfy
        CALL Recall_coords      ;!
        CALL NC,FmuL
        JR re_sr2

mumR_sr
        CALL mnstbfy
        CALL Recall_coords      ;!
        CALL NC,FmuR
        JR re_sr2

leaf_sr
        CALL SetOutPut
        CALL mnstbfy
        CALL FOutLeaf
        JP mnstbfe

spider_sr
        PUSH BC
        CALL mnstbfy
        LD HL,OutSpiderW
        CALL mnstbfehl
        POP BC
        CALL mnstbfy
        LD HL,OutUppSpd
        JP mnstbfehl

ghost_sr
        LD A,(Crosstaken)
        OR A
        RET NZ
        CALL mnstbfy
        CALL FOGh1
        CALL WlkAdr
        LD C,0
        CALL BlkWay
        JP mnstbfe

BlkWay  LD B,0
        ADD HL,BC
        LD BC,#1FF   ;-) не препрыг! :)))
        CALL d_way2
        ADD HL,DE
        LD B,2
        CALL d_way1
        ADD HL,DE
        LD (HL),C
        RET 

ty4ka_sr
        CALL mnstbfy
        LD HL,OutTy4KA
        JP mnstbfehl

xakep_sr
        CALL SetOutPut
        CALL mnstbfy
        LD HL,OutXakep
        JP mnstbfehl

exit_sr
        LD A,#7F
        PUSH BC
        LD B,10
        LD HL,RuneXtaken
        AND (HL)
        INC HL
        DJNZ $-2
        POP BC
        RET Z
        CALL mnstbfy
        LD HL,OutExit
        CALL LDIYHL
        CALL WlkAdr
        INC (IY+4)
        LD A,(place_buff+3)
        LD C,0
        OR A
        JR NZ,$+4
        INC C
        INC C
        CALL BlkWay
        LD BC,#01FF
        CALL door_way
        JP mnstbfe

light_sr
        LD A,(machinetbl)
        OR A
        RET NZ
        CALL mnstbfy
        CALL FOLigh
        CALL Wmlq1
        CALL WlkAdr
        LD C,4
        CALL BlkWay
        JP mnstbfe

lights_sr
        LD A,(machinetbl)
        OR A
        RET NZ
        CALL mnstbfy
        CALL FOli
        JP mnstbfe

shit1_sr
        CALL mnstbfy
        CALL FOSh11
        JR dosr1

shit2_sr
        CALL mnstbfy
        CALL FOSh21
        JR dosr1

shit3_sr
        CALL mnstbfy
        CALL FOSh31
        JR dosr1

shit4_sr
        CALL mnstbfy
        CALL FOSh41
        JR dosr1

tycon_sr
        CALL SetOutPut
        CALL mnstbfy
        LD A,(Kolyetaken)
        OR A
        LD (IY+6),0
        LD HL,OTycSleep
        JR NZ,$+5
        LD HL,OutTycBody
        JR rh_s1 ;mnstbfehl

SetOutPut
        LD HL,SetOutOr
        EX (SP),HL
        PUSH HL
        PUSH BC
        LD HL,OSetPut
        CALL SetOutOr+3
        POP BC
        RET 

SetOutOr
        LD HL,OSetOr
        PUSH HL
        CALL mnstbfy
        POP HL
        LD (IY+7),#FE   ;не монстр
        JR rh_s1 ;JP mnstbfehl

door_sr
        LD HL,doortbl
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        CALL mnstbfy
        LD HL,OutDoor
        CALL LDIYHL
        CALL WlkAdr
        LD BC,#3FF
        CALL door_way
dosr1   JP mnstbfe

rych_sr
        LD HL,rychtbl
        ADD HL,DE
        BIT 7,(HL)
        CALL mnstbfy
        LD HL,OutRych
        JR Z,$+5
        LD HL,OutRy1
rh_s1   JP mnstbfehl

rychR_sr
        LD HL,rychRtbl
        ADD HL,DE
        BIT 7,(HL)
        CALL mnstbfy
        LD HL,OutRychR
        JR Z,$+5
        LD HL,OutRyR1
        JR rh_s1

strel_sr
        CALL mnstbfy
        LD HL,streltbl
        ADD HL,DE
        LD A,(HL)
        OR A
        PUSH AF
        CALL str_sr
        POP AF
        JR NZ,str_sr2
        EX DE,HL
str_sr2 JR rh_s1 ;JP mnstbfehl

str_sr  PUSH AF
        CALL WlkAdr
        POP AF
        JR Z,$+4
        LD A,#FF
        LD (HL),A
        INC HL
        LD A,(HL)
        OR A
        LD HL,OutStrelaL
        LD DE,OutStrelaLW
        RET Z
        LD HL,OutStrelaR
        LD DE,OutStrelaRW
        RET 

elemO_sr
        LD HL,ElmTbl
        ADD HL,DE
        LD A,(HL)
        OR A
        CALL mnstbfy
        JR NZ,eO_s1
        LD HL,OutElmO
        JR mnstbfehl

eO_s1   CALL EOEl
        JR mnstbfe

fir2_sr LD HL,RunePlaces
        ADD HL,DE
        LD E,(HL)
        LD HL,RuneXtaken
        ADD HL,DE
        LD A,(HL)
        OR A
        RET Z
        AND #7F
        CALL mnstbfy
        JR NZ,fir2rsr
        LD HL,OutFire2NoRune
        LD (IY+8),E
        JR mnstbfehl

fir2rsr LD DE,OutFire2
        CALL RndSprF
        JR mnstbfe

;----------------------------------------------

mnstbfy
        LD IY,0
        CALL ccbfy
        LD (IY+8),0
nmbrmnst EQU $-1
        LD (IY+6),0
        RET 

mnstbfehl
        CALL LDIYHL
mnstbfe
        LD BC,10
        LD (IY+9),B
        ADD IY,BC
        LD (mnstbfy+2),IY
        RET 

;----------------------------------------------

RndSprF
        CALL RND_A
        AND 7
RndSprF1 LD L,A
        LD H,0
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,DE
        JP LDIYHL

luck_sr LD HL,lucktbl
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        CALL firebfy
        LD (IY+6),E
        LD HL,OutLuck
        JR luh_sr1

luckh_sr
        LD A,(door2zamok)
        LD (luck2zamok),A
        LD HL,kyrplucktbl
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        CALL firebfy
        LD HL,OutLuckHid
luh_sr1 CALL LDIYHL
        LD C,#FF
        CALL LuGost
        JR gsfibf

doorh_sr
        LD HL,hiddoortbl
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        CALL firebfy
        LD HL,OutDoorHid
drhsr   CALL LDIYHL
        CALL WlkAdr
        LD BC,#3FF
        CALL door_way
        JR gsfibf

wall_sr
        LD HL,walltbl
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        CALL firebfy
        LD HL,OutWall
        JR drhsr

gaz_sr  CALL firebfy
        CALL Gaz_sr1
gsfibf  JR firebfe

fir1_sr CALL firebfy
        LD DE,OutFire1
fir1_1  CALL RndSprF
        JR firebfe

ldw1_sr CALL firebfy
        LD DE,OutLDw
        JR fir1_1

fontan_sr
        CALL firebfy
        LD DE,OutFontan
        JR fir1_1

lup1_sr CALL firebfy
        LD DE,OutLUp
        CALL RND_A
        AND #1F
        CALL RndSprF1
        JR firebfe

dropw_sr
        CALL firebfy
        CALL bgODWb
        JR firebfe

kap_sr  CALL firebfy
        CALL enOKp
        JR firebfe

Ruchej_sr
        CALL firebfy
        CALL FOutRuchej
        JR firebfe

;-----------------------
firebfy LD IY,0
        JP ccbfy

firebfe LD BC,8
        ADD IY,BC
        LD (firebfy+2),IY
        RET 

ccbfy   LD HL,(ROOMCRDSXY)
        ADD HL,BC
        LD BC,#1010
        ADD HL,BC
        LD (IY),L
        LD (IY+1),H
        LD (IY+7),0
typemnst EQU $-1
        RET 

;---------------------------------------------------------------
;                      Описание монстров
;---------------------------------------------------------------

OutFire1
        FZS M1W,#0000,f1,#0101,2
        FZS M1W,#0000,f2,#0101,2
        FZS M1W,#0000,f3,#0101,2
        FZS M1W,#0000,f4,#0101,2
        FZS M1W,#0000,f5,#0101,2
        FZS M1W,#0000,f6,#0101,2
        FZS M1W,#0000,f7,#0101,2
        FZS FOutFire1,#0000,f8,#0101,2

FOutFire1
        CALL M1W
        RET NZ
        LD HL,OutFire1
        JP LDIYHL


a_exm2blE LD D,0
a_exm2bl LD B,2
        JR a_exmXbl

a_exm3blE LD D,0
a_exm3bl LD B,3
a_exmXbl LD H,(IY+5)
        LD L,(IY+4)
        ADD HL,DE
        LD DE,-WLKLEN
        XOR A
        RLCA 
        XOR (HL)
        AND #FE
        XOR (HL)
        ADD HL,DE
        DJNZ $-6
        RET 

a_exm4bl LD B,4
        JR a_exmXbl

a_exm5bl LD B,5
        JR a_exmXbl


; череп на хребте

M1StepL
        FZS M1SLB,0,rngol3,#0201,Monster1Clr
        FZS M1W1,0,rngol4,#0201,Monster1Clr
M1StepL1 FZS M1VFL,#FF00,rngol1,#0201,Monster1Clr
        FZS M1SLE,#FF00,rngol2,#0201,Monster1Clr

M1HitL  FZS M1tstdmgL,#FF00,rnhitl1,#201,Monster1Clr
        FZS M1tstdmgL,#FF,rnhitl2,#102,Monster1Clr
        FZS M1tstdmgL,#FF,rnhitl3,#102,Monster1Clr
        FZS 0,#FFFF,rnhitl4,#202,Monster1Clr
        FZS 0,#FFFF,rnhitl5,#202,Monster1Clr
        FZS M1HLt,#FFFF,rnhitl6,#202,Monster1Clr
        FZS M1FLE,#FF00,rnhitl1,#201,Monster1Clr

M1UppL  FZS M1W,#FF00,rnhitl1,#201,Monster1Clr
        FZS M1W,#FF,rnhitl2,#102,Monster1Clr
        FZS M1W4,#FF,rnhitl3,#102,Monster1Clr
        FZS M1W,#FF,rnhitl2,#102,Monster1Clr
        FZS M1FLE,#FF00,rnhitl1,#201,Monster1Clr

M1DieL  FZS 0,#0000,rndiel1,#0101,Monster1Clr
        FZS 0,#00FF,rndiel2,#0202,Monster1Clr
        FZS M1Di1,#00FF,rndiel3,#0202,Monster1Clr
        FZS 0,#00FF,rndiel4,#0102,Monster1Clr
        FZS M1Di1,#00FF,rndiel5,#0202,Monster1Clr
M1DieL1 FZS M1SLB,#FF00,rndiel6,#0201,Monster1Clr
        FZS M1W2W,#0000,rndiel7,#0101,Monster1Clr
        FZS M1FLE,#FF00,rndiel6,#0201,Monster1Clr

M1Di1   LD E,WLKLEN+1
        CALL a_exm2blE
        AND 1
        LD HL,M1DieL1
        JP NZ,LDIYHL
        JP UpdGoR

M1W2W   DEC (IY+6)
        JP NZ,RepFaze
        RET 

M1tstdmgL;
        LD A,(IY+9)
        CP kickrebronogR
        JP NZ,M1W1
        LD HL,M1DieL
M1tdmgL1 LD (IY+6),50
        JP LDIYHL

M1VFL   CALL M1VtstL
        JR NZ,M1VFNL
        LD (IY+9),0
        LD HL,M1HitL
        JP M1SLB2

M1VtstL LD A,(HERO)
        CP (IY)
        RET NZ
        LD A,(HERO+1)
        SUB (IY+1)
        CP -1
        RET 

M1VFNL  LD A,0
        OR A
        JR Z,M1VFNL2
        DEC A
        LD (M1VFNL+1),A
        JR M1W1

M1VFNL2 CALL RND_A
        BIT 5,A
        JR Z,M1W1
        AND 7
        ADD A,24
        LD (M1VFNL+1),A
        LD HL,M1UppL
        JR M1SLB2

M1SLB
        LD (IY+9),0
        CALL verdwnm
        JR NZ,M1SLB1
M1SLB3  INC (IY)
        CALL WlkAdr
M1SLB4  JP RepFaze

M1SLB1  LD E,WLKLEN-1
        CALL a_exm2blE
        LD HL,M1StepR
M1SLB5  CP 2
        JR Z,M1W1
        LD A,(IY+6)
        OR A
        CALL Z,RND_A
        INC A
        AND #1F
        LD (IY+6),A
        JR Z,M1SLB2
        JR M1SLB4

M1FLE   LD (IY+9),0
        LD HL,M1StepL1
        JR M1SLB2

M1W1    LD A,(HERO)
        CP (IY)
        JR NZ,M1W
        LD A,(HERO+1)
        SUB (IY+1)
        JR NC,$+3
        NEG 
        CP 4            ;степень храбро/пугливости ребронога
        JR NC,M1W
        XOR A
        RET 

M1W4    LD A,(IY+6)
        INC A
        AND 7
        JR M1W21

M1W     LD A,(IY+6)
        INC A
        AND 1
M1W21   LD (IY+6),A
        JR NZ,M1SLB4 ;RepFaze
        RET 

M1SLE   CALL M1W1
        RET NZ
        DEC (IY+1)
        CALL WlkAdr
        LD HL,M1StepL
M1SLB2  JP LDIYHL

M1HLt   CALL M1VtstL
        JR Z,$+4        ;слева и прямо под реброном
        OR A            ;
        RET NZ          ;
        CALL damage_sr
        DB dmg_rebronog

;---
M1StepR
        FZS M1SRB,#FF00,rngor3,#0201,Monster1Clr
        FZS M1W1,#FF00,rngor4,#0201,Monster1Clr
M1StepR1 FZS M1VFR,0,rngor1,#0201,Monster1Clr
        FZS M1SRE,0,rngor2,#0201,Monster1Clr

M1VFR   CALL M1VtstR
        JR NZ,M1VFNR
        LD (IY+9),0
        LD HL,M1HitR
        JR M1SLB2

M1VtstR LD A,(HERO)
        CP (IY)
        RET NZ
        LD A,(HERO+1)
        SUB (IY+1)
        CP 1
        RET 

M1FRE   LD HL,M1StepR1
        JR M1SLB2

M1VFNR  LD A,0
        OR A
        JR Z,M1VFNR2
        DEC A
        LD (M1VFNR+1),A
        JP M1W1

M1VFNR2 CALL RND_A
        ;LD A,R
        BIT 5,A
        JP Z,M1W1
        AND 7
        ADD A,24
        LD (M1VFNR+1),A
        LD HL,M1UppR
        JP M1SLB2

M1HitR  FZS M1tstdmgR,#0,rnhitr1,#0201,Monster1Clr
        FZS M1tstdmgR,#FF,rnhitr2,#0102,Monster1Clr
        FZS M1tstdmgR,#FF,rnhitr3,#0102,Monster1Clr
        FZS 0,#FF,rnhitr4,#0202,Monster1Clr
        FZS 0,#FF,rnhitr5,#0202,Monster1Clr
        FZS M1HRt,#FF,rnhitr6,#0202,Monster1Clr
        FZS M1FRE,0,rnhitr1,#0201,Monster1Clr

M1UppR  FZS M1W,0,rnhitr1,#0201,Monster1Clr
        FZS M1W,#FF,rnhitr2,#0102,Monster1Clr
        FZS M1W4,#FF,rnhitr3,#0102,Monster1Clr
        FZS M1W,#FF,rnhitr2,#0102,Monster1Clr
        FZS M1FRE,0,rnhitr1,#0201,Monster1Clr

M1DieR  FZS 0,#0000,rndier1,#0101,Monster1Clr
        FZS 0,#FFFF,rndier2,#0202,Monster1Clr
        FZS M1DiR,#FFFF,rndier3,#0202,Monster1Clr
        FZS 0,#00FF,rndier4,#0102,Monster1Clr
        FZS M1DiR,#FFFF,rndier5,#0202,Monster1Clr
M1DieR1 FZS M1SRB,#0000,rndier6,#0201,Monster1Clr
        FZS M1W2W,#0000,rndier7,#0101,Monster1Clr
        FZS M1FRE,#0000,rndier6,#0201,Monster1Clr

M1DiR   LD E,WLKLEN-1
        CALL a_exm2blE
        AND 1
        LD HL,M1DieR1
        JP NZ,LDIYHL
        JP UpdGoL

M1tstdmgR
        LD A,(IY+9)
        CP kickrebronogL
        JP NZ,M1W1
        LD HL,M1DieR
        JP M1tdmgL1

M1SRB
        LD (IY+9),0
        CALL verdwnm
        JP Z,M1SLB3
M1SRB1  LD E,WLKLEN+1
        CALL a_exm2blE
        LD HL,M1StepL
        JP M1SLB5

M1SRE   CALL M1W1
        RET NZ
        INC (IY+1)
        CALL WlkAdr
        LD HL,M1StepR
        JP M1SLB2

verdwnm LD E,WLKLEN     ;пол ли снизу?
        CALL a_exm3blE
        AND 4
        RET 

M1HRt   CALL M1VtstR
        JR Z,$+4
        OR A
        RET NZ
        CALL damage_sr
        DB dmg_rebronog

; череп на кисти...

HdStpL
        FZS HdStL,0,headl,#0201,HeadClr
        FZS HdvFL,0,headl+16,#0201,HeadClr
        FZS HdLKi,0,headl+32,#0201,HeadClr
        FZS HdLKi,0,headl+48,#0201,HeadClr
        FZS HdLKi,0,headl+64,#0101,HeadClr
        FZS HdGL,0,headl+72,#0101,HeadClr
        FZS HdvFL,0,headl+80,#0201,HeadClr
        FZS EHdSL,0,headl+96,#0201,HeadClr

EHdSL   LD HL,HdStpL
        JP LDIYHL

HdLKi
        LD A,(IY+6)
        CP 128
        JR C,HdLKi1
HdLKi2  LD DE,WLKLEN+1
        CALL a_exm2bl
        CP 2
        JR Z,HdLKi3
        LD (IY+6),0
        JP HdStR

HdLKi3  INC (IY+6)
        CALL RepFaze
        JR HdGR

HdLKi1  LD A,(IY+9)
        CP kickheadR
        RET NZ
        LD (IY+6),-4
        LD (IY+9),0
        JR HdLKi2

HdStL
        LD DE,WLKLEN-1
        CALL a_exm2bl
        CP 2
        JR Z,HdvFL
        XOR A
        LD (IY+6),A
        LD HL,HdStpR
        CALL LDIYHL
HdGR    INC (IY+1)
        JP WlkAdr

;пров на удар героя элтоком
HdFigL  FZS dolsbh,0,headflr,#0201,HeadClr      ;бьет!
        FZS EHdFL,0,headl+96,#0201,HeadClr

HdvFL   LD (IY+9),0
        LD A,(IY+6)
        OR A
        JR Z,HdvFL1
        DEC (IY+6)
        RET 

HdvFL1  LD DE,#0100
        LD BC,#0201
        CALL TstZoneH
        LD (IY+6),0
        RET NC
        LD HL,HdFigL
        JP LDIYHL

EHdFL   LD A,(IY+6)
        INC A
        LD (IY+6),A
        CP 5
        JP NC,EHdSL
        LD HL,HdFigL
        JP LDIYHL

dolsbh  LD A,by_head
        LD (HERO+9),A
        LD D,(IY+1)
        LD E,(IY)
        LD (pauk_y+1),DE
        RET 

HdStpR  FZS HdStR,#FF00,headr+96,#0201,HeadClr
        FZS HdvFR,#FF00,headr+80,#0201,HeadClr
        FZS HdRKi,#FF00,headr+64,#0201,HeadClr
        FZS HdRKi,#FF00,headr+48,#0201,HeadClr
        FZS HdRKi,#0000,headr+40,#0101,HeadClr
        FZS HdGR,#0000,headr+32,#0101,HeadClr
        FZS HdvFR,#FF00,headr+16,#0201,HeadClr
        FZS EHdSR,#FF00,headr,#0201,HeadClr

HdStR   LD DE,1+WLKLEN
        CALL a_exm2bl
        CP 2
        JR Z,HdvFR
        LD HL,HdStpL
        CALL LDIYHL
HdGL    DEC (IY+1)
        JP WlkAdr

EHdSR   LD HL,HdStpR
        JP LDIYHL

HdRKi
        LD A,(IY+6)
        CP 128
        JR C,HdRKi1
HdRKi2  LD DE,WLKLEN-1
        CALL a_exm2bl
        CP 2
        JR Z,HdRKi3
        LD (IY+6),0
        JP HdStL

HdRKi3  INC (IY+6)
        CALL RepFaze
        JR HdGL

HdRKi1  LD A,(IY+9)
        CP kickheadL
        RET NZ
        LD (IY+6),-4
        LD (IY+9),0
        JR HdRKi2

HdFigR  FZS dolsbh,#FF00,headflr+16,#0201,HeadClr ;бьет!
        FZS EHdFR,#FF00,headr,#0201,HeadClr

HdvFR   LD (IY+9),0
        LD A,(IY+6)
        OR A
        JR Z,HdvFR1
        DEC (IY+6)
        RET 

HdvFR1  LD DE,#0000
        LD BC,#0201
        CALL TstZoneH
        LD (IY+6),0
        RET NC
        LD HL,HdFigR
        JP LDIYHL

EHdFR
        LD A,(IY+6)
        INC A
        LD (IY+6),A
        CP 5
        JR NC,EHdSR
        LD HL,HdFigR
        JP LDIYHL

;Toth

ttsL    FZS VttsL,#00FF,TothGoL,#0102,TothClr
        FZS M1W,#00FF,TothGoL+16,#0202,TothClr
        FZS M1W,#00FF,TothGoL+48,#0202,TothClr
        FZS M1W,#00FF,TothGoL+80,#0202,TothClr
        FZS M1W,#00FF,TothGoL+112,#0202,TothClr
        FZS M1W,#00FF,TothGoL+144,#0202,TothClr
        FZS M1W,#00FF,TothGoL+176,#0202,TothClr
        FZS M1W,#00FF,TothGoL+208,#0202,TothClr
        FZS M1W,#00FF,TothGoL+240,#0202,TothClr
        FZS EttsL,#00FF,TothGoL+272,#0202,TothClr

ttfL    FZS jmptothsnd,#00FE,TothFL,#0102,TothClr
        FZS 0,#00FD,TothFL+16,#0102,TothClr
        FZS 0,#FFFD,TothFL+32,#0202,TothClr
        FZS VttfL,#FFFD,TothFL+64,#0202,TothClr
        FZS 0,#FFFE,TothFL+64,#0202,TothClr
        FZS 0,#FFFF,TothFL+96,#0202,TothClr
        FZS EttsL,#00FF,TothFL,#0102,TothClr

VttfR
        LD DE,#0100
        JR VttfL+3
VttfL
        LD DE,#FF00
        LD BC,#0101
        CALL TstZoneH
        RET NC
        LD HL,(HERO+4)
        LD DE,-WLKLEN
        ADD HL,DE
        LD (HERO+4),HL
        CALL ReHerFaze
        CALL damage_sr
        DB dmg_toth

VttsL
        LD A,(IY+6)
        CP 0-10
        JR C,VttsL5
        INC A
        LD (IY+6),A
        JP Z,VttsLJ
        JP RepFaze

VttsL5  OR A
        JR NZ,VttsL0
        CALL VttRND
        JR Z,VttsL2
VttsL0  DEC A
        LD (IY+6),A
        JR NZ,VttsL1

VttsL2  LD DE,WLKLEN-1
        CALL a_exm3bl
        CP 4
        JP Z,HdGL
EttsR   LD HL,ttsR
        JP LDIYHL

VttRND  CALL RND_A
        LD C,A
        RLCA 
        RLCA 
        AND 3
        RET Z
        LD A,(HERO)
        SUB (IY)
        LD A,C
        LD C,#78
        JR Z,$+4
        LD C,#0F
        AND C
        ADD A,10
        RET 

VttsL1  LD HL,RepFaze
        PUSH HL
        LD IX,HERO
        LD A,(IX)
        CP (IY)
        RET NZ
        LD BC,(KindHero)
        LD A,(place_buff+3) ;1-влево, 0-вправо
        ;XOR 1
        LD B,A
        LD A,(IX+1)
        SUB (IY+1)
        DJNZ VttsL6 ;переход - вправо
        CP 1        ;за спиной
        JR NZ,VttsL4
        DEC C
        DEC C   ;бежит
        RET NZ
        LD (IY+6),#FF
        RET 

VttsL6  CP -2
        JR NZ,VttsL4
        DEC C
        DEC C
        JR VttsL3

VttsL4  CP -1
VttsL3  RET NZ
        POP HL
VttsLJ  LD HL,ttfL
        JP LDIYHL

;
VttsR   LD A,(IY+6)
        CP 0-10
        JR C,VttsR5
        INC A
        LD (IY+6),A
        JP Z,VttsRJ
        JP RepFaze

VttsR5  OR A
        JR NZ,VttsR0
        CALL VttRND
        JR Z,VttsR2
VttsR0  DEC A
        LD (IY+6),A
        JR NZ,VttsR1

VttsR2  LD DE,WLKLEN+1
        CALL a_exm3bl
        CP 4
        JP Z,HdGR
EttsL   LD HL,ttsL
        JP LDIYHL

VttsR1  LD HL,RepFaze
        PUSH HL
        LD IX,HERO
        LD A,(IX)
        CP (IY)
        RET NZ
        LD BC,(KindHero)
        LD A,(place_buff+3) ;1-влево, 0-вправо
        XOR 1
        LD B,A
        LD A,(IY+1)
        SUB (IX+1)
        DJNZ VttsR6 ;переход - вправо
        CP 1        ;за спиной
        JR NZ,VttsR4
        DEC C
        DEC C   ;бежит
        RET NZ
        LD (IY+6),#FF
        RET 

VttsR6  CP -2
        JR NZ,VttsR4
        DEC C
        DEC C
        JR VttsR3

VttsR4  CP -1
VttsR3  RET NZ
        POP HL
VttsRJ  LD HL,ttfR
        JP LDIYHL

ttsR    FZS VttsR,#00FF,TothGoR+288,#0102,TothClr
        FZS M1W,#FFFF,TothGoR+256,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+224,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+192,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+160,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+128,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+96,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+64,#0202,TothClr
        FZS M1W,#FFFF,TothGoR+32,#0202,TothClr
        FZS EttsR,#FFFF,TothGoR,#0202,TothClr

ttfR    FZS jmptothsnd,#00FE,TothFR+112,#0102,TothClr
        FZS 0,#00FD,TothFR+96,#0102,TothClr
        FZS 0,#00FD,TothFR+64,#0202,TothClr
        FZS VttfR,#00FD,TothFR+32,#0202,TothClr
        FZS 0,#00FE,TothFR+32,#0202,TothClr
        FZS 0,#00FF,TothFR,#0202,TothClr
        FZS EttsR,#00FF,TothFR+112,#0102,TothClr

;--- SpId'yrIsHa :)
OutSpd

        FZS M2W,#0001,spider1,#0102,7
         FZSP #FF,thread,#0102,7
        FZS M2W,#0001,spider2,#0102,7
         FZSP #FF,thread,#0102,7
        FZS M2W,#0001,spider3,#0102,7
         FZSP #FF,thread,#0102,7
        FZS M2W,#0001,spider4,#0102,7
         FZSP #FF,thread,#0102,7

OutSpd3 FZS M2W,#0000,spider1,#0102,7
         FZSP #FF,thread,#0101,7
        FZS M2W,#0000,spider2,#0102,7
         FZSP #FF,thread,#0101,7
        FZS M2W,#0000,spider3,#0102,7
         FZSP #FF,thread,#0101,7
        FZS M2W,#0000,spider4,#0102,7
         FZSP #FF,thread,#0101,7

OutSpd2 FZS M2W,#00FF,spider1,#0102,7
        FZS M2W,#00FF,spider2,#0102,7
        FZS M2W,#00FF,spider3,#0102,7
        FZS TSK_,#00FF,spider4,#0102,7

OutSpd1 FZS M2W,#00FF,spider4,#0102,7
        FZS M2W,#00FF,spider3,#0102,7
        FZS M2W,#00FF,spider2,#0102,7
        FZS TS1,#00FF,spider1,#0102,7

        FZS M2W,#0000,spider4,#0102,7
         FZSP #FF,thread,#0101,7
        FZS M2W,#0000,spider3,#0102,7
         FZSP #FF,thread,#0101,7
        FZS M2W,#0000,spider2,#0102,7
         FZSP #FF,thread,#0101,7
        FZS TS2,#0000,spider1,#0102,7
         FZSP #FF,thread,#0101,7

        FZS M2W,#0001,spider4,#0102,7
         FZSP #FF,thread,#0102,7
        FZS M2W,#0001,spider3,#0102,7
         FZSP #FF,thread,#0102,7
        FZS M2W,#0001,spider2,#0102,7
         FZSP #FF,thread,#0102,7
        FZS TS3,#0001,spider1,#0102,7
         FZSP #FF,thread,#0102,7

TS3
espdr1  LD HL,OutSpd
        JR TS1___

bgspd1  LD (IY+8),0
        LD HL,OutSpd1
        JR TS1___

TS2     LD HL,OutSpd3
        LD E,2*WLKLEN
        JR TS1+3

TS1     LD HL,OutSpd2
        PUSH HL
        CALL WlkAdr
        CALL exm2blE
        OR A
        POP HL
        JR Z,M2WQ
        INC (IY+6)
        LD A,(IY+6)
        AND 15
        JP NZ,RepFaze
TS1___  JP LDIYHL

TSK_    INC (IY+6)
        LD A,(IY+6)
        AND #1F
        JP NZ,RepFaze
        LD A,(IY+8)
        OR A
        RET Z
        DEC (IY+8)
        RET 

M2WQ    LD A,(IY+8)
        CP 2
        JR Z,TS1___
M2W     LD BC,#0003
        LD A,(HERO)
        SUB (IY)
        CP 7
        JR NC,M2W2 ;не испуг
        LD A,(HERO+1)
        SUB (IY+1)
        INC A
        CP C
        JR NC,M2W2 ;не испуг
        LD (IY+8),2
M2W2    LD A,(IY+8)
        DEC A
        JR NZ,M2W3
        LD C,15
        JR M2W1

M2W3    DEC A
        JR NZ,M2W1
        LD C,A
M2W1    INC (IY+6)
        LD A,(IY+6)
        AND C
        JP NZ,RepFaze
        RET 

