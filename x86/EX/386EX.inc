;
; x86/EX/386EX.inc
;

; The following are definitions specifically for the 80386EX
;
; Note that they're defined by Intel as part of the 'DNA' of the chip: almost
; literally, if you think of the silicon as defining the CPU's operation.

;-------------------------------------------------------------------------------
%include        "x86/EX/RemapCFG.inc" ; Definitions for RemapCFG ports
;-------------------------------------------------------------------------------
%include        "x86/EX/GPIO.inc"     ; Definitions for GPIO ports
;-------------------------------------------------------------------------------
%include        "x86/EX/CSU.inc "     ; Definitions for Chip Select Unit
;-------------------------------------------------------------------------------
