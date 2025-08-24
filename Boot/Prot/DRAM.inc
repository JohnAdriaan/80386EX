;
; Boot/Prot/DRAM.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

DRAM.Limit      RESD            1

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.Prot.DRAM:
; Test size of DRAM, in SRAM.Size increments. Stop when ECB reached
                XOR             EDX, EDX          ; Too many errors counter
                MOV             EDI, DRAM.Start
.Loop:
                MOV             [EDI], EDI        ; Store address in address
                CMP             [EDI], EDI        ; Did it work?
                JE              .Same

                INC             DL                ; Nope! Try again
                JNZ             .Loop
                JMP             Boot.Fatal        ; Too often. Bail!
.Same:
                TEST            EDX, EDX
                JZ              .Next
                MOV             EBX, `0x==`       ; Report number of attempts
                MOV             ESI, EDI
                CALL            Hex
                MOV             EBX, `0x\r\n`
                MOV             ESI, EDX
                CALL            Hex
                XOR             EDX, EDX
.Next:
                ADD             EDI, SRAM.Size
;               CMP             EDI, ECB.Mem.Start
                CMP             EDI, x86.EX.Addr.Size / 2 ; Maximum CS resolution?
                JB              .Loop

; Because of DRAM wrap-around, [DRAM.Start] (kind of) holds the inverse of the DRAM size
                MOV             EDX, [DRAM.Start]
                OR              EDX, x86.EX.Addr.Size / 2 ; Set maximum value
                MOV             EAX, EDX                  ; Get copy
                NOT             EDX                       ; NOT one
                DEC             EAX                       ; DEC the other
                AND             EAX, EDX                  ; AND the two together

                MOV             [SRAM.Start + DRAM.Limit], EAX ; Save away RAM limit

                SHR             EAX, 16                   ; Only interested in top half
                AND             AX, x86.EX.CSU.MSKH.Mask  ; Isolate MSKH
                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.MSKH
                OUT             DX, AX                    ; Set CS to only DRAM
