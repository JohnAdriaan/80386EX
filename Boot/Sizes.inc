;
; Boot/Sizes.inc
;

;===============================================================================
; Calculate final Boot.Real Segment size
; Note this segment falls through to Boot.GDT
                SEGMENT         Boot.Real   START=ROM.ORG   ALIGN=Align.Desc

                ALIGN           Align.Desc ;, DB 0FFh  ; Need to pad with NOP

Boot.Real.Size  EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Real.Size

%assign         Boot.Size       Boot.Size + Boot.Real.Size
;-------------------------------------------------------------------------------
; Calculate final Boot.GDT Segment size
; Note this Segment falls through from Boot.Real
                SEGMENT         Boot.GDT   VFOLLOWS=Boot.Real  ALIGN=Align.Desc

                ALIGN           Align.Desc, DB 0FFh

Boot.GDT.Size   EQU             $ - $$

Boot.GDT.Start  EQU            (Boot.Prot.Start - Boot.GDT.Size) & ~Mask.Para

%assign         Image.Size      Image.Size + Boot.GDT.Size

%assign         Boot.Size       Boot.Size + Boot.GDT.Size

;               SEGMENT         Boot.GDT     START=Boot.GDT.Start
;-------------------------------------------------------------------------------
; Calculate final Boot.Font Segment size
                SEGMENT         Boot.Font   VFOLLOWS=Boot.GDT   ALIGN=Align.Para

Boot.Font.Size  EQU             $ - $$

%assign         Image.Size      Image.Size + Boot.Font.Size

%assign         Boot.Size       Boot.Size + Boot.Font.Size
;-------------------------------------------------------------------------------
; Calculate final Boot.Prot Segment size
                SEGMENT         Boot.Prot

                ALIGN           Align.Para, DB 0FFh

Boot.Prot.Size  EQU             $ - $$

Boot.Prot.Start EQU            (Boot.Reset.Start - Boot.Prot.Size) & ~Mask.Para

%assign         Image.Size      Image.Size + Boot.Prot.Size

%assign         Boot.Size       Boot.Size + Boot.Prot.Size

;               SEGMENT         Boot.Prot    START=Boot.Prot.Start
;-------------------------------------------------------------------------------
; Calculate final Boot.Reset Segment size
                SEGMENT         Boot.Reset

Boot.Reset.Size EQU             $ - $$

Boot.Reset.Start EQU            x86.Reset

%assign         Image.Size      Image.Size + Boot.Reset.Size

%assign         Boot.Size       Boot.Size + Boot.Reset.Size

;-------------------------------------------------------------------------------
; Fill EEPROM Segment with 0FFh
                SEGMENT         EEPROM  ALIGN=1

%assign         EEPROM.Pad      ROM.Size - Boot.Size

                TIMES           EEPROM.Pad DB 0FFh

;-------------------------------------------------------------------------------
; Ensure Boot.Data is not too large
                SEGMENT         Boot.Data  NOBITS

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