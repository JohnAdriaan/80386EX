;
; Boot/Real/Real.inc
;

; Real-mode definitions and code files
;-------------------------------------------------------------------------------
%include        "Boot/Real/CPU.inc"          ; Init CPU
;-------------------------------------------------------------------------------
%include        "Boot/Real/386EX.inc"        ; Init 386EX peripherals
;-------------------------------------------------------------------------------
%include        "Boot/Real/CSU.inc"          ; Init Chip Select Unit (CSU)
;-------------------------------------------------------------------------------
%include        "Boot/Real/ROM.inc"          ; Init ROM Chip Select (CS)
;-------------------------------------------------------------------------------
%include        "Boot/Real/SRAM.inc"         ; Init SRAM Chip Select (CS)
;-------------------------------------------------------------------------------
%include        "Boot/Real/DRAM.inc"         ; Init DRAM Chip Select (CS)
;-------------------------------------------------------------------------------
%include        "Boot/Real/FPU.inc"          ; Init FPU, if present
;-------------------------------------------------------------------------------
%include        "Boot/Real/PIC.inc"          ; Init Priority Interrupt Controllers
;-------------------------------------------------------------------------------
%include        "Boot/Real/GPIO.inc"         ; Init General-Purpose I/O (Lites)
;-------------------------------------------------------------------------------
%include        "Boot/Real/Timer.inc"        ; Init Timer (TCU)
;-------------------------------------------------------------------------------
%include        "Boot/Real/SIO.inc"          ; Init Serial I/O (UART)
;-------------------------------------------------------------------------------
%include        "Boot/Real/IDE.inc"          ; Init IDE Chip Select (CS)
;-------------------------------------------------------------------------------
%include        "Boot/Real/SDCard.inc"       ; Init SDCard
;-------------------------------------------------------------------------------
%include        "Boot/Real/ECB.inc"          ; Init Euro Card Bus Chip Selects (CS)
;-------------------------------------------------------------------------------
%include        "Boot/Real/Video.inc"        ; Video display
