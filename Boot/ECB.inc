;
; Boot/ECB.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "ECB", 0

Boot.ECB.Init:
                RET

                Boot.Table.Entry Boot.ECB.Init
