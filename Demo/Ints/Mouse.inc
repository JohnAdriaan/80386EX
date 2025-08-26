;
; Ints/Mouse.inc
;

; This module implements the Mouse interrupt handler.
;
; Needless to say, extending the functionality is left as an exercise for the
; reader!

Ints.Mouse:
                PUSH            EAX             ; Need these registers
                PUSH            DS

                ; Point to Video
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             DS, AX
                INC     BYTE    [WORD (Boot.PIC.B.Base + 4) * x86.WORD.Size]

                ; Point to Global Data
                MOV             AX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             DS, AX

                IN              AL, Kbd.Data    ; Get character from keyboard
                MOV             [Data.Mouse.Code], AL ; Store in global Data

                Dev.PIC.B.EOI                   ; Can now acknowledge PIC

                POP             DS              ; That was easy!
                POP             EAX
                IRETD
