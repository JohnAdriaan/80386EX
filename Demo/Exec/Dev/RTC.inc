;
; Exec/Dev/RTC.inc
;

%push           Exec.RTC    ; Don't leave these %defines lying around

%macro          BCD             1
                MOV             AL, [WORD Boot.RTC.Clock + Dev.RTC.DS1302.Clock %+ %1]
                SHL             EAX, 4              ; AL BCD to AH:AL BCD
                SHR             AL, 4               ; Well, it is now!
                AAD                                 ; AH:AL BCD to AL binary
%endmacro

Exec.RTC:
                XOR             EAX, EAX            ; Zero all of EAX for BCD
                XOR             EDI, EDI            ; Accumulate into EDI
                PUSH            DS
                PUSH            FS
                POP             DS                  ; More efficient to use DS

                BCD             .Year
                MOV             DH, AL              ; Save year
                DEC             AL                  ; Was it Year 0?
                JS              .Save               ; Yes, so ignore
                CMP             AL, 99              ; Was it above 99?
                JAE             .Save               ; Yes, so ignore

                IMUL            ECX, EAX, 365       ; Days into ECX
                SHR             EAX, 2              ; Number of leap years (not including this year)
                ADD             ECX, EAX            ; Include leap days

                BCD             .Month
                MOV             DL, AL              ; Save month
                DEC             AL                  ; Was it Month 0?
                JS              .Save               ; Yes, so ignore
                CMP             AL, 12              ; Was it above December?
                JAE             .Save               ; Yes, so ignore

                MOV             BX, .Months
             CS XLATB                               ; Convert month number to day count
                CMP             DL, 10              ; Need to add 256?
                JB              .Not256             ; (XLATB is bytes only)
                ADD             ECX, 256
.Not256:
                ADD             ECX, EAX            ; Add in number of days

                BCD             .Date
                DEC             AL                  ; Was it Date 0?
                JS              .Save               ; Yes, so ignore
                CMP             AL, 31              ; Was it more than 31?
                JAE             .Save               ; Yes, so ignore
                ADD             ECX, EAX            ; Add in number of days

                ; Chip knows about Feb 29, so test for Leap March+
                TEST            DH, 0011h           ; Is this year a Leap Year?
                JNZ             .NotLeap
                CMP             DL, 3               ; Is it March already?
                JB              .NotLeap
                INC             ECX                 ; Add one for Feb 29 this year
.NotLeap:
                BCD             .Hour
                CMP             AL, 24              ; More than 24 hours?
                JAE             .Save
                IMUL            ECX, 24             ; Days into Hours
                ADD             ECX, EAX

                BCD             .Min
                CMP             AL, 60              ; More than 60 minutes?
                JAE             .Save
                IMUL            ECX, 60             ; Hours into Minutes
                ADD             ECX, EAX

                BCD             .Sec
                CMP             AL, 60              ; More than 60 seconds?
                JAE             .Save
                IMUL            ECX, 60             ; Minutes into Seconds
                LEA             EDI, [ECX + EAX]    ; Add in seconds, into EDI

.Save:
                POP             DS
                MOV             [WORD Data.Secs],  EDI
                RET

.Months         DB              0, 31, 31+28, 31+28+31, 31+28+31+30, 31+28+31+30+31
                DB              31+28+31+30+31+30, 31+28+31+30+31+30+31, 31+28+31+30+31+30+31+31
                DB              31+28+31+30+31+30+31+31+30-256, 31+28+31+30+31+30+31+31+30+31-256,
                DB              31+28+31+30+31+30+31+31+30+31+30-256
%pop
