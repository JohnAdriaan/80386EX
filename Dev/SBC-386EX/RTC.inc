;
; Dev/SBC-386EX/RTC.inc
;

; These are the definitions for the SBC-386EX Real-Time Clock chip

Dev.SBC386EX.RTC:

Dev.SBC386EX.RTC.In      EQU  x86.EX.P1 + x86.EX.GPIO.PIN   ; In port
Dev.SBC386EX.RTC.Out     EQU  x86.EX.P1 + x86.EX.GPIO.LTC   ; Out port
Dev.SBC386EX.RTC.Dir     EQU  x86.EX.P1 + x86.EX.GPIO.DIR   ; Direction port

Dev.SBC386EX.RTC.CE      EQU  x86.EX.PIN.3    ; Enable pin
Dev.SBC386EX.RTC.SCLK    EQU  x86.EX.PIN.2    ; Clock pin
Dev.SBC386EX.RTC.IO      EQU  x86.EX.PIN.0    ; Data pin
