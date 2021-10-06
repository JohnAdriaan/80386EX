;
; Boot/Defn.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                DB              Version.Author, "'s"
                ALIGN           Align.Para, DB ' '

                DB              Version.Boot
                ALIGN           Align.Para, DB ' '

                DB              'v', Version.String
                DB              ' ', Version.Copyright
                ALIGN           Align.Para, DB ' '

%substr         Boot.Date       __?DATE?__ 3,-1
                DB              Boot.Date
                DB              __?TIME?__
