;
; Boot/DRAM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "DRAM"

Boot.DRAM.Init:
                RET

                Boot.Table.Entry Boot.DRAM.Init
