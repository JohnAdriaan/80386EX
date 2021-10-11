;
; Dev/Timer.inc
;

; These are the definitions for the Programmable Interval Timer

                SEGMENT         IO

Dev.Timer:

Dev.Timer.Port  EQU             040h

Dev.Timer.ClockFreq EQU         1_843_200 / 2
