;
; Exec/Dev/Video.inc
;

; This module installs a Video interrupt handler.
; The video controller doesn't have dual-port RAM, so the screen refresh and the
; CPU writes interfere with each other and corrupt the writes. (Boy do they!)
; So writes can only happen during the blanking interval, when the refresh
; isn't accessing the RAM. Luckily it raises an interrupt during this period,
; so we can simply copy the values from a buffer to the screen.

Exec.Dev.Video:
                ; Talk to CRTC
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC.Addr

                ; Turn off cursor
                MOV             AX, Dev.SBC386EX.VGA3.CRTC.Value(              \
                                        .Ncs1,                                 \
                                        Dev.SBC386EX.VGA3.CRTC.Cursor.Off)
                OUT             DX, AX

%ifdef USE_DOUBLEBUFFER
                ; First, install a Video interrupt handler
                MOV             EAX, Ints.Video     ; Handler
                MOV             BX,  Demo.IDT.Video ; Interrupt
                MOV             CX,  x86.Selector(Demo.GDT.Ints, .GDT, .RPL0)
                MOV             DL,  x86.Type.Sys(.Int, .DPL0, .386)
                CALL            Exec.Alloc.IDT

                ; Clear double-buffer
                CLD
                MOV             AX, Dev.VGA.CharAttr(' ', Demo.User.Ball.Colour)
                MOV             DX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             ECX, Screen.Rows * Screen.Cols * 2 / x86.WORD.Size
                MOV             ES, DX
                XOR             EDI, EDI
                REP             STOSW

                ; Enable Vertical Retrace interrupt
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CRTC.Addr
                MOV             AX, Dev.SBC386EX.VGA3.CRTC.Value(              \
                                        .Control.1,                            \
                                        Dev.SBC386EX.VGA3.CRTC.Control.1.IB |  \
                                        Dev.SBC386EX.VGA3.CRTC.Control.1.Sy)
                OUT             DX, AX

; Finally, enable the Video interrupt in the PIC
                Dev.PIC.B.Enable  .Video                ; Unmask Video IRQ
%endif
                RET
