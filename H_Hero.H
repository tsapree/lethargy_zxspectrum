; Герой. Монстры.

        MAIN "",#C0

;StandR1Fire
;StandR2Fire процедуры обработки огня из стоячего положения ?)
;StandL1Fire
;StandL2Fire

begher

StandRight1
        FZM StRLoop1,#00FE,golft01,#0103,HeroClr

StandRight2
        FZM StRLoop2,#00FE,golft01,#0103,HeroClr

StRLoop1
        LD HL,emukeys
        LD HL,StRL21
        LD HL,FallRLp
        LD (HerFaze+1),HL
        LD (DIRECT1),A
        EX AF,AF'
        CALL HeroStand
        XOR A
        CALL place_s
        CALL verdwn
        LD HL,LDIYHL
        PUSH HL
        LD HL,FallDwnR
        RET Z
        LD A,(IY+9)
        OR A
        LD C,0
        CALL NZ,loss_sr
        EX AF,AF'
        BIT 4,A
StandR1Fire
        CALL NZ,_ret
        CP 1+8
        JP Z,JmpRsr
        CALL clrfrr
        RRCA 
        JP C,G_right_sr1
        RRCA 
        LD HL,StandLeft1
        RET C
        RRCA 
        JP C,KDwR
        RRCA 
        JR C,KUpR
StRLbk  POP HL
StRL21  LD HL,StandRight1
LDIYHL
StRL1   LD (IY+2),L
        LD (IY+3),H
_ret    RET 

StRLoop2
        LD HL,emukeys
        LD HL,StRL21
        LD HL,FallRLp
        LD (HerFaze+1),HL
        LD (DIRECT1),A
        EX AF,AF'
        CALL HeroStand
        XOR A
        CALL place_s
        CALL verdwn
        LD HL,LDIYHL
        PUSH HL
        LD HL,FallDwnR
        RET Z
        LD A,(IY+9)
        OR A
        LD C,0
        CALL NZ,loss_sr
        EX AF,AF'
        BIT 4,A
StandR2Fire
        CALL NZ,_ret
        CP 1+8
        JR Z,JmpRsr
        CALL clrfrr
        RRCA 
        JP C,G_right_sr2
        RRCA 
        LD HL,StandLeft1
        RET C
        RRCA 
        JR C,KDwR
        RRCA 
        JR C,KUpR
        POP HL
StRL22  LD HL,StandRight2
        JR LDIYHL

KUpR    LD DE,0
        CALL exm4bl     ;
        RRA 
        RL C
        OR A
        JR NZ,KUpR2
        LD DE,1-WLKLEN
        CALL exm5bl
        BIT 3,A
        JR Z,KUpR1
        AND #06
        LD HL,UpR3
        JR NZ,KUpR2
        RR C
        RET NC
KUpR2   JP StRL21

KUpR1   AND #1C
        CP #10
        LD HL,UpR2
        RET Z
        JR KUpR2

KDwR
        LD DE,WLKLEN*2-1
        CALL exm3bl
        JR NZ,KUpR2
        LD HL,DwR
        RET 

JmpRsr
        LD DE,1
        CALL exm3bl
        EX AF,AF'
        LD HL,JmpRightSmall
JmpRsr1 LD A,0
        OR A
        JR Z,$+5
        LD HL,JmpRight
        CALL clrfrr1
        RET Z
        JP StRLbk

setfrr  EX AF,AF'
        LD A,1
        JR clrfrr2

clrfrr  EX AF,AF'
clrfrr1 XOR A
        LD (JmpLsr1+1),A
clrfrr2 LD (JmpRsr1+1),A
        EX AF,AF'
        RET 

G_right_sr1
        LD DE,1+WLKLEN ;на знакоместо вправо и вниз
        CALL exm3bl
        LD HL,StepDwR1
        RET Z
        CP 4
        JR Z,Run_Right_sr1
        RRCA 
        JR NC,ver_step_ur1
        LD HL,StandRight1
        RET 

