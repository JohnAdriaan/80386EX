;
; Sizes.inc
;

; Calculate final Header Segment size
                SEGMENT         Demo  ALIGN=x86.PARA

                ALIGN           x86.PARA, DB 0

Header.Size     EQU             $ - $$

%assign         Image.Size      Image.Size + Header.Size

%assign         Demo.Size       Demo.Size + Header.Size
;-------------------------------------------------------------------------------
; Calculate final IDT Segment size
                SEGMENT         IDT  VSTART=0  ALIGN=x86.PARA

IDT.Addr        EQU             Code.Base - IDT.Size

IDT.Limit       EQU             $ - $$ - 1

                ALIGN           x86.PARA, DB 0

IDT.Size        EQU             $ - $$

%assign         Image.Size      Image.Size + IDT.Size

%assign         Demo.Size       Demo.Size + IDT.Size
;-------------------------------------------------------------------------------
; Calculate final Ints Segment size
                SEGMENT         Ints  VSTART=0  ALIGN=x86.PARA

Ints.Base       EQU             IDT.Addr + IDT.Size ; Equivalent to Code.Base

Ints.Limit      EQU             $ - $$ - 1

                ALIGN           x86.PARA

Ints.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + Ints.Size

%assign         Demo.Size       Demo.Size + Ints.Size
;-------------------------------------------------------------------------------
; Calculate final User.Code Segment size
                SEGMENT         User  VSTART=0  ALIGN=x86.PARA

User.Base       EQU             Ints.Base + Ints.Size

User.Limit      EQU             $ - $$ - 1

                ALIGN           x86.PARA

User.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + User.Size

%assign         Demo.Size       Demo.Size + User.Size
;-------------------------------------------------------------------------------
; Calculate final User.LDT Segment size
                SEGMENT         User.LDT  ALIGN=x86.PARA  NOBITS

User.LDT.Limit  EQU             $ - $$ - 1

                ALIGNB          x86.PARA

User.LDT.Size   EQU             $ - $$
;-------------------------------------------------------------------------------
; Calculate final User.Data Segment size
                SEGMENT         User.Data  ALIGN=x86.PARA  NOBITS

User.Data.Limit EQU             $ - $$ - 1

                ALIGNB          x86.PARA

User.Data.Size  EQU             $ - $$
;-------------------------------------------------------------------------------
; Calculate final Exec Segment size
                SEGMENT         Exec  VSTART=0  ALIGN=x86.PARA

Exec.Base       EQU             User.Base + User.Size

Exec.Limit      EQU             $ - $$ - 1

                ALIGN           x86.PARA

Exec.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + Exec.Size

%assign         Demo.Size       Demo.Size + Exec.Size
;-------------------------------------------------------------------------------
; Calculate final Exec.LDT Segment size
                SEGMENT         Exec.LDT  VSTART=0  ALIGN=x86.PARA

Exec.LDT.Base   EQU             Exec.Base + Exec.Size

Exec.LDT.Limit  EQU             $ - $$ - 1

                ALIGN           x86.PARA, DB 0

Exec.LDT.Size   EQU             $ - $$

%assign         Image.Size      Image.Size + Exec.LDT.Size

%assign         Demo.Size       Demo.Size + Exec.LDT.Size
;-------------------------------------------------------------------------------
; Calculate final GDT Segment size
                SEGMENT         GDT  VSTART=0  ALIGN=x86.PARA

GDT.Base        EQU             Exec.LDT.Base + Exec.LDT.Size

GDT.Limit       EQU             $ - $$ - 1

; Note that GDT grows from here - no alignment necessary

GDT.Size.Init   EQU             $ - $$   ; Initial size of GDT

GDT.Size        EQU             8192 * x86.Desc_size ; Largest size of GDT

%assign         Image.Size      Image.Size + GDT.Size.Init

%assign         Demo.Size       Demo.Size + GDT.Size.Init
;===============================================================================
; Calculate final Boot.Real Segment size
; Note this segment falls through to Boot.GDT
                SEGMENT         Boot.Real   ALIGN=x86.PARA ; Real mode segment

                ALIGN           x86.PARA ;, DB 0FFh     ; Need to pad with NOP

Boot.Real.Size  EQU             $ - $$

Boot.Real.Start EQU            (Boot.GDT.Start - Boot.Real.Size) & ~(x86.PARA-1)

%assign         Image.Size      Image.Size + Boot.Real.Size

%assign         Boot.Size       Boot.Size + Boot.Real.Size

;                SEGMENT         Boot.Real    START=Boot.Real.Start
;-------------------------------------------------------------------------------
; Calculate final Boot.GDT Segment size
; Note this Segment falls through from Boot.Real
                SEGMENT         Boot.GDT   ALIGN=x86.PARA

                ALIGN           x86.PARA, DB 0FFh

Boot.GDT.Size   EQU             $ - $$

Boot.GDT.Start  EQU            (Boot.Prot.Start - Boot.GDT.Size) & ~(x86.PARA-1)

%assign         Image.Size      Image.Size + Boot.GDT.Size

%assign         Boot.Size       Boot.Size + Boot.GDT.Size

;               SEGMENT         Boot.GDT     START=Boot.GDT.Start
;-------------------------------------------------------------------------------
; Calculate final Boot.Prot Segment size
                SEGMENT         Boot.Prot

                ALIGN           x86.PARA, DB 0FFh

Boot.Prot.Size  EQU             $ - $$

Boot.Prot.Start EQU            (Boot.Reset.Start - Boot.Prot.Size) & ~(x86.PARA - 1)

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

%assign         EEPROM.Pad      ROM.Size - Demo.Size - Boot.Size

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
