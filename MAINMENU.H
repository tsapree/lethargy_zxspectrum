;Главное Меню.

        MAIN "",#C0

depack_game
;main_pg        EQU 0
;lvl_pg         EQU 1
;gfx_pg         EQU 3
;mus_pg         EQU 4
;fzs_pg         EQU 6
;agfx_pg        EQU 7
        LD A,lvl_pg
        CALL depack0
        LD A,gfx_pg
        CALL depack0
        LD A,mus_pg
        LD HL,#DE00
        LD DE,#CA2F
        CALL depack1
        LD A,fzs_pg
        CALL depack0
        LD A,agfx_pg
depack0 LD DE,#C000
        LD HL,#C000
depack1 CALL ONPAGE
        JP DEHRUST

M_MENU
        CALL SaveVars
        CALL MMInit
        CALL SHOWROOM

MMLp1   EI 
        HALT 
        XOR A
        LD (intcntr+1),A
        CALL SHWSPZ

        IF ?SaveMenuMove
        CALL QAOPSP     ;если запись скрипта
        CALL VerFir
        LD A,#FB        ; опрос на выход (E)
        IN A,(#FE)      ;  !
        AND #4          ;  !
        JP NZ,MMLp1     ;  !
        ELSE 
        IFN ?SAVEOBJ-2
        DISPLAY "опрос на выход из меню (E)"
        LD A,#FB
        IN A,(#FE)
        AND #4
        JP Z,IM1
        ENDIF 
        CALL MM_SR
        JR Z,MMLp1
        ENDIF 

        IFN ?SaveMenuMove
        JP S_GAME       ;  !
        ELSE 
        LD A,mmgo_pg
        CALL ONPAGE
        CALL IM1
        LD HL,_SVname
        LD DE,#5CDD
        LD BC,9
        LDIR 
        LD DE,#C000
        LD HL,(emk0+1)
        INC HL
        INC HL
        LD (HL),0
        INC HL
        XOR A
        SBC HL,DE
        EX DE,HL
        LD C,#0B
        CALL #3D13
        XOR A
        CALL ONPAGE
        RET 

_SVname DB "goself  C"

        ENDIF 

MM_SR   CALL 0
        XOR A
        RET 

QAOPSP
        LD BC,#100
inkWALK LD A,#FE        ;SS
        IN A,(#FE)
        AND 1
        CP B
        RL C

inKEMP1 NOP 
        NOP 

inkFIRE LD A,#7F
        IN A,(#FE)
        AND 1
        CP B
        RL C

inkUP   LD A,#FB
        IN A,(#FE)
        AND 1
        CP B
        RL C

inkDOWN LD A,#FD
        IN A,(#FE)
        AND 1
        CP B
        RL C

inkLEFT LD A,#DF
        IN A,(#FE)
        AND 2
        CP B
        RL C

inkRIGH LD A,#DF
        IN A,(#FE)
        AND 1
        CP B
        RL C

        LD A,C
inkR1   AND #3F
        LD (DIRECT),A
        RET 

inKEMP2 IN A,(#1F)
        AND #1F
        RRC C
        RRC C
        RRC C
        OR C
        JR inkR1

DIRECT  DB 0
DIRECT1 DB 0

VerFir  LD A,0  ;0 - нет файра, #10 - файр, иначе - нет
        OR A
        JR Z,VerFir1
        AND #10
        JR NZ,VerFir1
        LD A,(DIRECT)
        AND #10
        XOR #10
        RET Z
        XOR A
        LD (VerFir+1),A
        RET 

VerFir1 LD A,(DIRECT)
        AND #10
        LD (VerFir+1),A
        RET 

W4Enter JR W4NEntN
        CALL W4Ent1
        RET C
        LD A,#18
        LD (W4Enter),A
        RET 

W4Ent1  LD A,#BF
        IN A,(#FE)
        AND 1
        CP 1
        RET 

W4NEntN CALL W4Ent1
        CCF 
        RET C
        CCF 
        LD A,#3E
        LD (W4Enter),A
        RET 

RestVars
        CALL ONPAGE_agfx
        LD HL,NULL_VARS+SIZE_VARS-1
        LD DE,BEGIN_VARS+SIZE_VARS-1
        LD BC,SIZE_VARS
        LDDR 
        JP ONPAGE_main

MMInit
        CALL RestVars
        LD A,7
        CALL ClrScrA

        LD HL,room_menu_page*256+room_menu_start
        LD DE,crds_menu_start
        LD BC,StandRight1
        CALL setupHERO1
        CALL ONPAGE_agfx
        LD HL,#4028
        LD DE,mmlogo
        LD BC,#1003
        CALL outspr
        LD HL,#5828
        LD C,3
        CALL outatr

        IF ?SaveMenuMove
        LD A,mmgo_pg
        CALL ONPAGE
        LD HL,#C000
        LD (emk0+1),HL
        LD (HL),1
        INC HL
        LD (HL),0
        ENDIF 

        LD A,fzs_pg
        CALL ONPAGE
        LD A,#CD
        CALL GMI1
        LD HL,MMSEL
        LD (MMTXTS+1),HL
        LD HL,CTRLSEL
        LD (MM_SR+1),HL
        RET 

setupHERO1
        LD A,#21
        LD (i_plmuz),A
        LD (i_game),A
        LD (i_plsnd),A
        XOR A
        LD (MMatr+2),A
        LD (intcntr+1),A
        LD A,#C3
        LD (SHOWROOM),A
setupHERO2
        LD A,H;room_menu_page
        LD (LVL_pg),A
        LD A,L;room_menu_start
        LD (ROOM),A

setupHERO
        LD HL,HERO
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        LD (HL),C
        INC HL
        LD (HL),B
        INC HL
        LD B,6
        XOR A
        LD (HL),A
        INC HL
        DJNZ $-2
        LD (HL),#FF
        LD HL,HeroCrds
        LD (SetCrdHero+1),HL
        RET 

GMInit
        CALL RestVars
        CALL CleAtr
        LD A,gfx_pg
        CALL ONPAGE

        LD HL,#4000
        LD DE,panel
        LD BC,#2005
        CALL outspr
        EX DE,HL
        LD DE,#5800
        LD BC,32*5
        LDIR 

        LD HL,room_game_page*256+room_game_start
        LD DE,crds_game_start
        LD BC,StandRight1
        CALL setupHERO2
        LD A,1
        LD (MMatr+2),A

        LD A,#21
        LD (SHOWROOM),A
        LD (i_plmuz),A
        LD A,#CD
        LD (i_game),A
        LD (i_plsnd),A

        LD A,fzs_pg
        CALL ONPAGE
        LD A,#21
GMI1    LD (StLLoop1),A
        LD (StLLoop2),A
        LD (StRLoop1),A
        LD (StRLoop2),A
        CALL gomode
        LD HL,TBL_OMS
        LD (OOOSt+1),HL
        LD A,agfx_pg
        CALL ONPAGE
        LD HL,begin_buff4coords
        LD DE,begin_buff4coords+1
        LD BC,len_buff4coords
        LD (HL),#FF
        LDIR 
        CALL cleMONSTRS
        JP ONPAGE_fzs

SHOWMMROOM
        CALL Remember_Coords
        XOR A
        LD (flybfycur),A
        LD (NoRoomChange+1),A

        LD HL,#5AFF
        LD DE,#5AFE
        LD BC,#2FF-160
        LD (HL),A
        LDDR 

        LD A,main_pg
        CALL ONPAGE
        CALL SHROM2
        IFN ?SaveMenuMove
        LD A,agfx_pg
        CALL ONPAGE
        CALL MMTXTS
        ENDIF 
        LD A,main_pg
        JP ONPAGE

        IF 1
SHMR2   LD (HL),.OLVDATA
        PUSH DE
        LD A,(DE)
        RES 7,D
        RES 7,A
        LD (DE),A
        LD A,D
        AND %1011
        ADD A,A
        ADD A,A
        ADD A,A         ;#58-#5B: %01011000-%01011011
        LD D,A
        LD B,8
SHMR3   SET 7,D
        LD A,(DE)
        RES 7,D
        LD (DE),A
        INC D
        DJNZ SHMR3
        POP DE
        RET 
        ENDIF 

        IF ?SaveMenuMove
emukeys
        PUSH AF
        PUSH AF
        LD A,mmgo_pg
        CALL ONPAGE
        POP AF
emk0    LD HL,#C000
        INC HL
        CP (HL)
        JR Z,emk1
        INC HL
        LD (HL),0
        INC HL
        LD (HL),A
emk1    DEC HL
        INC (HL)
        JR NZ,emk2
        DEC (HL)
        INC HL
        INC HL
        LD (HL),A
        DEC HL
        LD (HL),1
emk2    LD (emk0+1),HL
        LD A,fzs_pg
        CALL ONPAGE
        POP AF
        RET 

        ELSE 

emukeys LD A,1
        DEC A
        JR Z,emk1
        LD (emukeys+1),A
n_ekey  LD A,0
        LD (DIRECT1),A
        RET 

emk1
        LD HL,(ektbl)
        CALL ONPAGE_agfx
        LD A,(HL)
        OR A
emkZ    CALL Z,emk2
        LD A,(HL)
        LD (emukeys+1),A
        INC HL
        LD A,(HL)
        LD (n_ekey+1),A
        INC HL
        LD (ektbl),HL
        CALL ONPAGE_fzs
        JR n_ekey

emk2    LD HL,ekeytbl
        RET 

        ENDIF 

MMTXTS  LD HL,NOTXT
        LD DE,SavUndTxtBuff
        LD (mmostr+2),DE
        LD A,#FF
        LD (DE),A

MMTXTS1 LD E,(HL)
        INC HL
        LD A,(HL)
        INC HL
        OR A
        RET Z
        LD D,A
        PUSH HL
        CALL mmostr
        POP HL
        JR MMTXTS1

mmostr  EXX 
        LD DE,SavUndTxtBuff
        EXX 
        EX DE,HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL

        PUSH DE
        PUSH HL
        LD L,E
        LD H,0
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        ADD HL,HL
        LD A,L
        OR D
        LD L,A
        ADD HL,HL
        EX DE,HL
        LD HL,TBL_OMS-960 ;32*5*6
        ADD HL,DE
        ADD HL,DE
        ADD HL,DE
        PUSH HL
        EXX 
        POP HL
        LD BC,6
        EXX 
        POP HL
        POP DE

MMPR1   PUSH HL
        CALL A2SA
        POP IX
        EX DE,HL
        LD A,7+64
MMPR6   SUB 64
MMPR5   LD (MMPR3+1),A
MMPR2   LD A,(IX)
        OR A
        JR NZ,MMPR2N
        EXX 
        LD (mmostr+2),DE
        EXX 
        RET 

MMPR2N  INC IX
        CP 32
        JR Z,MMPR4
        JR C,MMPR5
        CP 127
        JR NC,MMPR6
        PUSH AF
        CALL MMPR8
        POP AF
        CALL MMPRS
MMPR4   INC E
        EXX 
        ADD HL,BC
        EXX 
        JR MMPR2

MMPR5REP LD DE,0
MMPRS   LD (MMPR5REP+1),DE
        PUSH DE
        ADD A,A
        LD L,A
        LD H,0
        ADD HL,HL
        ADD HL,HL
        LD DE,mmfnt-256
        ADD HL,DE
        POP DE
        LD C,D
        LD B,8
        LD A,(HL)
        LD (DE),A
        INC HL
        INC D
        DJNZ $-4
        LD A,C
        CALL scratr+1
        LD L,E
MMPR3   LD (HL),7
        LD D,C
        RET 

MMPR8   LD (MMPR9+1),DE
        EXX 
        EX DE,HL
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        EX DE,HL
        LD A,(HL)
        CP .OLVDATA
        JR Z,$+4
        LD A,.OCleSpr
        LD (DE),A
        INC DE
        JR NZ,MMPR7
        PUSH HL
        PUSH BC
        LD B,8
MMPR9   LD HL,0
        EX DE,HL
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        EX DE,HL
        LD A,(HL)
        LD (DE),A
        INC H
        INC DE
        DJNZ $-4
        DEC H
        CALL scratr
        LD A,(HL)
        LD (DE),A
        INC DE
        POP BC
        POP HL
MMPR7   LD A,#FF
        LD (DE),A
        LD (HL),.OLVDATA
        EXX 
        RET 

RepUTxt CALL ONPAGE_agfx
        LD HL,SavUndTxtBuff
RUT1    LD A,(HL)
        INC HL
        LD E,A
        INC A
        RET Z
        LD D,(HL)
        INC HL
        LD A,(HL)
        INC HL
        LD (DE),A
        CP .OLVDATA
        JR NZ,RUT1
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD B,8
        LD A,(HL)
        LD (DE),A
        INC D
        INC HL
        DJNZ $-4
        DEC D
        EX DE,HL
        CALL scratr
        EX DE,HL
        LD A,(HL)
        INC HL
        LD (DE),A
        JR RUT1

CTRLSEL
        CALL nullpressed
        CALL redef
        JR NC,CTS1
        SUB "1"
        RET C
        JR Z,SELKEYB
        DEC A
        JR Z,SELSINC
        DEC A
        JR Z,SELCURS
        DEC A
        JR Z,SELKEMP

        IFN ?NoSound
        DEC A
;       JR Z,SELSTER
        ENDIF 

CTS1    CALL QAOPSP
        CALL VerFir

NOE2GAM RET ;Z

        POP HL
        RET 

SELKEYB
        XOR A
        LD DE,selkeyb
        LD HL,SELKEYB
SKB5    LD BC,0
SKB51   LD (SELK2+1),A
        LD (SELK21+1),HL
        LD (inKEMP1),BC
        LD HL,SELK1
        LD (MM_SR+1),HL
        LD HL,MMWK
        LD (MMTXTS+1),HL
        INC HL
        INC HL
        LD BC,mmup
        CALL SKB3
        CALL RepUTxt
        JP MMTXTS

SELSINC
        LD BC,pRESINC
        CALL preRedE
        LD A,5
        LD HL,SELSINC
        LD DE,selsinc
        JR SKB5

SELCURS
        LD BC,pRECURS
        CALL preRedE
        LD A,5
        LD HL,SELCURS
        LD DE,selcurs
        JR SKB5

SELKEMP
        LD A,5
        LD HL,SELKEMP
        LD DE,selkemp
        LD BC,inKEMP2-inkFIRE*256+#18
        JR SKB51

SKB3    LD A,1
        LD (SKB6+1),A

SKB2    LD A,(DE)
        OR A
        RET Z
        SUB "?"
        JR NZ,SKB4
SKB6    CP 1
        LD (SKB6+1),A
SKB4    LD (HL),A
        JR Z,$+3
        LD (HL),C
        INC HL
        LD (HL),A
        JR Z,$+3
        LD (HL),B
        INC HL

SKB1    LD A,(BC)
        OR A
        JR Z,$+5
        INC BC
        JR SKB1

        DEC BC
        LD A,(DE)
        LD (BC),A
        INC DE
        INC BC
        INC BC
        JR SKB2

selkeyb DB "?","?","?","?","?","?","?",0
selkemp DB "^","^","^","^","^","?","?",0
selsinc DB "9","8","6","7","0","?","?",0
selcurs DB "7","6","5","8","0","?","?",0

SELK1
SELK2   LD A,0
        CP 7
        JP C,Selk2
        CALL nullpressed
        CALL redef
        RET NC
        CP "N"
SELK21  JP Z,SELKEYB
        CP "Y"
        RET NZ
        LD A,#C8 ;RET Z
        LD (NOE2GAM),A
        LD HL,mmpres
        LD (MMSEL2F),HL
        LD HL,MMSEL
        LD (MMTXTS+1),HL
        LD HL,CTRLSEL
        LD (MM_SR+1),HL
        CALL RepUTxt
        JP MMTXTS

nullpressed
        PUSH HL
        PUSH BC
        LD HL,keystbl
        LD B,5*8
        RES 7,(HL)
        INC HL
        DJNZ $-3
        POP BC
        POP HL
        RET 

preRedE LD HL,w4rKEYB+4
        LD A,5
pRE1    EX AF,AF'
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD A,(BC)
        LD (DE),A
        INC BC
        INC DE
        INC DE
        INC DE
        INC DE
        LD A,(BC)
        INC BC
        LD (DE),A
        LD DE,8-2
        ADD HL,DE
        EX AF,AF'
        DEC A
        JR NZ,pRE1
        LD E,5
pRE2    LD A,(BC)
        INC BC
        LD HL,keystbl
        CP (HL)
        JR Z,$+5
        INC HL
        JR $-4

        SET 7,(HL)
        DEC E
        JR NZ,pRE2
        RET 

pRESINC DB #EF,2,#EF,4,#EF,16,#EF,8,#EF,1
        DB "09876"
pRECURS DB #EF,8,#EF,16,#F7,16,#EF,4,#EF,1
        DB "56780"

Selk2
        LD HL,w4rKEYB
        ADD A,A
        ADD A,A
        ADD A,A
        LD E,A
        LD D,0
        ADD HL,DE
SELK3   LD A,0
        INC A
        AND 3
        LD (SELK3+1),A
SELK4   LD A,1
        JR NZ,$+7
        XOR 1!6
        LD (SELK4+1),A
        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD (DE),A

        PUSH HL
        CALL redef
        JR NC,$+4
        SET 7,(HL)
        POP HL
        RET NC

        PUSH AF
        PUSH AF
        CALL ONPAGE_agfx
        LD A,7
        LD (MMPR3+1),A
        POP AF
        PUSH HL
        PUSH BC
        CALL MMPR5REP
        POP BC
        POP HL
        POP AF

        LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        LD (DE),A
        INC DE
        INC DE
        LD A,(DE)
        OR A
        JR Z,SELK5
        PUSH HL
        PUSH BC
        LD HL,MMWK
        LD A,(HL)
        INC HL
        OR (HL)
        INC HL
        JR NZ,$-4
        LD (HL),0
        INC HL
        LD (HL),0
        DEC HL
        DEC HL
        LD (HL),D
        DEC HL
        LD (HL),E
        CALL mmostr
        POP BC
        POP HL
SELK5   LD E,(HL)
        INC HL
        LD D,(HL)
        INC HL
        EX DE,HL
        LD (HL),B
        INC HL
        INC HL
        INC HL
        INC HL
        LD (HL),C
        EX DE,HL
        LD A,(SELK2+1)
        INC A
        LD (SELK2+1),A
        XOR A
        RET 

w4rKEYB DW #5937,mmdown-2,inkUP+1,0
        DW #5957,mmleft-2,inkDOWN+1,0
        DW #5977,mmright-2,inkLEFT+1,0
        DW #5997,mmfire-2,inkRIGH+1,0
        DW #59B7,mmselec-2,inkFIRE+1,0
        DW #59F7,mmwalk-2,W4Ent1+1,0
        DW #5A17,mmok-2,inkWALK+1,0
        DW 0

SaveVars
        CALL ONPAGE_agfx
        LD HL,BEGIN_VARS
        LD DE,NULL_VARS
        LD BC,SIZE_VARS
        LDIR 
        LD A,(SaveVars)
        ADD A,#C9-#CD
        LD (SaveVars),A
        JP ONPAGE_main

redef
redef1  LD A,1
        OR A
        JR Z,redef2
        XOR A
        IN A,(#FE)
        CPL 
        AND 31
        RET NZ
redef2  LD (redef1+1),A
        IN A,(#FE)
        CPL 
        AND 31
        RET Z
        LD (redef1+1),A
        LD HL,keystbl
        LD BC,#7FFE
redef5  IN A,(C)
        LD DE,#8005
redef4  RLC D
        RRCA 
        JR NC,redef3
redef6  INC HL
        DEC E
        JR NZ,redef4
        RRC B
        JR C,redef5
        RET 

redef3  BIT 7,(HL)
        JR NZ,redef6
        LD A,(HL)
        LD C,D
        SCF 
        RET 

keystbl DB "_]MNB"
        DB "[LKJH"
        DB "POIUY"
        DB "09876"
        DB "12345"
        DB "QWERT"
        DB "ASDFG"
        DB "\ZXCV"


;меню выбора органа управления
MMSEL   DW mmkbd,mmkmp,mmsin,mmcur,mmcss
        IFN ?NoSound
        DW mmsnd,mmabc
        ENDIF 
MMSEL2F DW 0,0
mmkbd   DB 10,10,#86, "1",7," KEYBOARD",0
mmsin   DB 11,10,#86, "2",7," SINCLAIR",0
mmcur   DB 12,10,#86, "3",7," CURSOR",0
mmkmp   DB 13,10,#86, "4",7," KEMPSTON",0
mmsnd
        IFN ?NoSound
        DB 15,10,#86, "5",7," STEREO",0
mmabc   DB 15,19,15,"ABC",0
        ENDIF 
mmpres  DB 19,5,#5,"HIT FIRE TO START GAME",0
mmcss   DB 22,3,"(C) 2001-2003 STUDIO STALL",0

;
MMWK    DW mmpak4,0,0,0,0,0,0,0,0,0,0

mmpak4  DB 7,9,6,"PRESS A KEY FOR",0
mmup    DB 9,18,        "UP - ?",0
mmdown  DB 10,16,     "DOWN - ?",0
mmleft  DB 11,16,     "LEFT - ?",0
mmright DB 12,15,    "RIGHT - ?",0
mmfire  DB 13,16,     "FIRE - ?",0
mmselec DB 15,14,   "SELECT - ?",0
mmwalk  DB 16,16,     "WALK - ?",0
mmok    DB 18,15,#84,"OK? (Y/N)",0

NOTXT   DW 0

RunFiCut
        POP HL
        DEC HL
        DEC HL
        DEC HL
        LD (HL),#C9
        LD HL,Exit2FiCut+1

        IF ?SAVEOBJ-2
        LD (HL),.EXITCS ;FinalCut
        INC HL
        LD (HL),'EXITCS ;FinalCut
        ELSE 
        LD (HL),.FinalCut
        INC HL
        LD (HL),'FinalCut
        ENDIF 
        LD HL,SDG_1+1
        LD (HL),.FinalCut
        INC HL
        LD (HL),'FinalCut
        RET 

FinalCut
        POP HL
        XOR A
        OUT (#FE),A
        CALL FCInit
        CALL InitOSp

        LD B,60
        EI 
        HALT 
        DJNZ $-1

        CALL SHOWROOM
        CALL FCLp0
        CALL ClrScrF7
        LD HL,Logo1_scr
        LD DE,Logo1_scr_1
        LD BC,Logo1_len
        CALL exch
        LD HL,Logo2_scr
        LD DE,Logo2_scr_1
        LD BC,Logo2_len
        CALL exch
        LD HL,end2
        LD DE,end2_temp
        LD BC,end2_temp_size
        CALL exch
        CALL ONPAGE_lvl
        LD HL,_ocodestart
        LD DE,GGFX
        LD BC,_ocodesize
        LDIR 
        JP OUTRO_TEXT

FCLp0   XOR A
        LD (FCLp2+1),A

FCLp1   EI 
        HALT 
        XOR A
        LD (intcntr+1),A
        CALL SHWSPZ
FCLp2   LD A,0
        OR A
        RET NZ
        JR FCLp1

FCInit  DI 

        IF ?SAVEOBJ-2
        LD A,lvl_pg
        CALL depack0
        ENDIF 

        CALL IM2
        XOR A
        CALL ClrScrA

        IFN ?SAVEOBJ-2
        LD HL,#C000
LdRM    LD A,out_pg_virt
        CALL ONPAGE
        PUSH HL
        LD DE,#5B00
        LD BC,#100
        LDIR 
        LD A,lvl_pg
        CALL ONPAGE
        POP DE
        LD HL,#5B00
        LD BC,#100
        LDIR 
        EX DE,HL
        LD A,H
        OR A
        JR NZ,LdRM
        ENDIF 

        CALL RestVars

        LD HL,room_outro_page*256+room_outro_start
        LD DE,crds_outro_start
        LD BC,AppearR
        CALL setupHERO1

        LD A,fzs_pg
        CALL ONPAGE
        LD A,#CD
        CALL GMI1
        LD HL,NOTXT
        LD (MMTXTS+1),HL
        LD HL,ekeyoutrotbl
        LD (ektbl),HL
        LD HL,emustop
        LD (emkZ+1),HL
        CALL ONPAGE_lvl
        LD HL,FCMUZA
        LD DE,#CA2F
        LD BC,SIZE_FCMUZA
        PUSH DE
        PUSH BC
        LD DE,ATRS_BUFF
        PUSH DE
        LDIR 
        CALL ONPAGE_mus
        POP HL
        POP BC
        POP DE
        LDIR 
        CALL INIT
        LD A,#CD
        LD (i_plmuz),A
        RET 

emustop LD HL,ekeystop
        INC A
        LD (FCLp2+1),A
        RET 

exch    CALL ONPAGE_lvl
        PUSH DE
        PUSH BC
        LD DE,ATRS_BUFF
        PUSH DE
        LDIR 
        CALL ONPAGE_fzs
        POP HL
        POP BC
        POP DE
        LDIR 
        RET 

fcemukey
        LD A,0
        INC A
        LD (fcemukey+1),A
        SUB 20
        JR NC,fcem0
        XOR A
        RET 

fcem0   SUB 9
        JR NC,fcem1
fcem3   LD A,ri
        RET 

fcem1   JR NZ,fcem2
        INC A
        LD (NoRoomChange+1),A
        LD HL,Drawing
fcem4   POP DE
        LD DE,LDIYHL
        PUSH DE
        RET 

fcem2   SUB 10
        JR C,fcem3
        LD HL,ScBye
        JR fcem4

EM_MENU
        DISPLAY "MMenu size: ",EM_MENU-M_MENU

        ORG #C000,agfx_pg
        LOCAL 
;------------------------------------------------------------
; Compiled by Hell Editor v0.7 (c) 2001-2 tsap ree stall

        DW room00,room01,room02,room03,room04,room05,room06
        DW room07

;Nonamed!
room00  DD #05000E14
        DD #0031510033090204030D06000F05040300126C10000405030013
        DD #0F00220E030A0600110F0016090403020302190106000C0F0002
        DD #106D0119011900010065062A02360428091204
        DD #01FB03FBFFFF
        DB #01,#09,Efire1,#00
        DB #0B,#0C,ERebronR,#00
        DB #04,#02,ERebronR,#01
        DB #FF
        DB #FF

;Nonamed!
room01  DD #00090D17
        DD #190046190119000E5100070503020A00150F0018090204020800
        DD #160D0A06004505040204030A0600110E0A106D001A0245041504
        DD #2E05160345072F
        DD #FF020503FCFF
        DB #02,#13,Efire1,#01
        DB #FF
        DB #FF

;Nonamed!
room02  DD #05020E08
        DD #000E51001A0502030600056C0F000A1900151900191900010029
        DD #04110214021802
        DD #01FB03FBFF0402
        DB #00,#06,Efire1,#02
        DB #FF
        DB #FF

;Nonamed!
room03  DD #00081316
        DD #000A19003C51000619000651000F5818004318004318003F1800
        DD #3F1901040D06000E19011901020A000519011901190003190119
        DD #010A016D0007000A0242021602420242023E023E050E04070602
        DD #0509
        DD #0005040500F803FA
        DB #02,#05,Efire1,#03
        DB #02,#13,Efire1,#04
        DB #11,#02,ERebronL,#00
        DB #FF
        DB #FF

;Nonamed!
room04  DD #05150705
        DD #001A0903030600026D100001001A0405
        DD #FF0000FFFF
        DB #FF
        DB #FF

;Nonamed!
room05  DD #0005101B
        DD #340177013401340134013839343A77000B353101320133000231
        DD #01320133000E35001A35000230000620000C3401340135000221
        DD #00062C000C357700052B00133400045100083000025100073401
        DD #35000625000625000A35340019355400072800062F0008340135
        DD #000F2D00083577000257000630000E3401340009220006220006
        DD #340177000A230006230003340134017600093401340134013401
        DD #34013401340176000F76017701770013001A011A013105160133
        DD #03180133033202180216040A0E28
        DD #FFFF0618FF
        DB #05,#00,Efire1,#05
        DB #05,#0C,Efire1,#06
        DB #FF
        DB #FF

;Nonamed!
room06  DD #081D0603
        DD #001135001101
        DD #FF07FDFFFF
        DB #FF
        DB #FF

;Nonamed!
room07  DD #02000920
        DD #0000340134013401340134013401340134013401340134013401
        DD #34013401340134000100FF000120
        DD #FF0700FFFF
        DB #FF
        DB #FF

;-----------------------------------------------------
        ENDL 
