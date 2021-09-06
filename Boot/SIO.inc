;
; Boot/SIO.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "SIO", 0

Boot.SIO.Init:
                Boot.Table.Next Boot.SIO.Init
