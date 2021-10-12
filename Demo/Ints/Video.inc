;
; Ints/Video.inc
;

; This module implements the Video interrupt handler.
; It copies the Video buffer to the Screen.

Ints.Video:
                PUSHAD                    ; Need most registers
                PUSH            DS        ; And these segment registers too
                PUSH            ES

MOV DX, Dev.SBC386EX.Lite.Out
IN  AL, DX
ADD AL, 1 << Dev.SBC386EX.Lite.Shift
OUT DX, AL

                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             DS, AX
                MOV             AX, x86.Selector(Demo.GDT.Screen, .GDT, .RPL0)
                MOV             ES, AX

                ; Copy Video buffer to Screen
                CLD
                MOV             ECX, Screen.Rows * Screen.Cols * 2 / x86.DWORD.Size
                XOR             ESI, ESI
                XOR             EDI, EDI
                REP             MOVSD

                MOV             AL, Dev.PIC.Cmd.EOI ; Acknowledge interrupt in PIC
                OUT             Dev.PIC.B.Cmd, AL   ; Acknowledge slave PIC first
                OUT             Dev.PIC.A.Cmd, AL

                POP             ES
                POP             DS
                POPAD
                IRETD                     ; And return where we left off
