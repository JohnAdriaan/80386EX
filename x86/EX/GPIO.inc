;
; x86/EX/GPIO.inc
;

; These are the definitions for the 80386EX GPIO ports

; Note that because these ports are in the I/O space, they can only be accessed
; with IN and OUT instructions: there is no Read/Modify/Write alternative.
; And because they are accessed a whole byte at a time, it is imperative that
; ONLY the requisite bit(s) are modified. The only way to completely guarantee
; that is to access the port with interrupts disabled.

; These are the generic definitions for the PIN values
x86.EX.PIN7     EQU             1000_0000b
x86.EX.PIN6     EQU             0100_0000b
x86.EX.PIN5     EQU             0010_0000b
x86.EX.PIN4     EQU             0001_0000b
x86.EX.PIN3     EQU             0000_1000b
x86.EX.PIN2     EQU             0000_0100b
x86.EX.PIN1     EQU             0000_0010b
x86.EX.PIN0     EQU             0000_0001b

; These are the specific values for each of the 80386EX internal peripherals
x86.EX.P1.BIU.HLDA   EQU     x86.EX.PIN7
x86.EX.P1.BIU.HOLD   EQU     x86.EX.PIN6
x86.EX.P1.BIU.LOCK   EQU     x86.EX.PIN5

x86.EX.P1.SIO0.RI    EQU     x86.EX.PIN4
x86.EX.P1.SIO0.DSR   EQU     x86.EX.PIN3
x86.EX.P1.SIO0.DTR   EQU     x86.EX.PIN2
x86.EX.P1.SIO0.RTS   EQU     x86.EX.PIN1
x86.EX.P1.SIO0.DCD   EQU     x86.EX.PIN0
x86.EX.P2.SIO0.CTS   EQU     x86.EX.PIN7
x86.EX.P2.SIO0.TXD   EQU     x86.EX.PIN6
x86.EX.P2.SIO0.RXD   EQU     x86.EX.PIN5

x86.EX.P3.SIO.COMCLK EQU     x86.EX.PIN7

x86.EX.P2.CSU.CS4    EQU     x86.EX.PIN4
x86.EX.P2.CSU.CS3    EQU     x86.EX.PIN3
x86.EX.P2.CSU.CS2    EQU     x86.EX.PIN2
x86.EX.P2.CSU.CS1    EQU     x86.EX.PIN1
x86.EX.P2.CSU.CS0    EQU     x86.EX.PIN0

x86.EX.P3.PM.PWRDOWN EQU     x86.EX.PIN6

x86.EX.P3.ICU.INT3   EQU     x86.EX.PIN5
x86.EX.P3.ICU.INT2   EQU     x86.EX.PIN4
x86.EX.P3.ICU.INT1   EQU     x86.EX.PIN3
x86.EX.P3.ICU.INT0   EQU     x86.EX.PIN2

x86.EX.P3.Timer1.OUT EQU     x86.EX.PIN1

x86.EX.P3.Timer0.OUT EQU     x86.EX.PIN0

; These are the Mode configuration port registers
; Set bit to 0 for I/O mode
; Set bit to 1 for Peripheral mode
x86.EX.P1CFG    EQU             0_F820h
x86.EX.P2CFG    EQU             0_F822h
x86.EX.P3CFG    EQU             0_F824h

; These are the (read-only) pin state port registers
x86.EX.P1PIN    EQU             0_F860h
x86.EX.P2PIN    EQU             0_F868h
x86.EX.P3PIN    EQU             0_F870h

; These are the desired pin output (latch) port registers
; Set bit to 1 if input mode is required
x86.EX.P1LTC    EQU             0_F862h
x86.EX.P2LTC    EQU             0_F86Ah
x86.EX.P3LTC    EQU             0_F872h

; These are the pin direction port registers (if in I/O mode)
; Set bit to 0 for input or open-drain output
; Set bit to 1 for output
x86.EX.P1DIR    EQU             0_F864h
x86.EX.P2DIR    EQU             0_F86Ch
x86.EX.P3DIR    EQU             0_F874h
