;
; Boot/IDE.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "IDE", 0

Boot.IDE.Init:
                Boot.Table.Next Boot.IDE.Init
