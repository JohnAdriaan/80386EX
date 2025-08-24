;
; Boot/Real/SIO.inc
;

; Initialise the Serial I/O device. As a debugoutput device, it's invaluable!
; Not as much as the VGA monitor - but that takes a LOT to get set up. Meanwhile...

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.SIO:
; Enable Divisor Latch Access Bit (used to program the baud rate)
                MOV             DX, Dev.UART.COM1 + Dev.UART.LCR
                MOV             AL, Dev.UART.LCR.DLAB
                OUT             DX, AL

; Program a fast baud rate
                MOV             DX, Dev.UART.COM1 + Dev.UART.DLR.Lo
                MOV             AX, Dev.UART.Clock / Boot.SIO.BaudRate
                OUT             DX, AX

; Disable the Divisor Latch Access Bit - and specify the desired Protocol (8N1?)
                MOV             DX, Dev.UART.COM1 + Dev.UART.LCR
                MOV             AL, Boot.SIO.Protocol
                OUT             DX, AL

; Enable the two Modem Control Register outputs: Data Terminal Ready and Ready to Send
                MOV             DX, Dev.UART.COM1 + Dev.UART.MCR
                MOV             AL, Dev.UART.MCR.DTR | Dev.UART.MCR.RTS
                OUT             DX, AL

%define HEADER
%ifdef HEADER
                CLD
                MOV             CX,.Mess.Len
                MOV             SI,.Message + Boot.CS

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
