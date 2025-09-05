;
; Boot/Prot/Prot.inc
;

; Protected-mode definition and code files

;-------------------------------------------------------------------------------
%include        "Boot/Prot/PM.inc"           ; Go into Protected Mode
;-------------------------------------------------------------------------------
%include        "Boot/Prot/SRAM.inc"         ; Init Static RAM (SRAM) and CS
;-------------------------------------------------------------------------------
%include        "Boot/Prot/DRAM.inc"         ; Init Dynamic RAM (DRAM) and CS
;-------------------------------------------------------------------------------
%include        "Boot/Prot/Video.inc"        ; Init Video
;-------------------------------------------------------------------------------
%include        "Boot/Prot/KbdMouse.inc"     ; Init Keyboard/Mouse controller
;-------------------------------------------------------------------------------
%include        "Boot/Prot/RTC.inc"          ; Init Real-Time Clock
;-------------------------------------------------------------------------------
Boot.Exit:
                MOV             EBP, [SRAM.Start + DRAM.Limit] ; Tell Executive RAM limit
                JMP             Demo.Boot
;-------------------------------------------------------------------------------
%include        "Boot/Prot/Hex.inc"          ; Hex out the serial port
;-------------------------------------------------------------------------------
%include        "Boot/Prot/Fatal.inc"        ; Fatal routine
;-------------------------------------------------------------------------------
