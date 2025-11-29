;предметы

        MAIN "",#C0

;-----------------------

chest_it OR A
        LD (IY+5),A
        RET Z
        DEC A
        LD L,A
        ADD A,A
        ADD A,A
        ADD A,L
        ADD A,A
        LD HL,OutChest1
        ADD A,L
        LD L,A
        ADC A,H
        SUB L
        LD H,A
        LD A,(IY+2)
        LD (IY+6),A
        LD A,(IY+3)
        LD (IY+7),A
        LD (IY+5),2     ;кол-во попаданий
        JP LDIYHL

elem_sr SUB Eelem1
        LD (r_sr_2-1),A
        LD HL,ElemXtaken
        CALL ver_took
        RET NZ
        LD HL,OutEl1
        XOR A
        JR r_sr_3

rune_sr
        SUB Erune1
        LD (r_sr_2-1),A
        LD (r_sr_4+1),A
        LD HL,RuneXtaken
        CALL ver_took
        RET NZ
r_sr_4  LD A,0
        OR A
        JR Z,$+4
        LD A,1  ;chest1
        LD HL,OutRune1
r_sr_3  ADD HL,DE
r_sr_1  PUSH HL
        CALL runebfy
        POP HL
        LD (IY+2),L
        LD (IY+3),H
        LD (IY+4),0
r_sr_2  CALL chest_it
        JP runebfe


takerune
        CALL check22
        RET NC
        LD (IY),#FE
        LD E,(IY+4)
        LD D,0
        LD HL,RuneXtaken
        ADD HL,DE
        SET 7,(HL)
        JP viz_runes

;       IF X1>=X2 AND X1<X2+SX2 THEN YES!
;       IF X2>=X1 AND X2<X1+SX1 THEN YES!

check22
        LD A,#FE        ;смещение спрайта по IY относ. вертик
        LD BC,#0202     ;размеры спрайта, кот. по IY наход

check_hero
        LD DE,#0103     ;размеры чела
        LD HL,HERO      ;адрес описателя

check   ADD A,(HL)
        SUB (IY)
        JR C,verrng1
        CP C
        JR verrng0

verrng1 NEG 
        CP E
verrng0 RET NC
        INC HL
        LD A,(HL)
        SUB (IY+1)
        JR C,verrng2
        CP B
        RET 

verrng2 NEG 
        CP D
        RET 


key_sr  SUB Ekey1
        LD (r_sr_2-1),A
        LD HL,KeyXtaken
        CALL ver_took
        RET NZ
        LD HL,OutKey1
        ADD HL,DE
        LD A,1  ;chest1
        JR r_sr_1

ver_took
        LD D,0
        LD E,A
        ADD HL,DE
        ADD A,A
        ADD A,A
        ADD A,E
        LD E,A
        BIT 7,(HL)
        RET 

;какие одинаковые процедуры! надо в одну обьеденить!

sword_sr
        LD A,(Swordtaken)
        OR A
        RET NZ
        LD HL,OutSword
        LD A,1  ;chest1
        JP r_sr_1

axe_sr
        LD HL,OutAxe
        LD A,2  ;chest1
        JP r_sr_1

bow_sr  LD A,(Bowtaken)
        OR A
        RET NZ
        LD HL,OutBow
        LD A,1  ;chest1
        JP r_sr_1

arr_sr
        EX AF,AF'
        LD (r_sr_2-1),A
        LD HL,ArrS
        CALL ver_took
        RET NZ
        LD HL,OutArr
        LD A,2  ;chest1
        JP r_sr_1

fbal_sr
        EX AF,AF'
        LD (r_sr_2-1),A
        LD HL,FBalls
        CALL ver_took
        RET NZ
        LD HL,OutFBal
        LD A,1  ;chest1
        JP r_sr_1

Life_sr EX AF,AF'
        LD (r_sr_2-1),A
        LD HL,Livetaken
        CALL ver_took
        RET NZ
        LD HL,OutLife
        LD A,3  ;chest1
        JP r_sr_1

Kap_sr  EX AF,AF'
        LD (r_sr_2-1),A
        LD HL,Kaptaken
        CALL ver_took
        RET NZ
        LD HL,OutKap
        LD A,2  ;chest1
        JP r_sr_1

almaz_sr LD A,(Almaztaken)
        OR A
        RET NZ
        LD HL,OutAlmaz
        LD A,2  ;chest1
        JP r_sr_1

krest_sr LD A,(Crosstaken)
        OR A
        RET NZ
        LD HL,OutKrest
        LD A,1  ;chest1
        JP r_sr_1

money_sr EX AF,AF'
        LD (r_sr_2-1),A
        LD HL,Cointaken
        CALL ver_took
        RET NZ
        LD HL,OutMoney
        LD A,3  ;chest3
        JP r_sr_1

kolye_sr LD A,(Kolyetaken)
        OR A
        RET NZ
        LD HL,OutKolye
        LD A,2  ;chest3
        JP r_sr_1

skript_sr LD A,(Scripttaken)
        OR A
        RET NZ
        LD HL,OutSkript
        XOR A   ;no chest
        JP r_sr_1

;----------------------------------------------

runebfe LD BC,8
        ADD IY,BC
        LD (runebfy+2),IY
        RET 

runebfy LD IY,0
        CALL ccbfy
        DEC (IY)
        RET 

;movobjbuff     DW XY
;               DW curfaze
;               DW option (адрес в проходимости)
;               DW option (

;Взятия :))

takealmaz
        CALL check22
        RET NC
        LD HL,Almaztaken
        DEC (HL)
        LD BC,select_almaz
        JP takeitem1

takekolye
        CALL check22
        RET NC
        LD HL,Kolyetaken
        DEC (HL)
        LD BC,select_kolye
        JP takeitem1

takescript
        CALL check22
        RET NC
        LD HL,Scripttaken
        DEC (HL)
        LD BC,select_script
        JP takeitem1

takecross
        CALL check22
        RET NC
        LD HL,Crosstaken
        DEC (HL)
        LD BC,select_cross
        JP takeitem1

takesword
        CALL check22
        RET NC
        LD HL,Swordtaken
        DEC (HL)
        LD BC,select_sword ;.. см ниже
        JP takeitem1    ;если надо будет написать "--", изменю

takebow
        CALL check22
        RET NC
        LD HL,Bowtaken
        DEC (HL)
        LD BC,select_bow
        LD A,bowarrs
        JP takeitem

takearr
        CALL check22
        RET NC
        LD A,(Bowtaken)
        OR A
        RET Z
        LD HL,OutBow
        LD (IY+2),L
        LD (IY+3),H
        LD DE,Bow
        LD HL,ArrS
        CALL tkfbl2
        JP takeitem

takearruzd
        CALL check22
        JR NC,tau1
        LD HL,OutBow
        LD (IY+2),L
        LD (IY+3),H
        LD A,(IY+7)
        AND #7F
        JP takeitem

tau1    CALL WlkAdr
        ADD HL,DE
        ADD HL,DE
        LD A,(HL)
        OR A
        RET NZ
        INC HL
        OR (HL)
        RET NZ
        INC (IY)
        RET 

takecoin
        CALL check22
        RET NC
        LD HL,Cointaken
        CALL tkfbl2
        LD BC,select_coin
        JR takeitem1

takelive
        CALL check22
        RET NC
        LD A,(LIVES)
        CP 7
        RET NC
        INC A
        LD (LIVES),A
        LD HL,Livetaken
        CALL tkfbl2
        PUSH IY
        CALL AddLini
        POP IY
        LD (IY),#FE
tlsr    LD IX,NRG-"T"-4
        LD A,"S"+32
        SUB (IX+"T"+4)
        RET C
        PUSH AF
        JP dmgsr1

takefbl
        CALL check22
        RET NC
        LD BC,select_fball
        LD HL,FBalls
tkfbl1  CALL tkfbl2
        JR takeitem

tkfbl2  LD E,(IY+4)
        LD D,0
        ADD HL,DE
        LD A,(HL)
        OR #80
        LD (HL),A ;)
        RET 

takekap
        CALL check22
        RET NC
        LD HL,Kaptaken
        LD BC,select_kapkan
        JR tkfbl1

takeelem CALL check22
        RET NC
        LD HL,ElemXtaken
        LD BC,select_elm1
        JR takey1

takekey
        CALL check22
        RET NC
        LD HL,KeyXtaken
        LD BC,select_key1
takey1  CALL tkfbl2
        EX DE,HL
        ADD HL,HL
        ADD HL,HL ;хл*4
        ADD HL,BC
        LD B,H
        LD C,L

takeitem1
        LD A,1