G_right_sr2
        LD DE,1+WLKLEN ;на знакоместо вправо и вниз
        CALL exm3bl
        LD HL,StepDwR2
        RET Z
        CP 4
        LD HL,RunRight2 ;GoRight2
        JR Z,Run_Right_sr2
        RRCA 
        JR NC,ver_step_ur2
        LD HL,StandRight2
        RET 

verdwn  LD E,WLKLEN     ;пол ли снизу?
        CALL exm3blE
        AND 4
        RET 

Run_Right_sr1
        LD A,(DIRECT1)
        AND #20
        JR NZ,RRs1
        LD DE,2+WLKLEN
        CALL exm3bl
        LD HL,RunRight1 ;GoRight1
        CP 4
        RET Z
RRs1    LD HL,GoRight1
        RET 

ver_step_ur1
        LD DE,1-WLKLEN
        CALL exm2bl
        LD HL,StandRight1
        RET NZ
        LD HL,StepUpR1
        RET 

Run_Right_sr2
        LD A,(DIRECT1)
        AND #20
        JR NZ,RRs2
        LD DE,2+WLKLEN
        CALL exm3bl
        LD HL,RunRight2 ;GoRight1
        CP 4
        RET Z
RRs2    LD HL,GoRight2
        RET 

ver_step_ur2
        LD DE,1-WLKLEN
        CALL exm2bl
        LD HL,StandRight2
        RET NZ
        LD HL,StepUpR2
        RET 

GoRight1
        FZM HeroGo,#00FE,golft02,#0103,HeroClr
        FZM 0,#00FE,golft03,#0203,HeroClr
        FZM 0,#00FE,golft04,#0203,HeroClr
        FZM UpdGoR,#00FE,golft05,#0203,HeroClr
        FZM 0,#FFFE,golft06,#0203,HeroClr
        FZM 0,#FFFE,golft07,#0203,HeroClr
        FZM StRL22,#FFFE,golft08,#0203,HeroClr

GoRight2
        FZM HeroGo,#00FE,golft10,#0103,HeroClr
        FZM 0,#00FE,golft11,#0203,HeroClr
        FZM 0,#00FE,golft12,#0203,HeroClr
        FZM UpdGoR,#00FE,golft13,#0203,HeroClr
        FZM 0,#FFFE,golft14,#0203,HeroClr
        FZM 0,#FFFE,golft15,#0203,HeroClr
        FZM StRL21,#FFFE,golft16,#0203,HeroClr

UpdGoR
        INC (IY+1)
        JP WlkAdr

RunRight1
        ;stand
        FZM HeroRun,#00FE,runl1,#0203,HeroClr
        FZM UpdRR3,#00FE,runl2,#0303,HeroClr
        FZM 0,#FFFE,runl3,#0303,HeroClr
        FZM UpdRR3,#00FE,runl4,#0203,HeroClr
        FZM StRLoop2,#FFFE,runl5,#0203,HeroClr

RunRight2
        FZM HeroRun,#00FE,runl6,#0203,HeroClr
        FZM UpdRR3,#00FE,runl7,#0303,HeroClr
        FZM 0,#FFFE,runl8,#0303,HeroClr
        FZM UpdRR3,#00FE,runl9,#0203,HeroClr
        FZM StRLoop1,#FFFE,runla,#0203,HeroClr

UpdRR3  LD A,(StRLoop1+3)
        CP #C3
        JP Z,RepFaze
UpdRR2  INC (IY+1)
        CALL setfrr
        JP WlkAdr

FallDwnR
        FZM FallRLp,#00FE,golft01,#0103,HeroClr

FallRLp CALL clrfrr
        CALL verdwn
        JP NZ,FRLpE1
        INC (IY)
        CALL WlkAdr
        LD HL,FallDwnR
        IFN ?FlyingSkull
        JP LDIYHL
        ELSE 
        JP RepFze
        ENDIF 

