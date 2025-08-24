;
; Boot/Real/SRAM.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.SRAM:
; Configure SRAM Chip Select (CS4)
                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(SRAM.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(SRAM.Start, NOSMM, BS8, NORDY, SRAM.Waits)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.Mem(SRAM.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.Mem(SRAM.Mask, NOSMM, CSEN)
                OUT             DX,AX
