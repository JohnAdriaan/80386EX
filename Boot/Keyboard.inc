;
; Boot/Keyboard.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "Kbd", 0

Boot.Keyboard.Init:
                RET

                Boot.Table.Entry Boot.Keyboard.Init
