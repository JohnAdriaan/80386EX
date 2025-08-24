;
; Boot/Real/FPU.inc
;

; Detect, and if present enable, the Floating Point Unit

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

; Use current hardware semantics to enable Floating Point Unit if present
Boot.FPU:
                FPU.Detect
                JNZ             .Exit                       ; No, so no FPU

                FPU.Enable
.Exit:
