;
; Dev/Timer.inc
;

; These are the definitions for the Programmable Interval Timer

                SEGMENT         IO

Dev.Timer:

Dev.Timer.Port  EQU             040h
Dev.Timer.Ctrl  EQU             043h

;Dev.Timer.ClockFreq EQU         4_772_728 / 4   ; Original IBM PC
Dev.Timer.ClockFreq EQU         1_843_200 / 2   ; SBC386EX TMRCLK0
;Dev.Timer.ClockFreq EQU         CPU.CLK2 / 2    ; 80386EX PSClk default
