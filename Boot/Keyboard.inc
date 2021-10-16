;
; Boot/Keyboard.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.Keyboard:

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.Keyboard:
                MOV             EBX, `KBD\r`
                CALL            Hex
