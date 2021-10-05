;
; Boot/Reset.inc
;

;-------------------------------------------------------------------------------
                SEGMENT        Boot.Reset

                USE16

; This is the CPU Reset entry point. JMP to the Boot code
Boot.Reset:
                JMP            Boot.Code.Entry

