;
; Boot.inc
;

; This routine copies ROM structures to RAM before using them.
; The structures copied are:
; 0) [Optional] The ROM code itself, into DRAM or SRAM (see below)
; 1) The IDT. The first 48 (or so) entries are already defined in ROM, but new
;    ones (up to 256 total) can be created at run-time, so the table has to be
;    in RAM. Then the IDTR is initialised.
; 2) The full GDT. Again, the first few entries are effectively fixed, since
;    Interrupt Handlers point to them. So the ones defined in ROM are copied,
;    then the rest of the GDT is zeroed waiting for more entries to be created
;    at runtime. Then the GDTR is initialised.
; 3) The Executive's LDT. This is fairly static, but it may need to be modified
;    (see below). Then the LDTR is initialised.
; 4) All of the above structures are copied and initialised to DRAM.
;
;    Optionally, the code itself can be copied out of ROM and into RAM - of
;    either flavour: SRAM or DRAM. Both types of RAM are faster to access, but
;    SRAM is even faster; but at least DRAM is expected to exist!

                SEGMENT         Demo.Boot

                USE32

Demo.Boot:
                XOR             ECX, ECX        ; Can now load just CX (smaller)

%ifdef COPY_ROM
; Copy code to S/DRAM
                MOV             CX,  Copy.Size / x86.DWORD.Size
                MOV             ESI, Copy.Source
                MOV             EDI, Copy.Dest
             CS REP             MOVSD
%endif

; Copy and fill IDT to RAM
                MOV             CX,  Demo.IDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.IDT.start
                MOV             EDI, Demo.IDT.Base
             CS REP             MOVSD

                MOV             CX,  (x86.IDT.Num.Max - Demo.IDT.Num) * x86.Desc.Size / x86.DWORD.Size
                LEA             ESI, [EDI - x86.Desc.Size] ; Copy final entry
                REP             MOVSD                      ; Repeatedly

; Copy and fill GDT to RAM
                MOV             CL,  Demo.GDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.GDT.start
                MOV             EDI, Demo.GDT.Base
             CS REP             MOVSD

                ; Zero out the rest of the GDT
                XOR             EAX, EAX        ; Zeroes
                MOV             CX,  (x86.GDT.Num.Max - Demo.GDT.Num) * x86.Desc.Size / x86.DWORD.Size
                REP             STOSD

; Copy and fill Exec.LDT to RAM
                MOV             CL,  Demo.Exec.LDT.Num * x86.Desc.Size / x86.DWORD.Size
                MOV             ESI, section.Demo.Exec.LDT.start
                MOV             EDI, Demo.Exec.LDT.Base
             CS REP             MOVSD

;               MOV             CL,  (Demo.Exec.LDT.Num.Max - Demo.Exec.LDT.Num) * x86.Desc.Size / x86.DWORD.Size
;               REP             STOSD           ; Gonna be overwritten immediately anyway...

; Now that everything's copied, point (in order) to GDT, IDT, and LDT
            O32 LGDT            [Demo.GDT.Base + Demo.GDT.Alloc.Pseudo]

                PUSH   DWORD    Demo.IDT.Base        ; Put on stack as Pseudo-descriptor
                PUSH    WORD    x86.IDT.Size.Max - 1 ; Only this many entries in IDT
            O32 LIDT            [ESP]
; We're about to abandon the stack, so don't bother fixing it up!

                MOV             AX, x86.Selector(Demo.GDT.Exec.LDT, .GDT, .RPL0)
                LLDT            AX

; Jump to Executive Entry inside the LDT
                JMP             x86.Selector(Demo.Exec.LDT.Code, .LDT, .RPL0) : DWORD Demo.Exec.Entry

%if 0
.Forever:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

                MOV             AL, 42
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                JMP             .Forever
%endif
