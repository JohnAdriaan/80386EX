;
; Ints/KeyMouse.inc
;

; This module implements the Keyboard and Mouse interrupt handler. It takes the
; Data from the Key/Mouse controller, notes where it came from, and buffers
; it appropriately.
;
; Keyboard:
; Note that the value stored is a scan-code, which is different from what you
; get from a getc() call - that's ASCII. Scan-codes are whatever the keyboard
; wants to generate for each key, and there's nothing obvious about their
; arrangement - so I've added code that displays the Hex value of the scan-code
; on the screen on every interrupt.
;
; Also note that the keyboard generates one interrupt when the key is pressed,
; and a second (with the same scan-code but with the high bit set) when the key
; is released. In this way the keyboard handler can keep track of which keys are
; currently being held down. If the key isn't released after a short while,
; another scan-code will be generated, again with the high bit clear.
;
; What isn't necssarily obvious is that for some keys there are two (or more)
; interrupts generated. The original PC had one set of number and arrow keys,
; while the Extended keyboard duplicated these with a keypad.
; For older systems these new keys had to generate the same scan-codes as the
; old ones, but newer systems wanted to distinguish between the two. So the new
; keys were designed to prefix the old scan-code with a "magic" keypress that
; the old systems didn't know about, so simply ignored.
;
; Mouse:
; Different mouses encode their data differently. This code is for the one I'm
; using, but if I can find others to try, I'll try to generalise the algorithm.
; (How hard can it be?)
; Note that the Interrupt routine merely stores the received codes: it does not
; try to decode them. That's left to outside the Interrupt routine.

Ints.KeyMouse:
                PUSH            EAX             ; Need these registers
                PUSH            EBX
                PUSH            ESI
                PUSH            DS

                ; Point to Global Data (and zero EAX.Hi)
                MOV             EAX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             DS, AX

.Loop:
                IN              AL, Kbd.Stat     ; Get current status
                TEST            AL, Dev.Kbd.Stat.OBF ; Output Buffer Full?
                JZ              .Empty           ; No, so leave

                MOV             AH, AL           ; Save status for more checks

                IN              AL, Kbd.Data     ; Get code from controller

                TEST            AH, Dev.Kbd.Stat.Parity    ; Parity error?
                JNZ             .Loop                      ; Yes, so ignore

                TEST            AH, Dev.Kbd.Stat.Mouse.OBF ; Is it the Mouse Output Buffer?
                MOV             ESI, Data.Mouse.Buffer     ; Assume it is
                JNZ             .Buffer          ; It was a Mouse code, so save it

                MOV             ESI, Data.Key.Buffer   ; Save in Key buffer instead
                CMP             AL, Demo.Debug.Key     ; Trying to invoke the debugger?
                JNE             .Buffer                ; No. Save as normal
                OR              EAX, 1_0000h     ; Invoke debugger!
.Buffer:
                CALL            Ints.Buffer.Push
                JMP             .Loop            ; Look for more
.Empty:
                Dev.PIC.A.EOI                    ; Can now acknowledge PIC

                SHR             EAX, 16          ; Was the debugger key hit?
                JZ              .Continue        ; Don't invoke the Debugger
                STI                              ; Do! So need interrupts back on
                DEBUG                            ; (Debugger uses keyboard)
.Continue:

                POP             DS              ; That was easy!
                POP             ESI
                POP             EBX
                POP             EAX
                IRETD
