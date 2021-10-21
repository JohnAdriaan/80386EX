;
; Exec/Clock.inc
;

Exec.Clock.Attr EQU             Dev.VGA.BlackBack | Dev.VGA.Grey

Exec.Clock:
                MOV             EAX, [WORD Data.Secs]
                MOV             EDI, (Screen.Cols - (3+3+3+2+3+3+2)) * 2

                MOV             EBX, 24 * 60 * 60
                XOR             EDX, EDX
                DIV             EBX             ; EAX=Days, EDX=HH:MM:SS

                MOV             EBP, EDX        ; Save away
                MOV             EBX, 365
                XOR             EDX, EDX
                DIV             EBX             ; EAX=Years(?), EDX=Days

                LEA             ECX, [EAX + 1]  ; Year number starts at 2001
                SHR             EAX, 2          ; Number of Leap Years (not including this one)
                SUB             EDX, EAX        ; Subtract from number of days
                JNC             .NotLeap
                ADD             EDX, 365        ; Add days back in
                DEC             ECX             ; One less year
.NotLeap:
                MOV             ESI, .Months
.Month:
             CS LODSB                           ; Get number of days for this month
                CBW
                SUB             EDX, EAX
                JC              .Date
                ADD             ESI, 3
                JMP             .Month
.Date:
                LEA             EAX, [EDX + EAX + 1]
                MOV             CH, AL           ; CH=Date, SI=Month, CL=Year

                MOV             EAX, EBP         ; Get HH:MM:SS
                MOV             BX, 60 * 60
                XOR             EDX, EDX
                DIV             BX               ; AX=Hours, DX=MM:SS

                MOV             BH, AL           ; BH is Hours
                MOV             EAX, EDX
                MOV             BL, 60
                DIV             BL
                MOV             EDX, EAX         ; DH=Secs, DL=Mins

                MOV             BL, ' '          ; Leading space
                CALL            .Dec
                MOV             AL, ' '
                STOSW
             CS LODSB                            ; Month
                STOSW
             CS LODSB
                STOSW
             CS LODSB
                STOSW
                MOV             AL, ' '
                STOSW
                MOV             BL, '0'          ; Leading zero
                MOV             CH, CL           ; Year
                CALL            .Dec
                MOV             AL, ','
                STOSW
                MOV             AL, ' '
                STOSW
                MOV             CH, BH
                CALL            .Dec
                MOV             AL, ':'
                STOSW
                MOV             CH, DL
                CALL            .Dec
                MOV             AL, ':'
                STOSW
                MOV             CH, DH
;               CALL            .Dec
;               RET
;...............................................................................
.Dec:
                MOV             AX, 10    ; AL=Divisor, AH=0
                XCHG            CH, AL    ; AX=0-99
                DIV             CH        ; AH=Units, AL=Tens
                MOV             CH, AH    ; CH=Units
                ADD             AL, '0'
                CMP             AL, '0'   ; Show leading instead?
                JNE             .Dec.Show ; No, so show AL
                MOV             AL, BL
.Dec.Show:
                MOV             AH, .Attr
                STOSW
                MOV             AL, CH
                ADD             AL, '0'
                STOSW
                RET

.Months         DB              `\x1FJan\x1CFeb\x1FMar\x1EApr\x1FMay\x1EJun`
                DB              `\x1FJul\x1FAug\x1ESep\x1FOct\x1ENov\x1FDec`
