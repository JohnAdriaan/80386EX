;
; Boot/GPIO.inc
;

; The SBC-386EX has used some of the CPU's internal peripherals, and has added
; other external ones, connected to the GPIO ports. Thus these need to be
; configured as inputs or outputs as necessary

; Rather than getting each module to configure their GPIOs individually,
; this module will set them all.

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
; (Table repeated in IO.inc)

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.GPIO:

; Before configuring GPIO directions, configure GPIO latches to OFF
; P1 GPIOs
                MOV             DX, x86.EX.P1 + x86.EX.GPIO.LTC
                MOV             AL, Dev.SBC386EX.Lite.3    | \
                                    Dev.SBC386EX.Lite.2    | \
                                    Dev.SBC386EX.Lite.1    | \
                                    Dev.SBC386EX.Lite.0    | \
                                    Dev.SBC386EX.RTC.CE    | \
                                    Dev.SBC386EX.RTC.SCLK
; Skipped the following:
;                                   x86.EX.P1.SIO0.RTS
;                                   Dev.SBC386EX.RTC.Data
                OUT             DX, AL

; P2 GPIOs: All of P2 is dedicated to internal peripherals: no GPIOs used
;               MOV             DX, x86.EX.P2 + x86.EX.GPIO.LTC
;               MOV             AL, 0
; Skipped the following:
;                                   x86.EX.P2.SIO0.CTS
;                                   x86.EX.P2.SIO0.TXD
;                                   x86.EX.P2.SIO0.RXD
;                                   x86.EX.P2.CSU.CS4
;                                   x86.EX.P2.CSU.CS3
;                                   x86.EX.P2.CSU.CS2
;                                   x86.EX.P2.CSU.CS1
;                                   x86.EX.P2.CSU.CS0
;               OUT             DX, AL

; P3 GPIOs
                MOV             DX, x86.EX.P3 + x86.EX.GPIO.LTC
                MOV             AL, Dev.SBC386EX.SDCard.CS | \
                                    Dev.SBC386EX.SDCard.CD | \
                                    Dev.SBC386EX.FPU.PEREQ
; Skipped the following:
;                                   x86.EX.P3.SIO.COMCLK
;                                   x86.EX.P3.ICU.INT3
;                                   x86.EX.P3.ICU.INT2
;                                   x86.EX.P3.ICU.INT1
;                                   x86.EX.P3.ICU.INT0

                OUT             DX, AL

; Configure Outputs for GPIO pins
; P1 GPIO Outputs
                MOV             DX, x86.EX.P1 + x86.EX.GPIO.DIR
                MOV             AL, Dev.SBC386EX.Lite.3    | \
                                    Dev.SBC386EX.Lite.2    | \
                                    Dev.SBC386EX.Lite.1    | \
                                    Dev.SBC386EX.Lite.0    | \
                                    Dev.SBC386EX.RTC.CE    | \
                                    Dev.SBC386EX.RTC.SCLK  | \
                                    Dev.SBC386EX.RTC.IO        ; Note bi-dir
; Skipped the following:
;                                   x86.EX.P1.SIO0.RTS
                OUT             DX, AL

; P2 GPIO Outputs: All of P2 is dedicated to internal peripherals: no GPIOs configurable
;               MOV             DX, x86.EX.P2 + x86.EX.GPIO.DIR
;               MOV             AL, 0
; Skipped the following:
;                                   x86.EX.P2.SIO0.CTS
;                                   x86.EX.P2.SIO0.TXD
;                                   x86.EX.P2.SIO0.RXD
;                                   x86.EX.P2.CSU.CS4
;                                   x86.EX.P2.CSU.CS3
;                                   x86.EX.P2.CSU.CS2
;                                   x86.EX.P2.CSU.CS1
;                                   x86.EX.P2.CSU.CS0
;               OUT             DX, AL

; P3 GPIO Outputs
                MOV             DX, x86.EX.P3 + x86.EX.GPIO.DIR
                MOV             AL, Dev.SBC386EX.SDCard.CS
; Skipped the following:
;                                   x86.EX.P3.SIO.COMCLK
;                                   x86.EX.P3.ICU.INT3
;                                   x86.EX.P3.ICU.INT2
;                                   x86.EX.P3.ICU.INT1
;                                   x86.EX.P3.ICU.INT0
;                                   Dev.SBC386EX.SDCard.CD
;                                   Dev.SBC386EX.FPU.PEREQ
                 OUT             DX, AL

                 MOV             DX, Dev.SBC386EX.Lite.Out
                 MOV             AL, 0x90
                 OUT             DX, AL
