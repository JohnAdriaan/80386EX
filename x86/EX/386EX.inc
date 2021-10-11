;
; x86/EX/386EX.inc
;

; The following are definitions specifically for the 80386EX
;
; Note that they're defined by Intel as part of the 'DNA' of the chip: almost
; literally, if you think of the silicon as defining the CPU's operation.

x86.EX.Addr.Size EQU       0400_0000h ; Physical address size
;-------------------------------------------------------------------------------
%include        "x86/EX/Remap.inc"    ; Definitions for RemapCFG ports
;-------------------------------------------------------------------------------
%include        "x86/EX/GPIO.inc"     ; Definitions for GPIO ports
;-------------------------------------------------------------------------------
%include        "x86/EX/CSU.inc "     ; Definitions for Chip Select Unit
;-------------------------------------------------------------------------------
%include        "x86/EX/RFS.inc "     ; Definitions for Refresh Control Unit
;-------------------------------------------------------------------------------
%include        "x86/EX/TMR.inc "     ; Definitions for Timer/Counter Unit
;-------------------------------------------------------------------------------
