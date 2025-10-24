;
; Exec/User/LDT.inc
;

; This module creates a User-mode Program's LDT and populates it.
; For demonstration purpose, it deliberately "forgets" to mark some of the
; Segments as "Present", which should trigger the Segment Not Present exception.

Exec.User.LDT:
                ; Allocate an LDT
                MOV             ECX, Demo.User.LDT.Size ; Need this many bytes (zeroes high)
                CALL            Exec.Alloc.LDT
                TEST            EAX, EAX                ; Any left?
                JZ              .Failed                 ; Nope! Finished

                MOV             [%$LDT], EAX            ; Want to keep this!

                ; Allocate Stack0
                MOV             CX, Demo.User.Stack0.Size ; Get some RAM for Stack0
                CALL            Exec.Alloc.RAM
                TEST            EAX, EAX                ; Any left?
                JZ              .Failed                 ; Nope!

                MOV             DL, x86.Type.Mem(.Stack, .DPL0, .RW) & ~Demo.System.Present
                MOV             DH, x86.Gran.Mem(.Byte, .Small)
                CALL            Exec.Alloc.LDT.Mem      ; Allocate LDT Entry
                CMP             AX, Demo.User.LDT.Stack0
                JNE             .Failed

                ; Allocate Stack3
                MOV             CX,  Demo.User.Stack3.Size ; Get some RAM for Stack3
                CALL            Exec.Alloc.RAM
                TEST            EAX, EAX                ; Any left?
                JZ              .Failed                 ; Nope!

                MOV             DL, x86.Type.Mem(.Stack, .DPL3, .RW) & ~Demo.System.Present
                MOV             DH, x86.Gran.Mem(.Byte, .Small)
                CALL            Exec.Alloc.LDT.Mem      ; Allocate LDT Entry
                CMP             AX, Demo.User.LDT.Stack3
                JNE             .Failed

                ; Allocate Data
                MOV             CX,  Demo.User.Data.Size ; Get some RAM for Data
                CALL            Exec.Alloc.RAM
                TEST            EAX, EAX                ; Any left?
                JZ              .Failed                 ; Nope!

                MOV             DL, x86.Type.Mem(.Data, .DPL3, .RW) & ~Demo.System.Present
                MOV             DH, x86.Gran.Mem(.Byte, .Big)
                CALL            Exec.Alloc.LDT.Mem      ; Allocate LDT Entry
                CMP             AX, Demo.User.LDT.Data
                JNE             .Failed

                ; Allocate Code
                MOV             EAX, Demo.User.Base     ; Assembled User code
                MOV             CX,  Demo.User.Limit+1
                MOV             DL,  x86.Type.Mem(.Code, .DPL3, .R) & ~Demo.System.Present
                MOV             DH,  x86.Gran.Mem(.Byte, .Def32)
                CALL            Exec.Alloc.LDT.Mem      ; Allocate LDT Entry
                CMP             AX,  Demo.User.LDT.Code
                JNE             .Failed

                ; Now enable the LDT
                CALL            Exec.Alloc.LDT.Enable   ; Finished!

                MOV             EAX, [%$LDT]            ; LDT descriptor
                JMP             .End
.Failed:
                XOR             EAX, EAX
.End:
                RET
