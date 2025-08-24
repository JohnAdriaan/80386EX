;
; Boot/Real/CPU.inc
;
; At boot, the DX register contains ID and Stepping information.
; In real mode, BP needs to be maintained - but the high part of EBP isn't used...

                SEGMENT         Boot.Real

                USE16
               
Boot.CPU:
                SHL             EDX, 16           ; Move DX to EDX high
                MOV             EBP, EDX          ; DX_0000 now saved in EBP!
