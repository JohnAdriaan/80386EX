;
; Exec/Exec.inc
;

; This module finishes the transition into Protected Mode, sets up the system to
; be less "bare bones" than was achieved via the bootstrap process, and finally
; starts to actually create some User-mode programs.
;
; First, you'll note I'm no longer using the "stream of code" paradigm that I
; used for the bootstrap - the need for that has gone away. I now have as much
; memory as I need!
;
; Second, you'll note that there are Allocate functions to handle common
; operations, like allocating more Memory, or an entry in the GDT or an LDT.

                SEGMENT         Exec

                USE32

; At this point we're still in Boot-time Linear addressing.
; Be careful with addresses!
Exec.Entry:
            O32 LGDT            [GDT.NULL + GDT.Alloc.Pseudo]

                PUSH   DWORD    IDT         ; Put on stack as Pseudo-descriptor
                PUSH    WORD    IDT.Limit   ; Only this many entries in IDT
            O32 LIDT            [ESP]
; We're about to abandon the stack, so don't bother fixing it up!

                MOV             AX, Selector(GDT.Exec.LDT, GDT, RPL0)
                LLDT            AX
                JMP             Exec.LDT.Code : DWORD Exec.Code

                ALIGN           Align.Para, DB 0FFh

; Made it! We're booted in Protected Mode! (You can un-cross your fingers now...)
; Before we can do anything else though, we need to set up a Protected Mode stack
Exec.Code:
                ; Point to Stack
                MOV             AX,Selector(Exec.LDT.Stack, .LDT, .RPL0)
                MOV             SS,AX
                XOR             ESP,ESP ; One of the advantages of Expand-Down Stacks!

                ; Initialise the rest of the registers
                CALL            Exec.Init

                ; Create more robust critical Fault handlers, with their own contexts
                ; To demonstrate the need for this, uncomment the next line...
;               MOV             ESP,1   ; The next stack operation will triple-fault
                CALL            Exec.Ints
                ; Once they've been installed, the same instruction is handled
;               MOV             ESP,1   ; This will fault, but at least it's handled

                ; OK, we're all ready! Time to start the system!
                STI                     ; Enable interrupts

                ; Set up the Timer interrupt handler, and enable it
                CALL            Exec.Timer

                ; Human interaction (via the keyboard) would be nice...
                CALL            Exec.Key

                ; Everything's ready! We can start to create User-mode Programs
                JMP             Exec.User
;-------------------------------------------------------------------------------
%include        "Exec/Init.inc"         ; Initialise rest of Protected Mode
;-------------------------------------------------------------------------------
%include        "Exec/Ints/Ints.inc"    ; Install more sophisticated Fault handlers
;-------------------------------------------------------------------------------
%include        "Exec/Timer.inc"        ; Install Timer interrupt handler
;-------------------------------------------------------------------------------
%include        "Exec/Key.inc"          ; Install keyboard handler
;-------------------------------------------------------------------------------
%include        "Exec/User/User.inc"    ; Start creating User programs
;-------------------------------------------------------------------------------
%include        "Exec/Alloc/Alloc.inc"  ; Helper functions to allocate things
;-------------------------------------------------------------------------------
%include        "Exec/LDT.inc"          ; The Executive's LDT
;-------------------------------------------------------------------------------
%include        "Exec/GDT.inc"          ; The System's GDT
