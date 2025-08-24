;
; Boot/Real/DRAM.inc
;

DRAM.Mask       EQU             x86.EX.Addr.Size - 1 ; Assume whole address space

; First, some calculations
%assign         DRAM.Counter    (DRAM.Refresh * 1_000) * (CPU.CLK2 / 1_000_000) / DRAM.Rows

%if (DRAM.Counter & x86.EX.RFS.CIR.RC) != DRAM.Counter
%warning DRAM Counter (DRAM.Counter) truncated
%assign         DRAM.Counter    x86.EX.RFS.CIR.RC       ; So, replace with the maximum
%endif

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.DRAM:
; Configure DRAM Chip Select (CS2)
                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(DRAM.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(DRAM.Start, NOSMM, BS16, NORDY, DRAM.Waits)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.Mem(DRAM.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.Mem(DRAM.Mask, NOSMM, CSEN)
                OUT             DX, AX

; Configure DRAM Refresh Control Unit
                MOV             DX, x86.EX.RFS.BAD
                MOV             AX, (DRAM.Start >> x86.EX.RFS.BAD.Shift) & x86.EX.RFS.BAD.RA
                OUT             DX, AX

                MOV             DX, x86.EX.RFS.ADD
                MOV             AX, (DRAM.Start >> 0) & x86.EX.RFS.ADD.RA
                OUT             DX, AX

                MOV             DX, x86.EX.RFS.CIR
                MOV             AX, DRAM.Counter & x86.EX.RFS.CIR.RC
                OUT             DX, AX

                MOV             DX, x86.EX.RFS.CON
                MOV             AX, x86.EX.RFS.CON.REN         ; Refresh ENable
                OUT             DX, AX
