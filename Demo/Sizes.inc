;
; Demo.Sizes.inc
;

Demo.Base       EQU             ROM.Start ; ***!!!*** Change when COPY_ROM implemented

; Calculate final Demo.Data Segment size
                SEGMENT         Demo.Data  FOLLOWS=Boot.Data ALIGN=Align.Para  NOBITS

Demo.Data.Size  EQU             $ - $$

;-------------------------------------------------------------------------------
; Calculate final Demo.Label Segment size
                SEGMENT         Demo.Label  ALIGN=Align.Para

                ALIGN           Align.Para, DB 0xFF

Demo.Label.Size EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.Label.Size

%assign         Image.Size      Image.Size + Demo.Label.Size
;-------------------------------------------------------------------------------
; Calculate final Demo.IDT Segment size
                SEGMENT         Demo.IDT  VSTART=0  ALIGN=Align.Para

Demo.IDT.Num    EQU             ($ - $$) / x86.Desc.Size

                ALIGN           Align.Para, DB 0

Demo.IDT.Size   EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.IDT.Size

%assign         Image.Size      Image.Size + Demo.IDT.Size
;-------------------------------------------------------------------------------
; Calculate final Demo.Boot Segment size
                SEGMENT         Demo.Boot  ALIGN=Align.Para

                ALIGN           Align.Para      ; Pad with NOPs

Demo.Boot.Size  EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.Boot.Size

%assign         Image.Size      Image.Size + Demo.Boot.Size
;-------------------------------------------------------------------------------
; Calculate final Demo.Ints Segment size
                SEGMENT         Demo.Ints  VSTART=0  ALIGN=Align.Para

Demo.Ints.Base  EQU             Demo.Base + Demo.Size
Demo.Ints.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para      ; Pad with NOPs

Demo.Ints.Size  EQU             $ - $$

%ifdef COPY_ROM
Copy.Source     EQU             section.Demo.Ints.start
%endif ; COPY_ROM

%assign         Demo.Size       Demo.Size + Demo.Ints.Size

%assign         Image.Size      Image.Size + Demo.Ints.Size
;-------------------------------------------------------------------------------
; Calculate final Demo.Exec Segment size
                SEGMENT         Demo.Exec  VSTART=0  ALIGN=Align.Para

Demo.Exec.Base  EQU             Demo.Base + Demo.Size
Demo.Exec.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para

Demo.Exec.Size  EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.Exec.Size

%assign         Image.Size      Image.Size + Demo.Exec.Size

%ifdef COPY_ROM
Copy.Size       EQU             Demo.Exec.Base + Demo.Exec.Size - Copy.Dest
%endif
;-------------------------------------------------------------------------------
; Calculate final Exec.LDT Segment size
                SEGMENT         Demo.Exec.LDT  VSTART=0  ALIGN=Align.Para

Demo.Exec.LDT.Num EQU           ($ - $$) / x86.Desc.Size

Demo.Exec.LDT.Num.Max EQU       Demo.Exec.LDT.Pos / x86.Desc.Size

Demo.Exec.LDT.Limit EQU         Demo.Exec.LDT.Pos-1

Demo.Exec.LDT.Size  EQU         Demo.Exec.LDT.Pos

                ALIGN           Align.Para, DB 0FFh

%assign         Demo.Size       Demo.Size + ($ - $$)

%assign         Image.Size      Image.Size + ($ - $$)
;-------------------------------------------------------------------------------
; Calculate final User.Code Segment size
                SEGMENT         Demo.User  VSTART=0  ALIGN=Align.Para

Demo.User.Base  EQU             Demo.Base + Demo.Size
Demo.User.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para

Demo.User.Size  EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.User.Size

%assign         Image.Size      Image.Size + Demo.User.Size
;-------------------------------------------------------------------------------
; Calculate final User.LDT Segment size
                SEGMENT         Demo.User.LDT  ALIGN=Align.Para  NOBITS

Demo.User.LDT.Limit EQU         $ - $$ - 1

                ALIGNB          Align.Para

Demo.User.LDT.Size  EQU         $ - $$
;-------------------------------------------------------------------------------
; Calculate final User.Data Segment size
                SEGMENT         Demo.User.Data  ALIGN=Align.Para  NOBITS

Demo.User.Data.Limit EQU        $ - $$ - 1

                ALIGNB          Align.Para

Demo.User.Data.Size  EQU        $ - $$
;-------------------------------------------------------------------------------
; Calculate final Demo.GDT Segment size
                SEGMENT         Demo.GDT  VSTART=0  ALIGN=Align.Para

Demo.GDT.Limit  EQU             $ - $$ - 1

Demo.GDT.Num    EQU             ($ - $$) / x86.Desc.Size

; Note that GDT grows from here - no alignment necessary

Demo.GDT.Size   EQU             $ - $$   ; Initial size of GDT

%assign         Demo.Size       Demo.Size + Demo.GDT.Size

%assign         Image.Size      Image.Size + Demo.GDT.Size
