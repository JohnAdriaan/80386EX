;
; Dev/SBC386EX/Defn.inc
;

; These are the hardware-assigned sizes and clocks for the SBC386EX board
CPU.CLK2        EQU             32_000_000      ; In Hertz
CPU.TMRCLK0     EQU              1_843_200      ; In Hertz

Dev.Timer.ClockFreq EQU         CPU.TMRCLK0 / 2 ; TMRCLK0
;Dev.Timer.ClockFreq EQU         CPU.CLK2 / 2    ; PSClk default

%define         ROM.CS          UCS

%define         SRAM.CS         CS4

%define         DRAM.CS         CS2

%define         ECB.Mem.CS      CS3
ECB.Mem.Size    EQU             512 * 1024
ECB.Mem.Speed   EQU             20
ECB.Mem.Waits   EQU             0

%define         ECB.IO.CS       CS0
ECB.IO.Size     EQU             0020h
ECB.IO.Speed    EQU             40
ECB.IO.Waits    EQU             2
