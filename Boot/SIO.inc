;
; Boot/SIO.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "SIO", 0

Boot.SIO.Init:
                RET

                Boot.Table.Entry Boot.SIO.Init
