; Build & Session counter v1.2
;begin build countin' -- 26.11.01
;begin session countin' -- 26.11.01

        BUILD=03574
        SESSION=00447
        BUILD=BUILD+1

_pAgEdB EQU #27        ;!!! Страница данного текста

_aDrBlD EQU #C0AE      ;!!! Адрес первой цифры билда
_aDrSeS EQU _aDrBlD+15 ;!!! Адрес первой цифры сессии

;!!!
;!!! Данный исходник считает количество компиляций и перезаписей
;!!! вашего проекта...
;!!! Обратите внимание на страницу размещения этого текста!
;!!!

_OLDADR

        MACRO VAL_NUMB
        _sum=:0
        _zxc=10000
        DUP 5
        _nnn=0
        DUP 9
        IF _sum-_zxc<1&1
        _sum=_sum-_zxc
        _nnn=_nnn+1
        ENDIF 
        EDUP 
        DB _nnn+"0"
        _zxc=_zxc/10
        EDUP 
        ENDM 

        ORG _aDrBlD,_pAgEdB
        IFN "BU"-{$-6}
        DISPLAY "Wrong BUILD usage:",{$-6},"<>BU"
        ELSE 
        VAL_NUMB BUILD

        ORG _aDrSeS,_pAgEdB
        IFN "SE"-{$-8}
        DISPLAY "Wrong SESSION usage:",{$-8},"<>SE"
        ELSE 
        IF .{#C027}
        SESSION=SESSION+1
        VAL_NUMB SESSION
        ENDIF 
        ENDIF 

        ORG #C027,_pAgEdB ;флаг измененности
        DB 1

        ENDIF 
        ORG _OLDADR

        DISPLAY 
        DISPLAY /D,BUILD,"-й билд, ",/D,SESSION,"-я сессия"
        DISPLAY 