StepUpR1
        FZM 0,#00FE,gul1,#0103,HeroClr
        FZM 0,#00FE,gul2,#0203,HeroClr
        FZM 0,#00FE,gul3,#0203,HeroClr
        FZM UpdStepUR,#00FE,gul4,#0203,HeroClr
        FZM 0,#FFFE,gul5,#0204,HeroClr
        FZM 0,#FFFE,gul6,#0203,HeroClr
        FZM StRL22,#FFFE,gul7,#0203,HeroClr

StepUpR2
        FZM 0,#00FE,gul8,#0103,HeroClr
        FZM 0,#00FE,gul9,#0203,HeroClr
        FZM 0,#00FE,gula,#0203,HeroClr
        FZM UpdStepUR,#00FE,gulb,#0203,HeroClr
        FZM 0,#FFFE,gulc,#0204,HeroClr
        FZM 0,#FFFE,guld,#0204,HeroClr
        FZM StRL21,#FFFE,gule,#0203,HeroClr

UpdStepUR
        DEC (IY)
        JP UpdGoR


StepDwR1
        FZM 0,#00FE,gdl1,#0203,HeroClr
        FZM 0,#00FE,gdl2,#0204,HeroClr
        FZM 0,#00FE,gdl3,#0204,HeroClr
        FZM 0,#00FF,gdl4,#0203,HeroClr
        FZM VStepDwr1,#00FF,gdl5,#0203,HeroClr
        FZM 0,#FFFE,gdl6,#0203,HeroClr
        FZM StRL22,#FFFE,gdl7,#0203,HeroClr

VStepDwr1
        INC (IY)
        CALL UpdGoR
        LD E,WLKLEN
        CALL exm3blE
        RET NZ
        JP FallRLp

StepDwR2
        FZM 0,#00FE,gdl8,#0203,HeroClr
        FZM 0,#00FE,gdl9,#0204,HeroClr
        FZM 0,#00FE,gdla,#0204,HeroClr
        FZM 0,#00FF,gdlb,#0203,HeroClr
        FZM VStepDwr1,#00FF,gdlc,#0203,HeroClr
        FZM 0,#FFFE,gdld,#0203,HeroClr
        FZM StRL21,#FFFE,gdle,#0203,HeroClr

UpR2    FZM 0,#00FE,ul21,#0103,HeroClr
        FZM 0,#00FE,ul22,#0203,HeroClr
UpR21   FZM UpdUR21,#00FD,ul23,#0204,HeroClr
        FZM 0,#FFFF,ul24,#0204,HeroClr
        FZM 0,#FFFF,ul25,#0203,HeroClr
        FZM 0,#FFFE,ul26,#0204,HeroClr
        FZM 0,#FFFE,ul27,#0204,HeroClr
        FZM StRL22,#FFFE,ul28,#0203,HeroClr

UpdUR21 DEC (IY)
        DEC (IY)
        JP UpdGoR

UpR3    FZM 0,#00FE,ul31,#0103,HeroClr
        FZM 0,#00FE,ul32,#0103,HeroClr
        FZM 0,#00FE,ul33,#0103,HeroClr
        FZM 0,#00FD,ul34,#0204,HeroClr
        FZM 0,#00FD,ul35,#0204,HeroClr
        FZM EUpR3,#00FD,ul36,#0203,HeroClr

EUpR3   DEC (IY)
        LD HL,UpR21
_lih1   JP LDIYHL

UpdDR21 INC (IY)
        INC (IY)
        CALL UpdGoL
        CALL verdwn
        RET NZ
        INC (IY)
        CALL WlkAdr
        LD HL,DwR3
        JR _lih1

UpdDR22 CALL verdwn
        JP Z,FallRLp
        RET 

DwR     FZM 0,#FFFE,ul28,#0203,HeroClr
        FZM 0,#FFFE,ul27,#0204,HeroClr
        FZM 0,#FFFE,ul26,#0204,HeroClr
        FZM 0,#FFFF,ul25,#0203,HeroClr
        FZM 0,#FFFF,ul24,#0204,HeroClr
        FZM UpdDR21,#FFFF,ul23,#0204,HeroClr
        FZM 0,#00FE,ul22,#0203,HeroClr
        FZM StRL22,#00FE,ul21,#0103,HeroClr

