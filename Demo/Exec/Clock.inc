;
; Exec/Clock.inc
;

;                               Fri, 22 Oct 21, 01:20:22
Clock.String    EQU             3 +2+3 +3 +3 +2+3 +3 +2

Exec.Clock:
                CALL            Exec.Clock.Convert ; EDX:EAX gets YYYY/MM/DD:D/HH/MM/SS

                PUSH            ES
                PUSH            SS
                POP             ES
                LEA             EDI, [EBP - Clock.String]
                CALL            Exec.Clock.String  ; ES:EDI gets "ddd, DD MMM YY, HH:MM:SS"
                POP             ES

                RET
;...............................................................................
Exec.Clock.Get:
                MOV             EDX, [WORD Data.Secs]
                MOV             EAX, [WORD Data.Ticks]
                RET
;...............................................................................
Exec.Clock.Convert:
                XOR             EDX, EDX
                MOV             ESI, 24 * 60 * 60
                DIV             ESI             ; EAX=Days, EDX=HH:MM:SS

                MOV             EDI, EDX        ; Save away
                MOV             ECX, EAX
                XOR             EDX, EDX
                MOV             ESI, 7          ; Days in week
                DIV             ESI             ; DL is day number (0=Mon)
                MOV             BH,  DL         ; BH is day number

                MOV             EAX, ECX
                XOR             EDX, EDX
                MOV             ESI, 365        ; Days per (most) years
                DIV             ESI             ; AX=Years(?), EDX=Days

                LEA             ECX, [EAX + 2001] ; Years start at 2001
                SHR             EAX, 2          ; Number of Leap Years (not including this one)
                SUB             EDX, EAX        ; Subtract from number of days
                JNC             .NoWrap
                ADD             EDX, 365        ; Add days back in
                DEC             ECX             ; One less year
                TEST            CL, 0011b       ; Is this (now) year a Leap Year?
                JNZ             .NoWrap
                INC             EDX             ; Yes, so include Feb 29
.NoWrap:
                MOV             BL, CL          ; BL is Year LSB
                SHL             ECX, x86.DWORD.Hi ; Save in High ECX
                MOV             ESI, .Months
                CLD
.Month:
             CS LODSB                           ; Get number of days for this month
                CBW
                INC             CH              ; Next month
                TEST            BL, 0011b       ; Leap year?
                JNZ             .NotLeap
                CMP             CH, 2           ; February?
                JNE             .NotLeap
                INC             AL              ; Hath 29 days
.NotLeap:
                SUB             EDX, EAX
                JNC             .Month

                LEA             EAX, [EDX + EAX + 1] ; Months start at 1
                MOV             CL, AL           ; CH=Month, CL=Date

                MOV             EAX, EDI         ; Get HH:MM:SS
                XOR             EDX, EDX
                MOV             ESI, 60 * 60
                DIV             ESI              ; AL=Hours, DX=MM:SS

                MOV             BL, AL           ; BL is Hours
                SHL             EBX, x86.DWORD.Hi ; High EBX is now Day:Hours

                MOV             EAX, EDX
                MOV             BL, 60
                DIV             BL
                MOV             BH, AL           ; BH=Mins
                MOV             BL, AH           ; BL=Secs

                MOV             EDX, ECX
                MOV             EAX, EBX
                RET
.Months         DB              31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
;...............................................................................
Exec.Clock.String:
                XOR             EBX, EBX            ; Zero EBX
                MOV             ECX, EAX            ; ECX = D:HH:MM:SS
                SHLD            EBX, EAX, x86.BYTE.Bits ; BL=Day

                LEA             ESI, [.Days + EBX*2 + EBX]
             CS LODSB
                STOSB
             CS LODSB
                STOSB
             CS LODSB
                STOSB
                MOV             AL, ','
                STOSB
                MOV             AL, ' '
                STOSB

                MOV             BL, ' '          ; Leading space
                CALL            .Dec             ; DL is already Date
                MOV             AL, ' '
                STOSB

                MOV             BL, DH           ; BL=Month (1-12)
                LEA             ESI, [.Months + EBX*2 + EBX - 3]
             CS LODSB
                STOSB
             CS LODSB
                STOSB
             CS LODSB
                STOSB
                MOV             AL, ' '
                STOSB
                SHLD            EAX, EDX, x86.DWORD.Hi ; AX=Year
                MOV             BH, 100
                DIV             BH               ; AH=Year, AL=Century

                MOV             BL, '0'          ; Leading zero
                MOV             DL, AH           ; Year
                CALL            .Dec
                MOV             AL, ','
                STOSB
                MOV             AL, ' '
                STOSB

                SHLD            EDX, ECX, x86.DWORD.Hi ; Get HH into DL
                CALL            .Dec
                MOV             AL, ':'
                STOSB
                MOV             DL, CH
                CALL            .Dec
                MOV             AL, ':'
                STOSB
                MOV             DL, CL
;               CALL            .Dec
;               RET
;...............................................................................
; Prints DL (<BL>0-99). Modifies AX, DL and EDI
.Dec:
                MOV             AX, 10    ; AH=0, AL=Divisor
                XCHG            DL, AL    ; AX=0-99
                DIV             DL        ; AH=Units, AL=Tens
                MOV             DL, AH    ; DL=Units
                ADD             AL, '0'
                CMP             AL, '0'   ; Show leading instead?
                JNE             .Dec.Show ; No, so show AL
                MOV             AL, BL
.Dec.Show:
                STOSB
                MOV             AL, DL
                ADD             AL, '0'
                STOSB
                RET
.Days           DB              "MonTueWedThuFriSatSun"
.Months         DB              "JanFebMarAprMayJunJulAugSepOctNovDec"