;DE=spr 'item'
;BC=sr
;A=number of 'item', b7=множественность
takeitem
        LD (IY),#FE
        LD L,(IY+2)
        LD H,(IY+3)
        INC HL
        INC HL
        LD E,(HL)
        INC HL
        LD D,(HL)
        LD HL,Inventory
        PUSH AF
        PUSH BC
        LD B,(HL)
        INC B
        JR tkitf3

tkitf1  LD A,(HL)
        INC HL
        CP E
        JR NZ,tkitf2
        LD A,(HL)
        CP D
        JR Z,fndpit1
tkitf2  INC HL
        INC HL
tkitf3  INC HL
        INC HL
        DJNZ tkitf1
        LD (HL),E
        INC HL
        LD (HL),D
        INC HL
        POP BC
        LD (HL),C
        INC HL
        LD (HL),B
        INC HL
        POP AF
        LD (HL),A
        LD HL,Inventory
        INC (HL)
fndpit2
        LD A,1
        CALL ewspsr2
        JP takeitemsnd

fndpit1 POP BC
        POP AF
        INC HL
        INC HL
        INC HL
        LD E,A
        RES 7,A
        RES 7,(HL)
        ADD A,(HL)
        CP 99
        JR C,$+4
        LD A,99
        XOR E
        AND #7F
        XOR E
        LD (HL),A
        JR fndpit2

;---------------------------------------------------------------
;                      Описание предметов
;---------------------------------------------------------------

;--Rune--
OutRune1  FZR takerune,rune1,RuneClr
OutRune2  FZR takerune,rune2,RuneClr
OutRune3  FZR takerune,rune3,RuneClr
OutRune4  FZR takerune,rune4,RuneClr
OutRune5  FZR takerune,rune5,RuneClr
OutRune6  FZR takerune,rune6,RuneClr
OutRune7  FZR takerune,rune7,RuneClr
OutRune8  FZR takerune,rune8,RuneClr
OutRune9  FZR takerune,rune9,RuneClr
OutRune0  FZR takerune,rune0,RuneClr

OutBow    FZR takebow,Bow,BowClr
OutArr    FZR takearr,arrow,BowClr
OutArrUzd FZR takearruzd,arrow,BowClr
OutSword  FZR takesword,Sword,BowClr
OutAxe    FZR 0,Hammer,BowClr
OutFBal   FZR takefbl,Firebal,BowClr
OutKap    FZR takekap,Kapkan,KapClr

OutLife   FZR takelive,life2,BowClr

OutKey1   FZR takekey,key1,KeyClr
OutKey2   FZR takekey,key2,KeyClr
OutKey3   FZR takekey,key3,KeyClr
OutKey4   FZR takekey,key4,KeyClr
OutKey5   FZR takekey,key5,KeyClr

OutAlmaz  FZR takealmaz,almaz,RichClr
OutKrest  FZR takecross,Krest,RichClr
OutMoney  FZR takecoin,money,MoneyClr
OutKolye  FZR takekolye,kolye,RichClr
OutSkript FZR takescript,skript,RichClr

OutEl1    FZR takeelem,elem1,RichClr
OutEl2    FZR takeelem,elem2,RichClr
OutEl3    FZR takeelem,elem3,RichClr
OutEl4    FZR takeelem,elem4,RichClr
OutEl5    FZR takeelem,elem5,RichClr

OutChest1 FZR breakchst,Chest1,3
          FZR breakchst,Chest1+32,3
OutChest2 FZR breakchst,Chest2,#45
          FZR breakchst,Chest2+32,#45
OutChest3 FZR breakchst,Chest3,#44
          FZR breakchst,Chest3+32,#44

breakchst LD A,(IY+5)
        BIT 7,A
        RET Z
        LD L,(IY+2)
        LD H,(IY+3)
        LD DE,5
        ADD HL,DE
        AND #7F
        DEC A
        LD (IY+5),A
        JP NZ,LDIYHL
        ;CALL chestsnd
        LD L,(IY+6)
        LD H,(IY+7)
b_ch1   JP LDIYHL

;------------------------------------------
;Процы обработки предметов в руках

;--- Просто нога и рука
select_hand
        LD HL,FirRycL
        LD DE,FirRycR
        JP seldof

FirRycR
        CP 16+1 ;фире+ригхт
        JR Z,FiKickR
        CP 16+4 ;фире+довн
        JR Z,FiPuncR
        CP 16+8 ;фире+уп
        RET NZ
        LD HL,srcrycr
        LD (PushRsr+1),HL
        POP HL
        LD HL,PushR
        RET 

