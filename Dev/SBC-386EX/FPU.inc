;
; Dev/SBC-386EX/FPU.inc
;

; These are the definitions for the SBC-386EX FPU Detect interface

Dev.SBC386EX.FPU:

Dev.SBC386EX.FPU.In      EQU  x86.EX.P3 + x86.EX.GPIO.PIN    ; In port

Dev.SBC386EX.FPU.PEREQ   EQU  x86.EX.PIN.0     ; Processor Extension Request
