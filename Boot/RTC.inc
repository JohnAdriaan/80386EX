;
; Boot/RTC.inc
;
; The SBC386EX Real-Time Clock (RTC) has a Super Capacitor to supply maintenance
; power while the main power is off. The RTC chip will charge that capacitor,
; if told to do so. Unfortunately, the command requires the Write Protect lock
; to be removed first, so it's a multi-step operation.

%if Dev.SBC386EX.RTC.IO != 0000_0001b
%error I/O bit is not LSb! Change the algorithm
%endif

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

Boot.RTC.Clock  RESB            Dev.RTC.DS1302.Clock.Len
Boot.RTC.Trickle RESB           1
Boot.RTC.Data   RESB            Dev.RTC.DS1302.Data.Len

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.RTC:
                CLD

                MOV             DX, Dev.SBC386EX.RTC.Out
                IN              AL, DX          ; Get current Latch state

                AND             AL, ~(Dev.SBC386EX.RTC.CE | Dev.SBC386EX.RTC.SCLK | Dev.SBC386EX.RTC.IO) ; Everything RTC off
                OUT             DX, AL

                XOR             ESI, ESI        ; Single-byte writes

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.WP | Dev.RTC.DS1302.Cmd.Write
                MOV             BL, Dev.RTC.DS1302.WP.Allow
                MOV             CH, 1
                CALL            Boot.RTC.Write

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Trickle | Dev.RTC.DS1302.Cmd.Write
                MOV             BL, Dev.RTC.DS1302.Trickle.TCS | Dev.RTC.DS1302.Trickle.Diode.1 | Dev.RTC.DS1302.Trickle.Resistor.2
                MOV             CH, 1
                CALL            Boot.RTC.Write

; Send .Time
;                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Write
;                MOV             CH, Dev.RTC.DS1302.Clock.Len
;                MOV             SI, .Time                 ; Write out CS:.Time
;                CALL            Boot.RTC.Write

                XOR             ESI, ESI                   ; Single-byte writes again

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.WP | Dev.RTC.DS1302.Cmd.Write
                MOV             BL, Dev.RTC.DS1302.WP.Deny
                MOV             CH, 1
                CALL            Boot.RTC.Write

; Zero RTC Data
;                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Data | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Write
;                MOV             BL, 0
;                MOV             CH, Dev.RTC.DS1302.Data.Len
;                CALL            Boot.RTC.Write

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Read
                MOV             CH, Dev.RTC.DS1302.Clock.Len
                MOV             EDI, SRAM.Start + Boot.RTC.Clock
                CALL            Boot.RTC.Read

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Trickle | Dev.RTC.DS1302.Cmd.Read
                MOV             CH, 1
                MOV             EDI, SRAM.Start + Boot.RTC.Trickle
                CALL            Boot.RTC.Read

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Data | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Read
                MOV             CH, Dev.RTC.DS1302.Data.Len
                MOV             EDI, SRAM.Start + Boot.RTC.Data
;               CALL            Boot.RTC.Read
;               JMP             Boot.RTC.Exit
                PUSH            Boot.RTC.Exit
;...............................................................................
Boot.RTC.Read:
                OR              AL, Dev.SBC386EX.RTC.CE     ; Chip Enable
                OUT             DX, AL                      ; Now need 1 us
                MOV             BH, AL                      ; Into BH

                CALL            Boot.RTC.Send

                OR              BH, Dev.SBC386EX.RTC.IO     ; Prepare to Input
.Loop.Bytes:
                MOV             CL, 8                       ; Bits in byte
.Loop.Bits:
                MOV             AL, BH                      ; Clock Low
                OUT             DX, AL

                MOV             DX, Dev.SBC386EX.RTC.In     ; Read .IO
                IN              AL, DX
                SHR             AL, 1                       ; Get .IO into Carry
                RCR             AH, 1                       ; Get Carry into AH

                MOV             AL, BH
                OR              AL, Dev.SBC386EX.RTC.SCLK   ; Clock high
                MOV             DX, Dev.SBC386EX.RTC.Out
                OUT             DX, AL

                DEC             CL                          ; Any more bits?
                JNZ             .Loop.Bits

                MOV             AL, AH                      ; AH into AL
                STOSB                                       ; So can STOSB

                DEC             CH                          ; Any more bytes?
                JNZ             .Loop.Bytes

                AND             AL, ~(Dev.SBC386EX.RTC.CE | Dev.SBC386EX.RTC.SCLK | Dev.SBC386EX.RTC.IO) ; Everything RTC off
                OUT             DX, AL
                RET
;...............................................................................
;.Time:
;                DB              00h        ; Secs
;                DB              55h        ; Mins
;                DB              Dev.RTC.DS1302.Hour.24 | 00h ; Hours (UTC)
;                DB              21h        ; Date
;                DB              10h        ; Month
;                DB              04h        ; Day (1=Monday)
;                DB              21h        ; Year
;...............................................................................
Boot.RTC.Write:
                OR              AL, Dev.SBC386EX.RTC.CE     ; Chip Enable
                OUT             DX, AL
                MOV             BH, AL                      ; Into BH

                CALL            Boot.RTC.Send
.Loop:
                TEST            ESI, ESI
                JZ              .BL
                MOV             BL, [CS:ESI]
                INC             ESI
.BL:
                MOV             AH, BL
                CALL            Boot.RTC.Send
                DEC             CH                          ; Any more bytes?
                JNZ             .Loop

                AND             AL, ~(Dev.SBC386EX.RTC.CE | Dev.SBC386EX.RTC.SCLK | Dev.SBC386EX.RTC.IO) ; Everything RTC off
                OUT             DX, AL
                RET
;...............................................................................
Boot.RTC.Send:
                MOV             CL, 8                       ; Bits in Cmd
.Loop:
                SHR             AH, 1                       ; LSb into Carry
                ADC             AL, 0                       ; Only works if .IO is LSb
                OUT             DX, AL
                OR              AL, Dev.SBC386EX.RTC.SCLK   ; Clock high
                OUT             DX, AL
                MOV             AL, BH                      ; Clock, Data Low
                DEC             CL
                JNZ             .Loop
                RET
;...............................................................................
Boot.RTC.Exit:
