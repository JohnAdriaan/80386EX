;
; Dev/Timer.inc
;

; These are the definitions for the Programmable Interval Timer

                SEGMENT         IO

Dev.Timer:

Dev.Timer.Port  EQU             040h
Dev.Timer.Ctrl  EQU             043h

;Dev.Timer.ClockFreq EQU         4_772_728 / 4   ; Original IBM PC
