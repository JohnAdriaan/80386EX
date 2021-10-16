;
; Boot/IDE.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32
                
Boot.IDE:
                MOV             EBX, `IDE\r`
                CALL            Hex
