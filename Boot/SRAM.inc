;
; Boot/SRAM.inc
;

SRAM.Start      EQU             (ROM.Start & ~SRAM.Mask) - SRAM.Size
SRAM.Mask       EQU             SRAM.Size - 1

;-------------------------------------------------------------------------------
                SEGMENT         SRAM  START=SRAM.Start  NOBITS

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data  VSTART=0   NOBITS
                
CPU.ID          RESW            1

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.SRAM:
; Configure SRAM Chip Select (CS4)
                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.ADH
                MOV             AX, x86.EX.CSU.ADH.Value.Mem(SRAM.Start)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.ADL
                MOV             AX, x86.EX.CSU.ADL.Value.Mem(SRAM.Start, NOSMM, BS8, NORDY, 0)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.MSKH
                MOV             AX, x86.EX.CSU.MSKH.Value.Mem(SRAM.Mask)
                OUT             DX, AX

                MOV             DX, x86.EX.CSU.%[SRAM.CS] + x86.EX.CS.MSKL
                MOV             AX, x86.EX.CSU.MSKL.Value.Mem(SRAM.Mask, NOSMM, CSEN)
                OUT             DX,AX

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.SRAM:
; Initialise SRAM with known value - then test for it
                CLD
                MOV             EAX, "SRAM"
                MOV             ECX, SRAM.Size / 4
                MOV             EDI, SRAM.Start
                REP             STOSD

                MOV             ECX, SRAM.Size / 4
                MOV             EDI, SRAM.Start
                REPE            SCASD
                JNE             Boot.Fatal

                MOV             EBX, `S:= `
                MOV             ESI, SRAM.Start
                CALL            Hex
                MOV             EBX, `0x\r\n`
                MOV             ESI, SRAM.Size
                CALL            Hex

                SHRD            EAX, EBP, 16              ; Get Processor ID
                MOV             [SRAM.Start + CPU.ID], AX ; (See Boot/CPU.inc)
