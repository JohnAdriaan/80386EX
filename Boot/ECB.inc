;
; Boot/ECB.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "ECB", 0

Boot.ECB.Init:
                Boot.Table.Next  Boot.ECB.Init
