;
; Boot/CPU.inc
;
; At boot, the DX register contains ID and Stepping information.
; The SP register needs to be maintained - but the high part of ESP isn't used.

                SEGMENT         Boot.Code

                ALIGN           4

Boot.CPU.Init:
                SHL             EDX, 16           ; Save DX in EDX high
                MOV             DX, SP            ; Get SP into DX
                MOV             ESP, EDX          ; DX now saved in ESP(high)
                RET

                Boot.Table.Entry Boot.CPU.Init    ; Store entry in Boot Table
