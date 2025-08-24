;
; Ints/Video.inc
;

; This module implements the Video interrupt handler.
; It copies the Video buffer to the Screen.

Ints.Video:
                CLD
                PUSHAD                    ; Need most registers

                ; This is going to take a LONG time, so acknowledge and re-enable interrupts
                MOV             AL, Dev.PIC.Cmd.EOI ; Acknowledge interrupt in PIC
                OUT             Dev.PIC.B.Cmd, AL   ; Acknowledge slave PIC first
                OUT             Dev.PIC.A.Cmd, AL
                STI

                MOV             BP, Dev.SBC386EX.Lite.Out ; To measure double-buffer overhead

                MOV             EDX, EBP
                IN              AL, DX
                XOR             AL, Dev.SBC386EX.Lite.0
                OUT             DX, AL

                ; Acknowledge CRTC interrupt
                MOV             AL, Dev.SBC386EX.VGA3.CRTC.Status
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC.Addr ; Point to Status register
                OUT             DX, AL
                INC             DX
                IN              AL, DX                               ; Read it
                TEST            AL, Dev.SBC386EX.VGA3.CRTC.Status.SB ; In vertical blanking?
                JZ              .TooLate                             ; No. Maybe next time

                ; Note we could still be in the same blanking period as last time...
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             BX, x86.Selector(Demo.GDT.Screen, .GDT, .RPL0)

                PUSH            DS        ; Need these segment registers too
                PUSH            ES
                CALL            .Copy
                POP             ES
                POP             DS
.TooLate:

                MOV             EDX, EBP            ; Measurable duty cycle
                IN              AL, DX
                XOR             AL, Dev.SBC386EX.Lite.0
                OUT             DX, AL

                POPAD
                IRETD                     ; And return where we left off

.Copy:
                ; Copy Video buffer to Screen
                MOV             DS, AX
                MOV             ES, BX
                MOV             ECX, Screen.Rows * Screen.Cols * 2 / x86.DWORD.Size
                XOR             ESI, ESI
                XOR             EDI, EDI
                REP             MOVSD
                RET
