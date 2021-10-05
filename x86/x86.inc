;
; x86/x86.inc
;

; The following are definitions for the 80386 and later CPUs.
;
; Note that they're defined by Intel as part of the 'DNA' of the chip: almost
; literally, if you think of the silicon as defining the CPU's operation.

%define         x86.NIBBLE.Bits        (x86.BYTE.Bits / 2)
%define         x86.NIBBLE.Mask        (1 << x86.NIBBLE.Bits - 1)

%define         x86.BYTE                1
%define         x86.BYTE.Bits           8
%define         x86.BYTE.Mask          (1 << x86.BYTE.Bits - 1)

%define         x86.WORD                2
%define         x86.WORD.Bits          (x86.WORD * x86.BYTE.Bits)
%define         x86.WORD.Mask          (1 << x86.WORD.Bits - 1)
%define         x86.WORD.Hi             8

%define         x86.DWORD               4
%define         x86.DWORD.Bits         (x86.DWORD * x86.BYTE.Bits)
%define         x86.DWORD.Mask         (1 << x86.DWORD.Bits - 1)
%define         x86.DWORD.Hi            16
%define         x86.DWORD.Hi.8          16 + 8

%define         x86.QWORD               8
%define         x86.QWORD.Bits         (x86.QWORD * x86.BYTE.Bits)
%define         x86.QWORD.Hi            32
%define         x86.QWORD.Hi.16         32 + 16
%define         x86.QWORD.Hi.8          32 + 16 + 8

%define         x86.PARA                16
%define         x86.PARA.Bits          (x86.PARA * x86.BYTE.Bits)

%define         x86.Reset               0_FFF0h

%define         x86.Page.Shift          12
%define         x86.Page.Size           1 << x86.Page.Shift

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