DwR3    FZM 0,#00FD,ul36,#0203,HeroClr
        FZM 0,#00FD,ul35,#0204,HeroClr
        FZM 0,#00FD,ul34,#0204,HeroClr
        FZM UpdDR22,#00FE,ul33,#0103,HeroClr
        FZM 0,#00FE,ul32,#0103,HeroClr
        FZM StRL22,#00FE,ul31,#0103,HeroClr

;--------------------Left-----------------------

StandLeft1
        FZS StLLoop1,#00FE,golft01,#0103,HeroClr

StandLeft2
        FZS StLLoop2,#00FE,golft01,#0103,HeroClr

StLLoop1
        LD HL,emukeys
        LD HL,StLL21
        LD HL,FallLLp
        LD (HerFaze+1),HL
        LD (DIRECT1),A
        EX AF,AF'
        CALL HeroStand
        LD A,1
        CALL place_s
        CALL verdwn
        LD HL,LDIYHL
        PUSH HL
        LD HL,FallDwnL
        RET Z
        LD A,(IY+9)
        OR A
        LD C,1
        CALL NZ,loss_sr
        EX AF,AF'
        BIT 4,A
StandL1Fire
        CALL NZ,_ret

        CP 2+8
        JR Z,JmpLsr
        CALL clrfrl
        RRCA 
        LD HL,StandRight1
        RET C
        RRCA 
        JR C,G_left_sr1
        RRCA 
        JP C,KDwL
        RRCA 
        JR C,KUpL
StLLbk  POP HL
StLL21  LD HL,StandLeft1
        JP LDIYHL

G_left_sr1
        LD DE,WLKLEN-1 ;на знакоместо влево и вниз
        CALL exm3bl
        LD HL,StepDwL1
        RET Z
        CP 4
        JR Z,Run_Left_sr1
        RRCA 
        JR NC,ver_step_ul1
        LD HL,StandLeft1
        RET 

Run_Left_sr1
        LD A,(DIRECT1)
        AND #20
        JR NZ,RLs1
        LD DE,WLKLEN-2
        CALL exm3bl
        LD HL,RunLeft1
        CP 4
        RET Z
RLs1    LD HL,GoLeft1
        RET 

JmpLsr
        LD DE,-1
        CALL exm3bl
        EX AF,AF'
        LD HL,JmpLeftSmall
JmpLsr1 LD A,0
        OR A
        JR Z,$+5
        LD HL,JmpLeft
        CALL clrfrl1
        RET Z
        JR StLLbk

setfrl  EX AF,AF'
        LD A,1
        JR clrfrl1+1

clrfrl  EX AF,AF'
clrfrl1 XOR A
        LD (JmpLsr1+1),A
        EX AF,AF'
        RET 

KUpL    LD DE,0
        CALL exm4bl
        RRA 
        RL C
        OR A
        JR NZ,KUpL2
        LD DE,-1-WLKLEN
        CALL exm5bl
        BIT 3,A
        JR Z,KUpL1
        AND #06
        LD HL,UpL3
        JR NZ,KUpL2
        RR C
        RET NC
KUpL2   JP StLL21

KUpL1   AND #1C
        CP #10
        LD HL,UpL2
        RET Z
        JR KUpL2

KDwL    LD DE,WLKLEN*2+1
        CALL exm3bl
        JR NZ,KUpL2
        LD HL,DwL
        RET 

ver_step_ul1
        LD DE,-1-WLKLEN
        CALL exm2bl
        LD HL,StandLeft1
        RET NZ
        LD HL,StepUpL1
        RET 

ver_step_ul2
        LD DE,-1-WLKLEN
        CALL exm2bl
        LD HL,StandLeft2
        RET NZ
        LD HL,StepUpL2
        RET 

