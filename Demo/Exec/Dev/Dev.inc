;
; Exec/Dev/Dev.inc
;

; This module holds all the Device drivers for the Executive

;-------------------------------------------------------------------------------
%include        "Demo/Exec/Dev/Timer.inc"    ; Install Timer interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Dev/Key.inc"      ; Install Keyboard interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Dev/Mouse.inc"    ; Install Mouse interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Dev/Video.inc"    ; Install Video interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Dev/RTC.inc"      ; Set up Real Time Clock data
