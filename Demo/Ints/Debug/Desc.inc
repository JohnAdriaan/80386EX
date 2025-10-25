;
; Ints/Debug/Desc.inc
;

; This handles the Descriptor movement

Ints.Debug.Desc.Next:
                MOV             EAX,DS             ; Get current Descriptor
                AND             EAX, ~x86.Seg.RPL  ; But at RPL0
.Loop:
                ADD             AX, x86.Desc_size  ; Go to next Descriptor
.EAX:
                CALL            Ints.Debug.Desc.Check
                JNE             .Loop
                RET
;...............................................................................
Ints.Debug.Desc.Prev:
                MOV             EAX,DS             ; Get current Descriptor
                AND             EAX, ~x86.Seg.RPL  ; But at RPL0
.Loop:
                SUB             AX, x86.Desc_size  ; Go to previous Descriptor
                CALL            Ints.Debug.Desc.Check
                JNE             .Loop
                RET
;...............................................................................
Ints.Debug.Desc.Check:
; This checks the current Descriptor for readability. If not, it simply returns.
; If it is readable, it sets up the necessary registers; in particular the
; values for Minimum and Maximum.
; One step it does take is to check the result of the just-completed Next or
; Prev. If that over- or under-flowed, it swaps to the other Descriptor Table
; (GDT or LDT). Also note that since there's no easy way to determine the size
; of the current LDT, or even the GDT, it is easiest to simply check all the
; Descriptors.
                JNC             .Readable        ; Didn't overflow: keep going
                XOR             EAX, x86.Seg.TI  ; Use other Descriptor Table
.Readable:
                VERR            AX               ; Can I read it?
                JNZ             .End             ; Nope. Keep looking!

                LAR             EDX,EAX          ; Get DPL into (E)DX
                AND             EDX,x86.Desc.Type.DPL.LAR.Mask  ; Isolate DPL
                SHR             EDX,x86.Desc.Type.DPL.LAR.Shift ; Move to RPL
                OR              EAX,EDX          ; Update DS with it (we're CPL0, so...)
                MOV             DS,EAX           ; Found!

                LSL             EDX,EAX          ; Maximum address
                XOR             EBX,EBX          ; Minimum address
                MOV             ESI,EBX          ; Start at Minimum

                LAR             EAX,EAX          ; One more thing...
                TEST            AH, x86.Desc.Mem.Type.Code  ; Is it Code?
                JNZ             .Found                      ; OK, good
                TEST            AH, x86.Desc.Mem.Type.Data.Expand ; ExpandDown?
                JZ              .Found                      ; No! Phew!

                XCHG            EBX,EDX          ; Yes, so everything's upside down!
                INC             EBX              ; Or off-by-one
                NOT             EDX              ; Or inverted!
                ; Start at "top" of Segment, less a screenful
                MOV             ESI,0-(Debug.Show.Height*Debug.BytesPerRow) ; Screenful

                SHR             EAX,16           ; Also need to check Gran byte
                TEST            AL,x86.Desc.Mem.Gran.Big ; 32-bit?
                JNZ             .Found           ; Yes.
                MOV             AX,0_FFFFh       ; No. Need to mask off high word
                AND             EDX,EAX          ; Maximum address
                AND             ESI,EAX          ; Starting address
.Found:
                XOR             EAX,EAX          ; Set Z flag - Found!
.End:
                RET
