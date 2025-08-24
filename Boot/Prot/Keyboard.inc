;
; Boot/Prot/Keyboard.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.Keyboard:
                MOV             EBX, `KBD\r`
                CALL            Hex
