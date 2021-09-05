;
; Boot/ROM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "ROM", 0

Boot.ROM.Init:
                RET

                Boot.Table.Entry Boot.ROM.Init
