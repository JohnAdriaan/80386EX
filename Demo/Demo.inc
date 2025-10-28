;
; Demo.inc
;

%ifdef COPY_ROM_DRAM
%define COPY_ROM                ; Ensure both set
%else
%ifdef COPY_ROM                 ; Want to copy ROM, but...
%ifndef USE_SRAM                ; ...don't have SRAM?
%define COPY_ROM_DRAM           ; Sanity check
%endif ; !USE_SRAM
%endif ; COPY_ROM
%endif

%ifdef USE_DOUBLEBUFFER_DRAM
%define USE_DOUBLEBUFFER        ; Ensure both set
%else
%ifdef USE_DOUBLEBUFFER         ; Want double-buffering, but...
%ifndef USE_SRAM                ; ...don't have SRAM?
%define USE_DOUBLEBUFFER_DRAM   ; Sanity check
%endif ; !USE_SRAM
%endif ; USE_DOUBLEBUFFER
%endif

                SEGMENT         Demo

%ifdef COPY_ROM_DRAM
Copy.Dest       EQU             0000_0000_0000_0000h
Demo.IDT.Base   EQU             (Copy.Size + x86.PAGE.Size - 1) & ~x86.PAGE.Mask
%else
%ifdef COPY_ROM
Copy.Dest       EQU             SRAM.Start
%endif
Demo.IDT.Base   EQU             0000_0000h
%endif
Demo.GDT.Base   EQU             Demo.IDT.Base + x86.PAGE.Size
Demo.Exec.LDT.Base   EQU        Demo.GDT.Base + x86.GDT.Size.Max
Demo.Exec.Stack.Base EQU        Demo.Exec.LDT.Base + Demo.Exec.LDT.Size
Demo.Exec.Stack.Top  EQU        Demo.Exec.Stack.Base + Demo.Exec.Stack.Size
Demo.First      EQU             Demo.Exec.Stack.Top ; First unallocated RAM

Screen.Base     EQU             Dev.SBC386EX.VGA3.Mem.Start
Screen.Cols     EQU             Screen.Width
Screen.Rows     EQU             Screen.Height

; This is the sequence of Segments. This is important, since some don't need copying!
                SEGMENT         Boot.Data       NOBITS ; Define this first - it goes before
                SEGMENT         Demo.Data       NOBITS
                SEGMENT         Demo.Label             ; Not used
                SEGMENT         Demo.IDT               ; Used during Demo.Boot
                SEGMENT         Demo.Boot              ; This copies to xRAM
                SEGMENT         Demo.Ints              ; Copy this to xRAM
                SEGMENT         Demo.Exec              ; Copy this to xRAM
                SEGMENT         Demo.User              ; Copy this to xRAM
                SEGMENT         Demo.Exec.LDT          ; Used during Demo.Boot
                SEGMENT         Demo.GDT               ; Used during Demo.Boot
                SEGMENT         Demo.User.LDT   NOBITS
                SEGMENT         Demo.User.Data  NOBITS

; At this point we're still in Boot-time Linear addressing.
; Be careful with addresses!

%include        "Demo/Defn.inc"         ; Definitions for various parameters
;-------------------------------------------------------------------------------
%include        "Demo/Data.inc"         ; Global Data Segment
;-------------------------------------------------------------------------------
%include        "Demo/Label.inc"        ; Add human-readable information to ROM code
;-------------------------------------------------------------------------------
%include        "Demo/Boot.inc"         ; Initialise Executive structures
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Ints.inc"    ; Interrupt handlers
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Exec.inc"    ; Supervisor Mode executive
;-------------------------------------------------------------------------------
%include        "Demo/User/User.inc"    ; User Mode program
;-------------------------------------------------------------------------------
%include        "Demo/GDT.inc"          ; Global Descriptor Table (GDT)
