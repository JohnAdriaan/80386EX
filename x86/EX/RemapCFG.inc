;
; x86/EX/RemapCFG.inc
;

; These are the definitions for the 80386EX RemapCFG port

x86.EX.RemapCFG         EQU     0022h           ; I/O port for RemapCFG register

x86.EX.RemapCFG.ESE     EQU     1000_0000_0000_0000b ; Enable Expanded I/O
x86.EX.RemapCFG.S1R     EQU     0000_0000_0100_0000b ; Hide SIO1 from DOS (02F8)
x86.EX.RemapCFG.S0R     EQU     0000_0000_0010_0000b ; Hide SIO0 from DOS (03F8)
x86.EX.RemapCFG.ISR     EQU     0000_0000_0001_0000b ; Hide Slave PIC from DOS (00A0)
x86.EX.RemapCFG.IMR     EQU     0000_0000_0000_1000b ; Hide Master PIC from DOS (0020)
x86.EX.RemapCFG.DR      EQU     0000_0000_0000_0100b ; Hide DMA from DOS (0000)
x86.EX.RemapCFG.TR      EQU     0000_0000_0000_0001b ; Hide Timer from DOS (0040)
