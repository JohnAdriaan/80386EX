;
; x86/IVT.inc
;

; These are the definitions for the (Real Mode) Interrupt Vector Table.

x86.IVT.Max     EQU             100h

x86.IVT.Base    EQU             0000h         ; Interrupt Vector Table
x86.IVT.Size    EQU             x86.IVT.Max * x86.DWORD.Size ; This many DWORD vectors
