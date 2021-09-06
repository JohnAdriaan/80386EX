;
; Boot/SRAM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "SRAM"

Boot.SRAM.Init:
                Boot.Table.Next Boot.SRAM.Init
