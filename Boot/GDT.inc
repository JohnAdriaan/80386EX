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
                MOV             EAX, CR0
                OR              AX,  x86.CR0.PE      ; Protected mode Enable
                MOV             CR0, EAX
                JMP             x86.Selector(Boot.GDT.Code - Boot.GDT, .GDT, .RPL0) : DWORD Boot.Prot.Entry

                ALIGN           Align.Para, DB 0FFh
Boot.GDT:

.Base           EQU             x86.EX.Addr.Size - 1_0000h + section.Boot.GDT.start + Boot.GDT - $$

.Code.Base      EQU             x86.EX.Addr.Size - 1_0000h ; Duplicate Reset CS...
.Code.Limit     EQU             0_FFFFh
.Code.Type      EQU             x86.Type.Mem(.Code, .DPL0, .R) | x86.Desc.Mem.Type.Accessed
.Code.Gran      EQU             x86.Gran.Mem(.Byte, .Big)        ; ...except in 32-bit mode

.Data.Base      EQU             DRAM.Start
.Data.Limit     EQU             (x86.EX.Addr.Size - 1) >> x86.PAGE.Shift
.Data.Type      EQU             x86.Type.Mem(.Data, .DPL0, .RW) | x86.Desc.Mem.Type.Accessed
.Data.Gran      EQU             x86.Gran.Mem(.Page, .Big)

.NULL           EQU             $
.LIDT           DW              0
.LGDT           EQU             $
.LGDT.Limit     DW              .Length - 1
.LGDT.Addr      DD              .Base
.Code           x86.Desc.Mem    .Code.Base, .Code.Limit, .Code.Type, .Code.Gran
.Data           x86.Desc.Mem    .Data.Base, .Data.Limit, .Data.Type, .Data.Gran
.Length         EQU             $ - Boot.GDT
