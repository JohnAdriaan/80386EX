;
; Boot/Reset.inc
;

; This is the CPU Reset entry point

                SEGMENT        Boot.Reset  START=x86.Reset  ALIGN=1

Boot.Reset:
                MOV            AX, CS
                MOV            SS, AX
                MOV            SP, Boot.Table.Start
                RET
