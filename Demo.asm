;
; Demo.asm
;

%define         Version.Program   "Demonstrator"
%define         Version.Author    "John Burger"
%define         Version.Name      Version.Author, "'s 80386 ", Version.Program
%substr         Version.Year      __DATE__ 3, 2
%define         Version.Copyright "(c)2014-", Version.Year

%define         Version.Major   1
%define         Version.Minor   0
%define         Version.Build   102

%defstr         Version.String  %[Version.Major].%[Version.Minor].%[Version.Build]

;*******************************************************************************

; This file gives a complete example of the steps necessary to initialise an
; 80386EX PC to start some Tasks and switch between them. It is completely
; written in assembly language, and uses no extra libraries.
;
; It has been written to be assembled with the Netwide Assembler NASM, which
; is a free download (http://www.nasm.us/) and will run on a number of different
; development platforms - Windows, Linux and OS-X.
;
; The NASM command line to assemble this source is simple:
; nasm -fith -lDemo.lst -oDemo.hex Demo.asm
;===============================================================================

; Define .map file output. Map files are your friend! They can help you work out
; whether the assembler understands what you thought you told it...
                [map all Demo.map]

%assign         Image.Size      0     ; Starting size. See Sizes.inc below

%assign         Demo.Size       0     ; Starting size. See Sizes.inc below

;===============================================================================

; The following are just definitions. Lots and lots of definitions...
; I hate "magic" numbers. Only 0 and 1 are numbers; the rest need labels!
; And comments. Lots and lots of comments...
%include        "x86/x86.inc"   ; Definitions for CPU
;===============================================================================
%include        "Dev/Dev.inc"   ; Definitions for other Devices

;*******************************************************************************

                USE32           ; This is all 32-bit Protected Mode

%include        "Demo/Demo.inc" ; Definitions for the rest of the program
;===============================================================================
%include        "Demo/Data.inc" ; Global Data
;===============================================================================
%include        "Ints/Ints.inc" ; Interrupt handlers
;===============================================================================
%include        "User/User.inc" ; User Mode program
;===============================================================================
%include        "Exec/Exec.inc" ; Supervisor Mode executive
;===============================================================================
%include        "Demo/Sizes.inc"; Calculate final Sizes
