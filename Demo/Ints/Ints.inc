;
; Ints/Ints.inc
;

;-------------------------------------------------------------------------------
%include        "Demo/Ints/IDT.inc"          ; First, define an IDT
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Vectors.inc"      ; Vectors for each interupt
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Fault.inc"        ; Default Fault handling code
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Single.inc"       ; Example single-step handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Debug/Debug.inc"  ; Example debug handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/User.inc"         ; Demonstrate User System Services
;-------------------------------------------------------------------------------
%include        "Demo/Ints/IRQs.inc"         ; Vectors for each IRQ
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Timer.inc"        ; Example Timer interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Key.inc"          ; Example Keyboard interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Video.inc"        ; Example Video interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Util.inc"         ; Utility functions
