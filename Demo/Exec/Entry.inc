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
                CALL            Exec.Dev.Timer

                ; Human interaction (via the keyboard and mouse) would be nice...
                CALL            Exec.Dev.KbdMouse

                ; But a human needs to be able to see things! So set up a video handler
                CALL            Exec.Dev.Video

                ; Let's set the time
                CALL            Exec.Dev.RTC

                ; Everything's ready! We can start to create User-mode Programs
                CALL            Exec.User

                CLD
                MOV             AX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             ES, AX

                ENTER           Clock.String, 0                 ; Make room on stack
                MOV             [EBP], DWORD ` Z\r\n`           ; Overwrite saved EBP with Zulu+CRLF
%ifdef DATE_TEST

                MOV             EAX, (12 * 60 + 34) * 60 + 56  ; Mon, 1 Jan 2001, 12:34:56
%endif
Demo.Exec.Idle:
%ifdef DATE_TEST
                LEA             EDX, [EAX + 24 * 60 * 60 + 61] ; Add a day and a second
                PUSH            EDX
                CALL            Exec.Clock

                MOV             ECX, Clock.String + 4
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
%endif ; DATE_TEST

                CALL            Exec.Clock.Get     ; EDX:EAX gets Secs:Ticks
                MOV             EAX, EDX           ; EAX is Secs
                CALL            Exec.Clock
                MOV             AH, Dev.VGA.BlackBack | Dev.VGA.Grey
                MOV             ECX, Clock.String + 2 ; Include 'Zulu'
                LEA             ESI, [EBP - Clock.String]
                MOV             EDI, (Screen.Cols - Clock.String - 2) * x86.WORD.Size
.Show:
             SS LODSB
                STOSW
                LOOP            .Show

                IN              AL, Kbd.Stat
                MOV             AH, Dev.VGA.RedBack + Dev.VGA.White
                MOV             EDI, 30 * x86.WORD.Size ; Int 30/31 is close to IRQ 1...
                CALL            .Hex

                MOV             AH, Dev.VGA.CyanBack + Dev.VGA.White
.Test.Key:
                MOV             ESI, Data.Key.Buffer
                CALL            Demo.GDT.Ints : Ints.Buffer.Pop.External

                JZ              .Test.Mouse
                MOV             EDI, (Boot.PIC.A.Base + 1) * x86.WORD.Size
                CALL            .Hex
.Test.Mouse:
                MOV             ESI, Data.Mouse.Buffer
                CALL            Demo.GDT.Ints : Ints.Buffer.Pop.External
                JZ              .Finish
                MOV             EDI, (Boot.PIC.B.Base + 4) * x86.WORD.Size
                CALL            .Hex
.Finish:
                User.Yield

%ifdef DATE_TEST
                POP             EAX                ; Restore for next increament
%endif
                JMP             Demo.Exec.Idle

.Hex:
                MOV             DL, AL             ; Save byte to display
                SHR             AL, 4              ; Look at top nibble
                CALL            .Hex.Digit         ; Display it
                MOV             AL, DL             ; Get byte back
                AND             AL, 0Fh            ; Look at bottom nibble
.Hex.Digit:
                ADD             AL, '0'            ; Convert to ASCII
                CMP             AL, '9'            ; Need to hexify?
                JBE             .Hex.Show          ; Nope!
                ADD             AL, 'A'-'9'-1      ; Yeah. Add in Hexify factor
.Hex.Show:
                STOSW                              ; Store as (both) ASCII and background colour
                RET
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