FiKickR POP HL
        LD HL,KickR
        RET 

srcbrkL LD DE,#FDFF
        JP srcrnf

srcbrkR LD DE,#02FF
        JP srcrnf

FiPuncR POP HL
        LD HL,PunchR
        RET 

srcpncL
        LD H,kickrebronogL
        LD DE,#FF00 ;описание смещения центра действия
        LD A,kickheadL
        JR srcpnR1
srcpncR
        LD H,kickrebronogR
        LD DE,#0100 ;описание смещения центра действия
        LD A,kickheadR
srcpnR1 LD L,ERebronR
        LD (srcpnR2+1),A
        LD A,2
        CALL srcitmf
srcpnR2 LD H,kickheadL
        LD L,EHeadR
        LD A,2
        JP srcitmf

FirRycL
        CP 16+2 ;фире+лефт
        JR Z,FiKickL
        CP 16+4 ;фире+довн
        JR Z,FiPuncL
        CP 16+8 ;фире+уп
        RET NZ
        LD HL,srcrycl
        LD (PushLsr+1),HL
        POP HL
        LD HL,PushL
        RET 

FiKickL POP HL
        LD HL,KickL
        RET 

FiPuncL POP HL
        LD HL,PunchL
        RET 

;попытка опускания рычага
srcrycr
        LD A,3
        LD (currelm+2),A
        CALL srcelmr    ;проверка на 5й элемент
        LD HL,pushdown_r*256+ERychag
                  ;номер действия, оказываемого на предмет
        LD DE,#01FF ;описание смещения центра действия
        JP srcitmf1

srcrycl
        LD A,3
        LD (currelm+2),A
        CALL srcelml    ;проверка на 5й элемент
        LD HL,pushdown_r*256+ErychagR
        LD DE,#FFFF
        JP srcitmf1

;--- Файрбольчик
select_fball
        LD HL,FirFBL
        LD DE,FirFBR
        JP seldof

FirFBL
        LD DE,OutFBL
        LD BC,#FFFF ;слева из живота
FirFBL1 LD HL,VerFir+1
        BIT 4,(HL)
        RET Z
        DEC (HL)
        PUSH AF
        CALL srcitmI
        JR Z,NoFirFB
        DEC (HL)
        ;пров. на наличие
        EX DE,HL
        CALL flyadd
        CALL fbalsnd
NoFirFB POP AF
        RET 

FirFBR
        LD DE,OutFBR
        LD BC,#01FF
        JR FirFBL1

flyadd  PUSH HL
        LD HL,(HERO)
        LD A,H
        ADD A,B
        LD B,A
        LD A,L
        ADD A,C
        LD C,A
        POP HL

;Проца добавляет в группу летящих файрбол (или че у вас там)
;HL=описатель спрайто-группы
;BC=coords
flybfy
        LD A,(flybfycur) ;уменьшать когда файрбол убираю
        INC A
        CP MaxFlyers
        RET NC
        LD (flybfycur),A
        PUSH IY
        LD IY,FLYBUFF
        PUSH BC
        LD BC,8
fndfliy LD A,(IY)
        INC A
        JR Z,fnedfliy
        INC A
        JR Z,fnedfliy
        ADD IY,BC
        JR fndfliy

        ;место найдено!
fnedfliy
        POP BC
        LD (IY),C
        LD (IY+1),B
        LD (IY+2),L
        LD (IY+3),H
        POP IY
        RET 

OutFBL  FZS FBLsr,0,newfbl+32,#0201,FBL_clr
        FZS EOFBL,0,newfbl+48,#0201,FBL_clr

OutFBR  FZS FBRsr,#FF00,newfbl,#0201,FBL_clr
        FZS EOFBR,#FF00,newfbl+16,#0201,FBL_clr

EOFBR   LD HL,OutFBR
        CALL LDIYHL
FBRsr   INC (IY+1)
        JR FBLs1

EOFBL   LD HL,OutFBL
        CALL LDIYHL
FBLsr   DEC (IY+1)
FBLs1   CALL WlkAdr
        LD A,(HL)
        OR A
        JR NZ,EFbL      ;кто, блин, насадил всякого ???

        ;проверка на попадание в чудиков :)
        LD HL,E2heads*256+E2heads
        LD DE,#0002
        LD BC,#0103
        LD A,3
        JP shtitm

