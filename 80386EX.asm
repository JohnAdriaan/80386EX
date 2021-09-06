;
; 80386EX.asm
;

                CPU               386

%define         Name              "80386EX"
%substr         Name.Stamp        %[Name] 3, 5
%substr         Version.Year      __DATE__ 3, 2
%define         Version.Author    "John Adriaan"
%define         Version.Demo      "80386 Demo Code"
%define         Version.Boot      "386EX Boot ROM"
%define         Version.Copyright 169, "2014-", %[Version.Year]

%define         Version.Major     0
%define         Version.Minor     0
%define         Version.Build     0

%defstr         Version.String    %[Version.Major].%[Version.Minor].%[Version.Build]
%defstr         Version.Stamp     v%[Version.Major]%[Version.Minor]

;*******************************************************************************

; This file is the boot ROM for the SBC-386EX from RetroBrew Computers:
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
;===============================================================================

; Define .map file output. Map files are your friend! They can help you work out
; whether the assembler understands what you thought you told it...
                [map all 80386EX.map]

%assign         Image.Size     0     ; Starting size. See Sizes.inc below

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

;*******************************************************************************
                USE16           ; Boot in 16-bit Real Mode

%include        "Boot/Boot.inc" ; Real Mode bootstrap

                SEGMENT         Boot.Reset    ALIGN=8

                DB              Name.Stamp, Version.Stamp

;===============================================================================
%include        "Sizes.inc"     ; Final sizes for all of the above
