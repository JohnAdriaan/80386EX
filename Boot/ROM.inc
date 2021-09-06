;
; Boot/ROM.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "ROM", 0

Boot.ROM.Init:
                Boot.Table.Next Boot.ROM.Init
