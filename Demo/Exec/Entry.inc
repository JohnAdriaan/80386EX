;
; Exec/Entry.inc
;

                SEGMENT         Demo.Exec

; Made it! We're booted in Protected Mode! (You can un-cross your fingers now...)
; Before we can do anything else though, we need to set up a Protected Mode stack
Demo.Exec.Entry:

                ; Point to Stack
                MOV             AX,  x86.Selector(Demo.Exec.LDT.Stack, .LDT, .RPL0)
                MOV             SS,  AX
                XOR             ESP, ESP ; One of the advantages of Expand-Down Stacks!

                ; Initialise the rest of the registers
                CALL            Exec.Init

                ; Create more robust critical Fault handlers, with their own contexts
                ; To demonstrate the need for this, uncomment the next line...
;               MOV             ESP, 1   ; The next stack operation will triple-fault
                CALL            Exec.Ints
                ; Once they've been installed, the same instruction is handled
;               MOV             ESP, 1   ; This will fault, but at least it's handled

                ; OK, we're all ready! Time to start the system!
                STI                      ; Enable interrupts

                ; Set up the Timer interrupt handler, and enable it
                CALL            Exec.Timer

                ; Human interaction (via the keyboard) would be nice...
                CALL            Exec.Key

                ; But a human needs to be able to see things! So set up a video handler
                CALL            Exec.Video

                ; Let's set the time
                CALL            Exec.RTC

                ; Everything's ready! We can start to create User-mode Programs
                CALL            Exec.User

                CLD
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             ES, AX

                ENTER           Clock.String, 0                 ; Make room on stack
                MOV             [EBP], DWORD `\r\n`             ; Overwrite saved EBP with CRLF

                MOV             EAX, (12 * 60 + 34) * 60 + 56
Demo.Exec.Idle:
                LEA             EDX, [EAX + 24 * 60 * 60 + 61]
                PUSH            EDX
                CALL            Exec.Clock

                MOV             ECX, Clock.String + 2
                LEA             ESI, [EBP - Clock.String]
.Send:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

             SS LODSB
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                LOOP            .Send

                CALL            Exec.Clock.Get     ; EDX:EAX gets Secs:Ticks
                MOV             EAX, EDX           ; EAX is Secs
                CALL            Exec.Clock
                MOV             AH, Dev.VGA.BlackBack | Dev.VGA.Grey
                MOV             ECX, Clock.String
                LEA             ESI, [EBP - Clock.String]
                MOV             EDI, (Screen.Cols - Clock.String) * 2
.Show:
             SS LODSB
                STOSW
                LOOP            .Show
                User.Yield

                POP             EAX
                JMP             Demo.Exec.Idle

%if 0
.Forever:
                MOV             DX, Dev.UART.COM1 + Dev.UART.LSR
.Full:
                IN              AL, DX
                TEST            AL, Dev.UART.LSR.TBE
                JZ              .Full

                MOV             AL, 42
                MOV             DX, Dev.UART.COM1 + Dev.UART.Data
                OUT             DX, AL
                JMP             .Forever
%endif
