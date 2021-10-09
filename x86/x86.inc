;
; x86/x86.inc
;

; The following are definitions for the 80386 and later CPUs.
;
; Note that they're defined by Intel as part of the 'DNA' of the chip: almost
; literally, if you think of the silicon as defining the CPU's operation.

x86.NIBBLE.Bits EQU       (x86.BYTE.Bits / 2)
x86.NIBBLE.Mask EQU      ((1 << x86.NIBBLE.Bits) - 1)

x86.BYTE.Size   EQU        1
x86.BYTE.Bits   EQU        8
x86.BYTE.Mask   EQU      ((1 << x86.BYTE.Bits) - 1)

x86.WORD.Size   EQU        2
x86.WORD.Bits   EQU       (x86.WORD.Size * x86.BYTE.Bits)
x86.WORD.Mask   EQU      ((1 << x86.WORD.Bits) - 1)
x86.WORD.Hi     EQU        8

x86.DWORD.Size  EQU        4
x86.DWORD.Bits  EQU       (x86.DWORD.Size * x86.BYTE.Bits)
x86.DWORD.Mask  EQU      ((1 << x86.DWORD.Bits) - 1)
x86.DWORD.Hi    EQU        16
x86.DWORD.Hi.8  EQU        16 + 8

x86.QWORD.Size  EQU        8
x86.QWORD.Bits  EQU       (x86.QWORD.Size * x86.BYTE.Bits)
x86.QWORD.Hi    EQU        32
x86.QWORD.Hi.16 EQU        32 + 16
x86.QWORD.Hi.8  EQU        32 + 16 + 8

x86.PARA.Size   EQU        16
x86.PARA.Bits   EQU       (x86.PARA.Size * x86.BYTE.Bits)

x86.PAGE.Shift  EQU        12
x86.PAGE.Size   EQU       (0001h << x86.PAGE.Shift)

x86.Reset       EQU        0_FFF0h

Align.Byte      EQU        x86.BYTE.Size
Align.Word      EQU        x86.WORD.Size
Align.DWord     EQU        x86.DWORD.Size
Align.QWord     EQU        x86.QWORD.Size
Align.Para      EQU        x86.PARA.Size

Mask.Byte       EQU        x86.BYTE.Mask
Mask.Word       EQU        x86.WORD.Mask
Mask.DWord      EQU        x86.DWORD.Mask

Mask.Para       EQU        x86.PARA.Size - 1

                SEGMENT                 IO   VSTART=0   NOBITS

;-------------------------------------------------------------------------------
%include        "x86/EFlags.inc"        ; Definitions for EFlags register
;-------------------------------------------------------------------------------
%include        "x86/Seg.inc"           ; Definitions for Segment register
;-------------------------------------------------------------------------------
%include        "x86/CR0.inc"           ; Definitions for CR0 register
;-------------------------------------------------------------------------------
%include        "x86/Desc.inc"          ; Definitions for Descriptors
;-------------------------------------------------------------------------------
%include        "x86/TSS.inc"           ; Definitions for Task State Segment
;-------------------------------------------------------------------------------
%include        "x86/IVT.inc"           ; Definitions for Interrupt Vector Table
