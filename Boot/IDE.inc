;
; Boot/IDE.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "IDE", 0

Boot.IDE.Init:
                RET

                Boot.Table.Entry Boot.IDE.Init
