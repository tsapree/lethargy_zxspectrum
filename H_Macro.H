; Макросы

        MAIN "",#C0

        MACRO STDCAPS
        PUSH AF
        LD A,#FE
        IN A,(#FE)
        RRCA 
        DISPLAY "STD2 'caps-breakpoint' at ",$
        CALL NC,std2
        POP AF
        ENDM 

        MACRO STD2
        IFN ?SAVEOBJ-2
        DISPLAY "STD2 breakpoint at ",$
        CALL std2
        ENDIF 
        ENDM 

        MACRO ORGXX00
        IF "  "-"  :0"
        ORG '($-1)+1*256
        ELSE 
        ORG '($-1)+1*256,:0
        ENDIF 
        ENDM 

        MACRO CALLPG
        CALL callpg
        DB :0
        DW :1
        ENDM 

;       DW proga        ;прога для фазы
;       DB 1            ;один спрайт
;       DW #00FE        ;смещение от начальной координаты
;       DW gorgt01      ;адрес спрайта
;       DW #0103        ;размер спрайта (формат - столбец)
;       DB HeroClr      ;цвет спрайта

        MACRO FZS
        DW :0                   ;FZS
        IFN "  "-"  :1"         ;FZS
        _adrnumfzs=$            ;FZS
        DB 1                    ;FZS
        DB :1>4&#F0+(#0F&:1)    ;FZS
        DW :2                   ;FZS
        DB :3>4&#F0+(#0F&:3)    ;FZS
        DB :4                   ;FZS
        ELSE 
        DB 0
        ENDIF 
        ENDM 

        MACRO PCRD
        DB :0>4&#F0+(#0F&:0)    ;FZS
        ENDM 

        ;проверяет смещение на (+7-8) спрайта
        MACRO TSTFZ
        IFN (((':1)+8)&#F0)|(((.:1)+8)&#F0)
        DISPLAY ":0 :1,:2,:3"
        ENDIF 
        ENDM 

;также, как и предыдущий генерит инфу для фазы, разница в 7м
;бите адреса спрайта - флаге того, что спрайт надо повернуть при
;выводе

        MACRO FZM
        DW :0                   ;FZM
        IFN "  "-"  :1"         ;FZM
        _adrnumfzs=$            ;FZM
        DB 1                    ;FZM
        DB :1>4&#F0+(#0F&:1)    ;FZM
        DW :2-#8000             ;FZM
        DB :3>4&#F0+(#0F&:3)    ;FZM
        DB :4                   ;FZM
        ELSE 
        DB 0
        ENDIF 
        ENDM 

;по идее надо еще и FZMP сделать, но для героя это вряд ли пона-
;добится

;добавляет еще один спрайт в группу фазы

        MACRO FZSP
        _curadr=$
        ORG _adrnumfzs,fzs_pg
        DB {$}+1
        ORG _curadr,fzs_pg
        DB :0>4&#F0+(#0F&:0)
        DW :1
        DB :2>4&#F0+(#0F&:2)
        DB :3
        ENDM 

        MACRO FZMP
        _curadr=$
        ORG _adrnumfzs,fzs_pg
        DB {$}+1
        ORG _curadr,fzs_pg
        DB :0>4&#F0+(#0F&:0)
        DW :1-#8000
        DB :2>4&#F0+(#0F&:2)
        DB :3
        ENDM 

        MACRO DSP       ;спрайты комнат
        DW :0
        DB :1*16+:2
        ENDM 

        MACRO FZR
        DW :0,:1                ;FZR
        DB :2                   ;FZR
        ENDM 

        MACRO ROOMSPRITES
        Epg_lvl=$
        ORG #C000,gfx_pg
        ENDM 

        MACRO ENC
        E:0=.($-ENC_TABLE/2)
        DW :1
        ENDM 

        MACRO setcrds
        DW #10+:0*256+#10+:1
        DW :2
        DW :1*WLKLEN+:0+WALKONBUFF+(WLKLEN*WLKUP)+WLKLERI
        DW :3
        DW 0
        ENDM 

;проверяет область от :0 до $ на пересечение границей параграфа

        MACRO VER_EDGE
        IFN ':0-'$
        DISPLAY ":0 на границе параграфа!"
        ENDIF 
        ENDM 

        nmbMEGA=0

        MACRO MEGA
        roomMEGA=:0
        nmbMEGA=nmbMEGA+1
        tmpMEGA=$
        ORG Epg_agfx,agfx_pg
        ENDM 

        MACRO ENDMEGA
        DISPLAY "MEGA",/D,nmbMEGA," Size ",$-Epg_agfx
        lenMEGA=$-Epg_agfx
        begMEGA=Epg_agfx
        Epg_agfx=$

        ORG tblMEGA
        DB roomMEGA
        DW begMEGA
        DW lenMEGA
        tblMEGA=$
        DB #FF

        ORG tmpMEGA,main_pg
        ENDM 

        MACRO MEGALABEL
        :0=$-Epg_agfx+GGFX
        ENDM 

        MACRO ML
        :0=$-Epg_agfx+GGFX
        ENDM 

        MACRO SBM ;RebronL,#22,_sr
        DB E:0
        DW :2
        DW buff4coords
        DB Dead:0
        tmpSBM=$
        ORG buff4coords
        DS :1*5
        buff4coords=$
        len_buff4coords=$-begin_buff4coords
        ORG tmpSBM
        ENDM 
