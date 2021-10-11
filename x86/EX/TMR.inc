;                                                                ;
; x86/EX/TMR.inc
;

; These are the definitions for the 80386EX Timer/Counter Unit

                SEGMENT         IO

x86.EX.TMR:

; Timer Registers
x86.EX.TMR.CFG  EQU             0_F834h     ; TiMeR ConFiG register
x86.EX.TMR.CON  EQU             0_F043h     ; TiMeR CONtrol register
x86.EX.TMR.0    EQU             0_F040h     ; TiMeR 0 register
x86.EX.TMR.1    EQU             0_F041h     ; TiMeR 1 register
x86.EX.TMR.2    EQU             0_F042h     ; TiMeR 2 register

; Timer Config field values
x86.EX.TMR.CFG.DIS      EQU     1000_0000b  ; DISable CLKIN signals
x86.EX.TMR.CFG.SWGTEN   EQU     0100_0000b  ; SoftWare GaTe ENable
x86.EX.TMR.CFG.GT2CON   EQU     0010_0000b  ; GaTe 2 CONnection
x86.EX.TMR.CFG.CK2CON   EQU     0001_0000b  ; ClocK 2 CONnection
x86.EX.TMR.CFG.GT1CON   EQU     0000_1000b  ; GaTe 1 CONnection
x86.EX.TMR.CFG.CK1CON   EQU     0000_0100b  ; ClocK 1 CONnection
x86.EX.TMR.CFG.GT0CON   EQU     0000_0010b  ; GaTe 0 CONnection
x86.EX.TMR.CFG.CK0CON   EQU     0000_0001b  ; ClocK 0 CONnection

; Dsable values
x86.EX.TMR.CFG.Enable   EQU     0000_0000b  ; Enable CLKIN signals
x86.EX.TMR.CFG.Disable  EQU     1000_0000b  ; Disable CLKIN signals

; Gate 2 values
x86.EX.TMR.CFG.GT2.VCC  EQU     0000_0000b  ; GaTe 2 stuck high
x86.EX.TMR.CFG.GT2.Pin  EQU     0010_0000b  ; GaTe 2 pin used
x86.EX.TMR.CFG.GT2.Off  EQU     0100_0000b  ; GaTe 2 Off
x86.EX.TMR.CFG.GT2.On   EQU     0110_0000b  ; GaTe 2 On

; Clock 2 values
x86.EX.TMR.CFG.CK2.PSClk EQU    0000_0000b  ; Clock 2 by PSCLK
x86.EX.TMR.CFG.CK2.Pin   EQU    0001_0000b  ; Clock 2 by pin

; Gate 1 values
x86.EX.TMR.CFG.GT1.VCC  EQU     0000_0000b  ; GaTe 1 stuck high
x86.EX.TMR.CFG.GT1.Pin  EQU     0000_1000b  ; GaTe 1 pin used
x86.EX.TMR.CFG.GT1.Off  EQU     0100_0000b  ; GaTe 1 Off
x86.EX.TMR.CFG.GT1.On   EQU     0100_1000b  ; GaTe 1 On

; Clock 1 values
x86.EX.TMR.CFG.CK1.PSClk EQU    0000_0000b  ; Clock 1 by PSCLK
x86.EX.TMR.CFG.CK1.Pin   EQU    0000_0100b  ; Clock 1 by pin

; Gate 0 values
x86.EX.TMR.CFG.GT0.VCC  EQU     0000_0000b  ; GaTe 0 stuck high
x86.EX.TMR.CFG.GT0.Pin  EQU     0000_0010b  ; GaTe 0 pin used
x86.EX.TMR.CFG.GT0.Off  EQU     0100_0000b  ; GaTe 0 Off
x86.EX.TMR.CFG.GT0.On   EQU     0100_0010b  ; GaTe 0 On

; Clock 0 values
x86.EX.TMR.CFG.CK0.PSClk EQU    0000_0000b  ; Clock 0 by PSClk
x86.EX.TMR.CFG.CK0.Pin   EQU    0000_0001b  ; Clock 0 by pin

; Timer Control field values
x86.EX.TMR.CON.SC   EQU         1100_0000b  ; Select Counter
x86.EX.TMR.CON.RW   EQU         0011_0000b  ; Read/Write mode
x86.EX.TMR.CON.MODE EQU         0000_1110b  ; Mode
x86.EX.TMR.CON.FMT  EQU         0000_0001b  ; Count ForMaT

; Timer Control Select Counter values
x86.EX.TMR.CON.SC.0 EQU         0000_0000b  ; Select Counter 0
x86.EX.TMR.CON.SC.1 EQU         0100_0000b  ; Select Counter 1
x86.EX.TMR.CON.SC.2 EQU         1000_0000b  ; Select Counter 2
x86.EX.TMR.CON.Read EQU         1100_0000b  ; Readback mode (see documentation)

; Timer Control Read/Write values
x86.EX.TMR.CON.Latch  EQU       0000_0000b  ; Counter-latch format (see documentation)
x86.EX.TMR.CON.RW.LSB EQU       0001_0000b  ; Only change LSB
x86.EX.TMR.CON.RW.MSB EQU       0010_0000b  ; Only change MSB
x86.EX.TMR.CON.RW.LMB EQU       0011_0000b  ; Change LSB then MSB

; Timer Control Mode values
x86.EX.TMR.CON.MODE.0 EQU       0000_0000b  ; Mode 0
x86.EX.TMR.CON.MODE.1 EQU       0000_0010b  ; Mode 1
x86.EX.TMR.CON.MODE.2 EQU       0000_0100b  ; Mode 2
x86.EX.TMR.CON.MODE.3 EQU       0000_0110b  ; Mode 3
x86.EX.TMR.CON.MODE.4 EQU       0000_1000b  ; Mode 4
x86.EX.TMR.CON.MODE.5 EQU       0000_1010b  ; Mode 5

; Timer Control Format values
x86.EX.TMR.CON.FMT.Bin EQU      0000_0000b  ; Binary counting format
x86.EX.TMR.CON.FMT.BCD EQU      0000_0001b  ; Binary-coded Decimal format
