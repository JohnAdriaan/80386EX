;
; Demo.inc
;

                SEGMENT         Demo

Demo.IDT.Base   EQU             0000_0000h
Demo.Data.Base  EQU             Demo.IDT.Base + x86.IDT.Size.Max
Demo.GDT.Base   EQU             Demo.IDT.Base + x86.PAGE.Size
Demo.Exec.LDT.Base   EQU        Demo.GDT.Base + x86.GDT.Size.Max
Demo.Exec.Stack.Base EQU        Demo.Exec.LDT.Base + Demo.Exec.LDT.Size
Demo.Exec.Stack.Top  EQU        Demo.Exec.Stack.Base + Demo.Exec.Stack.Size
Demo.First      EQU             Demo.Exec.Stack.Top ; First unallocated RAM

Screen.Base     EQU             03F0_0000h
Screen.Cols     EQU             90
Screen.Rows     EQU             43

%include        "Demo/Defn.inc"         ; Definitions for various parameters
;-------------------------------------------------------------------------------
%include        "Demo/Data.inc"         ; Global Data Segment
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Ints.inc"    ; Interrupt handlers
;-------------------------------------------------------------------------------
%include        "Demo/User/User.inc"    ; User Mode program
;-------------------------------------------------------------------------------
                SEGMENT         Demo.Exec

%include        "Demo/Exec/Exec.inc"    ; Supervisor Mode executive
