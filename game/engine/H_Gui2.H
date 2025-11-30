; Графический движок. Вывод уровней, анимация энкаунтеров,
; системные процедуры управления, вывода и проч.

        MAIN "",#C0

_sbmbuff
        SBM RebronL,#22,sc_Rebron_sr    ;*
        SBM RebronR,#18,sc_Rebron_sr    ;*
        SBM HeadL,#04,sc_Head_sr        ;*
        SBM HeadR,#0B,sc_Head_sr        ;*
        SBM 2heads,#06,sc_2Heads_sr     ;*
        SBM TothL,#07,sc_Toth_sr        ;*
        SBM TothR,#07,sc_Toth_sr        ;*
        SBM ghost2,#03,sc_ghost_sr      ;*
        SBM mummyL,#09,sc_mummy_sr      ;*
        SBM mummyR,#0B,sc_mummy_sr      ;*
        DB #FF

sc_ghost_sr
sc_mummy_sr
sc_Toth_sr
sc_2Heads_sr
sc_Head_sr
sc_Rebron_sr
        PUSH DE
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,(HL)
        CP #C0
        JR C,sRs1
        INC A
        JR NZ,sRs1
        POP DE
        RET 

sRs1    LD (IY+6),A
        LD (IY+2),E
        LD (IY+3),D
        POP DE
        LD (IY),E
        LD (IY+1),D
        XOR A
        INC A
        RET 

Recall_coords
        PUSH AF
        PUSH HL
        PUSH DE

        CALL ONPAGE_agfx
        CALL sbmsr
        PUSH AF
        CALL ONPAGE_fzs
        POP AF

        POP DE
        POP HL
        JR Z,R_Cr1
        POP AF
        SCF 
        RET 
R_Cr1   POP AF
        RET 

sbmsr
        LD A,(IY+7)
        LD HL,_sbmbuff
        LD DE,6
sbmsr1  CP (HL)
        JR Z,sbmsr2
        ADD HL,DE
        JR sbmsr1

sbmsr2  CALL sbmsr21
        PUSH DE
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,E
        OR A
        JR Z,$+4
        INC A
        RET NZ
        POP DE
        RET 

sbmsr21 INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        PUSH DE
        LD E,(HL)
        INC HL
        LD D,(HL)
        LD A,(IY+8)
        LD L,A
        ADD A,A
        ADD A,A
        ADD A,L
        LD L,A
        LD H,0
        ADD HL,DE
        POP DE
        RET 

Remember_Coords
        LD A,(page)
        PUSH AF
        CALL ONPAGE_agfx
        PUSH IY
        LD IY,MONSTRS
        LD BC,10
RCLoop  LD DE,6
        LD A,(IY)
        INC A
        JR Z,RCEnd
        INC A
        JR Z,RCL1
        LD HL,_sbmbuff
RCL3    LD A,(HL)
        INC A
        JR Z,RCL1
        DEC A
        CP (IY+7)
        JR NZ,RCL2
        CALL sbmsr21
        LD E,(IY)
        LD D,(IY+1)
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        LD E,(IY+2)
        LD D,(IY+3)
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        LD A,(IY+6)
        LD (HL),A
RCL1    ADD IY,BC
        JR RCLoop

RCL2    ADD HL,DE
        JR RCL3

RCEnd   POP IY
        POP AF
        CALL ONPAGE
        RET 

DeadMonster
        LD HL,_sbmbuff
        LD DE,6
        LD A,(IY+7)
DeMon1  CP (HL)
        ADD HL,DE
        JR Z,DeMon2
        JR DeMon1

DeMon2  DEC HL
        LD A,(HL)
        LD (IY+6),A
        RET 

;hl=scr
;de=spr
itm0    PUSH HL
        CALL o_stlb0
        POP HL
        INC L
o_stlb0 CALL o_slb01
        CALL dwnhl1
o_slb01 LD B,8
        LD A,(DE)
        LD (HL),A
        INC DE
        INC H
        DJNZ $-4
        RET 

o_stlb4 CALL o_slb41
        CALL dwnhl1
o_slb41 LD B,8
        LD A,(DE)
        RRCA 
        RRCA 
        RRCA 
        RRCA 
        XOR (HL)
        AND C
        XOR (HL)
        LD (HL),A
        INC DE
        INC H
        DJNZ $-11
        RET 

itm4    LD C,#0F
        PUSH HL
        CALL o_clhs
        POP HL
        CALL itm41
        CALL itm41
o_clhs  CALL o_clhs1
        CALL dwnhl1
o_clhs1 LD B,8
        LD A,(HL)
        AND C
        LD (HL),A
        INC H
        DJNZ $-4
        RET 

itm41   PUSH HL
        PUSH DE
        LD C,#0F
        CALL o_stlb4
        POP DE
        POP HL
        INC L
        PUSH HL
        LD C,#F0
        CALL o_stlb4
        POP HL
        RET 

viz_dig
        LD A,(Inventory+1)
        INC A
        CALL srcitm
        DEC HL
        LD A,(HL)
        CP 128
        PUSH AF
        RES 7,A
        OR A
        CALL calcule_dig
        LD A,E
        LD DE,#404F
        CALL digout
        LD A,B
        CALL digout
        POP AF
        LD C,digmany
        JR C,v_ni2
        CP 138
        JR NC,v_ni2
        EX AF,AF'
v_ni3   LD A,0
        OR A
        JR NZ,v_ni2-1
v_ni1   LD A,0
        INC A
;       AND #1F
        LD (v_ni1+1),A
        AND #10
        JR NZ,$+4
        LD C,dignull
        EX AF,AF'
v_ni2   LD HL,#584F
        AND #7F
        JR NZ,$+4
        LD C,dignull
        LD (HL),C
        INC L
        LD (HL),C
        RET 

calcule_dig;
        LD B,#0A
        LD E,B
        RET Z
        LD BC,#FF0A
        CALL $+7
        LD E,B
        LD BC,#FF01
        INC B
        SUB C
        JR NC,$-2
        ADD A,C
        RET 

digout  ADD A,A
        ADD A,A
        ADD A,A
        LD HL,digits
        ADD A,L
        LD L,A
        ADC A,H
        SUB L
        LD H,A
        PUSH DE
        LD A,(HL)
        LD (DE),A
        INC HL
        INC D
        LD A,D
        AND 7
        JR NZ,$-7
        POP DE
        INC E
        RET 

viz_runes_1 LD (virflg1+1),A
viz_runes
        PUSH IX
        LD IX,RuneXtaken
        LD HL,#5811
        LD B,10
v_ru1   CALL v_ru2
        LD (HL),C
        INC L
        DEC B
        CALL v_ru2
        LD (HL),C
        INC L
        LD (HL),C
        INC L
        DJNZ v_ru1
        POP IX
        RET 

v_ru2   LD A,(IX)
        INC IX
        OR A
        LD C,norune_clr
        RET Z
        AND #7F
        LD C,tknrun_clr
        RET Z
        LD C,actrun_clr
        RET 

viinvclr
        LD A,(Inventory)
        OR A
        LD DE,active_itm_clr*256+pass_itm_clr
        JR NZ,$+3

setvclr LD D,E
        LD HL,#586A
        CALL setvi_c2
        LD L,#8A
setvi_c2
        CALL setvi_c1
        LD (HL),D
        INC L
        LD (HL),D
        INC L
setvi_c1
        LD B,5
        LD (HL),E
        INC L
        DJNZ $-2
        RET 

viz_invent
        CALL viinvclr
vizinvo CALL viz_dig

        LD HL,#406A
        CALL ouit2 ;ини

        LD A,5
        EX AF,AF'
        LD BC,(Inventory)
        LD A,B
        SUB 2
        JR NC,noni1

        PUSH BC
