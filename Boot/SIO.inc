;
; Boot/SIO.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.SIO:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LCR
                MOV             AL, Dev.UART.LCR.DLAB
                OUT             DX, AL

                MOV             DX, Dev.UART.COM1 + Dev.UART.DLR.Lo
                MOV             AX, Dev.UART.Clock / Boot.BaudRate
                OUT             DX, AX

                MOV             DX, Dev.UART.COM1 + Dev.UART.LCR
                MOV             AL, Boot.Protocol
                OUT             DX, AL

                MOV             DX, Dev.UART.COM1 + Dev.UART.MCR
                MOV             AL, Dev.UART.MCR.DTR | Dev.UART.MCR.RTS
                OUT             DX, AL

%define HEADER
%ifdef HEADER
                CLD
                MOV             CX,.Mess.Len
                MOV             SI,.Message

.Loop:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

             CS LODSB
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                LOOP            .Loop

                JMP             .Exit

.Message        DB             `SBC386EX\r\n`
.Mess.Len       EQU            $ - .Message

.Exit:
%endif
