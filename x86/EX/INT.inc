;
; x86/EX/INT.inc
;

; These are the definitions for the 80386EX Interrupt Control Unit

                SEGMENT         IO

; Pin Configuration
x86.EX.INT.CFG         EQU      0_F832h

; OR these together to form correct CFG value
x86.EX.INT.CFG.CE      EQU      1000_0000b    ; Cascade Enable
x86.EX.INT.CFG.CE.Dis  EQU      0000_0000b    ; Cascade Disable
x86.EX.INT.CFG.IR3     EQU      0100_0000b    ; Master Interrupt Request 3
x86.EX.INT.CFG.IR4     EQU      0010_0000b    ; Master Interrupt Request 4
x86.EX.INT.CFG.SWAP    EQU      0001_0000b    ; Slave SWAP INT6 vs DMAINT
x86.EX.INT.CFG.IR6     EQU      0000_1000b    ; Slave Interrupt Request 6
x86.EX.INT.CFG.IR6.Dis EQU      0000_0000b    ; Slave Interrupt Request 6 disable
x86.EX.INT.CFG.IR5     EQU      0000_0100b    ; Slave Interrupt Request 5 (see documentation)
x86.EX.INT.CFG.IR5.Dis EQU      0000_0000b    ; Slave Interrupt Request 5 disable
x86.EX.INT.CFG.IR1     EQU      0000_0010b    ; Slave Interrupt Request 1
x86.EX.INT.CFG.SSIO    EQU      0000_0000b    ; SSIO interrupt (IRQ9)
x86.EX.INT.CFG.IR0     EQU      0000_0001b    ; Slave Interrupt Request 0
x86.EX.INT.CFG.IR0.Dis EQU      0000_0000b    ; Slave Interrupt Request 0 disable
