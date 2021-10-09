;
; Boot/GDT.inc
;

; This sets up the GDT and JMPs to Protected Mode.
; It uses the most abbreviated Protected Mode possible, simply to allow all of
; the RAM to be tested. It also zeroes the IDT: any Exception will HALT the CPU.

;-------------------------------------------------------------------------------
                SEGMENT         Boot.GDT

                USE16

Boot.Real.GDT:
            O32 LIDT            [CS:Boot.GDT.LIDT]   ; ZEROES OUT IDT!
            O32 LGDT            [CS:Boot.GDT.LGDT]   ; This only works because I made it do!
                Dev.Lites       0111b
                MOV             EAX, CR0
                OR              AX, x86.CR0.PE       ; Protected mode Enable
                MOV             CR0, EAX
                JMP             (Boot.GDT.Code - Boot.GDT) : DWORD Boot.Prot.Entry

                ALIGN           Align.Desc, DB 0FFh
Boot.GDT:

;                               End of addresses - ROM size + Boot Real size + offset to here
.Base           EQU             x86.EX.Addr.Size - ROM.Size + Boot.Real.Size + ($ - $$)

.Code.Base      EQU             x86.EX.Addr.Size - 1_0000h ; Duplicate Reset CS...
.Code.Limit     EQU             0_FFFFh
.Code.Type      EQU             Type.Mem(.Code, .DPL0, .R) | x86.Desc.Mem.Type.Accessed
.Code.Gran      EQU             Gran.Mem(.Byte, .Big)        ; ...except in 32-bit mode

.Data.Base      EQU             DRAM.Start
.Data.Limit     EQU             (x86.EX.Addr.Size - 1) >> x86.PAGE.Shift
.Data.Type      EQU             Type.Mem(.Data, .DPL0, .RW) | x86.Desc.Mem.Type.Accessed
.Data.Gran      EQU             Gran.Mem(.Page, .Big)

.NULL           EQU             $
.LIDT           DW              0
.LGDT           EQU             $
.LGDT.Limit     DW              .Length - 1
.LGDT.Addr      DD              .Base
.Code           Desc.Mem        .Code.Base, .Code.Limit, .Code.Type, .Code.Gran
.Data           Desc.Mem        .Data.Base, .Data.Limit, .Data.Type, .Data.Gran
.Length         EQU             $ - Boot.GDT
