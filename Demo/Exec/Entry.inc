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
.Idle:
                CALL            Exec.Clock
                User.Yield
                JMP             .Idle

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
