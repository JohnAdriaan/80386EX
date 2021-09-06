;
; Boot/FPU.inc
;

                SEGMENT         Boot.Code

                ALIGN           4

Boot.FPU.Init:
                FNINIT                            ; Init FPU (No Wait)
                FNSTSW          AX                ; Store status in AX
                TEST            AX,AX             ; Should be zero
                JNZ             .Exit             ; Nope! No '387, so leave

                MOV             EAX, CR0          ; '387 found!
                OR              EAX, x86.CR0.MP   ; Enable MP bit
                MOV             CR0, EAX          ; in CR0
.Exit:
                Boot.Table.Next Boot.FPU.Init    ; Store entry in Boot Table
