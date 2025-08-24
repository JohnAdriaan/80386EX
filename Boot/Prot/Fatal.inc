;
; Boot/Prot/Fatal.inc
;

; This module shows a fatal hardware condition detected during Boot

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Fatal.Hex:
                CALL            Hex
Boot.Fatal:
                MOV             DX, Dev.SBC386EX.Lite.Out
                MOV             AL, 0101b << Dev.SBC386EX.Lite.Shift
.Loop:
                OUT             DX, AL
            A16 LOOP            $
                XOR             AL, Dev.SBC386EX.Lite.Mask
                JMP             .Loop