oni_1   PUSH AF
        LD DE,nothing
        CALL Out1Itm
        POP AF
        INC A
        EX AF,AF'
        DEC A
        RET Z
        EX AF,AF'
        JR NZ,oni_1
        POP BC
        XOR A
noni1   PUSH AF
        SUB C
        NEG 
        LD C,A
        POP AF
        CALL srcitm
        INC C
        JR noni2

voitm1  LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        INC HL
        INC HL
        INC HL
        PUSH HL
        PUSH BC
        CALL Out1Itm
        POP BC
        POP HL
        EX AF,AF'
        DEC A
        RET Z
        EX AF,AF'
noni2   DEC C
        JR NZ,voitm1

oni_2   LD DE,nothing
        CALL Out1Itm
        EX AF,AF'
        DEC A
        RET Z
        EX AF,AF'
        JR oni_2

wspsr1  LD HL,wspyhtbl
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD (wspsr1+1),HL
        BIT 7,D
        JP Z,setvclr+1
        PUSH DE
        RET 

ewspsr  CALL viz_invent
ewspsr1 XOR A
ewspsr2 LD (wspflg1+1),A
        LD HL,wspyhtbl
        LD (wspsr1+1),HL
        RET 

srcitmI
        LD A,(Inventory+1)
        INC A
        PUSH DE
        CALL srcitm
        POP DE
        DEC HL
        LD A,(HL)
        AND #7F
        LD A,(HL)
        RET 

srcitm
        LD E,A
        LD D,0
        LD L,E
        LD H,D
        ADD HL,HL
        ADD HL,HL
        ADD HL,DE
        LD DE,Inventory+2
        ADD HL,DE
        RET 

Out1Itm JR ouit4
ouit0   LD HL,#406A
        PUSH HL
        CALL itm0
        POP HL
        INC L
        INC L
        LD (ouit4+1),HL
        LD A,#18
ouit1   LD (Out1Itm),A
        RET 

ouit4   LD HL,0
        PUSH HL
        CALL itm4
        POP HL
        INC L
        INC L
        INC L
ouit2   LD (ouit0+1),HL
        LD A,#3E
        JR ouit1

SHLT    LD A,1
        LD (v_ni3+1),A
        HALT 
        XOR A
        LD (v_ni3+1),A
        RET 

SelItem
        LD IX,Inventory
        LD A,(IX)
        OR A
        RET Z
        CALL ewspsr1
SelItLp EI 
        CALL SHLT
SelItL1 CALL SIt1c
        CALL QAOPSP
        AND %11
        JR Z,NMvIt
        DEC A
        JP Z,SIMvR
        DEC A
        JR Z,SIMvL
NMvIt   CALL W4Enter
        JR C,SelItLp
        LD A,(Inventory+1)
        CALL srcitm
        INC HL
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        LD A,D
        OR E
        JR Z,$+7
        PUSH DE
        LD DE,ONPAGE_fzs
        PUSH DE
        JP viinvclr

SIMvL   LD A,(IX+1)
        OR A
        JR Z,SelItLp
        DEC (IX+1)
        SUB 3
        LD DE,nothing
        JR C,$+8
        CALL srcitm
        LD E,(HL)
        INC HL
        LD D,(HL)
        LD HL,#10
        ADD HL,DE
        EX DE,HL
        LD B,2
        PUSH DE
SRPR1   EI 
        CALL SHLT
        PUSH BC
        CALL SIt1c
        LD B,16
        LD HL,#406A
        CALL RElR
        CALL RElR
        CALL dwnhl
        DJNZ $-9
        POP BC
        DJNZ SRPR1
        POP DE
        LD B,8
SRPR2   EI 
        CALL SHLT
        PUSH BC
        PUSH DE
        CALL SIt1c
        POP DE
        PUSH DE
        LD B,16
        LD HL,#406A
        CALL RSlR
        CALL RSlR
        CALL dwnhl
        INC DE
        DJNZ $-10
        POP DE
        POP BC
        LD A,B
        CP 5
        JR NZ,$+7
        LD HL,#FFF0
        ADD HL,DE
        EX DE,HL
        DJNZ SRPR2
        JP SelItL1

