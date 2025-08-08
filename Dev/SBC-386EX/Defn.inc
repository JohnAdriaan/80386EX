;
; Dev/SBC386EX/Defn.inc
;

; These are the hardware-assigned sizes and clocks for the SBC386EX board
CPU.CLK2        EQU             32_000_000      ; In Hertz
CPU.TMRCLK0     EQU              1_843_200      ; In Hertz

Dev.Timer.ClockFreq EQU         CPU.TMRCLK0 / 2 ; TMRCLK0
;Dev.Timer.ClockFreq EQU         CPU.CLK2 / 2    ; PSClk default

%define         ROM.CS          UCS
%if 0     ; 29F040
ROM.Size        EQU             512 * 1024      ; In bytes
ROM.Speed       EQU             70              ; In nanoseconds
ROM.Waits       EQU             2
%elif 0   ; 29F010
ROM.Size        EQU             128 * 1024      ; In bytes
ROM.Speed       EQU             70              ; In nanoseconds
ROM.Waits       EQU             2
%elif 1   ; 28C64
ROM.Size        EQU             8 * 1024        ; In bytes
ROM.Speed       EQU             150             ; In nanoseconds
ROM.Waits       EQU             3
%endif

%define         SRAM.CS         CS4
SRAM.Size       EQU             32 * 1024       ; In bytes
SRAM.Speed      EQU             20              ; In nanoseconds
SRAM.Waits      EQU             0

%define         DRAM.CS         CS2
;DRAM.Size      EQU             8 * 1024 * 1024 ; Calculated at runtime
%if 0      ; MT16D832-6
DRAM.Speed      EQU             60              ; In nanoseconds
DRAM.Refresh    EQU             32              ; In milliseconds
DRAM.Rows       EQU             2048            ; In... rows
DRAM.Waits      EQU             2
%elif 1    ; HY5116494B J-60
DRAM.Speed      EQU             60              ; In nanoseconds
DRAM.Refresh    EQU             64              ; In milliseconds
DRAM.Rows       EQU             4096            ; In... rows
DRAM.Waits      EQU             2
%endif

%define         ECB.Mem.CS      CS3
ECB.Mem.Size    EQU             512 * 1024
ECB.Mem.Speed   EQU             20
ECB.Mem.Waits   EQU             0

%define         ECB.IO.CS       CS0
ECB.IO.Size     EQU             0020h
ECB.IO.Speed    EQU             40
ECB.IO.Waits    EQU             2
