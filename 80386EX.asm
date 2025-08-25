;
; 80386EX.asm
;

;===============================================================================
; This file is a boot ROM for the SBC-386EX from RetroBrew Computers:
; https://www.RetroBrewcComputers.org/doku.php?id=boards:sbc:sbc-386ex:rev2.0
;
; It has been written to be assembled with the Netwide Assembler NASM, which
; is a free download (http://www.nasm.us/) and will run on a number of different
; development platforms - Windows, Linux and MacOS.
;
; The NASM command line to assemble this source depends on the output format:
; Binary format: nasm.exe -@ Options.txt -l80386EX.lst 80386EX.asm
; Intel Hex format: nasm.exe -@ Options.txt -fith -l80386EX.lst -o80386EX.hex 80386EX.asm
; Note that the Options.txt file contains definitions for which ICs were used
; in the target board
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
; 'Demo' : Let's see what we can do with Protected Mode
; 'Boot' : Boot code
; 'Boot/Real' : Real-mode boot code
; 'Boor/Prot' : Protected-mode boot code
;===============================================================================

                SECTALIGN         OFF   ; No implicit ALIGN => SECTALIGN effects

                CPU               386

; These are the boot-time definitions
%define         Boot.SIO.BaudRate 115_200
%define         Boot.SIO.Protocol Dev.UART.Word8 | Dev.UART.ParityNone | Dev.UART.Stop1

Screen.Width    EQU               90
Screen.Height   EQU               30
Screen.Size     EQU               Screen.Width * Screen.Height * 2

%define         Font.Height       16
%define         Font.Width        9

; These are some version identifiers
%define         Name              "80386EX"
%substr         Name.Stamp        %[Name] 3, 5
%substr         Version.Year      __DATE__ 3, 2
%define         Version.Author    "John Adriaan"
%define         Version.Demo      "386 Demonstrator"
%define         Version.Boot      "'386EX Boot ROM"
%define         Version.Copyright 169, "2014-", %[Version.Year]

%define         Version.Major     0
%define         Version.Minor     1
%define         Version.Build     0

%defstr         Version.String    %[Version.Major].%[Version.Minor].%[Version.Build]
%defstr         Version.Stamp     v%[Version.Major]%[Version.Minor]

;*******************************************************************************

; Define .map file output. Map files are your friend! They can help you work out
; whether the assembler understands what you thought you told it...
                [map all 80386EX.map]

%define         ROM.ORG         0

                ORG             ROM.ORG

%assign         Demo.Size       0     ; Size of Demo part. See */Sizes.inc below

%assign         Boot.Size       0     ; Size of Boot part. See /*Sizes.inc below

%assign         Image.Size      0     ; Whole Image size. See */Sizes.inc below

;===============================================================================
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
                SEGMENT         Demo

                USE32
%include        "Demo/Demo.inc" ; Demo to show Protected Mode features

%include        "Demo/Sizes.inc"
;===============================================================================
                SEGMENT         EPROM
%include        "EPROM.inc"     ; Padding for unused EPROM
;===============================================================================
                SEGMENT         Boot

                USE16           ; Boot in 16-bit Real Mode

%include        "Boot/Boot.inc" ; Real Mode bootstrap

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Reset

                USE16

; This is the CPU Reset entry point. JMP to the Boot code
Boot.Reset:
                JMP            Boot.Real.Entry

                ALIGN           8, DB 0FFh

                DB              Name.Stamp, Version.Stamp

;===============================================================================
%include        "Sizes.inc"     ; Clean up all Segment sizes
