;
; Dev/SBC-386EX/SDCard.inc
;

; These are the definitions for the SBC-386EX SDCard interface

Dev.SBC386EX.SDCard:

Dev.SBC386EX.SDCard.In   EQU  x86.EX.P3 + x86.EX.GPIO.PIN    ; In port
Dev.SBC386EX.SDCard.Out  EQU  x86.EX.P3 + x86.EX.GPIO.LTC    ; Out port

Dev.SBC386EX.SDCard.CS   EQU  x86.EX.PIN.6     ; Chip select
Dev.SBC386EX.SDCard.CD   EQU  x86.EX.PIN.1     ; Card changed
