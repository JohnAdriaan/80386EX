;
; Dev/SBC386EX/Defn.inc
;

; These are the hardware-assigned sizes and clocks for the SBC386EX board
CPU.CLK2        EQU             32_000_000      ; In Hertz
CPU.TMRCLK0     EQU              1_843_200      ; In Hertz

Dev.Timer.ClockFreq EQU         CPU.TMRCLK0 / 2 ; TMRCLK0
;Dev.Timer.ClockFreq EQU         CPU.CLK2 / 2    ; PSClk default

ROM.Size        EQU             8 * 1024        ; In bytes
%define         ROM.CS          UCS
ROM.Speed       EQU             150             ; In nanoseconds
ROM.Waits       EQU             3

SRAM.Size       EQU             32 * 1024       ; In bytes
%define         SRAM.CS         CS4
SRAM.Speed      EQU             20              ; In nanoseconds
SRAM.Waits      EQU             0

;DRAM.Size      EQU             8 * 1024 * 1024 ; Calculated at runtime
%define         DRAM.CS         CS2
DRAM.Speed      EQU             60              ; In nanoseconds
DRAM.Refresh    EQU             64              ; In milliseconds
DRAM.Rows       EQU             1024            ; In... rows
DRAM.Waits      EQU             2

ECB.Mem.Size    EQU             512 * 1024
%define         ECB.Mem.CS      CS3
ECB.Mem.Speed   EQU             20
ECB.Mem.Waits   EQU             0

ECB.IO.Size     EQU             0020h
%define         ECB.IO.CS       CS0
ECB.IO.Speed    EQU             40
ECB.IO.Waits    EQU             2
