;
; Boot/Boot.inc
;

; This is the Boot ROM, including reset Entry Point. It runs in Real Mode.
;
; The biggest problem is that immediately after Reset, there is no RAM! The
; only storage that can be relied upon are the CPU's registers themselves -
; not including this ROM image, of course.
; Which gave me an idea. With no RAM, there's no Stack, so the code can't be
; written as a series of subroutines. Instead, it either has to be written
; linearly, as one long string of code, or with separate modules that each have
; to JMP to the next module - which ruins their modularity.
; Unless I implemented a table of JMP vectors in ROM, and each routine would
; finish by executing a JMP [CS:??], where ?? was the designated vector register.
; With no stack BP would be available - pity I can't JMP [CS:SP] in 16-bit code.
; Or can I? After all, that's basically what RET does...
; Implement a hard-coded stack, where each value is in fact the start address
; of the next routine to run.
; So, each routine won't be CALLed - but they will do a RET at their end.
; It is important that the modules are %included in the order below: each will
; prepare resources for future modules.

%include        "Boot/Defn.inc"         ; Definitions for use by ROM routines
;-------------------------------------------------------------------------------
%include        "Boot/Table.inc"        ; Table of RET values

;-------------------------------------------------------------------------------
%include        "Boot/CPU.inc"          ; Init CPU
;-------------------------------------------------------------------------------
%include        "Boot/FPU.inc"          ; Init FPU
;-------------------------------------------------------------------------------
%include        "Boot/IO.inc"           ; Init Advanced I/O space
;-------------------------------------------------------------------------------
%include        "Boot/GPIO.inc"         ; Init General-Purpose I/O (Lites)
;-------------------------------------------------------------------------------
%include        "Boot/CSU.inc"          ; Init Chip Select Unit (CSU)
;-------------------------------------------------------------------------------
%include        "Boot/ROM.inc"          ; Init ROM Chip Select
;-------------------------------------------------------------------------------
%include        "Boot/SRAM.inc"         ; Init Static RAM (SRAM) Chip Select
;-------------------------------------------------------------------------------
%include        "Boot/SIO.inc"          ; Init Serial I/O (UART)
;-------------------------------------------------------------------------------
%include        "Boot/DRAM.inc"         ; Init Dynamic RAM (DRAM) and CS
;-------------------------------------------------------------------------------
%include        "Boot/RTC.inc"          ; Init Real-Time Clock
;-------------------------------------------------------------------------------
%include        "Boot/IDE.inc"          ; Init IDE and Chip Select
;-------------------------------------------------------------------------------
%include        "Boot/SDCard.inc"       ; Init SDCard
;-------------------------------------------------------------------------------
%include        "Boot/ECB.inc"          ; Init EuroCard Bus Chip Selects
;-------------------------------------------------------------------------------
%include        "Boot/Video.inc"        ; Init Video
;-------------------------------------------------------------------------------
%include        "Boot/Keyboard.inc"     ; Init Keyboard

;-------------------------------------------------------------------------------
%include        "Boot/Reset.inc"        ; CPU Reset entry point
;-------------------------------------------------------------------------------