StLLoop2
        LD HL,emukeys
        LD HL,StLL21
        LD HL,FallLLp
        LD (HerFaze+1),HL
        LD (DIRECT1),A
        EX AF,AF'
        CALL HeroStand
        LD A,1
        CALL place_s
        CALL verdwn
        LD HL,LDIYHL
        PUSH HL
        LD HL,FallDwnL
        RET Z
        LD A,(IY+9)
        OR A
        LD C,1
        CALL NZ,loss_sr
        EX AF,AF'
        BIT 4,A
StandL2Fire
        CALL NZ,_ret

        CP 2+8
        JP Z,JmpLsr
        CALL clrfrl
        RRCA 
        LD HL,StandRight1
        RET C
        RRCA 
        JR C,G_left_sr2
        RRCA 
        JP C,KDwL
        RRCA 
        JP C,KUpL
        POP HL
StLL22  LD HL,StandLeft2
        JP LDIYHL

G_left_sr2
        LD DE,WLKLEN-1 ;на знакоместо влево и вниз
        CALL exm3bl
        LD HL,StepDwL2
        RET Z
        CP 4
        JR Z,Run_Left_sr2
        RRCA 
        JR NC,ver_step_ul2
        LD HL,StandLeft2
        RET 

Run_Left_sr2
        LD A,(DIRECT1)
        AND #20
        JR NZ,RLs2
        LD DE,WLKLEN-2
        CALL exm3bl     ;было 4, если впереди на высоте 3
        LD HL,RunLeft2  ;непроходимость, не бежал
        CP 4            ;было 8
        RET Z
RLs2    LD HL,GoLeft2
        RET 

        ;0
        ;1,3,5,7
        ;2,6
        ;    0 1 2 3 4 5 6 7
        ;      *   *   *   *
        ;___     * *     * *
        ;            * * * *

GoLeft1
        FZS HeroGo,#00FE,golft02,#0103,HeroClr
        FZS 0,#FFFE,golft03,#0203,HeroClr
        FZS 0,#FFFE,golft04,#0203,HeroClr
        FZS UpdGoL,#FFFE,golft05,#0203,HeroClr
        FZS 0,#00FE,golft06,#0203,HeroClr
        FZS 0,#00FE,golft07,#0203,HeroClr
        FZS StLL22,#00FE,golft08,#0203,HeroClr

GoLeft2 FZS HeroGo,#00FE,golft10,#0103,HeroClr
        FZS 0,#FFFE,golft11,#0203,HeroClr
        FZS 0,#FFFE,golft12,#0203,HeroClr
        FZS UpdGoL,#FFFE,golft13,#0203,HeroClr
        FZS 0,#00FE,golft14,#0203,HeroClr
        FZS 0,#00FE,golft15,#0203,HeroClr
        FZS StLL21,#00FE,golft16,#0203,HeroClr

UpdGoL  DEC (IY+1)
        JP WlkAdr

RunLeft1
        FZS HeroRun,#FFFE,runl1,#0203,HeroClr
        FZS UpdRL3,#FEFE,runl2,#0303,HeroClr
        FZS 0,#FFFE,runl3,#0303,HeroClr
        FZS UpdRL3,#FFFE,runl4,#0203,HeroClr
        FZS StLLoop2,#00FE,runl5,#0203,HeroClr

RunLeft2
        FZS HeroRun,#FFFE,runl6,#0203,HeroClr
        FZS UpdRL3,#FEFE,runl7,#0303,HeroClr
        FZS 0,#FFFE,runl8,#0303,HeroClr
        FZS UpdRL3,#FFFE,runl9,#0203,HeroClr
        FZS StLLoop1,#00FE,runla,#0203,HeroClr

UpdRL3  LD A,(StRLoop1+3)
        CP #C3
        JP Z,RepFaze
UpdRL2  DEC (IY+1)
        CALL setfrl
        JP WlkAdr
