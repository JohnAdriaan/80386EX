;
; Dev/SBC-386EX/RTC.inc
;

; These are the definitions for the SBC-386EX Real-Time Clock chip

Dev.SBC386EX.RTC.In      EQU  x86.EX.P1PIN   ; In port
Dev.SBC386EX.RTC.Out     EQU  x86.EX.P1LTC   ; Out port
Dev.SBC386EX.RTC.Dir     EQU  x86.EX.P1DIR   ; Direction port

Dev.SBC386EX.RTC.Reset   EQU  x86.EX.PIN3    ; Reset pin
Dev.SBC386EX.RTC.Clock   EQU  x86.EX.PIN2    ; Clock pin
Dev.SBC386EX.RTC.Data    EQU  x86.EX.PIN0    ; Data pin
