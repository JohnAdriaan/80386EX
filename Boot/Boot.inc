;
; Boot/Boot.inc
;

; This is the Boot ROM, including reset Entry Point. It initially runs in
; Real Mode, then transitions to Protected Mode to test RAM.
;
; The biggest problem is that immediately after Reset, there is no RAM! The
; only storage that can be relied upon are the CPU's registers themselves -
; not including this ROM image, of course.
;
; No RAM means no stack, so code can't be separately CALLable modules. Instead,
; it has to simply "fall through" from one module to the next. Be careful to
; JMP over any embedded data you might define...
;
; It is important that the modules are %included in the order below: each could
; prepare resources for future modules.
;

;===============================================================================
                SEGMENT         Boot.Data    NOBITS

%include        "Boot/Defn.inc"         ; Definitions for use by ROM routines
;-------------------------------------------------------------------------------
                SEGMENT         Boot

%include        "Boot/Label.inc"        ; Add human-readable identifiers to ROM code
;-------------------------------------------------------------------------------
                SEGMENT         Boot.Font

%include        "Boot/Font.inc"         ; Font definitions
;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Real.Entry:                        ; Reset JMP point

%include        "Boot/Real/Real.inc"
;-------------------------------------------------------------------------------
                SEGMENT         Boot.GDT

                USE16

%include        "Boot/GDT.inc"          ; Init Global Descriptor Table (GDT) in Real Mode

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

%include        "Boot/Prot/Prot.inc"
;-------------------------------------------------------------------------------
                SEGMENT         Boot.Reset

                USE16

%include        "Boot/Reset.inc"        ; CPU Reset entry point in Real Mode
;-------------------------------------------------------------------------------