;-
StepUpL1
        FZS 0,#00FE,gul1,#0103,HeroClr
        FZS 0,#FFFE,gul2,#0203,HeroClr
        FZS 0,#FFFE,gul3,#0203,HeroClr
        FZS UpdStepUL,#FFFE,gul4,#0203,HeroClr
        FZS 0,#00FE,gul5,#0204,HeroClr
        FZS 0,#00FE,gul6,#0203,HeroClr
        FZS StLL22,#00FE,gul7,#0203,HeroClr

StepUpL2
        FZS 0,#00FE,gul8,#0103,HeroClr
        FZS 0,#FFFE,gul9,#0203,HeroClr
        FZS 0,#FFFE,gula,#0203,HeroClr
        FZS UpdStepUL,#FFFE,gulb,#0203,HeroClr
        FZS 0,#00FE,gulc,#0204,HeroClr
        FZS 0,#00FE,guld,#0204,HeroClr
        FZS StLL21,#00FE,gule,#0203,HeroClr

UpdStepUL
        DEC (IY)
        JP UpdGoL

;------
StepDwL1
        FZS 0,#FFFE,gdl1,#0203,HeroClr
        FZS 0,#FFFE,gdl2,#0204,HeroClr
        FZS 0,#FFFE,gdl3,#0204,HeroClr
        FZS 0,#FFFF,gdl4,#0203,HeroClr
        FZS VStepDwl1,#FFFF,gdl5,#0203,HeroClr
        FZS 0,#00FE,gdl6,#0203,HeroClr
        FZS StLL22,#00FE,gdl7,#0203,HeroClr

VStepDwl1
        DEC (IY+1)
        INC (IY)
        CALL WlkAdr
        CALL exm3blE
        RET NZ
        JP FallLLp

StepDwL2
        FZS 0,#FFFE,gdl8,#0203,HeroClr
        FZS 0,#FFFE,gdl9,#0204,HeroClr
        FZS 0,#FFFE,gdla,#0204,HeroClr
        FZS 0,#FFFF,gdlb,#0203,HeroClr
        FZS VStepDwl1,#FFFF,gdlc,#0203,HeroClr
        FZS 0,#00FE,gdld,#0203,HeroClr
        FZS StLL21,#00FE,gdle,#0203,HeroClr


UpL2    FZS 0,#00FE,ul21,#0103,HeroClr
        FZS 0,#FFFE,ul22,#0203,HeroClr
UpL21   FZS UpdUL21,#FFFD,ul23,#0204,HeroClr
        FZS 0,#00FF,ul24,#0204,HeroClr
        FZS 0,#00FF,ul25,#0203,HeroClr
        FZS 0,#00FE,ul26,#0204,HeroClr
        FZS 0,#00FE,ul27,#0204,HeroClr
        FZS StLL22,#00FE,ul28,#0203,HeroClr

UpdUL21 DEC (IY)
        DEC (IY)
        JP UpdGoL

UpL3    FZS 0,#00FE,ul31,#0103,HeroClr
        FZS 0,#00FE,ul32,#0103,HeroClr
        FZS 0,#00FE,ul33,#0103,HeroClr
        FZS 0,#FFFD,ul34,#0204,HeroClr
        FZS 0,#FFFD,ul35,#0204,HeroClr
        FZS EUpL3,#FFFD,ul36,#0203,HeroClr

EUpL3   DEC (IY)
        LD HL,UpL21
        JP LDIYHL

FallDwnL
        FZS FallLLp,#00FE,golft01,#0103,HeroClr

FallLLp CALL clrfrl
        CALL verdwn
        JP NZ,FLLpE1
        INC (IY)
        CALL WlkAdr
        LD HL,FallDwnL
        IFN ?FlyingSkull
        JP LDIYHL
        ELSE 
        JP RepFze
        ENDIF 

DwL     FZS 0,#FE,ul28,#203,HeroClr
        FZS 0,#FE,ul27,#204,HeroClr
        FZS 0,#FE,ul26,#204,HeroClr
        FZS 0,#FF,ul25,#203,HeroClr
        FZS 0,#FF,ul24,#204,HeroClr
        FZS UpdDL21,#FF,ul23,#204,HeroClr
        FZS 0,#FFFE,ul22,#203,HeroClr
        FZS StLL22,#FE,ul21,#103,HeroClr

DwL3    FZS 0,#FFFD,ul36,#203,HeroClr
        FZS 0,#FFFD,ul35,#204,HeroClr
        FZS 0,#FFFD,ul34,#204,HeroClr
        FZS UpdDL22,#FE,ul33,#103,HeroClr
        FZS 0,#FE,ul32,#103,HeroClr
        FZS StLL22,#00FE,ul31,#103,HeroClr

UpdDL21 INC (IY)
        INC (IY)
        CALL UpdGoR
        CALL verdwn
        RET NZ
        INC (IY)
        CALL WlkAdr
        LD HL,DwL3
        JP LDIYHL

UpdDL22 CALL verdwn
        JP Z,FallLLp
        RET 

PushL   FZS 0,#FE,fgpush+168,#0103,HeroClr
        FZS 0,#FE,fgpush+144,#0103,HeroClr
        FZS 0,#FE,fgpush+120,#0103,HeroClr
        FZS 0,#FFFE,fgpush+72,#0203,HeroClr
        FZS PushLsr,#FFFE,fgpush+24,#0203,HeroClr
        FZS StLL22,#00FE,fgpush,#0103,HeroClr

PushLsr JP _ret

PushR   FZM 0,#FE,fgpush+168,#103,HeroClr
        FZM 0,#FE,fgpush+144,#103,HeroClr
        FZM 0,#FE,fgpush+120,#103,HeroClr
        FZM 0,#FE,fgpush+72,#0203,HeroClr
        FZM PushRsr,#00FE,fgpush+24,#0203,HeroClr
        FZM StRL22,#00FE,fgpush,#0103,HeroClr

PushRsr JP _ret

SwordL  FZS 0,#FE,fgswrd+384,#103,HeroClr
        FZS 0,#FFFE,fgswrd+336,#203,HeroClr
        FZS 0,#FFFE,fgswrd+288,#203,HeroClr
        FZS 0,#FEFE,fgswrd+216,#303,HeroClr
        FZS SwrdLsr,#FEFE,fgswrd+144,#303,HeroClr
        FZS 0,#FEFE,fgswrd+72,#303,HeroClr
        FZS 0,#FFFE,fgswrd+24,#203,HeroClr
        FZS StLL22,#00FE,fgswrd,#103,HeroClr

SwordR  FZM 0,#FE,fgswrd+384,#103,HeroClr
        FZM 0,#FE,fgswrd+336,#203,HeroClr
        FZM 0,#FE,fgswrd+288,#203,HeroClr
        FZM 0,#FE,fgswrd+216,#303,HeroClr
        FZM SwrdRsr,#FE,fgswrd+144,#303,HeroClr
        FZM 0,#FE,fgswrd+72,#303,HeroClr
        FZM 0,#FE,fgswrd+24,#203,HeroClr
        FZM StRL22,#FE,fgswrd,#103,HeroClr

NoHeroSr
        LD HL,NoHero
        LD (HERO+2),HL
        RET 

NoHero  FZS RepFaze

invizible_hero
        LD A,1
        LD (NoRoomChange+1),A
        LD (HERO+1),A
        DEC A
        DEC A
        LD (noinvent+1),A
        RET 

gomode  LD A,#21
        LD (noinvent+1),A
        LD (StRLoop1+3),A
        LD (StRLoop2+3),A
        LD (StLLoop1+3),A
        LD (StLLoop2+3),A
        RET 

stndmode LD A,#C3
        JR gomode+2

loss_sr CP by_head ;паук
        JR Z,lssr1
        CP by_lava
        JR Z,lssr2
        CP by_ty4ka
        JR Z,lssr3
lossr1  LD (IY+9),0
        RET 

lssr1
pauk_y  LD DE,0
        LD A,(IY)
        CP E
        JR NZ,lossr1
        LD A,dmg_elec
