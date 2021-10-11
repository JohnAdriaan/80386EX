;
; Exec/Exec.inc
;

; This module finishes the transition into Protected Mode, sets up the system to
; be less "bare bones" than was achieved via the bootstrap process, and finally
; starts to actually create some User-mode programs.
;
; You'll note that there are Allocate functions to handle common operations,
; like allocating more Memory, or an entry in the GDT or an LDT. Say "farewell"
; to assembler-assigned constants!

                SEGMENT         Demo.Exec

Demo.Exec.Stack.Size  EQU       x86.PAGE.Size    ; Don't need much

; At this point we're still in Boot-time Linear addressing.
; Be careful with addresses!
Demo.Entry      EQU             section.Demo.Exec.start
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Boot.inc"         ; Move to final positions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Entry.inc"        ; Entry point in Executive's LDT
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Init.inc"         ; Initialise rest of Protected Mode
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Ints/Ints.inc"    ; Install more sophisticated Fault handlers
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Timer.inc"        ; Install Timer interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Key.inc"          ; Install keyboard handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/User/User.inc"    ; Start creating User programs
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/Alloc.inc"  ; Helper functions to allocate things
;-------------------------------------------------------------------------------
%include        "Demo/Exec/LDT.inc"          ; The Executive's LDT
;-------------------------------------------------------------------------------
%include        "Demo/Exec/GDT.inc"          ; The System's GDT