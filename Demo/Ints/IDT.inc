;
; Ints/IDT.inc
;

; This is the Interrupt Descriptor Table for the system.
; For each potential interrupt, it points to the relevant routine.
; Note that only the first 32 Intel-reserved interrupts, and the 16 Interrupt
; ReQuest IRQs, are set up. Although sufficient memory has been allocated for
; all 256 interrupts, the IDT is only initialised with these first 48.
; Well, OK: 49. The last one points to an IRET, so that any `INT` instruction
; will immmediately return. The copy code duplicates that entry through the
; rest of the IDT.
;
; EDIT: I decided to add two more, callable from User mode:
; * INT 48 is a User-mode HLT replacement;
; * INT 49 is a Yield call - go to next Task.

                SEGMENT         Demo.IDT

                USE32

IDT.Int         EQU             x86.Type.Sys(.Int,  .DPL0, .386)
IDT.Trap        EQU             x86.Type.Sys(.Trap, .DPL0, .386)
IDT.User.Int    EQU             x86.Type.Sys(.Int,  .DPL3, .386)
IDT.User.Trap   EQU             x86.Type.Sys(.Trap, .DPL3, .386)

Demo.IDT:
Demo.IDT.Divide      x86.Desc.Sys    Demo.GDT.Ints, Ints.Int0, IDT.Trap     ; Int 00h
Demo.IDT.Single      x86.Desc.Sys    Demo.GDT.Ints, Ints.Int1, IDT.Trap     ; Int 01h
Demo.IDT.NMI         x86.Desc.Sys    Demo.GDT.Ints, Ints.Int2, IDT.Trap     ; Int 02h
Demo.IDT.Debug       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int3, IDT.Trap     ; Int 03h
Demo.IDT.INTO        x86.Desc.Sys    Demo.GDT.Ints, Ints.Int4, IDT.Trap     ; Int 04h
Demo.IDT.BOUND       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int5, IDT.Trap     ; Int 05h
Demo.IDT.BadOp       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int6, IDT.Trap     ; Int 06h
Demo.IDT.No387       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int7, IDT.Trap     ; Int 07h
Demo.IDT.Double      x86.Desc.Sys    Demo.GDT.Ints, Ints.Int8, IDT.Trap     ; Int 08h
Demo.IDT.Bad387      x86.Desc.Sys    Demo.GDT.Ints, Ints.Int9, IDT.Trap     ; Int 09h
Demo.IDT.BadTSS      x86.Desc.Sys    Demo.GDT.Ints, Ints.Int10, IDT.Trap    ; Int 0Ah
Demo.IDT.NoSeg       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int11, IDT.Trap    ; Int 0Bh
Demo.IDT.BadStack    x86.Desc.Sys    Demo.GDT.Ints, Ints.Int12, IDT.Trap    ; Int 0Ch
Demo.IDT.GPF         x86.Desc.Sys    Demo.GDT.Ints, Ints.Int13, IDT.Trap    ; Int 0Dh
Demo.IDT.Page        x86.Desc.Sys    Demo.GDT.Ints, Ints.Int14, IDT.Trap    ; Int 0Eh
Demo.IDT.15          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int15, IDT.Trap    ; Int 0Fh
Demo.IDT.Float       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int16, IDT.Trap    ; Int 10h
Demo.IDT.Align       x86.Desc.Sys    Demo.GDT.Ints, Ints.Int17, IDT.Trap    ; Int 11h
Demo.IDT.Machine     x86.Desc.Sys    Demo.GDT.Ints, Ints.Int18, IDT.Trap    ; Int 12h
Demo.IDT.SIMD        x86.Desc.Sys    Demo.GDT.Ints, Ints.Int19, IDT.Trap    ; Int 13h
Demo.IDT.VM          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int20, IDT.Trap    ; Int 14h
Demo.IDT.21          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int21, IDT.Trap    ; Int 15h
Demo.IDT.22          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int22, IDT.Trap    ; Int 16h
Demo.IDT.23          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int23, IDT.Trap    ; Int 17h
Demo.IDT.24          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int24, IDT.Trap    ; Int 18h
Demo.IDT.25          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int25, IDT.Trap    ; Int 19h
Demo.IDT.26          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int26, IDT.Trap    ; Int 1Ah
Demo.IDT.27          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int27, IDT.Trap    ; Int 1Bh
Demo.IDT.28          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int28, IDT.Trap    ; Int 1Ch
Demo.IDT.29          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int29, IDT.Trap    ; Int 1Dh
Demo.IDT.Security    x86.Desc.Sys    Demo.GDT.Ints, Ints.Int30, IDT.Trap    ; Int 1Eh
Demo.IDT.31          x86.Desc.Sys    Demo.GDT.Ints, Ints.Int31, IDT.Trap    ; Int 1Fh

Demo.IDT.Timer       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ0, IDT.Int      ; Int 20h
Demo.IDT.Key         x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ1, IDT.Int      ; Int 21h
Demo.IDT.Cascade     x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ2, IDT.Int      ; Int 22h
Demo.IDT.COM2        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ3, IDT.Int      ; Int 23h
Demo.IDT.COM1        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ4, IDT.Int      ; Int 24h
Demo.IDT.IRQ5        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ5, IDT.Int      ; Int 25h
Demo.IDT.Floppy      x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ6, IDT.Int      ; Int 26h
Demo.IDT.Printer     x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ7, IDT.Int      ; Int 27h
Demo.IDT.RTC         x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ8, IDT.Int      ; Int 28h
Demo.IDT.Video       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ9, IDT.Int      ; Int 29h
Demo.IDT.IRQ10       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ10, IDT.Int     ; Int 2Ah
Demo.IDT.IRQ11       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ11, IDT.Int     ; Int 2Bh
Demo.IDT.Mouse       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ12, IDT.Int     ; Int 2Ch
Demo.IDT.IRQ13       x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ13, IDT.Int     ; Int 2Dh
Demo.IDT.IDE0        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ14, IDT.Int     ; Int 2Eh
Demo.IDT.IDE1        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRQ15, IDT.Int     ; Int 2Fh

Demo.IDT.Halt        x86.Desc.Sys    Demo.GDT.Ints, Ints.Halt, IDT.User.Trap; Int 30h
Demo.IDT.Yield       x86.Desc.Sys    Demo.GDT.Ints, Ints.Yield, IDT.User.Int; Int 31h

Demo.IDT.IRET        x86.Desc.Sys    Demo.GDT.Ints, Ints.IRET, IDT.User.Trap; Copied
