;
; Boot/Boot.inc
;

; This is the Boot ROM, including reset Entry Point. It initially runs in
; Real Mode, then transitions to Protected Mode to test RAM.
;
; The biggest problem is that immediately after Reset, there is no RAM! The
; only storage that can be relied upon are the CPU's registers themselves -
; not including this ROM image, of course.
;
; No RAM means no stack, so code can't be separately CALLable modules. Instead,
; it has to simply "fall through" from one module to the next. Be careful to
; JMP over any embedded data you might define...
;
; Note that one module might have code for both Real and Protected Mode. In that
; case, the relevant segment will be opened, continuing on from the previous
; code. It could look like the code continues from Real to Protected - nope!
;
; It is important that the modules are %included in the order below: each could
; prepare resources for future modules.
;

;===============================================================================
                SEGMENT         Boot.Real

%include        "Boot/Defn.inc"         ; Definitions for use by ROM routines
;-------------------------------------------------------------------------------
Boot.Code.Entry:                        ; Reset JMP point

%include        "Boot/CPU.inc"          ; Init CPU
;-------------------------------------------------------------------------------
%include        "Boot/386EX.inc"        ; Init 386EX peripherals
;-------------------------------------------------------------------------------
%include        "Boot/FPU.inc"          ; Init FPU, if present
;-------------------------------------------------------------------------------
%include        "Boot/PIC.inc"          ; Init Priority Interrupt Controllers
;-------------------------------------------------------------------------------
%include        "Boot/GPIO.inc"         ; Init General-Purpose I/O (Lites)
;-------------------------------------------------------------------------------
%include        "Boot/Timer.inc"        ; Init Timer (TCU)
;-------------------------------------------------------------------------------
%include        "Boot/SIO.inc"          ; Init Serial I/O (UART)
;-------------------------------------------------------------------------------
%include        "Boot/CSU.inc"          ; Init Chip Select Unit (CSU)
;-------------------------------------------------------------------------------
%include        "Boot/GDT.inc"          ; Init Global Descriptor Table (GDT)
;-------------------------------------------------------------------------------
%include        "Boot/Font.inc"         ; Font definition
;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32
;-------------------------------------------------------------------------------
%include        "Boot/PM.inc"           ; Go into Protected Mode
;-------------------------------------------------------------------------------
%include        "Boot/ROM.inc"          ; Init ROM Chip Select (CS)
;-------------------------------------------------------------------------------
%include        "Boot/SRAM.inc"         ; Init Static RAM (SRAM) and CS
;-------------------------------------------------------------------------------
%include        "Boot/DRAM.inc"         ; Init Dynamic RAM (DRAM) and CS
;-------------------------------------------------------------------------------
%include        "Boot/ECB.inc"          ; Init EuroCard Bus Chip Selects
;-------------------------------------------------------------------------------
%include        "Boot/Video.inc"        ; Init Video
;-------------------------------------------------------------------------------
%include        "Boot/Keyboard.inc"     ; Init Keyboard
;-------------------------------------------------------------------------------
%include        "Boot/RTC.inc"          ; Init Real-Time Clock
;-------------------------------------------------------------------------------
%include        "Boot/IDE.inc"          ; Init IDE and Chip Select
;-------------------------------------------------------------------------------
%include        "Boot/SDCard.inc"       ; Init SDCard
;-------------------------------------------------------------------------------
Boot.Exit:
                MOV             EBP, [SRAM.Start + DRAM.Limit] ; Tell Executive RAM limit
                JMP      WORD   Demo.Boot
;-------------------------------------------------------------------------------
%include        "Boot/Hex.inc"          ; Hex out the serial port
;-------------------------------------------------------------------------------
%include        "Boot/Fatal.inc"        ; Fatal routine
;-------------------------------------------------------------------------------
%include        "Boot/Reset.inc"        ; CPU Reset entry point
;-------------------------------------------------------------------------------
