;
; Boot/Keyboard.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "Kbd", 0

Boot.Keyboard.Init:
                Boot.Table.Next  Boot.Keyboard.Init
