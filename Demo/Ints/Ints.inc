;
; Ints/Ints.inc
;

%define         User.Halt       INT 48
%define         User.Yield      INT 49

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
%include        "Demo/Ints/KbdMouse.inc"     ; Example Keyboard/Mouse interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Video.inc"        ; Example Video interrupt handler
;-------------------------------------------------------------------------------
%include        "Demo/Ints/Util.inc"         ; Utility functions
