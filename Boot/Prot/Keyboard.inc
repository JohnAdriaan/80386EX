;
; Boot/Prot/Keyboard.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

Boot.Kbd.Mouse  RESB            1

Boot.Kbd.Mouse.NotPresent EQU   0
Boot.Kbd.Mouse.Present    EQU   1

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

%macro          EIPtoESI        0
                CALL            %%Next
%%Next:
                POP             ESI
%endmacro

Boot.Prot.Keyboard:
; First, disable any attached device(s) to stop them sending data
                MOV             AH, Dev.Kbd.Cmd.Key.Disable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

                MOV             AH, Dev.Kbd.Cmd.Mouse.Disable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; Get current Controller Configuration
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Read
                CALL            .Cmd.Resp ; Also flushes any old data
                EIPtoESI
                JC              .Exit
                MOV             DH, AL ; And remember it

; Disable IRQs and Translation for proper decode
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                MOV             DL, 0
                CALL            .Cmd.Data
                EIPtoESI
                JC              .Exit

; Attempt to enable Mouse to see if Controller handles it
                MOV             AH, Dev.Kbd.Cmd.Mouse.Enable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; See if Controller enabled Mouse
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Read
                CALL            .Cmd.Resp
                EIPtoESI
                JC              .NoMouse
                TEST            AL, Dev.Kbd.Ctrl.Mouse.Disable
                JNZ             .NoMouse ; Nope!

; Disable Mouse again
                MOV             AH, Dev.Kbd.Cmd.Mouse.Disable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; Disable all enables (Luckily 0 means "enable Clock")
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                MOV             DL, 0
                CALL            .Cmd.Data
                EIPtoESI
                JC              .Exit

; Now test Mouse Port
                MOV             AH, Dev.Kbd.Cmd.Mouse.Test
                CALL            .Cmd.Resp
                EIPtoESI
                JC              .NoMouse
                CMP             AL, 00h    ; Expected result
                JNE             .NoMouse

; Tested OK, so enable Mouse port
                MOV             AH, Dev.Kbd.Cmd.Mouse.Enable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit
                OR              DH, Dev.Kbd.Ctrl.Mouse.Int ; Enable Mouse interrupts (later)
                AND             DH, ~Dev.Kbd.Ctrl.Mouse.Disable

                MOV             AH, Dev.Kbd.Cmd.Mouse.Data
                MOV             DL, 0xFF                   ; Reset mouse
                CALL            .Cmd.Data

                MOV             BH, Boot.Kbd.Mouse.Present
                JMP             .TestKeyboard

.NoMouse:
                MOV             BH, Boot.Kbd.Mouse.NotPresent
.TestKeyboard:
                MOV             [SRAM.Start + Boot.Kbd.Mouse], BH

                MOV             AH, Dev.Kbd.Cmd.Key.Test
                CALL            .Cmd.Resp
                EIPtoESI
                JC              .Exit
                CMP             AL, 00h
                MOVZX           ECX, AL
                EIPtoESI
                JNE             .Exit

                MOV             AH, Dev.Kbd.Cmd.Key.Enable
                CALL            .Cmd
                EIPtoESI
                JC              .Exit

; Keyboard and/or mouse are found. Enable interrupts
                OR              DH, Dev.Kbd.Ctrl.Key.Int
                AND             DH, ~Dev.Kbd.Ctrl.Key.Disable

                MOV             AH, Dev.Kbd.Cmd.Ctrl.Write
                MOV             DL, DH
                CALL            .Cmd.Data
                EIPtoESI
                JC              .Exit

; Get current Controller Configuration
                MOV             AH, Dev.Kbd.Cmd.Ctrl.Read
                CALL            .Cmd.Resp ; Also flushes any old data
                EIPtoESI
                JC              .Exit
                MOVZX            EDI, AL

                CALL            .Wait.IBF                  ; Input buffer still full?
                EIPtoESI
                JNZ             .Exit
                MOV             AL, 0xFF                   ; Reset keyboard
                OUT             Kbd.Data, AL

                EIPtoESI
                MOV             ECX, EDI
                JMP             .Exit

; Call to wait for Input Buffer to Empty
.Wait.IBF:
                ZeroCX
.IBF:
                IN                  AL, Kbd.Stat          ; Get status
                TEST                AL, Dev.Kbd.Stat.IBF  ; Input buffer still full?
           A16  LOOPNZ              .IBF                  ; Yep, so keep trying
                RET

; Call to wait for Output Buffer to Fill
.Wait.OBF:
                ZeroCX
.OBF:
                IN                  AL, Kbd.Stat          ; Get status
                TEST                AL, Dev.Kbd.Stat.OBF  ; Output buffer still empty?
           A16  LOOPZ               .OBF                  ; Yep, so keep trying
                RET

; Call with AH set to Command. Returns with Carry set on Error
.Cmd:
                CALL                .Wait.IBF
                JNZ                 .Cmd.Error
                MOV                 AL, AH
                OUT                 Kbd.Cmd, AL
                JMP                 .Cmd.Exit
.Cmd.Error:
                STC
.Cmd.Exit:
                RET

; Call with AH set to Command. Returns with AL holding response, or Carry set on Error
.Cmd.Resp:
                IN                  AL, Kbd.Data            ; Empty input buffer
                CALL                .Wait.IBF
                JNZ                 .Resp.Error
                MOV                 AL, AH
                OUT                 Kbd.Cmd, AL
                CALL                .Wait.OBF
                JZ                  .Resp.Error
                IN                  AL, Kbd.Data
                JMP                 .Resp.Exit
.Resp.Error:
                STC
.Resp.Exit:
                RET

; Call with AH set to Command, and DL set to Data. Returns with Carry set on Error
.Cmd.Data:
                CALL                .Wait.IBF
                JNZ                 .Data.Error
                MOV                 AL, AH
                OUT                 Kbd.Cmd, AL
                CALL                .Wait.IBF
                JNZ                 .Data.Error
                MOV                 AL, DL
                OUT                 Kbd.Data, AL
                JMP                 .Data.Exit
.Data.Error:
                STC
.Data.Exit:
                RET

.Exit:
                MOV             EBX, `K:= `
                SUB             ESI, DWORD Boot.Prot.Entry
                CALL            Hex
                MOV             EBX, `0x\r\n`
                MOV             ESI, ECX
                CALL            Hex
