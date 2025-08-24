;
; Dev/SBC-386EX/Video.inc
;

; These definitions are for the Video section of the RBC VGA3 card.

Vid.Mem.Start   EQU             ECB.Mem.Vid
Vid.IO.Start    EQU             ECB.IO.Vid

Vid.Font.Page   EQU            (Dev.SBC386EX.VGA3.Mem.Size >> x86.PAGE.Shift) - 1 ; For 512-char fonts, this must be even
Vid.Font.Addr   EQU            (Vid.Font.Page << x86.PAGE.Shift)
Vid.Font.CFG    EQU            (Vid.Font.Page << Dev.SBC386EX.VGA3.IO.CFG.Font.Shift)

;...............................................................................
                SEGMENT         IO

ECB.IO.Vid      EQU             ECB.IO.Start

;-------------------------------------------------------------------------------
                SEGMENT         ECB

ECB.Mem.Vid     RESB            Dev.SBC386EX.VGA3.Mem.Size

