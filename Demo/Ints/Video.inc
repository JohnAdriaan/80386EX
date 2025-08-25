;
; Ints/Video.inc
;

; This module implements the Video interrupt handler.
; It copies the Video buffer to the Screen (if DoubleBuffering is enabled).

Ints.Video:
                CLD
                PUSHAD                    ; Need most registers
                PUSH            DS

                ; Acknowledge CRTC interrupt
                MOV             AL, Dev.SBC386EX.VGA3.CRTC.Status
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC.Addr ; Point to Status register
                OUT             DX, AL
                INC             DX
                IN              AL, DX                               ; Read it
                MOV             AH, AL                               ; Into AH for later

                Dev.PIC.B.EOI

                MOV             DX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             DS, DX
                INC   BYTE      [WORD (Boot.PIC.B.Base + 1) * x86.WORD.Size] ; Dingle™ IRQ9

%ifdef USE_DOUBLEBUFFER
                TEST            AH, Dev.SBC386EX.VGA3.CRTC.Status.SB ; In vertical blanking?
                JZ              .TooLate                             ; No. Maybe next time

                ; This is going to take a LONG time, so re-enable interrupts
                STI

                MOV             BP, Dev.SBC386EX.Lite.Out ; To measure double-buffer overhead

                MOV             EDX, EBP
                IN              AL, DX
                XOR             AL, Dev.SBC386EX.Lite.0
                OUT             DX, AL

                ; Note we could still be in the same blanking period as last time...
                MOV             BX, x86.Selector(Demo.GDT.Screen, .GDT, .RPL0)

                PUSH            ES        ; Need these segment registers too
                MOV             ES, BX
                MOV             ECX, Screen.Rows * Screen.Cols * 2 / x86.DWORD.Size
                XOR             ESI, ESI
                XOR             EDI, EDI
                REP             MOVSD
                POP             ES

                MOV             EDX, EBP            ; Measurable duty cycle
                IN              AL, DX
                XOR             AL, Dev.SBC386EX.Lite.0
                OUT             DX, AL
.TooLate:
%endif

                POP             DS
                POPAD
                IRETD                     ; And return where we left off
