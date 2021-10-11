;
; Exec/Alloc/Alloc.inc
;

; This module handles allocating various system resources in separate helper
; functions.
;
; One sub-module is called DT.inc - it handles allocating in both GDTs and LDTs,
; but requires some setup first: this is performed in the appropriate sub-module.
; As such, it's only to be used internally: alas, assembler doesn't have a
; "private:" designator!

;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/RAM.inc"    ; RAM-related functions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/DT.inc"     ; Descriptor Table helper functions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/IDT.inc"    ; IDT-related functions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/GDT.inc"    ; GDT-related functions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/LDT.inc"    ; LDT-related functions
;-------------------------------------------------------------------------------
%include        "Demo/Exec/Alloc/TSS.inc"    ; TSS-related functions
