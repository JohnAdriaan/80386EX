;
; Boot/Fatal.inc
;

; This module shows a fatal hardware condition detected during Boot

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Exit:
                MOV             DX, Dev.SBC386EX.Lite.Out
                MOV             AL, 5 << Dev.SBC386EX.Lite.Shift
.Loop:
                OUT             DX, AL
            A16 LOOP            $
                XOR             AL, Dev.SBC386EX.Lite.Mask
                JMP             .Loop

;-------------------------------------------------------------------------------
Boot.Fatal.Hex:
                CALL            Hex
Boot.Fatal:
                HLT
