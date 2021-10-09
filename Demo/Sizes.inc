;
; Demo.Sizes.inc
;

; Calculate final Header Segment size
                SEGMENT         Demo  ALIGN=Align.Para

                ALIGN           Align.Para, DB 0

Header.Size     EQU             $ - $$

%assign         Image.Size      Image.Size + Header.Size

%assign         Demo.Size       Demo.Size + Header.Size
;-------------------------------------------------------------------------------
; Calculate final IDT Segment size
                SEGMENT         IDT  VSTART=0  ALIGN=Align.Para

IDT.Addr        EQU             Code.Base - IDT.Size

IDT.Limit       EQU             $ - $$ - 1

                ALIGN           Align.Para, DB 0

IDT.Size        EQU             $ - $$

%assign         Image.Size      Image.Size + IDT.Size

%assign         Demo.Size       Demo.Size + IDT.Size
;-------------------------------------------------------------------------------
; Calculate final Ints Segment size
                SEGMENT         Ints  VSTART=0  ALIGN=Align.Para

Ints.Base       EQU             IDT.Addr + IDT.Size ; Equivalent to Code.Base

Ints.Limit      EQU             $ - $$ - 1

                ALIGN           Align.Para

Ints.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + Ints.Size

%assign         Demo.Size       Demo.Size + Ints.Size
;-------------------------------------------------------------------------------
; Calculate final User.Code Segment size
                SEGMENT         User  VSTART=0  ALIGN=Align.Para

User.Base       EQU             Ints.Base + Ints.Size

User.Limit      EQU             $ - $$ - 1

                ALIGN           Align.Para

User.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + User.Size

%assign         Demo.Size       Demo.Size + User.Size
;-------------------------------------------------------------------------------
; Calculate final User.LDT Segment size
                SEGMENT         User.LDT  ALIGN=Align.Para  NOBITS

User.LDT.Limit  EQU             $ - $$ - 1

                ALIGNB          Align.Para

User.LDT.Size   EQU             $ - $$
;-------------------------------------------------------------------------------
; Calculate final User.Data Segment size
                SEGMENT         User.Data  ALIGN=Align.Para  NOBITS

User.Data.Limit EQU             $ - $$ - 1

                ALIGNB          Align.Para

User.Data.Size  EQU             $ - $$
;-------------------------------------------------------------------------------
; Calculate final Exec Segment size
                SEGMENT         Exec  VSTART=0  ALIGN=Align.Para

Exec.Base       EQU             User.Base + User.Size

Exec.Limit      EQU             $ - $$ - 1

                ALIGN           Align.Para

Exec.Size       EQU             $ - $$

%assign         Image.Size      Image.Size + Exec.Size

%assign         Demo.Size       Demo.Size + Exec.Size
;-------------------------------------------------------------------------------
; Calculate final Exec.LDT Segment size
                SEGMENT         Exec.LDT  VSTART=0  ALIGN=Align.Para

Exec.LDT.Base   EQU             Exec.Base + Exec.Size

Exec.LDT.Limit  EQU             $ - $$ - 1

                ALIGN           Align.Para, DB 0

Exec.LDT.Size   EQU             $ - $$

%assign         Image.Size      Image.Size + Exec.LDT.Size

%assign         Demo.Size       Demo.Size + Exec.LDT.Size
;-------------------------------------------------------------------------------
; Calculate final GDT Segment size
                SEGMENT         GDT  VSTART=0  ALIGN=Align.Para

GDT.Base        EQU             Exec.LDT.Base + Exec.LDT.Size

GDT.Limit       EQU             $ - $$ - 1

; Note that GDT grows from here - no alignment necessary

GDT.Size        EQU             $ - $$   ; Initial size of GDT

%assign         Image.Size      Image.Size + GDT.Size

%assign         Demo.Size       Demo.Size + GDT.Size
;===============================================================================