SIMvR   LD A,(IX+1)
        INC A
        CP (IX)
        JP NC,SelItLp
        INC (IX+1)
        ADD A,2
        CP (IX)
        LD DE,nothing
        JR NC,$+8
        CALL srcitm
        LD E,(HL)
        INC HL
        LD D,(HL)

        LD B,2
        PUSH DE
SLPR1   EI 
        CALL SHLT
        PUSH BC
        CALL SIt1c
        LD B,16
        LD HL,#406A+11
        CALL RElL
        CALL RElL
        CALL dwnhl
        DJNZ $-9
        POP BC
        DJNZ SLPR1
        POP DE

        LD B,8
SLPR2   EI 
        CALL SHLT
        PUSH BC
        PUSH DE
        CALL SIt1c
        POP DE
        PUSH DE
        LD B,16
        LD HL,#406A+11
        CALL RSlL
        CALL RSlL
        CALL dwnhl
        INC DE
        DJNZ $-10
        POP HL
        POP BC
        LD A,B
        CP 5
        JR Z,$+3
        EX DE,HL
        DJNZ SLPR2
        JP SelItL1

RElL    XOR A
        JR Rell1

RSlL    EX DE,HL
        RLC (HL)
        EX DE,HL

Rell1   LD A,L
        DUP 12
        RL (HL)
        DEC L
        EDUP 
        LD L,A
        RET 

RElR    XOR A
        JR Relr1

RSlR    EX DE,HL
        RRC (HL)
        EX DE,HL

Relr1   LD A,L
        DUP 12
        RR (HL)
        INC L
        EDUP 
        LD L,A
        RET 

SIt1c   LD A,0
        INC A
        CP 7*2-2*2
        JR C,$+3
        XOR A
        LD (SIt1c+1),A
        SRL A
        INC A
        CP 8
        JR C,$+5
        SUB 14
        NEG 
        LD E,A
        JP setvclr

damage_sr
        POP BC
;       RET NC ;или какое там будет условие?
        PUSH AF
        LD A,(BC)
dmgsr1  LD HL,NRGpls
        ADD A,(HL)
        LD (HL),A
        POP AF
        RET 

;запоминание текущего плэйса скелета (когда стоит)

place_s LD DE,place_buff
        LD HL,HERO
        LDI 
        LDI 
        LD HL,ROOM
        LDI 
        LD (DE),A ;place_buff+3 - 1-влево, 0-вправо
        RET 

death
        XOR A
        LD (NRGpls),A
        INC A
        LD (tpyn+1),A
        LD A,(LIVES)    ;временное - самое постоянное!
        DEC A           ;придет время, изменю!
        LD (LIVES),A
        PUSH AF
        CALL ONPAGE_fzs
        CALL SubLini
        LD A,(tpyn_1+1)
        OR A
        JR NZ,dea11
        CALL telo_sr
        CALL invizible_hero
        CALL NoHeroSr
dea11   POP AF
        JR Z,alldeath
        XOR A
        RET 

DIIIE
        LD HL,place_reinc
        LD DE,HERO
        LDI 
        LDI 
        LD DE,ROOM
        LDI 
        LD A,(HL)
        OR A
        LD HL,StandRight1
        JR NZ,$+5
        LD HL,StandLeft1
        LD (HERO+2),HL
        LD HL,HeroCrds
        LD (SetCrdHero+1),HL
        XOR A
        LD (tpyn_1+1),A
        LD (tpyn+1),A
        JP StLp2

alldeath
        POP HL
        CALL GAMEOVER
        JP IM1

telo_sr
        LD IY,HERO
        LD HL,O_TELO
        LD BC,0
        LD IX,FLYBUFF
        LD DE,8
        CALL admnst1
        LD (IX+8),#FF
        LD (IX+6),20
        RET 

;----
drawborders
        CALL recalcborders

        LD IX,reshowtbl
        JR C,rcbo1
        LD A,(IX)
        CALL scpXbox
        CALL drwYbox2

        LD A,(IX+2)
        CALL drwXbox
rcbo3   LD A,(IX+3)
        CALL drwYbox
        CALL drwdlin
        RET 

rcbo1   LD A,(IX)
        CALL scpXbox
        CALL drwYbox1
        LD A,(IX+2)
        CALL scpXbox
        CALL drwulin
        JR rcbo3

scpXbox LD HL,HEAD_STRS*32+#4000
        LD DE,backgr
sXb2    OR A
        RET Z
        LD B,A
        ADD A,D
        LD D,A
sXb1    LD A,L
        ADD A,32
        LD L,A
        JR NC,$+6
        LD A,H
        ADD A,8
        LD H,A
        DJNZ sXb1
        RET 

drwYbox2
        BIT 7,(IX+1)
        JR Z,drwYb3
        CALL drwYbox1
        JP drwulin

drwYb3  CALL drwulin
drwYbox1
        LD A,(IX+1)
drwYbox BIT 7,A
        RES 7,A
        JR NZ,reXbox
        OR A
        RET Z
        LD BC,BORDERBOX
        JR drwXb

reXbox  OR A
        RET Z
        PUSH AF
        CALL rstHLDE
        POP AF
reXbx0  LD BC,0
        ADD HL,BC
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        LD B,A
reXb2   PUSH BC
reXb1   PUSH HL
reXbx1  LD B,0
        LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4

reXbx2  LD BC,0
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        POP HL
        INC H
        LD A,H
        AND 7
        JP NZ,reXb1
        CALL dwnhl1
        POP BC
        DJNZ reXb2
        RET 

drwXbox LD BC,MIDDLEBOX
drwXb   LD (rpSCRy2+1),A
        OR A
        RET Z
        LD A,(BC)
        INC BC
        INC A
        LD (rpSCRx1+1),A
        LD A,(BC)
        INC BC
        EXA 
        LD A,(BC)
        INC BC
        LD (rpSCRx2+1),A
        LD A,(BC)
        INC BC
        INC A
        LD (rpSCRx3+1),A
        LD A,(BC)
        LD (rpSCRx4+1),A
        CALL rstHLDE
        EXA 
        LD B,0
        LD C,A
        ADD HL,BC
        EX DE,HL
        ADD HL,BC
        EX DE,HL

rpSCRy2 LD B,5
rpSCR3  PUSH BC
rpSCR2  PUSH HL
rpSCRx1 LD B,0
        DJNZ rpSCR11
        JR rpSCRx2

rpSCR11 LD A,(DE)
        LD (HL),A
        INC L
        INC DE
        DJNZ $-4
        DEC L
        RES 0,(HL)
        INC L

rpSCRx2 LD C,0
        ADD HL,BC
        EX DE,HL
        ADD HL,BC
        EX DE,HL

rpSCRx3 LD B,0
        DJNZ rpSCR44
        JR rpSCRx4

rpSCR44 LD A,(DE)
        AND #7F
        JR rpSCR1

        LD A,(DE)
rpSCR1  LD (HL),A
        INC L
        INC DE
        DJNZ $-4
rpSCRx4 LD C,0
        EX DE,HL
        ADD HL,BC
        EX DE,HL
        POP HL
        INC H
        LD A,H
        AND 7
        JR NZ,rpSCR2
        CALL dwnhl1
        POP BC
        DJNZ rpSCR3
        LD (drwdlin+1),HL
        RET 

rstHLDE PUSH BC
        LD A,L
        AND 31
        LD B,0
        LD C,A
        SBC HL,BC
        EX DE,HL
        SBC HL,BC
        EX DE,HL
        POP BC
        RET 

drwdlin LD HL,0
        LD A,H
        CP #58
        RET NC
        CALL rstHLDE
        PUSH HL
        JR dul1

drwulin LD A,0
        OR A
        RET Z
        CALL rstHLDE
        PUSH HL
        CALL uphl
dul1    LD BC,0
        ADD HL,BC
dul2    LD B,0
        LD A,C
        OR A
        JR Z,$+6
        DEC L
        RES 0,(HL)
        INC L
        XOR A
        LD (HL),A
        INC L
        DJNZ $-2
        LD A,L
        AND 31
        JR Z,$+4
        RES 7,(HL)
        POP HL
        RET 

recalcborders
        LD IX,MIDDLEBOX
        LD HL,(ROOMCRDSXY)
        LD DE,(PREVROOM)
        EXX 
        LD HL,(ROOMCRDSSXSY)
        LD DE,(PREVROOM+2)
        EXX 

        LD A,L
        LD (drwulin+1),A
        LD A,H
        LD (dul1+1),A
        EXX 
        LD A,H
        EXX 
        LD (dul2+1),A

        LD A,E
        OR A
        JR Z,$+6
        DEC E
        EXX 
        INC E
        EXX 
        LD A,E
        EXX 
        ADD A,E
        CP 19
        JR NC,$+3
        INC E

        PUSH DE
        EXX 
        PUSH HL
        PUSH DE

        CALL rclcb4
        LD A,32
        CALL rclcb1
        LD IX,BORDERBOX
        LD A,32
        PUSH DE
        LD D,H
        LD E,L
        EXX 
        PUSH DE
        LD D,H
        LD E,L
        EXX 
        CALL rclcb1
        POP DE
        POP HL
        CALL rclcb3
        POP DE
        POP HL
        EXX 
        POP DE
        EXX 

        LD A,L
        SUB E
        JR C,rcbo4
        EXX 
        CP E
        CCF 
        EXX 
        RET NC
        JR rcbo2

rcbo4   NEG 
        EXX 
        CP L
        CCF 
        EXX 
        RET NC

rcbo2   EXX 
        LD A,E
        EXX 
        LD D,A
        SET 7,D
        LD (reshowtbl),DE
        EXX 
        LD A,L
        EXX 
        LD H,A
        LD (reshowtbl+2),HL
        SCF 
        RET 

rclcb1  LD (rclcb2+1),A
        LD A,H
        SUB D        ;l1=x2-x1
        JR NC,$+3
        XOR A        ;iF l1<0 then l1=0
        LD C,A
        SUB H
        NEG          ;x3=x2-l1
        JR Z,$+4
        DEC A
        INC C        ;if x3<>0 then dec x3:inc l1
        LD B,A

        LD A,H  ;x2
        EXX 
        ADD A,H ;sx2
        LD B,A  ;sx2+x2
        LD A,D  ;sx1
        EXX 
        ADD A,D ;x1+sx1
        EXX 
        SUB B   ;(x1+sx1)-(x2-sx2)
        JR NC,$+3
        XOR A
        LD C,A
        ADD A,B
rclcb2  CP 32
        JR NC,$+3
        INC C

        LD A,32
        SUB C
        SUB H
        EXX 
        SUB C
        EXX 
        LD B,A ;l4

        LD (IX+2),H
        LD (IX+3),C
        LD (IX+4),B
        EXX 
        LD (IX),C
        LD (IX+1),B
        RET 

rclcb3  LD A,H
        OR A
        JR Z,$+4
        DEC A
        INC D
        LD E,A
        LD (reXbx0+1),A
        ADD A,D
        CP 32
        JR NC,$+3
        INC D
        LD A,D
        LD (reXbx1+1),A
        SUB 32
        NEG 
        LD (reXbx2+1),A
        RET 

rclcb4  LD C,L  ;y3=y2
        LD A,E
        SUB L
        LD B,A  ;h1=y2-y1
        JR NC,rclcb31
        NEG 
        LD B,A
        LD A,C
        SUB B
        LD C,A
        SET 7,B
