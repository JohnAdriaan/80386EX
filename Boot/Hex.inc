;
; Boot/Hex.inc
;

; This subroutine transmits 12 characters:
; * The first two characters in EBX
; * The 8 hex characters representing ESI
; * The last two characters in EBX
; It destroys EAX, and zeroes EBX and ESI

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Hex:
                PUSH            ECX
                PUSH            EDX

                MOV             ECX, 12
.Loop:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

                CMP             EBX, 0x0000_FFFF
                JA              .DoEBX
                CMP             CX, 2
                JBE             .DoEBX

                SHLD            EAX, ESI, 4
                SHL             ESI, 4
                AND             AL, 0xF
                ADD             AL, '0'
                CMP             AL, '9'
                JBE             .Char
                ADD             AL, 'A'-'9'-1
                JMP             .Char
.DoEBX:
                MOV             AL, BL
                SHR             EBX, 8
.Char:
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                LOOP            .Loop

                POP             EDX
                POP             ECX
                RET
