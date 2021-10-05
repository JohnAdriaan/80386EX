;
; Boot/IO.inc
;
; The 80386EX Advanced Peripheral I/O space by default is disabled.
; Since we want to use some of them, it needs to be enabled with a sequence
; of accesses.
;
; +======+=====+===========+=====+===========================+
; | Port | Pin | Function  | Dir | Notes                     |
; |------+-----+-----------+-----+---------------------------|
; |  P1  |  7  | Lite3     | Out |                           |
; |      |  6  | Lite2     | Out |                           |
; |      |  5  | Lite1     | Out |                           |
; |      |  4  | Lite0     | Out |                           |
; |      |  3  | RTC_RESET | Out | Real-Time Clock Reset     |
; |      |  2  | RTC_CLK   | Out | Real-Time Clock clock     |
; |      |  1  | T_RTS0    | Out | SIO0 internal (RTS)       |
; |      |  0  | RTC_DQ    | I/O | Real-Time Clock data      |
; |------+-----+-----------+-----+---------------------------|
; |  P2  |  7  | T_CTS0    | In  | SIO0 internal (CTS)       |
; |      |  6  | T_TXD0    | Out | SIO0 internal (TXD)       |
; |      |  5  | T_RXD0    | In  | SIO0 internal (RXD)       |
; |      |  4  | CS_SRAM   | Out | CSU internal (CS4)        |
; |      |  3  | CS_XMEM   | Out | CSU internal (CS3)        |
; |      |  2  | CS_DRAM   | Out | CSU internal (CS2)        |
; |      |  1  | CS_LIO    | Out | CSU internal (CS1)        |
; |      |  0  | CS_XIO    | Out | CSU internal (CS0)        |
; |------+-----+-----------+-----+---------------------------|
; |  P3  |  7  | COMCLK    | In  | CLK internal (COMCLK)     |
; |      |  6  | SD_CS     | Out | SDCard Chip Select        |
; |      |  5  | IR7       | In  | PIC internal (INT3, IRQ7) |
; |      |  4  | IR6       | In  | PIC internal (INT2, IRQ6) |
; |      |  3  | IR5       | In  | PIC internal (INT1, IRQ5) |
; |      |  2  | IR1       | In  | PIC internal (INT0, IRQ1) |
; |      |  1  | SD_CD     | In  | SDCard Change Detect      |
; |      |  0  | PEREQ     | In  | 80387SX request detect    |
; +======+=====+===========+=====+===========================+
; (Table repeated in GPIO.inc)

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.IO:
                IN              AL, x86.EX.RemapCFG+1   ; Reset to State A
                MOV             AX, x86.EX.RemapCFG.ESE ; Enable Expanded I/O
                OUT             x86.EX.RemapCFG+1, AL   ; Move to State B
                XCHG            AH, AL
                OUT             x86.EX.RemapCFG, AL     ; Move to State C
                OUT             x86.EX.RemapCFG, AX     ; State D. ESE set!

; Configure which pins are set to internal peripherals
; P1
                MOV             DX, x86.EX.P1.CFG
                MOV             AL, x86.EX.P1.SIO0.RTS
                OUT             DX, AL

; P2
                MOV             DX, x86.EX.P2.CFG
                MOV             AL, x86.EX.P2.SIO0.CTS | \
                                    x86.EX.P2.SIO0.TXD | \
                                    x86.EX.P2.SIO0.RXD | \
                                    x86.EX.P2.CSU.CS4  | \
                                    x86.EX.P2.CSU.CS3  | \
                                    x86.EX.P2.CSU.CS2  | \
                                    x86.EX.P2.CSU.CS1  | \
                                    x86.EX.P2.CSU.CS0
                OUT             DX, AL

; P3
                MOV             DX, x86.EX.P3.CFG
                MOV             AL, x86.EX.P3.SIO.COMCLK | \
                                    x86.EX.P3.ICU.INT3   | \
                                    x86.EX.P3.ICU.INT2   | \
                                    x86.EX.P3.ICU.INT1   | \
                                    x86.EX.P3.ICU.INT0
                OUT             DX,AL