KillFly
EFbL    LD (IY),#FE     ;конец нашему файрболу :(
        LD HL,flybfycur
        DEC (HL)
FirCrs  RET 

;--- капканючка
select_kapkan
        LD HL,FirKPL
        LD DE,FirKPR
        JP seldof

FirKPL
        LD DE,PutKapL
        JP FKPL1

FirKPR  LD DE,PutKapR
FKPL1   LD HL,VerFir+1
        BIT 4,(HL)
        RET Z
        DEC (HL)
        EX DE,HL
        JP FBL2

PuKaL   LD BC,#FF00
        LD DE,StLL21
PuKaL1  LD HL,Kapka
        PUSH DE
        PUSH AF
        CALL flyadd
        POP AF
        RET 

PuKaR   LD BC,0
        LD DE,StRL21
        JR PuKaL1

Kapka   FZS W2Mum,0,kap,#0201,7
        FZS 0,0,kap+16,#0201,7
        FZS 0,0,kap+32,#0201,7
        FZS 0,0,kap+48,#0201,7
        FZS KMumm,0,kap+64,#0201,7
        FZS 0,0,kap+80,#0201,7
        FZS KillFly,0,kap+96,#0201,7

KMumm
        LD HL,killmumm*256+EmummyL
        JR $+5
W2Mum
        LD HL,holdmumm*256+EmummyL
        LD DE,#0100
        LD A,2
        CALL srcitmf
        DEC B
        RET Z
        JP RepFaze

;--- по идее - взятый крест (ну и пока скрипт, колье, алмаз)
select_script
select_kolye
select_almaz
select_cross
        LD HL,FirCrs
        LD DE,FirCrs
        JP seldof

;--- по идее - копейка
select_coin
        CALL FndCurItm
        LD A,(DE)
        CP 3
        JR C,select_cross
        LD HL,FirCoinL
        LD DE,FirCoinR
        JP seldof

FirCoinL
        LD HL,srccoil
        JP FirKeyL+3
FirCoinR LD HL,srccoir
        JP FirKeyR+3

srccoil LD DE,-#0300
        JR $+5
srccoir LD DE,-#0100
        LD HL,givecoin*256+Etable
        PUSH HL
        LD HL,tstMdd1
        LD (cntsr+1),HL
        POP HL
        CALL srcitmf1
        LD HL,tstMd
        LD (cntsr+1),HL
        RET 


;--- По идее - меч
select_sword
        LD HL,FirSwrL
        LD DE,FirSwrR
        JP seldof

FirSwrL
        LD DE,SwordL
        JR FirSwr1

FirSwrR LD DE,SwordR
FirSwr1 LD HL,VerFir+1 ;??? зачем так сложно?
        BIT 4,(HL)
        RET Z
        DEC (HL)
        POP HL
        EX DE,HL
        RET 

SwrdLsr
        LD DE,#FEFF
SwrdLs1 LD HL,1*256+EShit1
        CALL srcitmf1
        LD HL,1*256+EShit2
        CALL srcitmf1
        LD HL,1*256+EShit3
        DEC D
        CALL srcitmf1
        LD HL,1*256+EShit4
        JP srcitmf1

SwrdRsr  ;большую часть можно передвинуть в ^
        LD DE,#2FF
        JR SwrdLs1

;--- Лук. Парей. (или как его там?)
select_bow
        LD HL,FirBowL
        LD DE,FirBowR
        JP seldof

FirBowR
        LD HL,BowR
        JR $+5

FirBowL
        LD HL,BowL
FBL2    POP DE
        PUSH HL
        PUSH AF
        CALL srcitmI
        JR Z,FBL1
        DEC (HL)
        POP AF
        POP HL
        RET 

FBL1    POP AF
        POP HL
        PUSH DE
        RET 

select_elm1 LD E,0
            JR selelm1
select_elm2 LD E,1
            JR selelm1
select_elm3 LD E,2
            JR selelm1
select_elm4 LD E,3
            JR selelm1
select_elm5 LD E,4
selelm1 LD D,0
        LD HL,ElemXtaken
        ADD HL,DE
        LD A,(HL)
        AND #7
        INC A
        LD (currelm+2),A
        CALL FndCurItm
        LD HL,FirElmL
        LD DE,FirElmR
        JR seldof

FirElmL LD HL,srcelml ;!
        JR FirKeyL+3

FirElmR LD HL,srcelmr
        JR FirKeyR+3

srcelml LD DE,#FEFD
        JR currelm

srcelmr LD DE,#01FD
currelm LD HL,0+EFlypix
        JR srcitmf1

FndCurItm
        PUSH HL
        CALL srcitmI
        LD (LstItm),HL
        EX DE,HL
        POP HL
        RET NZ
        POP HL
        JP select_cross

;--- Кейсы

;5 ключей
select_key1 LD E,0
            JR selkey1
select_key2 LD E,1
            JR selkey1
select_key3 LD E,2
            JR selkey1
select_key4 LD E,3
            JR selkey1
select_key5 LD E,4

selkey1 LD D,0
        LD HL,KeyXtaken
        ADD HL,DE
        LD A,(HL)
        AND #7
        INC A
        LD (currkey+2),A
        CALL FndCurItm
        LD HL,FirKeyL
        LD DE,FirKeyR

seldof  LD (StandL1Fire+1),HL
        LD (StandL2Fire+1),HL
        EX DE,HL
        LD (StandR1Fire+1),HL
        LD (StandR2Fire+1),HL
        RET 

FirKeyL
        LD HL,srcdorl ;!
        LD (PushLsr+1),HL
        POP HL
        LD HL,PushL
        RET 

FirKeyR
        LD HL,srcdorr
FKR1    LD (PushRsr+1),HL
        POP HL
        LD HL,PushR
        RET 

srcdorl
        LD DE,#FF00
        JR currkey
srcdorr
        LD DE,#0100
currkey LD HL,0+EDoor
        JR srcitmf1

;srcrycr
;LD HL,pushdown_r*256+ERychag
;                 ;номер действия, оказываемого на предмет
;LD DE,#01FF ;описание смещения центра действия

srcitmf1 LD A,1
;поиск предмета воздействия :)
;IY=чел
srcitmf
        LD IX,MONSTRS
        LD BC,10
        LD (tstMd1+1),A
cntsrc  LD A,(IX)
        INC A
        RET Z
        INC A
        JR Z,cntsrc1
        INC B
cntsr   CALL tstMd
        RET Z   ;найден и оповещен
        DEC B
cntsrc1 ADD IX,BC
        JR cntsrc

tstMd   LD A,L
        SUB (IX+7)
        RET C
tstMd1  CP 0
        JR C,$+4
        OR A
        RET 

        LD A,(IX)
        SUB (IY)
        CP E
        RET NZ
        LD A,(IX+1)
        SUB (IY+1)
        CP D
tstMdd2 RET NZ
        LD (IX+9),H
        RET 

tstMdd1
        LD A,L
        SUB (IX+7)
        RET NZ
        LD A,(IX)
        SUB (IY)
        CP E
        RET NZ
        LD A,(IX+1)
        SUB (IY+1)
        SUB D
        CP 3
        CCF 
        SBC A,A
        JR tstMdd2

srcrnf  LD IX,RUNEBUFF
        LD BC,8
cntsrcr LD A,(IX)
        INC A
        RET Z
        INC A
        JR Z,cntsrcr1
        CALL tstMdr
        RET Z   ;найден и оповещен
cntsrcr1 ADD IX,BC
        JR cntsrcr

tstMdr  LD A,(IX+5)
        DEC A
        AND 8
        RET NZ
        LD A,(IX)
        SUB (IY)
        CP E
        RET NZ
        LD A,(IX+1)
        SUB (IY+1)
        CP D
        RET NZ
        SET 7,(IX+5)
        RET 

shtitm
        LD (shti4+1),A
        LD IX,MONSTRS
shti2   LD A,(IX)
        INC A
        RET Z
        INC A
        JR Z,shti1
        LD A,(IX+7)
        CP L
        JR Z,shti3
        CP H
        JR NZ,shti1
shti3   CALL TstZone
        JR NC,shti1
        LD A,(IX+9)
shti4   CP 0
        JR NC,shti1
        INC (IX+9)
        JP EFbL

shti1   PUSH BC
        LD BC,10
        ADD IX,BC
        POP BC
        JR shti2

TstZoneH LD IX,HERO

;IY=текущий obj
;IX=тестируемый
;DE=sxsy zone (сдвиг влево-вверх относ. координаты)
;BC=lenhgt zone (ширина-высота обьекта)

TstZone LD A,(IY)
        SUB (IX)
        ADD A,E
        CP C
        RET NC
        LD A,(IY+1)
        SUB (IX+1)
        ADD A,D
        CP B
        RET 

