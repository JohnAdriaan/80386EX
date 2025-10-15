;
; Boot/Prot/DRAM.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

DRAM.Limit      RESD            1

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

; Note there's logic to isolate SRAM and ECB accesses from DRAM, if they overlap
%define         DRAM.Max       x86.EX.Addr.Size

%ifdef USE_SRAM
%if DRAM.Max > SRAM.Start
%define         DRAM.Max       SRAM.Start
%endif
%endif ; USE_SRAM

%if DRAM.Max > ECB.Mem.Start
%define         DRAM.Max       ECB.Mem.Start
%endif

Boot.Prot.DRAM:
; Test size of DRAM, in 64K increments. Stop when DRAM.Max reached
%ifdef TEST_DRAM
                MOV             EAX, 5AA5_A55Ah   ; Alternating 0s and 1s
%endif
                MOV             ESI, DRAM.Start   ; Start from the very beginning...
.Loop:
%ifdef TEST_DRAM
                MOV             [ESI], EAX        ; Store value in address
                PAUSE                             ; ...beat...
                CMP             [ESI], EAX        ; Did it work?
                JNE             .Diff             ; No
                NOT      DWORD  [ESI]             ; Swap all bits
                PAUSE                             ; ...beat...
                XOR             [ESI], EAX        ; Should now be FFFF_FFFFh
                PAUSE                             ; ...beat...
                INC      DWORD  [ESI]             ; Should now be 0000_0000h
                JNZ             .Diff             ; Nope!
%endif ; TEST_DRAM
                MOV             [ESI], ESI        ; Store Address at address
                PAUSE                             ; ...beat...
                CMP             [ESI], ESI        ; Still there?
                JNE             .Diff             ; Nope!
                ADD             ESI, 1_0000h      ; Test next block
                CMP             ESI, DRAM.Max
                JB              .Loop
.Diff:
                MOV             EAX, [0000_0000h] ; Get lowest address back
                TEST            EAX, EAX          ; Should be zero
                JZ              .Found            ; It is! Fully populated!
                MOV             ESI, EAX          ; It isn't! Wrapped around!
                NEG             EAX               ; So isolate lowest set bit
                AND             ESI, EAX          ; e.g. 4M looped could produce 60M
.Found:
                MOV             EAX, ESI
                DEC             EAX               ; Turn into Limit, with Sign test
                MOV             EBX, `D!\r\n`
                JS              Boot.Fatal.Hex    ; No DRAM found!

                MOV             [SRAM.Start + DRAM.Limit], EAX ; Save away RAM limit

                SHR             EAX, 16                   ; Only interested in top half
                AND             AX, x86.EX.CSU.MSKH.Mask  ; Isolate MSKH
                MOV             DX, x86.EX.CSU.%[DRAM.CS] + x86.EX.CS.MSKH
                OUT             DX, AX                    ; Set CSU to only DRAM size

                MOV             EBX, `D:\r\n`
                CALL            Hex
