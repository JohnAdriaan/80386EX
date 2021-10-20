;
; Boot/RTC.inc
;

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
                MOV             BL, AL          ; Into BL
                OUT             DX, AL

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.WP | Dev.RTC.DS1302.Cmd.Write
                MOV             CH, 1
                MOV             ESI, .WP.Allow             ; Write out CS:.WP.Allow
                CALL            Boot.RTC.Write

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Trickle | Dev.RTC.DS1302.Cmd.Write
                MOV             CH, 1
                MOV             SI, .Charge                ; Write out CS:.Charge
                CALL            Boot.RTC.Write

; Send .Time
;                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Write
;                MOV             CH, Dev.RTC.DS1302.Clock.Len
;                MOV             SI, .Time                 ; Write out CS:.Time
;                CALL            Boot.RTC.Write

                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Clock | Dev.RTC.DS1302.WP | Dev.RTC.DS1302.Cmd.Write
                MOV             CH, 1
                MOV             ESI, .WP.Deny              ; Write out CS:.WP.Deny
                CALL            Boot.RTC.Write

; Zero .Data
;                MOV             AH, Dev.RTC.DS1302.Cmd.Enable | Dev.RTC.DS1302.Cmd.Data | Dev.RTC.DS1302.Cmd.Addr.Burst | Dev.RTC.DS1302.Cmd.Write
;                MOV             CH, Dev.RTC.DS1302.Data.Len
;                XOR             ESI, ESI
;                CALL            Boot.RTC.Write

                JMP             Boot.RTC.Get
;...............................................................................
.WP.Allow:
                DB              Dev.RTC.DS1302.WP.Allow
.Charge:
                DB              Dev.RTC.DS1302.Trickle.TCS | Dev.RTC.DS1302.Trickle.Diode.1 | Dev.RTC.DS1302.Trickle.Resistor.2
;.Time:
;                DB              00h        ; Secs
;                DB              35h        ; Mins
;                DB              Dev.RTC.DS1302.Hour.24 | 21h ; Hours
;                DB              20h        ; Date
;                DB              10h        ; Month
;                DB              03h        ; Day
;                DB              21h        ; Year
.WP.Deny:
                DB              Dev.RTC.DS1302.WP.Deny
;...............................................................................
Boot.RTC.Write:
                OR              AL, Dev.SBC386EX.RTC.CE     ; Chip Enable
                OUT             DX, AL
                MOV             BH, AL                      ; Into BH

                CALL            Boot.RTC.Send
.Loop:
                TEST            ESI, ESI
                JZ              .AH
                MOV             AH, [CS:ESI]
                INC             ESI
.AH:
                CALL            Boot.RTC.Send
                DEC             CH                          ; Any more bytes?
                JNZ             .Loop

                MOV             AL, BL                      ; Back to idle (disabled)
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
Boot.RTC.Get:
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

                MOV             AL, BL                      ; Back to idle (disabled)
                OUT             DX, AL
                RET
Boot.RTC.Exit:
