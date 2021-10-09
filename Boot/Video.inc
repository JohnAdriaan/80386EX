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
                CLD
                Dev.Lites       0101b

.0:
                MOV             DX, Vid.0.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC
                MOV             DI, .1              ; 'Return' address
                JMP             .Init
.1:
                MOV             DX, Vid.1.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC
                MOV             DI, .Exit           ; 'Return' address
.Init:
                MOV             AX, 0000h
                MOV             CX, Dev.SBC386EX.VGA3.CRTC_size
.Zero:
                OUT             DX, AX              ; Start by zeroing all registers
                INC             AX
                LOOP            .Zero

                MOV             CX, .Table.Num
                MOV             SI, .Table
.Loop:
             CS LODSW
                OUT             DX, AX
                LOOP            .Loop

                JMP             DI


.H.Displayed    EQU             Screen.Width
.V.Displayed    EQU             Screen.Height
.C.Height       EQU             Font.Height

%if .H.Displayed == 80
.H.Porch.Front  EQU             9
.H.Sync.Width   EQU             13
.H.Porch.Back   EQU             11
%elif .H.Displayed == 90
.H.Porch.Front  EQU             4
.H.Sync.Width   EQU             13
.H.Porch.Back   EQU             6
%endif
.H.Total        EQU             .H.Displayed + .H.Porch.Front + .H.Sync.Width + .H.Porch.Back

%if .V.Displayed == 25   ; (25 + 0 + 3) * 16 + 1 = 449 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             12   ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             3    ; Rows
.V.Total.Adjust EQU             1    ; Rasters
%elif .V.Displayed == 30 ; (30 + 0 + 2) * 16 + 13 = 525 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             10   ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             2    ; Rows
.V.Total.Adjust EQU             13   ; Rasters
%elif .V.Displayed == 43 ; (43 + 0 + 4) * 11 + 8 = 525 lines
.V.Porch.Front  EQU             1    ; Rows
.V.Sync.Adjust  EQU             0    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             3    ; Rows
.V.Total.Adjust EQU             8    ; Rasters
%elif .V.Displayed == 50 ; (50 + 0 + 5) * 8 + 9 = 449 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             12   ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             5    ; Rows
.V.Total.Adjust EQU             9    ; Rasters
%endif
.V.Total        EQU             .V.Displayed + .V.Porch.Front + .V.Porch.Back ; Rows

.Sync.Width     EQU             (.V.Sync.Width << 4) | (.H.Sync.Width << 0)

.Cursor.Start   EQU             .C.Height - 3
.Cursor.End     EQU             .Cursor.Start + 1
.Cursor.Blink   EQU             Dev.SBC386EX.VGA3.CRTC.Cursor.Slow

.Table:
                DB              Dev.SBC386EX.VGA3.CRTC.Nht,       .H.Total - 1
                DB              Dev.SBC386EX.VGA3.CRTC.Nhd,       .H.Displayed
                DB              Dev.SBC386EX.VGA3.CRTC.Nhsp,      .H.Displayed + .H.Porch.Front
                DB              Dev.SBC386EX.VGA3.CRTC.Nsw,       .Sync.Width
                DB              Dev.SBC386EX.VGA3.CRTC.Nvt,       .V.Total - 1
                DB              Dev.SBC386EX.VGA3.CRTC.Nadj,      .V.Total.Adjust
                DB              Dev.SBC386EX.VGA3.CRTC.Nvd,       .V.Displayed
                DB              Dev.SBC386EX.VGA3.CRTC.Nvsp,      .V.Displayed + .V.Porch.Front
                DB              Dev.SBC386EX.VGA3.CRTC.Nr,        .C.Height - 1
                DB              Dev.SBC386EX.VGA3.CRTC.Ncs1,      .Cursor.Start | .Cursor.Blink
                DB              Dev.SBC386EX.VGA3.CRTC.Nce1,      .Cursor.End
%if .V.Sync.Adjust>0
                DB              Dev.SBC386EX.VGA3.CRTC.Nvad,      .V.Sync.Adjust
                DB              Dev.SBC386EX.VGA3.CRTC.Control.1, Dev.SBC386EX.VGA3.CRTC.Control.1.Sy
%endif
.Table.Num      EQU             ($ - .Table) / x86.WORD.Size
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
;               CALL            .Init
;               JMP             .Exit
                PUSH            .Exit

.Init:
                MOV             AX, Dev.VGA.CharAttr(0, Boot.Text.Colour)
                MOV             ECX, Vid.Font.Addr / x86.WORD.Size
.Blank:
;                REP             STOSW                ; Blank video pages
                STOSW
                INC             AL
                LOOP            .Blank

                SHRD            EAX, EDI, 8          ; Get Vid.Mem.A15 into AL
                AND             AL, Dev.SBC386EX.VGA3.IO.CFG.A15

                MOV             ESI, section.Boot.Font.start
%if Font.Height == Dev.SBC386EX.VGA3.Font.Max
                MOV             CX, Boot.Font.Size / x86.DWORD.Size
             CS REP             MOVSD                ; Copy font from Boot.Font
%else
                XOR             EAX,EAX
.Font:
                MOV             CL, Font.Height
             CS REP             MOVSB
                MOV             CL, Dev.SBC386EX.VGA3.Font.Max - Font.Height
                REP             STOSB
                DEC             AH
                JNZ             .Font
%endif

                OR              AL, Vid.Font.CFG | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Font.256 | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Enable   | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Width.9
                OUT             DX, AL

                RET
.Exit:
