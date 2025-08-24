;
; Boot/Real/Video.inc
;

                SEGMENT         Boot.Real

                USE16

Boot.Real.Video:
                CLD
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC

                MOV             AX, 0000h
                MOV             CX, Dev.SBC386EX.VGA3.CRTC_size
.Zero:
                OUT             DX, AX              ; Start by zeroing all registers
                INC             AX
                LOOP            .Zero

                MOV             CX, .Table.Num
                MOV             SI, .Table + Boot.CS
.Loop:
             CS LODSW
                OUT             DX, AX
                LOOP            .Loop

                JMP             .Exit

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

%if .V.Displayed == 25   ; (25 + 0 + 3) * 16 + 2 = 450 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             12   ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             3    ; Rows
.V.Total.Adjust EQU             2    ; Rasters
%elif .V.Displayed == 30 ; (30 + 0 + 2) * 16 + 13 = 525 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             10   ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             2    ; Rows
.V.Total.Adjust EQU             13   ; Rasters
%elif .V.Displayed == 43 ; (43 + 1 + 3) * 11 + 8 = 525 lines
.V.Porch.Front  EQU             1    ; Rows
.V.Sync.Adjust  EQU             0    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             3    ; Rows
.V.Total.Adjust EQU             8    ; Rasters
%elif .V.Displayed == 46 ; (46 + 0 + 1) * 11 + 8 = 525 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             1    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             1    ; Rows
.V.Total.Adjust EQU             8    ; Rasters
%elif .V.Displayed == 50 ; (50 + 1 + 5) * 8 + 2 = 450 lines
.V.Porch.Front  EQU             1    ; Rows
.V.Sync.Adjust  EQU             2    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             5    ; Rows
.V.Total.Adjust EQU             2    ; Rasters
%elif .V.Displayed == 51 ; (51 + 1 + 4) * 8 + 2 = 450 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             2    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             5    ; Rows
.V.Total.Adjust EQU             2    ; Rasters
%elif .V.Displayed == 59 ; (59 + 2 + 4) * 8 + 5 = 525 lines ; More blanking time!
.V.Porch.Front  EQU             2    ; Rows
.V.Sync.Adjust  EQU             7    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             4    ; Rows
.V.Total.Adjust EQU             5    ; Rasters
%elif .V.Displayed == 60 ; (60 + 0 + 5) * 8 + 5 = 525 lines ; More blanking time!
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             1    ; Rasters (not counted)
.V.Sync.Width   EQU             1    ; Rasters (not counted)
.V.Porch.Back   EQU             5    ; Rows
.V.Total.Adjust EQU             5    ; Rasters
%elif .V.Displayed == 63 ; (63 + 0 + 2) * 8 + 5 = 525 lines
.V.Porch.Front  EQU             0    ; Rows
.V.Sync.Adjust  EQU             2    ; Rasters (not counted)
.V.Sync.Width   EQU             2    ; Rasters (not counted)
.V.Porch.Back   EQU             2    ; Rows
.V.Total.Adjust EQU             5    ; Rasters
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
