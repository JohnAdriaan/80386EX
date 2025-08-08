;
; Dev/UART.inc
;

; These are the definitions for the Universal Asynchronous Receiver/Transmitter.
; The original PC used the 8250; later the 16450 and 16550 was used.
; The 16550 has RX and TX FIFOs, and supports DMA

                SEGMENT         IO

Dev.UART.COM1   EQU             3F8h
Dev.UART.COM2   EQU             2F8h

Dev.UART.Clock  EQU             1_843_200 / 16

                STRUC           Dev.UART
.Data           RESB            1
.IER            RESB            1               ; Interrupt Enable Register
.IIR            RESB            1               ; Interrupt ID Register
.LCR            RESB            1               ; Line Control Register
.MCR            RESB            1               ; Modem Control Register
.LSR            RESB            1               ; Line Status Register
.MSR            RESB            1               ; Modem Status Register
.SCR            RESB            1               ; Scratchpad register

.RBR            EQU             .Data           ; Receive Buffer Register
.THR            EQU             .Data           ; Transmit Holding Register
.DLR            EQU             .Data           ; Divisor Latch Register (word)
.DLR.Lo         EQU             .Data           ; Divisor Latch Register Low
.DLR.Hi         EQU             .IER            ; Divisor Latch Register High
.FCR            EQU             .IIR            ; FIFO Control Register
.PSD            EQU             .LSR            ; Divisor Latch Prescalar Divisor
                ENDSTRUC

Dev.UART.IER.DMATX  EQU         1000_0000b      ; DMA Transmit End interrupt
Dev.UART.IER.DMARX  EQU         0100_0000b      ; DMA Receive End interrupt
Dev.UART.IER.MS     EQU         0000_1000b      ; Modem Status interrupt
Dev.UART.IER.RLS    EQU         0000_0100b      ; Receiver Line Status interrupt
Dev.UART.IER.TBE    EQU         0000_0010b      ; Transmit Buffer Empty interrupt
Dev.UART.IER.RBF    EQU         0000_0001b      ; Receive Buffer Full interrupt

Dev.UART.IIR.TXFIFO EQU         1000_0000b      ; Transmit FIFO enabled
Dev.UART.IIR.RXFIFO EQU         0100_0000b      ; Receive FIFO enabled
Dev.UART.IIR.TXEnd  EQU         0010_0000b      ; DMA TX End status (not interrupt)
Dev.UART.IIR.RXEnd  EQU         0001_0000b      ; DMA RX End status (not interrupt)
Dev.UART.IIR.IS     EQU         0000_1110b      ; Interrupt Status
Dev.UART.IIR.nIP    EQU         0000_0001b      ; not Interrupt Pending

Dev.UART.IIR.DMARX  EQU         0000_1110b      ; DMA Receive Status Interrupt
Dev.UART.IIR.Time   EQU         0000_1100b      ; RX Timeout Status Interrupt
Dev.UART.IIR.DMATX  EQU         0000_1010b      ; DMA Transmit Status Interrupt
Dev.UART.IIR.Line   EQU         0000_0110b      ; Line Status Interrupt
Dev.UART.IIR.RX     EQU         0000_0100b      ; Receive Status Interrupt
Dev.UART.IIR.TX     EQU         0000_0010b      ; Transmit Status Interrupt
Dev.UART.IIR.Modem  EQU         0000_0000b      ; Modem Status Interrupt

Dev.UART.FCR.Trig   EQU         1100_0000b      ; RX Trigger level
Dev.UART.FCR.DMAEnd EQU         0001_0000b      ; Enable DMA End in IIR
Dev.UART.FCR.DMA    EQU         0000_1000b      ; DMA mode (single vs FIFO)
Dev.UART.FCR.Tx     EQU         0000_0100b      ; TX FIFO Reset
Dev.UART.FCR.Rx     EQU         0000_0010b      ; RX FIFO Reset
Dev.UART.FCR.En     EQU         0000_0001b      ; FIFO Enable

Dev.UART.FCR.14     EQU         1100_0000B      ; 14-character trigger
Dev.UART.FCR.8      EQU         1000_0000b      ; 8-character trigger
Dev.UART.FCR.4      EQU         0100_0000B      ; 4-character trigger
Dev.UART.FCR.1      EQU         0000_0000b      ; 1-character trigger

Dev.UART.LCR.DLAB   EQU         1000_0000b      ; Divisor Latch Access Bit
Dev.UART.LCR.SB     EQU         0100_0000b      ; Set Break
Dev.UART.LCR.SP     EQU         0010_0000b      ; Sticky Parity
Dev.UART.LCR.EPS    EQU         0001_0000b      ; Even Parity Select (Sticky=0)
Dev.UART.LCR.PE     EQU         0000_1000b      ; Parity Enable
Dev.UART.LCR.STB    EQU         0000_0100b      ; Stop Bits
Dev.UART.LCR.WLS    EQU         0000_0011b      ; Word Length Select

Dev.UART.Word8      EQU         0000_0011b
Dev.UART.Word7      EQU         0000_0010b
Dev.UART.Baudot     EQU         0000_0000b

Dev.UART.ParityOdd  EQU         0000_1000b
Dev.UART.ParityEven EQU         0001_1000b
Dev.UART.ParityNone EQU         0000_0000b

Dev.UART.Stop1      EQU         0000_0000b
Dev.UART.Stop2      EQU         0000_0100b

Dev.UART.MCR.LOOP   EQU         0001_0000b      ; Loopback test
Dev.UART.MCR.OUT2   EQU         0000_1000b      ; OUT2
Dev.UART.MCR.OUT1   EQU         0000_0100b      ; OUT1
Dev.UART.MCR.RTS    EQU         0000_0010b      ; Request To Send
Dev.UART.MCR.DTR    EQU         0000_0001b      ; Data Terminal Ready

Dev.UART.LSR.TE     EQU         0100_0000b      ; Transmitter Empty
Dev.UART.LSR.TBE    EQU         0010_0000b      ; Transmkt Buffer Empty
Dev.UART.LSR.BI     EQU         0001_0000b      ; Break Interrupt
Dev.UART.LSR.FE     EQU         0000_1000b      ; Framing Error
Dev.UART.LSR.PE     EQU         0000_0100b      ; Parity Error
Dev.UART.LSR.OE     EQU         0000_0010b      ; Overrun Error
Dev.UART.LSR.RBF    EQU         0000_0001b      ; Receive Buffer Full

Dev.UART.PSD.Factor EQU         0000_1111b      ; Prescaler Division Factor

Dev.UART.MSR.DCD    EQU         1000_0000b      ; Data Carrier Detect
Dev.UART.MSR.RI     EQU         0100_0000b      ; Ring Indicator
Dev.UART.MSR.DSR    EQU         0010_0000b      ; Data Set Ready
Dev.UART.MSR.CTS    EQU         0001_0000b      ; Clear To Send
Dev.UART.MSR.DDCD   EQU         0000_1000b      ; Delta DCD
Dev.UART.MSR.TERI   EQU         0000_0100b      ; Trailing Edge RI
Dev.UART.MSR.DDSR   EQU         0000_0010b      ; Delta DSR
Dev.UART.MSR.DCTS   EQU         0000_0001b      ; Delta CTS
