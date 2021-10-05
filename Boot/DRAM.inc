;
; Boot/DRAM.inc
;

DRAM.Start      EQU             0000_0000h
DRAM.Mask       EQU             x86.EX.Addr.Size - 1 ; Assume whole address space

; First, some calculations
%assign         DRAM.Counter    (DRAM.Refresh * 1_000) * (CPU.CLK2 / 1_000_000) / DRAM.Rows

%if (DRAM.Counter & x86.EX.RFS.CIR.RC) != DRAM.Counter
%warning DRAM Counter (DRAM.Counter) truncated
%assign         DRAM.Counter    x86.EX.RFS.CIR.RC       ; So, replace with the maximum
%endif

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

DRAM.Limit      RESD            1

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.DRAM:
; Configure DRAM Chip Select (CS2)
                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(DRAM.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(DRAM.Start, NOSMM, BS16, NORDY, 2)
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

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.DRAM:
; Test size of DRAM, in SRAM.Size increments. Stop when ROM reached
                XOR             EDX, EDX          ; Too many errors counter
                MOV             EDI, DRAM.Start
.Set.Loop:
                CMP             EDI, SRAM.Start   ; Don't write in SRAM
                JE              .Set.Next
.Set:
                MOV             [EDI], EDI        ; Store address in address
                CMP             [EDI], EDI        ; Did it work?
                JE              .Set.Same

                INC             DL                ; Nope! Try again
                JNZ             .Set
                JMP             Boot.Fatal        ; Too often. Bail!
.Set.Same:
                TEST            EDX, EDX
                JZ              .Set.Next
                MOV             EBX, `0x==`       ; Report number of attempts
                MOV             ESI, EDI
                CALL            Hex
                MOV             EBX, `0x\r\n`
                MOV             ESI, EDX
                CALL            Hex
                XOR             EDX, EDX
.Set.Next:
                ADD             EDI, SRAM.Size
                CMP             EDI, ROM.Start
                JB              .Set.Loop

; Because of DRAM wrap-around, [DRAM.Start] (kind of) holds the inverse of the DRAM size
                MOV             EDX, [DRAM.Start]
                OR              EDX, x86.EX.Addr.Size     ; Set maximum value
                MOV             EAX, EDX                  ; Get copy
                NOT             EDX                       ; NOT one
                DEC             EAX                       ; DEC the other
                AND             EAX, EDX                  ; AND the two together

                MOV             [SRAM.Start + DRAM.Limit], EAX ; Save away RAM limit

                SHR             EAX, 16                   ; Only interested in top half
                AND             AX, x86.EX.CSU.MSKH.Mask  ; Isolate MSKH
                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.MSKH
                OUT             DX, AX                    ; Set CS to only DRAM
