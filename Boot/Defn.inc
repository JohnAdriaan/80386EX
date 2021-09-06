;
; Boot/Defn.inc
;

ROM.Size        EQU             8 * 1024

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Code      ALIGN=16

                ORG             1_0000h - ROM.Size

                DB              Version.Author, "'s"
                ALIGN           16, DB ' '

                DB              Version.Boot
                ALIGN           16, DB ' '

                DB              'v', Version.String
                DB              ' ', Version.Copyright
                ALIGN           16, DB ' '