rclcb31 LD (reshowtbl),BC
        LD A,E
        EXX 
        ADD A,E
        LD C,A
        LD A,L
        EXX 
        ADD A,L
        EXX 
        SUB C
        LD B,A
        JR NC,rclcb32
        NEG 
        LD B,A
        LD A,C
        SUB B
        LD C,A
        SET 7,B
rclcb32 EXX 
        LD A,B
        AND #7F
        ADD A,C
        EXX 
        SUB C
        NEG 
        LD C,A
        LD (reshowtbl+2),BC
        EXX 
        RET 

;-------------------
        ;0
        ;1,3,5,7
        ;2,6
        ;4
        ;    0 1 2 3 4 5 6 7
        ;      *   *   *   *
        ;___     * *     * *
        ;            * * * *

;                 0 1 2 3 4 5 6 7 8 9 A B C D E F
;
        ;       ?   x   x   x   x   x   x   x   x
        ;       ?     x x     x x     x x     x x
        ;       ?         x x x x         x x x x
        ;       *                 x x x x x x x x
        ;       x                                xxxxxxx
        ;_______x

exm2blE LD D,0
exm2bl  LD B,1
        JR exmXbl

exm3blE LD D,0
exm3bl  LD B,2
exmXbl  LD H,(IY+5)
        LD L,(IY+4)
        ADD HL,DE
        XOR A
        CP (HL)
        RLA 
        LD DE,-WLKLEN
        ADD HL,DE
        CP (HL)
        RLA 
        DJNZ $-3
        RET 

exm4bl  LD B,3
        JR exmXbl

exm5bl  LD B,4
        JR exmXbl


;-------------------

callpg
        EX (SP),HL
        LD A,(HL)
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        EX (SP),HL
        LD HL,(page-1)
        PUSH HL
        LD HL,ONPAGEPOP
        PUSH HL
        PUSH DE
        JR ONPAGE

ONPAGEPOP POP AF        ;
        JR ONPAGE

ONPAGE_lvl
        LD A,lvl_pg
        JR ONPAGE

ONPAGE_gfx
        LD A,gfx_pg
        JR ONPAGE

ONPAGE_mus
        LD A,mus_pg
        JR ONPAGE

ONPAGE_agfx
        LD A,agfx_pg
        JR ONPAGE

ONPAGE_fzs
        LD A,fzs_pg
        JR ONPAGE

ONPAGE_main
        LD A,main_pg

ONPAGE  PUSH BC
onp1    OR #10
        LD BC,#7FFD
        LD (page),A
        OUT (C),A
        POP BC
        RET 

        IFN ?NoSound
lavasnd
        LD C,sound_lavsnd
        JR Msound
takeitemsnd
        LD C,sound_titsnd
        JR MsoundC
jmptothsnd
        LD C,sound_jmptoth
        JR Msound

fallscsnd
        LD C,4
        JR MsoundC

lighsfx LD C,1
        JR Msound

kapsfx
        LD C,3
        JP Msound

alifsnd LD C,sound_pluslife
        JR MsoundC

arr1snd LD C,sound_strela01
        JR Msound

arr2snd LD C,sound_strela02
        JR Msound

hlftsnd LD C,sound_twoHLeft
        JR Msound

nozhsnd LD C,sound_nozhi
        JR Msound

knifsnd LD C,5
        JR MsoundC

fbalsnd LD C,sound_sfireball
        JR Msound

fbal2snd LD C,sound_sfirebal2
        JR Msound

xpehbsnd LD C,sound_xpehb
        JR Msound

chestsnd LD C,sound_brkchest
        JR Msound

MsoundC LD B,#20
        JR Msound1

Msound  LD B,(IY+1)
Msound1 CALLPG mus_pg,IniSmpNmb
        RET 

        ELSE 
knifsnd
kapsfx
fallscsnd
lighsfx RET 
        ENDIF 
