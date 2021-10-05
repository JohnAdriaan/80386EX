;
; Boot/FPU.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16
                
Boot.FPU:
; This following code is the recommended FPU detection sequence.
; That initial FNINIT locks up the CPU on this board though...
;               MOV             AX, 55AAh
;               FNINIT                            ; Init FPU (No Wait)
;               FNSTSW          AX                ; Store status in AX
;               TEST            AX,AX             ; Should be zero
;               JNZ             .Exit             ; Nope! No '387, so leave

; So, use the Processor Extension Request signal, which has been wired to a GPIO
                MOV             DX, Dev.SBC386EX.FPU.In     ; Look at FPU signal
                IN              AL, DX                      ; Get value
                TEST            AL, Dev.SBC386EX.FPU.PEREQ  ; Current request?
                JNZ             .Exit                       ; No, so no FPU

                SMSW            AX                ; '387 found!
                OR              AX, x86.CR0.MP    ; Enable Math Present bit
                AND             AX, ~x86.CR0.EM   ; Disable EMulate bit
                LMSW            AX                ; In Machine Status Word (CR0)
.Exit:
