;
; Demo.inc
;

;%define USE_SRAM

                SEGMENT         Demo

Demo.IDT.Base   EQU             0000_0000h
Demo.Data.Base  EQU             Demo.IDT.Base + x86.IDT.Size.Max
Demo.GDT.Base   EQU             Demo.IDT.Base + x86.PAGE.Size
Demo.Exec.LDT.Base   EQU        Demo.GDT.Base + x86.GDT.Size.Max
Demo.Exec.Stack.Base EQU        Demo.Exec.LDT.Base + Demo.Exec.LDT.Size
Demo.Exec.Stack.Top  EQU        Demo.Exec.Stack.Base + Demo.Exec.Stack.Size
Demo.First      EQU             Demo.Exec.Stack.Top ; First unallocated RAM

Screen.Base     EQU             03F0_0000h
Screen.Cols     EQU             Screen.Width
Screen.Rows     EQU             Screen.Height   

%include        "Demo/Defn.inc"         ; Definitions for various parameters
;-------------------------------------------------------------------------------
                SEGMENT         Demo.Boot

%include        "Demo/Boot.inc"         ; Move to final positions
;-------------------------------------------------------------------------------
                SEGMENT         Demo.Data   NOBITS

%include        "Demo/Data.inc"         ; Global Data Segment
;-------------------------------------------------------------------------------
                SEGMENT         Demo.IDT

                SEGMENT         Demo.Ints

%include        "Demo/Ints/Ints.inc"    ; Interrupt handlers
;-------------------------------------------------------------------------------
                SEGMENT         Demo.User

%include        "Demo/User/User.inc"    ; User Mode program
;-------------------------------------------------------------------------------
                SEGMENT         Demo.Exec

%include        "Demo/Exec/Exec.inc"    ; Supervisor Mode executive
