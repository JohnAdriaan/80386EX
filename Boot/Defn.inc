;
; Boot/Defn.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                DB              Version.Author, "'s"
                ALIGN           x86.PARA, DB ' '

                DB              Version.Boot
                ALIGN           x86.PARA, DB ' '

                DB              'v', Version.String
                DB              ' ', Version.Copyright
                ALIGN           x86.PARA, DB ' '

%substr         Boot.Date       __?DATE?__ 3,-1
                DB              Boot.Date
                DB              __?TIME?__
