;
; Dev/UART.inc
;

; These are the definitions for the Universal Asynchronous Receiver/Transmitter

                SEGMENT         IO

Dev.UART.COM1   EQU             3F8h

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
.DLR            EQU             .Data           ; Divisor Latch Register
.DLR.Lo         EQU             .Data           ; Divisor Latch Register Low
.DLR.Hi         EQU             .IER            ; Divisor Latch Register High
                ENDSTRUC

Dev.UART.IER.MS     EQU         0000_1000b      ; Modem Status interrupt
Dev.UART.IER.RLS    EQU         0000_0100b      ; Receiver Line Status interrupt
Dev.UART.IER.TBE    EQU         0000_0010b      ; Transmit Buffer Empty interrupt
Dev.UART.IER.RBF    EQU         0000_0001b      ; Receive Buffer Full interrupt

Dev.UART.IIR.IS     EQU         0000_0110b      ; Interrupt Status
Dev.UART.IIR.IP     EQU         0000_0001b      ; Interrupt Pending (not!)

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

Dev.UART.MSR.DCD    EQU         1000_0000b      ; Data Carrier Detect
Dev.UART.MSR.RI     EQU         0100_0000b      ; Ring Indicator
Dev.UART.MSR.DSR    EQU         0010_0000b      ; Data Set Ready
Dev.UART.MSR.CTS    EQU         0001_0000b      ; Clear To Send
Dev.UART.MSR.DDCD   EQU         0000_1000b      ; Delta DCD
Dev.UART.MSR.TERI   EQU         0000_0100b      ; Trailing Edge RI
Dev.UART.MSR.DDSR   EQU         0000_0010b      ; Delta DSR
Dev.UART.MSR.DCTS   EQU         0000_0001b      ; Delta CTS
