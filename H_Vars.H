; Переменные и константы

        MAIN "",#C0

IFN ?SAVEOBJ-2

;MapGoSee       DISPLAY "Видно карту проходимости"
;Border         DISPLAY "Дерьмо на бордюре"
SlowMotion      DISPLAY "Z для торможения"
AnyKey          DISPLAY "K для рычагов и дверей"
;FlyingSkull    DISPLAY "fluink joke fun mode ON!!!"
;SaveMenuMove   DISPLAY "Запись поведения героя в меню!"
ENDIF 

;NoSound        DISPLAY "Нет больше звуковых эффектов"


DISPLAY 

Kap_Wait4Close  EQU 15
TimeNoShit      EQU 50

DeadRebronL     EQU 0
DeadRebronR     EQU 0
DeadHeadL       EQU 0
DeadHeadR       EQU 0
Dead2heads      EQU -3  ;через 3 захода в комнату оживет.
DeadTothL       EQU 0
DeadTothR       EQU 0
Deadghost2      EQU 0
DeadmummyL      EQU -4
DeadmummyR      EQU -4

dmg_rebronog    EQU -5
dmg_kapkan      EQU -1
dmg_strelka     EQU -1 ;2heads
dmg_bit         EQU -2 ;2heads
dmg_shit        EQU -5
dmg_gazer       EQU -1
dmg_wedima      EQU -2
dmg_ghost2      EQU -3
dmg_ghost2fire  EQU -8
dmg_elec        EQU -1
dmg_ty4ka       EQU -5
dmg_typhon      EQU -5
dmg_toth        EQU -8
dmg_mummy       EQU -1

by_head         EQU 100
by_lava         EQU 101
by_ty4ka        EQU 102

;Pages:
main_pg         EQU 0
lvl_pg          EQU 1
gfx_pg          EQU 3

        IF ?SAVEOBJ-2
mus_pg          EQU 4
        ELSE 
mus_pg          EQU #46
        ENDIF 
mus_pg_virt     EQU #46
out_pg_virt     EQU #C3

fzs_pg          EQU 6
agfx_pg         EQU 7   ;#C000- фон глв меню ! переместить в др!

        IF ?SaveMenuMove
mmgo_pg         EQU #C7
        ENDIF 

;действия:
pushdown_r      EQU 1
open_door       EQU 2
strela_shitl    EQU 3
holdmumm        EQU 4
killmumm        EQU 5
kickrebronogL   EQU 6
kickrebronogR   EQU 7
kickheadL       EQU 8
kickheadR       EQU 9
givecoin        EQU 10

        ORG #6000

HEAD_STRS       EQU 5               ;строк в менюхе сверху
HEAD_CELLS      EQU HEAD_STRS*32
OUT_CELLS       EQU 768-HEAD_CELLS
OUT_LINES       EQU 24-HEAD_STRS
NULL_Y_CELL     EQU 16              ;на всякий случай, запас
NULL_X_CELL     EQU 16              ;на вылезший спрайт
MAX_OR_SPRS     EQU 64              ;кол-во налезающих др на др

ATRS_BUFF       DS 768              ;буфер для атрибутов экрана
                                    ;при прорисовке комнаты

TBL_SCOMS       DS 3*2*18           ;для вывода жизней
TBL_OMS         DS 3*2*OUT_CELLS+2  ;на экран + заглушка

                DS 82-6         ; больше места...
;VARS:
OR_BUFF_ADR     DW OR_SPRS_BUFF     ;после вывода на экран вос-
                                    ;станавливать!
page            DB 0
LVL_pg          DB agfx_pg

MaxMonstrs EQU 10 ;буфер расчитан на это кол-во монстров.
MaxFires   EQU 20 ;буфер на это кол-во огнеподобных обьектов
MaxFlyers  EQU #20 ;буфер расчитан на это кол-во файрболов
MaxRunes   EQU #10 ;кол-во руноподобных обьектов (не по or!)
MaxFlashes EQU 45 ;буфер вспышек для колонн. (+5 на всяк пожар.)

        ORGXX00
XYTABLE         DS 256

WLKUP           EQU 3   ;размер проходимости комнаты сверху
WLKDWN          EQU 2   ;размер проходимости комнаты снизу
WLKLERI         EQU 2   ;размер проходимости комнат слева/справа
WLKLEN          EQU 32+WLKLERI+WLKLERI
WLKHGT          EQU OUT_LINES+WLKUP+WLKDWN

