;
; Boot/Prot/Keyboard.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

Boot.Kbd        RESB            1

Boot.Kbd.Mouse  EQU             Dev.Kbd.Ctrl.Mouse.Int
Boot.Kbd.Kbd    EQU             Dev.Kbd.Ctrl.Key.Int

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

%macro          EIPtoESI        0
                CALL            %%Next
%%Next:
                POP             ESI
%endmacro

Boot.Prot.Keyboard:
                MOV      BYTE   [SRAM.Start + Boot.Kbd], 0

; First, reset the Controller
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Test
                CALL            .Cmd.Resp  ; Send Command; wait for Response
                EIPtoESI
                JC              .Exit
                CMP             AL, Dev.Kbd.Cmd.Ctrl.Test.OK
                EIPtoESI
                JNE             .Exit

; Then, disable everything
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                MOV             DL, Dev.Kbd.Ctrl.Mouse.Disable | \
                                    Dev.Kbd.Ctrl.Key.Disable   | \
                                    Dev.Kbd.Ctrl.Inhib.Disable
;                                   Dev.Kbd.Ctrl.PC.Compatible | \
;                                   Dev.Kbd.Ctrl.System        | \
;                                   Dev.Kbd.Ctrl.Mouse.Int     | \
;                                   Dev.Kbd.Ctrl.Key.Int

                CALL            .Cmd.Data
                EIPtoESI
                JC              .Exit

; Next, enable Keyboard
                MOV             AH, Dev.Kbd.Cmd.Key.Enable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; Then, test the Keyboard interface
                MOV             AH, Dev.Kbd.Cmd.Key.Test
                CALL            .Cmd.Resp
                EIPtoESI
                JC              .Exit
                CMP             AL, Dev.Kbd.Cmd.Key.Test.OK
                EIPtoESI
                JNE             .Exit

; Finally, reset the Keyboard
                CALL            .Wait.IBF
                JZ              .Kbd.Reset
                EIPtoESI
                SHL             ECX, x86.DWORD.Hi
                MOV             CH, Dev.Kbd.PS2.Reset
                JMP             .Exit

.Kbd.Reset:
                MOV             AL, Dev.Kbd.PS2.Reset
                OUT             Kbd.Data, AL

; Keyboard present!
                OR       BYTE   [SRAM.Start + Boot.Kbd], Boot.Kbd.Kbd

; Now, enable Mouse
                MOV             AH, Dev.Kbd.Cmd.Mouse.Enable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; Then, test the Mouse interface
                MOV             AH, Dev.Kbd.Cmd.Mouse.Test
                CALL            .Cmd.Resp
                EIPtoESI
                JC              .Exit
                CMP             AL, Dev.Kbd.Cmd.Mouse.Test.OK
                EIPtoESI
                JNE             .Exit

; Finally, reset the Mouse
                MOV             AH, Dev.Kbd.Cmd.Mouse.Data
                MOV             DL, Dev.Kbd.PS2.Reset
                CALL            .Cmd.Data
                EIPtoESI
                JC              .Exit

; Mouse present!
                OR       BYTE   [SRAM.Start + Boot.Kbd], Boot.Kbd.Mouse
                JMP             .Exit

; Call to wait if Input Buffer is Full
.Wait.IBF:
                XOR             ECX, ECX
.IBF:
                IN              AL, Kbd.Stat          ; Get status
                TEST            AL, Dev.Kbd.Stat.IBF  ; Input buffer still full?
           A16  LOOPNZ          .IBF                  ; Yep, so keep trying
                RET

; Call to wait for Output Buffer to Fill
.Wait.OBF:
                XOR             ECX, ECX
.OBF:
                IN              AL, Kbd.Stat          ; Get status
                TEST            AL, Dev.Kbd.Stat.OBF  ; Output buffer still empty?
           A16  LOOPZ           .OBF                  ; Yep, so keep trying
                RET

; Call with AH set to Command. Returns with Carry set on Error
.Cmd:
                CALL            .Wait.IBF
                JNZ             .Cmd.Error
                MOV             AL, AH
                OUT             Kbd.Cmd, AL
                JMP             .Cmd.Exit
.Cmd.Error:
                SHL             ECX, x86.DWORD.Hi
                MOV             CH, AH
                STC
.Cmd.Exit:
                RET

; Call with AH set to Command. Returns with AL holding response, or Carry set on Error
.Cmd.Resp:
                IN              AL, Kbd.Data      ; Empty input buffer
                MOV             DH, 10h           ; Try Cmd this many times
.Retry:
                CALL            .Wait.IBF
                JNZ             .Resp.Error
                MOV             AL, AH
                OUT             Kbd.Cmd, AL
                CALL            .Wait.OBF
                JNZ             .Resp
                DEC             DH
                JZ              .Resp.Error
                JMP             .Retry
.Resp:
                IN              AL, Kbd.Data
                SHL             ECX, x86.DWORD.Hi
                CLC
                JMP             .Resp.Exit
.Resp.Error:
                SHL             ECX, x86.DWORD.Hi
                STC
.Resp.Exit:
                MOV             CX, AX
                RET

; Call with AH set to Command, and DL set to Data. Returns with Carry set on Error
.Cmd.Data:
                CALL            .Wait.IBF
                JNZ             .Data.Error
                MOV             AL, AH
                OUT             Kbd.Cmd, AL
                CALL            .Wait.IBF
                JNZ             .Data.Error
                MOV             AL, DL
                OUT             Kbd.Data, AL
                JMP             .Data.Exit
.Data.Error:
                SHL             ECX, x86.DWORD.Hi
                MOV             CH, AH
                MOV             CL, DL
                STC
.Data.Exit:
                RET

.Exit:
                MOV             EBX, `K:= `
                SUB             ESI, DWORD Boot.Prot.Entry
                CALL            Hex

                MOV             DL, [SRAM.Start + Boot.Kbd]
                CMP             DL, 0
                JE              .End

                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                OR              DL, Dev.Kbd.Ctrl.Inhib.Disable | Dev.Kbd.Ctrl.System
                CALL            .Cmd.Data
                JC              .End
                SHL             ECX, x86.DWORD.Hi
                MOV             CH, AH
                MOV             CL, DL
.End:
                MOV             EBX, `0x\r\n`
                MOV             ESI, ECX
                CALL            Hex
