;
; Boot/Timer.inc
;

; Enable Timer 0. All other timers are purely internal - their pins are used elsewhere

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.Timer:
                MOV             DX, x86.EX.TMR.CFG
                MOV             AL, x86.EX.TMR.CFG.Enable  | \
                                    x86.EX.TMR.CFG.GT0.VCC | \
                                    x86.EX.TMR.CFG.CK0.PSClk ; Pin ; ***
                OUT             DX, AL

                MOV             DX, x86.EX.TMR.CON
                MOV             AL, x86.EX.TMR.CON.SC.0   | \
                                    x86.EX.TMR.CON.RW.LMB | \
                                    x86.EX.TMR.CON.MODE.2 | \
                                    x86.EX.TMR.CON.FMT.Bin
                OUT             DX, AL
