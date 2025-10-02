;
; Dev/SBC386EX/Defn.inc
;

; These are the hardware-assigned sizes and clocks for the SBC386EX board
CPU.CLK2        EQU             32_000_000      ; In Hertz
CPU.TMRCLK0     EQU              1_843_200      ; In Hertz

Dev.Timer.ClockFreq EQU         CPU.TMRCLK0 / 2 ; TMRCLK0
;Dev.Timer.ClockFreq EQU         CPU.CLK2 / 2    ; PSClk default

; These are the hardware-defined Chip Selects for the on-board peripherals
%define         ROM.CS          UCS

%define         SRAM.CS         CS4

%define         DRAM.CS         CS2

%define         ECB.Mem.CS      CS3

%define         ECB.IO.CS       CS0
