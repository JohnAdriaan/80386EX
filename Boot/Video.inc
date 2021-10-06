;
; Boot/Video.inc
;

; These definitions are for the Video section of the RBC VGA3 card.

Vid.0.Mem.Start EQU             ECB.Mem.Vid.0
Vid.0.IO.Start  EQU             ECB.IO.Vid.0

Vid.1.Mem.Start EQU             ECB.Mem.Vid.1
Vid.1.IO.Start  EQU             ECB.IO.Vid.1

Vid.Font.Page   EQU            (Dev.SBC386EX.VGA3.Mem.Size >> x86.PAGE.Shift) - 1 ; For 512-char fonts, this must be even
Vid.Font.Addr   EQU            (Vid.Font.Page << x86.PAGE.Shift)
Vid.Font.CFG    EQU            (Vid.Font.Page << Dev.SBC386EX.VGA3.IO.CFG.Font.Shift)

Boot.Text.Colour EQU            Dev.VGA.BlackBack | Dev.VGA.Grey

;...............................................................................
                SEGMENT         IO

ECB.IO.Vid.0    EQU             ECB.IO.Start + 0*Dev.SBC386EX.VGA3.IO.Size
ECB.IO.Vid.1    EQU             ECB.IO.Start + 1*Dev.SBC386EX.VGA3.IO.Size

;-------------------------------------------------------------------------------
                SEGMENT         ECB

ECB.Mem.Vid.0   RESB            Dev.SBC386EX.VGA3.Mem.Size
ECB.Mem.Vid.1   RESB            Dev.SBC386EX.VGA3.Mem.Size

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.Video:

.0:
                MOV             DX, Vid.0.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC
                MOV             DI, .1              ; 'Return' address
                JMP             .Init
.1:
                MOV             DX, Vid.1.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC
                MOV             DI, .Exit           ; 'Return' address
.Init:

                JMP             DI
.Exit:

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.Video:
                MOV             DX, Vid.0.IO.Start + Dev.SBC386EX.VGA3.IO.CFG
                MOV             EDI, Vid.0.Mem.Start
                CALL            .Init
                MOV             DX, Vid.1.IO.Start + Dev.SBC386EX.VGA3.IO.CFG
                MOV             EDI, Vid.1.Mem.Start
                PUSH            .Exit
;               CALL            .Init
;               JMP             .Exit

.Init:
                MOV             AX, (Boot.Text.Colour << Dev.VGA.Attr.Shift) | ' '
                MOV             ECX, Vid.Font.Addr / x86.WORD.Size
                REP             STOSW                ; Blank video pages

                SHRD            EAX, EDI, 8          ; Get Vid.Mem.A15 into AL
                AND             AL, Dev.SBC386EX.VGA3.IO.CFG.A15

                MOV             ECX, Boot.Font.Size / x86.DWORD.Size
                MOV             ESI, section.Boot.Font.start
             CS REP             MOVSD                ; Copy font from Boot.Font

                OR              AL, Vid.Font.CFG | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Font.256 | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Enable   | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Width.9
                OUT             DX, AL

                RET
.Exit:
