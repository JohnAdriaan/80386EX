;
; Boot/ROM.inc
;

ROM.Start       EQU             x86.EX.Addr.Size - ROM.Size
ROM.Mask        EQU             ROM.Size - 1

;-------------------------------------------------------------------------------
                SEGMENT         ROM   START=ROM.Start  NOBITS

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.ROM:
; Configure ROM Chip Select (UCS) to just its little area
                MOV             DX, x86.EX.CSU.%[ROM.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(ROM.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ROM.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(ROM.Start, NOSMM, BS8, NORDY, 3)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ROM.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.Mem(ROM.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[ROM.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.Mem(ROM.Mask, NOSMM, CSEN)
                OUT             DX,AX
