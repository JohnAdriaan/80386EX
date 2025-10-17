;
; Dev.ROM.inc
;

; ROM chip definitions.
; The definition for `%[ROM.Chip]` will use one of these sets of values.

ROM.29F040.Size  EQU            512 * x86.1K.Size ; In bytes (8_0000h)
ROM.29F040.Speed EQU            70                ; In nanoseconds
ROM.29F040.Waits EQU            2

ROM.29F010.Size  EQU            128 * x86.1K.Size ; In bytes (2_0000h)
ROM.29F010.Speed EQU            70                ; In nanoseconds
ROM.29F010.Waits EQU            2

ROM.28C256.Size  EQU            32 * x86.1K.Size  ; In bytes (0_8000h)
ROM.28C256.Speed EQU            150               ; In nanoseconds
ROM.28C256.Waits EQU            3

ROM.28C128.Size  EQU            16 * x86.1K.Size  ; In bytes (0_4000h)
ROM.28C128.Speed EQU            150               ; In nanoseconds
ROM.28C128.Waits EQU            3

; This pseudo-29F chip is designed to be the top 16K of any (fast) 29F chip
; If you choose this, ensure that at programming time you LOAD the buffer at
; 4000h below the ROM size: e.g. for a 29F010 LOAD at 0_1C000
ROM.29F16K.Size  EQU            16 * x86.1K.Size  ; In bytes (0_4000h)
ROM.29F16K.Speed EQU            70                ; In nanoseconds
ROM.29F16K.Waits EQU            2

ROM.28C64.Size   EQU            8 * x86.1K.Size   ; In bytes (0_2000h)
ROM.28C64.Speed  EQU            150               ; In nanoseconds
ROM.28C64.Waits  EQU            3

ROM.Size         EQU            ROM.%[ROM.Chip].Size
ROM.Speed        EQU            ROM.%[ROM.Chip].Speed
ROM.Waits        EQU            ROM.%[ROM.Chip].Waits

; ROM definitions for address mathematics
ROM.Start        EQU            x86.EX.Addr.Size - ROM.Size
ROM.Mask         EQU            ROM.Size - 1

; At Boot time, CS holds the value 0xF000 - but the hidden Selector cache holds
; a more nuanced value for the start address:
; 80386DX: 0xFFFF_F000
; 80386EX: 0x003F_F000
; 80386SX: 0x000F_F000
; This is important, because for a LONG time after Boot, CS isn't reloaded,
; which prevents the Boot Selector values from being overwritten into the
; below 1MB range.
; But meanwhile, the assembler doesn't really know this. It can be told something
; like "ROM.Start" - but that then butts up against Protected Mode addressing.
; In short, CS-relative addressing is a nightmare. `Boot.CS` needs to be added
; to all CS-relative addresses in Boot Real mode - until NASM can be told otherwise.
%if ROM.Size < 1_0000h
%define         Boot.CS         (1_0000h - ROM.Size)
%else
%define         Boot.CS         0
%endif

;-------------------------------------------------------------------------------
                SEGMENT         ROM   START=ROM.Start  NOBITS

