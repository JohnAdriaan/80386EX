;
; x86/EX/Remap.inc
;

; These are the definitions for the 80386EX Remap port

                SEGMENT     IO

                STRUC       x86.EX.Remap
.CFG            RESB        1
.CTRL           RESB        1
                ENDSTRUC

x86.EX.Remap.Port    EQU    0022h           ; I/O port for Remap register

x86.EX.Remap.CFG.ESE EQU    1000_0000_0000_0000b ; Enable Expanded I/O
x86.EX.Remap.CFG.S1R EQU    0000_0000_0100_0000b ; Hide SIO1 from DOS (02F8)
x86.EX.Remap.CFG.S0R EQU    0000_0000_0010_0000b ; Hide SIO0 from DOS (03F8)
x86.EX.Remap.CFG.ISR EQU    0000_0000_0001_0000b ; Hide Slave PIC from DOS (00A0)
x86.EX.Remap.CFG.IMR EQU    0000_0000_0000_1000b ; Hide Master PIC from DOS (0020)
x86.EX.Remap.CFG.DR  EQU    0000_0000_0000_0100b ; Hide DMA from DOS (0000)
x86.EX.Remap.CFG.TR  EQU    0000_0000_0000_0001b ; Hide Timer from DOS (0040)
