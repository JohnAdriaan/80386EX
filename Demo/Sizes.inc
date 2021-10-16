;
; Demo.Sizes.inc
;

; Calculate final Demo.Boot Segment size
                SEGMENT         Demo.Boot  ALIGN=Align.Para

                ALIGN           Align.Para, DB 0

Demo.Boot.Size  EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.Boot.Size

%assign         Image.Size      Image.Size + Demo.Boot.Size
;-------------------------------------------------------------------------------
; Calculate final IDT Segment size
                SEGMENT         Demo.IDT  VSTART=0  ALIGN=Align.Para

Demo.IDT.Num    EQU             ($ - $$) / x86.Desc.Size

                ALIGN           Align.Para, DB 0

Demo.IDT.Size   EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.IDT.Size

%assign         Image.Size      Image.Size + Demo.IDT.Size
;-------------------------------------------------------------------------------
; Calculate final Data Segment size
                SEGMENT         Demo.Data  START=0  ALIGN=Align.Para  NOBITS

Demo.Data.Limit EQU             $ - $$ - 1

;-------------------------------------------------------------------------------
; Calculate final Ints Segment size
                SEGMENT         Demo.Ints  VSTART=0  ALIGN=Align.Para

Demo.Ints.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para

Demo.Ints.Size  EQU             $ - $$

%ifdef USE_SRAM
Demo.Ints.Base  EQU             SRAM.Start + Demo.Size

Copy.Source     EQU             section.Demo.Ints.start

Copy.Dest       EQU             Demo.Ints.Base
%else
Demo.Ints.Base  EQU             x86.EX.Addr.Size - ROM.Size + Demo.Size
%endif

%assign         Demo.Size       Demo.Size + Demo.Ints.Size

%assign         Image.Size      Image.Size + Demo.Ints.Size
;-------------------------------------------------------------------------------
; Calculate final User.Code Segment size
                SEGMENT         Demo.User  VSTART=0  ALIGN=Align.Para

Demo.User.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para

%ifdef USE_SRAM
Demo.User.Base  EQU             SRAM.Start + Demo.Size
%else
Demo.User.Base  EQU             x86.EX.Addr.Size - ROM.Size + Demo.Size
%endif

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
; Calculate final Exec Segment size
                SEGMENT         Demo.Exec  VSTART=0  ALIGN=Align.Para

Demo.Exec.Limit EQU             $ - $$ - 1

                ALIGN           Align.Para

%ifdef USE_SRAM
Demo.Exec.Base  EQU             SRAM.Start + Demo.Size
%else
Demo.Exec.Base  EQU             x86.EX.Addr.Size - ROM.Size + Demo.Size
%endif

Demo.Exec.Size  EQU             $ - $$

%assign         Demo.Size       Demo.Size + Demo.Exec.Size

%assign         Image.Size      Image.Size + Demo.Exec.Size

%ifdef USE_SRAM
Copy.Size       EQU             Demo.Exec.Base + Demo.Exec.Size - Copy.Dest
%endif
;-------------------------------------------------------------------------------
; Calculate final Exec.LDT Segment size
                SEGMENT         Demo.Exec.LDT  VSTART=0  ALIGN=Align.Para

Demo.Exec.LDT.Num EQU           ($ - $$) / x86.Desc.Size

Demo.Exec.LDT.Num.Max EQU       Demo.Exec.LDT.Pos / x86.Desc.Size

Demo.Exec.LDT.Limit EQU         Demo.Exec.LDT.Pos-1

Demo.Exec.LDT.Size  EQU         Demo.Exec.LDT.Pos

                ALIGN           Align.Para, DB 0

%assign         Demo.Size       Demo.Size + ($ - $$)

%assign         Image.Size      Image.Size + ($ - $$)
;-------------------------------------------------------------------------------
; Calculate final GDT Segment size
                SEGMENT         Demo.GDT  VSTART=0  ALIGN=Align.Para

Demo.GDT.Limit  EQU             $ - $$ - 1

Demo.GDT.Num    EQU             ($ - $$) / x86.Desc.Size

; Note that GDT grows from here - no alignment necessary

Demo.GDT.Size   EQU             $ - $$   ; Initial size of GDT

%assign         Demo.Size       Demo.Size + Demo.GDT.Size

%assign         Image.Size      Image.Size + Demo.GDT.Size
;===============================================================================
