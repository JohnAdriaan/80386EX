;
; Dev/SBC-386EX/FPU.inc
;

; These are the definitions for the SBC-386EX FPU Detect interface

Dev.SBC386EX.FPU:

Dev.SBC386EX.FPU.In      EQU  x86.EX.P3 + x86.EX.GPIO.PIN    ; In port

Dev.SBC386EX.FPU.PEREQ   EQU  x86.EX.PIN.0     ; Processor Extension Request

; The default FPU Detect code's initial FNINIT locks up the CPU on this board
; So, use the Processor Extension Request signal, which has been wired to a GPIO
%macro          Dev.SBC386EX.FPU.Detect   0
                MOV             DX, Dev.SBC386EX.FPU.In     ; Look at FPU signal
                IN              AL, DX                      ; Get value
                TEST            AL, Dev.SBC386EX.FPU.PEREQ  ; Current request?
%endmacro

%define         FPU.Detect      Dev.SBC386EX.FPU.Detect
