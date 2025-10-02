;
; Boot/Prot/KbdMouse.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

Boot.Kbd        RESB            1

Boot.Kbd.Mouse  EQU             Dev.Kbd.Ctrl.Mouse.Int
Boot.Kbd.Kbd    EQU             Dev.Kbd.Ctrl.Key.Int

ALIGNB x86.PARA.Size
Boot.Kbd.ECX    RESD            20h

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

%macro          EIPtoESI        0
                CALL            %%Next
%%Next:
                POP             ESI
%endmacro

Boot.Prot.KbdMouse:
                MOV      BYTE   [SRAM.Start + Boot.Kbd], 0

MOV EDI, SRAM.Start + Boot.Kbd.ECX

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
                EIPtoESI                              ; Success!
                JMP             .Exit

; Call to wait if Input Buffer is Full
.Wait.IBF:
                XOR             ECX, ECX
.IBF:
                IN              AL, Kbd.Stat          ; Get status
                TEST            AL, Dev.Kbd.Stat.IBF  ; Input buffer still full?
            A16 LOOPNZ          .IBF                  ; Yep, so keep trying
XCHG EAX, ECX
STOSW
XCHG EAX, ECX
                RET

; Call to wait for Output Buffer to Fill
.Wait.OBF:
                XOR             ECX, ECX
.OBF:
                IN              AL, Kbd.Stat          ; Get status
                TEST            AL, Dev.Kbd.Stat.OBF  ; Output buffer still empty?
            A16 LOOPZ           .OBF                  ; Yep, so keep trying
XCHG EAX, ECX
STOSW
XCHG EAX, ECX
                RET

; Call with AH set to Command. Returns with Carry set on Error
.Cmd:
STOSW
                CALL            .Wait.IBF         ; Wait for free Cmd
                JNZ             .Cmd.Error        ; Didn't happen!
                MOV             AL, AH            ; Cmd to send
                OUT             Kbd.Cmd, AL       ; Send it
                SHL             ECX, x86.DWORD.Hi ; It took _this_ long
                CLC                               ; But it worked!
                JMP             .Cmd.Exit         ; And leave
.Cmd.Error:
                STC                               ; Indicate error
.Cmd.Exit:
                MOV             CH, AH            ; Record Cmd attempted
                RET

; Call with AH set to Command. Returns with AL holding response, or Carry set on Error
.Cmd.Resp:
STOSW
                IN              AL, Kbd.Data      ; Empty input buffer
                MOV             DH, 10h           ; Try Cmd this many times
.Retry:
                CALL            .Wait.IBF         ; Wait for free Cmd
                JNZ             .Resp.Error       ; Didn't happen!
                MOV             AL, AH            ; Cmd to send
                OUT             Kbd.Cmd, AL       ; Send it
                CALL            .Wait.OBF         ; Wait for response
                JNZ             .Resp             ; Got one!
                DEC             DH                ; Try Cmd again?
                JZ              .Resp.Error       ; Nope: tried too often. Error
                JMP             .Retry            ; Oh, all right!
.Resp:
                IN              AL, Kbd.Data      ; Grab response
                MOV             CH, DH            ; Assume a working CH would be 0FF
                SHL             ECX, x86.DWORD.Hi ; It took _this_ long
                CLC                               ; But it worked!
                JMP             .Resp.Exit        ; So leave
.Resp.Error:
                STC                               ; Indicate error (nothing to show!)
.Resp.Exit:
                MOV             CX, AX            ; Record Cmd and (maybe) response
                RET

; Call with AH set to Command, and DL set to Data. Returns with Carry set on Error
.Cmd.Data:
MOV AL, DL
STOSW
                CALL            .Wait.IBF         ; Wait for free Cmd
                JNZ             .Data.Error       ; Didn't happen!
                MOV             AL, AH            ; Cmd to send
                OUT             Kbd.Cmd, AL       ; Send it
                CALL            .Wait.IBF         ; Wait for Cmd to go
                JNZ             .Data.Error       ; Didn't happen!
                MOV             AL, DL            ; Data to send
                OUT             Kbd.Data, AL      ; Send it
                SHL             ECX, x86.DWORD.Hi ; It took _this_ long
                CLC                               ; But it worked!
                JMP             .Data.Exit        ; So leave
.Data.Error:
                STC                               ; Indicate error
.Data.Exit:
                MOV             CH, AH            ; Record Cmd...
                MOV             CL, DL            ; ...and Data attempted
                RET

.Exit:
                MOV             EBX, `K:= `
                SUB             ESI, Boot.Prot.Entry
                CALL            Hex

                MOV             DL, [SRAM.Start + Boot.Kbd]
                CMP             DL, 0
                JE              .End

                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                OR              DL, Dev.Kbd.Ctrl.PC.Compatible | \
                                    Dev.Kbd.Ctrl.Inhib.Disable | \
                                    Dev.Kbd.Ctrl.System
                CALL            .Cmd.Data
                JC              .End

                MOV             AH, Dev.Kbd.Cmd.Ctrl.Read
                CALL            .Cmd.Resp
.End:
                MOV             EBX, `0x\r\n`
                MOV             ESI, ECX
                CALL            Hex
