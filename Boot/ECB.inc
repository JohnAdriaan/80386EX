;
; Boot/ECB.inc
;

ECB.Mem.Start   EQU             x86.EX.Addr.Size - (1024 * 1024)
ECB.Mem.Mask    EQU             ECB.Mem.Size - 1
%define         ECB.Mem.Bus     BS8

ECB.IO.Start    EQU             00E0h
ECB.IO.Mask     EQU             ECB.IO.Size - 1
%define         ECB.IO.Bus      BS8

;-------------------------------------------------------------------------------
                SEGMENT         ECB   START=ECB.Mem.Start  NOBITS

;-------------------------------------------------------------------------------

; Set the Chip Select Unit for the ECB
; Chip Select XIO  (CS0):  00E0h-00FFh
; Chip Select XMEM (CS3):  03FY_XXXXh (where Y=0-7, X=0-F)

                SEGMENT         Boot.Real

                USE16

Boot.Real.ECB:
; Configure ECB.Mem Chip Select (CS3)
                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(ECB.Mem.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(ECB.Mem.Start, NOSMM, ECB.Mem.Bus, NORDY, 5)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.Mem(ECB.Mem.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.Mem(ECB.Mem.Mask, NOSMM, CSEN)
                OUT             DX,AX

; Configure ECB.IO Chip Select (CS0)
                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.IO(ECB.IO.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.IO(ECB.IO.Start, NOSMM, ECB.IO.Bus, NORDY, 3)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.IO(ECB.IO.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.IO(ECB.IO.Mask, NOSMM, CSEN)
                OUT             DX,AX

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.ECB:
