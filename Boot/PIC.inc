;
; Boot/PIC.inc
;

; The PICs need to be based to keep them away from the Intel-reserved interrupts
PIC.A.Base      EQU             20h
PIC.B.Base      EQU             28h

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.PIC:

