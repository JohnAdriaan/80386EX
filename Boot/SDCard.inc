;
; Boot/SDCard.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.SDCard:
                MOV             EBX, `SD\r\n`
                CALL            Hex
