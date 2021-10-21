;
; Defn.inc
;

; These are definitions for the rest of the program. You can experiment by
; changing them. Some expect to be changed (these first few), while others
; will have far-reaching impacts.

                SEGMENT         Demo.Boot

                DB              Version.Author, "'s"
                ALIGN           Align.Para, DB ' '
                DB              Version.Demo
                ALIGN           Align.Para, DB ' '

                DB              'v', Version.String
                DB              ' ', Version.Copyright
                ALIGN           Align.Para, DB ' '

%substr         Demo.Date       __?DATE?__ 3,-1
                DB              Demo.Date
                DB              __?TIME?__

; Change these to (almost) whatever you'd like. If you're too extreme, you'll
; get assemble-time errors. Others you won't know until you try...
; For example, Timer.Tick is limited on virtualisation programs like VMware,
; so that even programming ludicrous values will result in staid performance.
; However, on real hardware there isn't that sort of control. Go on, set the
; Timer to 1,000,000 times a second - I dare you!
Demo.Timer.Tick      EQU        256     ; Number of Timer Interrupts a second
Demo.Timer.Delta     EQU        1_0000_0000h / Demo.Timer.Tick
Demo.Window.Width    EQU        6       ; Width of each Task's Window
Demo.Window.Height   EQU        5       ; Height of each Task's Window

Demo.User.Ball         EQU      1       ; Try 3: it is an OEM 'Heart' symbol
Demo.User.Ball.Colour  EQU      Dev.VGA.BlueBack  | Dev.VGA.Gray
Demo.User.Frame.Colour EQU      Dev.VGA.GreenBack | Dev.VGA.White
Demo.User.Delay        EQU      0_FFFFh ; How long to 'idle' the Bounce animation

; A useful pseudo-instruction to invoke the built-in Debugger - after it's set up!
%define         DEBUG           DB 0CCh ; INT 3 - NASM assembles this as 0CD 03h

; This is the key to invoke the debugger.
; Some laptops don't have a Pause/Break key. Perhaps SysRq instead?
; Note that Pause/Break is designed to be a one-shot - it won't auto-repeat.
; Some keyboards don't reproduce this behaviour - and if you use a different
; key, it will repeat. To protect against invoking the debugger repeatedly,
; OR in the Dev.Key.Break scancode. This means that the Debugger will only be
; invoked (once) when you RELEASE the key, rather than when pressing it.
Demo.Debug.Key  EQU             Dev.Key.Pause   ; Also labelled "Break"
;Xemo.Debug.Key  EQU             Dev.Key.Break | Dev.Key.SysRq ; Debug on SysRq UP

; Another macro for debugging. Enable Single Step debugging - after it's set up!
%macro          TRACE           0
                PUSHFD
                OR      WORD    [ESP],x86.EFlags.TF
                POPFD
%endmacro

; See Ints/Timer.inc for a discussion on this (significant!) definition
Demo.System.TSS      EQU        x86.Desc.Mem.Gran.Avail

; This may need to be set to zero if you're using VirtualBox or Virtual PC. VMware is OK
Demo.System.Present  EQU        0 ; x86.Desc.Type.Present

; This is the Descriptor for the Alias for the Descriptor Table that holds it
Demo.DT.Alias        EQU        x86.Desc_size

; The following structure is held in the first (NULL) GDT entry. It holds the
; information about the current state of the GDT: how big it is, and which
; entries have been returned.
; It is designed to enable the following instruction to be used:
;         LGDT  [GDT.Alloc.Pseudo]
; This is accomplished by:
; 1) Storing the linear base address of the GDT in .Pseudo.Base
; 2) Storing the current GDT limit in .Pseudo.Limit
; 3) As entries are freed, adding them to the .Free list (this uses the entries
;    themselves to store the next Free one, or 0 to end the list).
                STRUC           Demo.GDT.Alloc
.Free           RESW            1       ; Index to first Free Descriptor, or 0
.Pseudo         EQU             $       ; You can do LGDT [GDT.Alloc.Pseudo]
.Pseudo.Limit   EQU             $
.Limit          RESW            1       ; Last allocated Descriptor
.Pseudo.Base    RESD            1       ; GDT.Base, as part of a pseudo-descriptor
                ENDSTRUC

; Like the GDT, the following structure is held in the first LDT entry - even
; though this is a valid entry according to Intel's definition.
; But by putting it there, and setting it up so that the important fields
; overlap the same fields in GDT.Alloc, the same code can be used to
; allocate Descriptors in either table.
; The "important fields" are simply .Free and .Limit
                STRUC           Demo.LDT.Alloc
.Free           RESW            1       ; Index to first Free Descriptor or 0
.Limit          RESW            1       ; Last (ever) allocated Descriptor
                RESB            1       ; Reserved
.Type           RESB            1       ; Make sure any attempt at access fails!
.GDT            RESW            1       ; This is the LDT's entry in the GDT
                ENDSTRUC

; As stated above, the two ?DT.Alloc structures have common elements:
                STRUC           Demo.DT.Alloc
.Free           RESW            1       ; Index to first Free Descriptor, or 0
.Limit          RESW            1       ; Last allocated Descriptor
                ENDSTRUC
