;
; Boot/Video.inc
;

; These definitions are for the Video section of the RBC VGA3 card.

Vid.Mem.Size    EQU             8000h
Vid.IO.Size     EQU             Vid.IO_size

Vid.0.Mem.Start EQU             ECB.Mem.Vid.0
Vid.0.IO.Start  EQU             ECB.IO.Vid.0

Vid.1.Mem.Start EQU             ECB.Mem.Vid.1
Vid.1.IO.Start  EQU             ECB.IO.Vid.1

Vid.Font.Addr   EQU             (Vid.Mem.Size >> x86.Page.Shift) - 1 ; For 512-char fonts, this must be even

;...............................................................................
                STRUC           Vid.IO
.KBD.Addr       RESB            1       ; Keyboard controller
.KBD.Data       RESB            1
.KBD            EQU             .KBD.Addr

.CRTC.Addr      RESB            1       ; CRT Controller
.CRTC.Data      RESB            1       ; CRT Controller
.CRTC           EQU             .CRTC.Addr

.CFG            RESB            1       ; Configuration

.MEM.Addr.Hi    RESB            1       ; High address for non-direct access
.MEM.Addr.Lo    RESB            1       ; Low address for non-direct access
.MEM.Data       RESB            1       ; Data (R/W) for non-direct access
                ENDSTRUC

Vid.IO.CFG.A15        EQU       1000_0000b
Vid.IO.CFG.Font.Addr  EQU       0111_0000b
Vid.IO.CFG.Font.Shift EQU       4
Vid.IO.CFG.Font.256   EQU       0000_0000b
Vid.IO.CFG.Font.512   EQU       0000_1000b
Vid.IO.CFG.Enable     EQU       0000_0100b
;Vid.IO.CFG.Rsvd      EQU       0000_0010b    ; Reserved
Vid.IO.CFG.Width.8    EQU       0000_0000b
Vid.IO.CFG.Width.9    EQU       0000_0001b

;-------------------------------------------------------------------------------
                SEGMENT         IO

ECB.IO.Vid.0    EQU             ECB.IO.Start + 0*Vid.IO.Size
ECB.IO.Vid.1    EQU             ECB.IO.Start + 1*Vid.IO.Size

;-------------------------------------------------------------------------------
                SEGMENT         ECB

ECB.Mem.Vid.0   RESB            Vid.Mem.Size
ECB.Mem.Vid.1   RESB            Vid.Mem.Size

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.Video:
                MOV             BP, Vid.0.IO.Start
                MOV             BX, Vid.0.Mem.Start ; & x86.WORD.Mask
                CALL            .Init
                MOV             BP, Vid.1.IO.Start
                MOV             BX, Vid.1.Mem.Start ; & x86.WORD.Mask
                CALL            .Init
                JMP             .Exit

.Init:
                RET
.Exit:

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.Video:
                MOV             EBX, Vid.0.Mem.Start
                CALL            .Init
                MOV             EBX, Vid.1.Mem.Start
                CALL            .Init
                JMP             .Exit

.Init:
                RET

.Font:
                TIMES           128 * 16 DB 5Ah
.Exit:

