;
; 80386EX.asm
;

;===============================================================================
; This file is a boot ROM for the SBC-386EX from RetroBrew Computers:
; https://www.retrobrewcomputers.org/doku.php?id=boards:sbc:sbc-386ex:rev2.0
;
; It has been written to be assembled with the Netwide Assembler NASM, which
; is a free download (http://www.nasm.us/) and will run on a number of different
; development platforms - Windows, Linux and OS-X.
;
; The NASM command line to assemble this source depends on the output format:
; Binary format: nasm.exe -l80386EX.lst 80386EX.asm
; Intel Hex format: nasm.exe -fith -l80386EX.lst -o80386EX.hex 80386EX.asm
;
; Unlike many projects, this one is not a series of modules that need to be
; independently compiled/assembled. Instead, this one file `%include`s all other
; files to provide a single image that is produced by the assembler.
;
; However, modularity is not lost: in fact, most files `%include` their own
; sub-files to make one cohesive whole. The project file hierarchy is designed
; to make it easy to know where to go:
; `x86`  : Definitions for the basic x86 CPU
; `Dev`  : Definitions for devices
; 'Ints' : Interrupt handlers
; 'User' : User space code
; 'Exec' : Executive to manage User space programs
; 'Boot' : Boot code
;===============================================================================

                CPU               386

; These are the boot-time definitions
%assign         Boot.BaudRate     115_200
%define         Boot.Protocol     Dev.UART.Word8 | Dev.UART.ParityNone | Dev.UART.Stop1

; These are the hardware-assigned sizes and clocks for the SBC386EX board
%assign         CPU.CLK2          32_000_000        ; In Hertz

%assign         ROM.Size          8 * 1024          ; In bytes
%define         ROM.CS            UCS
%assign         ROM.Speed         150               ; In nanoseconds

%assign         SRAM.Size         32 * 1024         ; In bytes
%define         SRAM.CS           CS4
%assign         SRAM.Speed        20                ; In nanoseconds

;%define        DRAM.Size         8 * 1024 * 1024   ; Calculated at runtime
%define         DRAM.CS           CS2
%assign         DRAM.Speed        60                ; In nanoseconds
%assign         DRAM.Refresh      64                ; In milliseconds
%assign         DRAM.Rows         1024              ; In... rows

%assign         ECB.Mem.Size      512 * 1024
%define         ECB.Mem.CS        CS3
%define         ECB.Mem.Speed     60

%assign         ECB.IO.Size       0020h
%define         ECB.IO.CS         CS0
%define         ECB.IO.Speed      20

; These are some version identifiers
%define         Name              "80386EX"
%substr         Name.Stamp        %[Name] 3, 5
%substr         Version.Year      __DATE__ 3, 2
%define         Version.Author    "John Adriaan"
%define         Version.Demo      "80386 Demo Code"
%define         Version.Boot      "386EX Boot ROM"
%define         Version.Copyright 169, "2014-", %[Version.Year]

%define         Version.Major     0
%define         Version.Minor     0
%define         Version.Build     1

%defstr         Version.String    %[Version.Major].%[Version.Minor].%[Version.Build]
%defstr         Version.Stamp     v%[Version.Major]%[Version.Minor]

;*******************************************************************************

; Define .map file output. Map files are your friend! They can help you work out
; whether the assembler understands what you thought you told it...
                [map all 80386EX.map]

%assign         Image.Size      0     ; Starting size. See Sizes.inc below

%assign         Demo.Size       0     ; Size of Demo part. See Sizes.inc below

%assign         Boot.Size       0     ; Size of Boot part. See Sizes.inc below

;===============================================================================
                ORG             1_0000h - ROM.Size

; The following are just definitions. Lots and lots of definitions...
; I hate "magic" numbers. Only 0 and 1 are numbers; the rest need labels!
; And comments. Lots and lots of comments...
%include        "x86/x86.inc"      ; Definitions for x86 CPU
;===============================================================================
%include        "x86/EX/386EX.inc" ; Definitions for 80386EX CPU
;===============================================================================
%include        "Dev/Dev.inc"      ; Definitions for other Devices
;===============================================================================
%include        "Dev/SBC-386EX/SBC-386EX.inc" ; Definitions for this board
;===============================================================================
%include        "Demo.inc"         ; Definitions for the demo part of the program

;*******************************************************************************

; This is Protected Mode code.

                USE32           ; 32-bit Protected Mode

%include        "Data.inc"      ; Global Data
;===============================================================================
%include        "Ints/Ints.inc" ; Interrupt handlers
;===============================================================================
%include        "User/User.inc" ; User Mode program
;===============================================================================
%include        "Exec/Exec.inc" ; Supervisor Mode executive
;*******************************************************************************

                %include        "EEPROM.inc"    ; Blank EEPROM
;===============================================================================

                USE16           ; Boot in 16-bit Real Mode

%include        "Boot/Boot.inc" ; Real Mode bootstrap

                SEGMENT         Boot.Reset

                ALIGN           8

                DB              Name.Stamp, Version.Stamp

;===============================================================================
%include        "Sizes.inc"     ; Final sizes for all of the above