lssrp   DEC C
        POP HL
        LD HL,ElecL
        LD DE,ElecR
        LD (elecdmg1),A
        JR lssre

lssr2   DEC C
        POP HL
        LD HL,RasplL
        LD DE,RasplR
lssre   JR Z,$+3
        EX DE,HL
        RET 

lssr3   LD A,dmg_ty4ka
        JR lssrp

SubLif  FZS 0,#FE,dyscul,#103,HeroClr
        FZS 0,#FE,dyscul-1,#103,HeroClr
        FZS 0,#FE,dyscul-5,#103,HeroClr
        FZS 0,#FE,dyscul-11,#103,HeroClr
        FZS fallscsnd,#FE,dyscul-18,#103,HeroClr
        FZS 0,#FE,dyscul-13,#103,HeroClr
        FZS 0,#FE,dyscul-12,#103,HeroClr
        FZS fallscsnd,#FE,dyscul-18,#103,HeroClr
        FZS NxAL2

SubLini LD A,(LIVES)
        LD HL,SubLif
        LD DE,SubLini
        JP ALiy

AddLif  FZS 0,#FE,ks1,#103,HeroClr
        FZS 0,#FE,ks2,#203,HeroClr
        FZS 0,#FE,ks3,#303,HeroClr

        FZS 0,#FE,ks41,#203,HeroClr
         FZSP #02FE,ks42,#0202,HeroClr

        FZS 0,#FE,ks51,#203,HeroClr
         FZSP #03FE,ks52,#0202,HeroClr

        FZS 0,#FE,addlif8+48,#203,HeroClr
         FZSP #04FF,ks62,#0202,HeroClr

AddLif2 FZS 0,#FE,addlif5,#103,HeroClr
         FZSP #04FF,ks7,#0202,HeroClr
        FZS 0,#FE,addlif2,#203,HeroClr
         FZSP #05FF,ks8,#0202,HeroClr
        FZS 0,#FE,addlif3,#203,HeroClr
         FZSP #05FF,ks7,#0102,HeroClr
         FZSP #06FF,ks9,#0102,HeroClr
        FZS 0,#FE,addlif4,#203,HeroClr
         FZSP #06FF,ks7,#0102,HeroClr
AddLif1 FZS 0,#FFFE,addlif5,#303,HeroClr
        FZS 0,#FFFE,addlif6,#303,HeroClr
        FZS 0,#FFFE,addlif7,#303,HeroClr
        FZS NxAL,#FFFE,addlif8,#303,HeroClr

NxAL    LD A,(IY+1)
        CP 14
        JR Z,NxAL1
        DEC A
        LD (IY+1),A
        LD HL,AddLif1
        JP LDIYHL

NxAL1
NxAL2   LD A,#FF
        LD (IY),A
        LD HL,TBL_OMS
        LD (OOOSt+1),HL
NxAL3   LD DE,0
        LD HL,0
        LD (NxAL3+1),HL
        LD A,D
        OR A
        RET Z
        PUSH DE
        RET 

AddLini CALL alifsnd
        LD A,(LIVES)
        SUB 2
        LD HL,AddLif
        LD DE,AddLini   ;чтобы потом если чего снова сработало
        JP ALiy

ALiy    LD IY,ALIFEBUFF
        LD C,(IY)
        INC C
        JR Z,ALiy1
        LD (NxAL3+1),DE
        RET 

ALiy1   LD DE,#1035-256
        ADD A,D
        LD D,A
        LD (IY),E
        LD (IY+1),D
        CALL LDIYHL
        LD HL,TBL_SCOMS
        LD (OOOSt+1),HL
        XOR A
        RET 

;---
ReHerFaze
        PUSH IY
        LD IY,HERO
HerFaze CALL 0
        POP IY
        RET 

HeroRun LD A,_HeroRun
        LD (KindHero),A
        RET 

HeroStand
        XOR A ;LD A,_HeroStand
        JR HeroRun+2

HeroGo
        LD A,_HeroGo
        JR HeroRun+2

        DISPLAY "Описалово Хероя: ",$-begher
