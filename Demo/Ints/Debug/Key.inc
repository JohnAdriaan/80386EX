;
; Ints/Debug/Key.inc
;

; This module handles the various keyboard actions.

Ints.Debug.Key:
;               HLT                             ; Wait for interrupt

                PUSH            EBX
                PUSH            ESI
                PUSH            DS
                MOV             AX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             DS, AX
                MOV             ESI, Data.Key.Buffer
                CALL            Ints.Buffer.Pop
                POP             DS
                POP             ESI
                POP             EBX
                JZ              .End            ; No keys, so leave

                CMP             AL,Debug.Key.Quit
                JE              .End            ; Quit?
                CMP             AL,Debug.Key.Format
                JE              .Format
                CMP             AL,Debug.Key.Up
                JE              .Up
                CMP             AL,Debug.Key.Down
                JE              .Down
                CMP             AL,Debug.Key.PgUp
                JE              .PgUp
                CMP             AL,Debug.Key.PgDn
                JE              .PgDn
                CMP             AL,Debug.Key.Prev
                JE              Ints.Debug.Desc.Prev
                CMP             AL,Debug.Key.Next
                JE              Ints.Debug.Desc.Next
.End:
                RET
;...............................................................................
Ints.Debug.Key.Format:
                CMP             EBP,Ints.Debug.Show.DWords
                JE              .Bytes
                MOV             EBP,Ints.Debug.Show.DWords
                JMP             .End
.Bytes:
                MOV             EBP,Ints.Debug.Show.Bytes
.End:
                RET
;...............................................................................
Ints.Debug.Key.Up:
                CMP             ESI,EBX          ; Reached Minimum?
                JBE             .End             ; Yep! Do nothing.

                SUB             ESI,Debug.BytesPerRow ; Move earlier in memory
.End:
                RET
;...............................................................................
Ints.Debug.Key.Down:
                MOV             EAX,ESI          ; Try some calculations
                ADD             EAX,Debug.Show.Height*Debug.BytesPerRow ; Add in bottom of Screen
                JO              .End             ; Overflow means too far!
                DEC             EAX              ; Need to, since Limit has -1
                CMP             EAX,EDX          ; Reached Maximum?
                JAE             .End             ; Yep, so too far

                ADD             ESI,Debug.BytesPerRow ; Move later in memory
.End:
                RET
;...............................................................................
Ints.Debug.Key.PgUp:
                MOV             CL,Debug.Show.Height-1 ; Leave one row the same
.Loop:
                CALL            Ints.Debug.Key.Up
                LOOP            .Loop
                RET
;...............................................................................
Ints.Debug.Key.PgDn:
                MOV             CL,Debug.Show.Height-1 ; Leave one row the same
.Loop:
                CALL            Ints.Debug.Key.Down
                LOOP            .Loop
                RET
