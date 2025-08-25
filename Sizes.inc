;
; Sizes.inc
;

;===============================================================================
; Calculate final Boot Segment size
; Note this segment falls through to Boot.Real
                SEGMENT         Boot   ALIGN=Align.Para

                ALIGN           Align.Para, DB 0FFh

Boot.Label.Size EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Label.Size

%assign         Boot.Size       Boot.Size + Boot.Label.Size

;-------------------------------------------------------------------------------
; Calculate final Boot.Real Segment size
; Note this segment falls through to Boot.GDT
                SEGMENT         Boot.Real   ALIGN=Align.Para

                ALIGN           Align.Para   ;, DB 0FFh ; Need to pad with NOPs

Boot.Real.Size  EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Real.Size

%assign         Boot.Size       Boot.Size + Boot.Real.Size

;-------------------------------------------------------------------------------
; Calculate final Boot.GDT Segment size
; Note this Segment falls through from Boot.Real
                SEGMENT         Boot.GDT   VFOLLOWS=Boot.Real  ALIGN=Align.Para

                ALIGN           Align.Para, DB 0FFh

Boot.GDT.Size   EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.GDT.Size

%assign         Boot.Size       Boot.Size + Boot.GDT.Size

;-------------------------------------------------------------------------------
; Calculate final Boot.Font Segment size
                SEGMENT         Boot.Font   VFOLLOWS=Boot.GDT   ALIGN=Align.Para

                ALIGN           Align.Para, DB 0FFh

Boot.Font.Size  EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Font.Size

%assign         Boot.Size       Boot.Size + Boot.Font.Size

;-------------------------------------------------------------------------------
; Calculate final Boot.Prot Segment size
                SEGMENT         Boot.Prot   ALIGN=Align.Para

                ALIGN           Align.Para, DB 0FFh

Boot.Prot.Size  EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Prot.Size

%assign         Boot.Size       Boot.Size + Boot.Prot.Size

;-------------------------------------------------------------------------------
; Calculate final Boot.Reset Segment size
                SEGMENT         Boot.Reset   ALIGN=Align.Para

Boot.Reset.Size EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Reset.Size

%assign         Boot.Size       Boot.Size + Boot.Reset.Size

;-------------------------------------------------------------------------------
; Fill EPROM Segment with 0FFh.
; Note that this declaration needs to be the last PROGBITS segment
                SEGMENT         EPROM  ALIGN=Align.Byte

EPROM.Pad       EQU             ROM.Size - Image.Size

                TIMES           EPROM.Pad DB 0FFh

%assign         Image.Size      Image.Size + EPROM.Pad
;-------------------------------------------------------------------------------
; Ensure Boot.Data is not too large
                SEGMENT         Boot.Data  VSTART=0  NOBITS

Boot.Data.Size  EQU             $ - $$

%assign         Boot.Data.Pad   SRAM.Size - Boot.Data.Size

                RESB            Boot.Data.Pad

;-------------------------------------------------------------------------------
; Ensure ECB is not too large
                SEGMENT         ECB  NOBITS

ECB.Seg.Size    EQU             $ - $$

%assign         ECB.Pad         ECB.Mem.Size - ECB.Seg.Size

                RESB            ECB.Pad

;-------------------------------------------------------------------------------
; Ensure SRAM is not too large
                SEGMENT         SRAM  NOBITS

SRAM.Seg.Size   EQU             $ - $$

%assign         SRAM.Pad        SRAM.Size - SRAM.Seg.Size

                RESB            SRAM.Pad

;-------------------------------------------------------------------------------
; Ensure ROM is not too large
                SEGMENT         ROM  NOBITS

ROM.Seg.Size    EQU             $ - $$

%assign         ROM.Pad         ROM.Size - ROM.Seg.Size

                RESB            ROM.Pad