;буфер проходимости
WALKONBUFF      DS WLKHGT*WLKLEN

WALKSERVBUFF    DS OUT_LINES*32     ;буфер для промежуточной
                                    ;прорисовки проходимости
                                    ;краевых комнат

        ORGXX00
OR_SPRS_BUFF    DS MAX_OR_SPRS*8    ;обязательно располагать
                                    ;кратно 8ми!!!
LOW_POROG       EQU '($-1)+2        ;ниже этого порога спрайтов
                                    ;быть не может

        ORGXX00

active_itm_clr  EQU #46         ;активный предмет
pass_itm_clr    EQU #41         ;неактивный предмет

norune_clr      EQU 1
tknrun_clr      EQU 5
actrun_clr      EQU 7

dignull         EQU #41
digmany         EQU #46

COLORS          DB 0
                DB 1
                DB 2
                DB 3
                DB 4
eClr3           DB 5
                DB 6
Monster1Clr             ;хребтоног
HeadClr                 ;голова на пальцах
THClr                   ;двуголовый
eClr1
                DB 7
HeroClr         DB 7

eClr5           DB #0F

DoorHClr        DB #42
DoorClr         DB #43
mumclr          DB #44  ;мумми
eClr6
molniq1         DB #45
molniq2         DB #46
eClr4
uppmolniq       DB #47
eClr2           DB #4D

RuneClr         DB 6
KapClr                  ;???
BowClr          DB 3
KeyClr          DB 6
Lav_clr         DB 2*8+6
ElmClr          DB #47
ShuClr          DB 3

TothClr         DB #46 ;тот он и в африке тот.

RichClr         DB #47 ;мигает #47-#45
MoneyClr        DB #46 ;мигает яркостью

FBL_clr         DB #42
FBL_clr1        DB #46

              DS 64-11,7 ;???;таблица цветов, здесь: рнд и проч.

                wscolpall=2

wspyhtbl        IF wscolpall
                DD #4A4F53575C5F65676E6F77777F7F
                DW vizinvo
                DD #7F7F77776E6F65675C5F53574A4F
                DW ewspsr
                ENDIF 

                IF wscolpall-1
                DD #4A4F53575C5F65676E6F77777F7F
                DW vizinvo
                DD #7F7F3F3F777737376E6F2E2F65672527
                DD #5C5F1C1F535713174A4F0A0F
                DW ewspsr
                ENDIF 

                IF wscolpall-2
                DD #4247
                DD #4347
                DD #4447
                DD #4547
                DD #4647
                DD #4747
                DD #7F7F
                DW vizinvo
                DD #4747
                DD #0707
                DD #4747
                DD #0707
                DD #4647
                DD #0607
                DD #4547
                DD #0507
                DD #4447
                DD #0407
                DD #4347
                DD #0307
                DD #4247
                DD #0207
                DW ewspsr
                ENDIF 

flybfycur       DB 0

NRG             DB "S"  ;энергия
NRGpls          DB 0    ;смещение для нее
                DB 32+"S" ;верхняя граница энергии
                DB "S"    ;нижняя

KindHero        DB 0 ;тип движения героя

_HeroStand      EQU 0
_HeroGo         EQU 1
_HeroRun        EQU 2

        ORGXX00
mirr_tbl        DS 256

        IF 0
room_game_page  EQU lvl_pg
room_game_start EQU #8  ;#22
crds_game_start EQU #191A
room_menu_page  EQU agfx_pg
room_menu_start EQU 2
crds_menu_start EQU #191A
room_outro_page EQU room_menu_page
room_outro_start EQU 5
crds_outro_start EQU #1B18
        ELSE 
room_game_page  EQU lvl_pg
room_game_start EQU 8
crds_game_start EQU #191A
room_menu_page  EQU agfx_pg
room_menu_start EQU 5
crds_menu_start EQU #1B18
        ENDIF 

PREVROOM        DW 0,#2013 ;DS 4

ROOM            DB room_game_start
ROOMCRDSXY
ROOMCRDY        DB 0
ROOMCRDX        DB 0
ROOMCRDSSXSY
ROOMCRDSY       DB 0
ROOMCRDSX       DB 0

ROOM_EXIT_LFT   DB #FF,0
ROOM_EXIT_RGT   DB #FF,0
ROOM_EXIT_UP    DB #FF,0
ROOM_EXIT_DWN   DB #FF,0

lxand_tbl       DB #00,#80,#C0,#E0,#F0,#F8,#FC,#FE
                VER_EDGE lxand_tbl

MIDDLEBOX       DS 5    ;L1,X3,L3,L2,L4
BORDERBOX       DS 5
reshowtbl       DS 4

                BEGIN_VARS

place_buff      DB #1A,#19,8,1
place_reinc     DB #1A,#19,8,1

ektbl           DW ekeytbl

LIVES           DB 7

Crosstaken      DB 0
Almaztaken      DB 0
Kolyetaken      DB 0
Scripttaken     DB 0

Cointaken       DS 6

Livetaken       DS 9

Kaptaken        DB 5
                DB 5
                DB 5
                DB 5
                DB 5
                DB 5
                DB 5

Arrowtaken      DB 3
                ;DB X - больше стрел пока нету.
LastArr         DB 1    ;это для стрелы, не воткнувшейся...

FBalls          DB 30 ;7й бит - взят, число - кол-во выстрелов
                DB 30
                DB 30
                DB 30
                DB 30
                DB 30
                DB 30
                DB 30

Swordtaken      DB 0

RuneXtaken      DS 10 ;#FF;#80 - взята, #81..#FF - поставлена
RunePlaces      DB 6
                DB 7
                DB 9
                DB 8
                DB 4
                DB 3
                DB 2
                DB 1
                DB 0
                DB 5

KeyXtaken       DB 4    ;7й бит установлен - ключ взят
                DB 1    ;смещения в таблице doortbl
                DB 3    ;
                DB 2
                DB 5

                ;        in room   to room
rychtbl         DB 16   ;0 !!!        30 - выключает тучку
                DB 7    ;4            6
                DB 8    ;18           15
                DB 0    ;25           10
                DB 14   ;49           57
                DB 9    ;58           20
rychRtbl        DB 15   ;41           57
                DB 12   ;46           61
                DB 13   ;64           64
                DB 10   ;65           24

doortbl
                DB 0    ;room10 Y
                DB 0    ;room11 2
door2zamok      DB 0    ;room29 4
                DB 0    ;room42 3
                DB 0    ;room47 1
                DB 0    ;room56 5
                DB 0    ;room76
hiddoortbl      DB 0    ;room6  Z
                DB 0    ;room15 D
kyrplucktbl     DB 0    ;room20 A
                DB 0    ;room24 B
luck2zamok      DB 0    ;room57
lucktbl         DB 0    ;room61 W
                DB 0    ;room64
walltbl         DB 0    ;room57
                DB 0    ;room57
machinetbl      DB 0    ;room00,room1E - machine&ty4ka

streltbl        DB 0
                DB 0
                DB 0
                DB 0

ElemXtaken      DB 1    ;
                DB 3
                DB 0
                DB 4
                DB 2

ElmTbl          DB 0    ;in:Elem2
                DB 0    ;in:Elem0
                DB 0    ;in:Elem4
                DB 0    ;in:Elem1
                DB 0    ;in:Elem3

Bowtaken        DB 0
bowarrs         EQU 5
ArrS            DB 2    ;кол-во их :I
                DB 3
                DB 2
                DB 2
                ;DB ...

LstItm          DW 0    ;адрес опред. использованного предм.
;--
max_invent      EQU 20  ;размер кармана
Inventory
                DB 1 ;кол-во предметов в кармане
                DB 0 ;текущий предмет

                SIZE_VARS=$-BEGIN_VARS

        DW handy
        DW select_hand
        DB 0     ;7й бит - цветастость

;       DW adrspr       ;адрес спрайта
;       DW itm_init_srs ;проца инициализации стреляния и проч
;       DB 0            ;кол-во на складе данного препарата.

        DS max_invent*5

herosprbuff     DS (4*4*8)            ;тут правые спрайты хера

Epg_vars=$

        NULL_VARS=0-#300-#600-SIZE_VARS
        SavUndTxtBuff=0-#300-#600
        begin_buff4coords=0-#300
        buff4coords=begin_buff4coords


