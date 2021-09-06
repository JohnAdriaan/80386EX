;
; Boot/DRAM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "DRAM"

Boot.DRAM.Init:
                Boot.Table.Next Boot.DRAM.Init
