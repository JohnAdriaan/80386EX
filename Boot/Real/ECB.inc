;
; Boot/ECB.inc
;

; This is the Euro Card Bus initialisation

; Set the Chip Select Unit for the ECB
; Chip Select XIO  (CS0):  ECB.IO.Start
; Chip Select XMEM (CS3):  ECB.Mem.Start

                SEGMENT         Boot.Real

                USE16

Boot.Real.ECB:
; Configure ECB.Mem Chip Select (CS3)
                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(ECB.Mem.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.Mem.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(ECB.Mem.Start, NOSMM, ECB.Mem.Bus, NORDY, ECB.Mem.Waits)
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
                MOV             AX, x86.EX.CSU.ADL.Value.IO(ECB.IO.Start, NOSMM, ECB.IO.Bus, NORDY, ECB.IO.Waits)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.IO(ECB.IO.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ECB.IO.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.IO(ECB.IO.Mask, NOSMM, CSEN)
                OUT             DX,AX
