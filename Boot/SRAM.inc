;
; Boot/SRAM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "SRAM"

Boot.SRAM.Init:
                RET

                Boot.Table.Entry Boot.SRAM.Init
