;
; Boot/PM.inc
;

; This sets up the GDT and enters Protected Mode.
; It uses the most abbreviated Protected Mode possible, simply to allow all of
; the RAM to be tested. It also zeroes the IDT: any Exception will HALT the CPU.

;-------------------------------------------------------------------------------
                SEGMENT         Boot.GDT

                USE16

Boot.Real.PM:
            O32 LGDT            [CS:Boot.GDT.LGDT]   ; This only works because I made it do!
            O32 LIDT            [CS:Boot.GDT.LIDT]   ; ZEROES OUT IDT!
                MOV             EAX, CR0
                OR              AX, x86.CR0.PE       ; Protected mode Enable
                MOV             CR0, EAX
            A32 JMP             (Boot.GDT.Code - Boot.GDT) : Boot.Prot.Entry

                ALIGN           x86.Desc.Size, DB 0FFh
Boot.GDT:

;                               End of addresses - Reset code size - Boot prot size - Boot GDT size + offset to here
.Addr           EQU             x86.EX.Addr.Size - Boot.Reset.Size - Boot.Prot.Size - Boot.GDT.Size +  ($ - $$)

.Code.Base      EQU             x86.EX.Addr.Size - 1_0000h ; Duplicate Reset CS...
.Code.Limit     EQU             0_FFFFh
.Code.Type      EQU             Type.Mem(Code, DPL0, R) | x86.Desc.Mem.Type.Accessed
.Code.Gran      EQU             Gran.Mem(Byte, Big)        ; ...except in 32-bit mode

.Data.Base      EQU             DRAM.Start
.Data.Limit     EQU             (x86.EX.Addr.Size - 1) >> x86.Page.Shift
.Data.Type      EQU             Type.Mem(Data, DPL0, RW) | x86.Desc.Mem.Type.Accessed
.Data.Gran      EQU             Gran.Mem(Page, Big)

.NULL           EQU             $
.LIDT           DW              0
.LGDT           EQU             $
.LGDT.Limit     DW              .Length - 1
.LGDT.Addr      DD              .Addr
.Code           Desc.Mem        .Code.Base, .Code.Limit, .Code.Type, .Code.Gran
.Data           Desc.Mem        .Data.Base, .Data.Limit, .Data.Type, .Data.Gran
.Length         EQU             $ - Boot.GDT

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32           ; We're in Protected Mode: 32-bit is king!

Boot.Prot.Entry:
                MOV             AX, Boot.GDT.Data - Boot.GDT
                MOV             DS, AX            ; Set DS to whole address space
                MOV             ES, AX            ; Set ES to whole address space
                MOV             FS, AX            ; Set FS to whole address space
                MOV             GS, AX            ; Set GS to whole address space
                MOV             SS, AX            ; Set SS to whole address space
                MOV             ESP, SRAM.Start + SRAM.Size ; Top of SRAM is stack
