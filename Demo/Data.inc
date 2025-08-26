;
; Data.inc
;

; This is the definition for the global Data Segment. Note that some
; values are populated at Boot

                SEGMENT         Demo.Data  START=0  ALIGN=Align.Para  NOBITS

                USE32

Data.RAM        RESD            1       ; Beginning of available RAM
Data.RAMTop     RESD            1       ; Top of RAM

Data.Secs       RESD            1       ; Number of Seconds since Epoch
Data.Ticks      RESD            1       ; Number of Ticks since boot

Data.Key.Code   RESB            1       ; Storage for key scan-code
Data.Key.Shifts RESB            1       ; Storage for current Key Shift states

Data.Mouse.Code RESB            1       ; Storage for mouse movements

                SEGMENT         Demo.Exec

%if 0
Exec.Data.Show:
                STD                          ; Work backwards
                MOV             AH, Dev.VGA.RedBack | Dev.VGA.White
                MOV             DX, x86.Selector(Demo.GDT.Video, .GDT, .RPL0)
                MOV             EDI, (Screen.Width - 1) * 2
                MOV             ES, DX

                MOV             EDX, [WORD Data.RAMTop]
                CALL            .Hex
                MOV             AL,  '/'
                STOSW
                MOV             EDX, [WORD Data.RAM]
                CALL            .Hex
;               MOV             AL, ' '
;               STOSW
;               MOV             EDX, [WORD Data.Ticks]
;               CALL            .Hex
;               MOV             AL, ':'
;               STOSW
;               MOV             EDX, [WORD Data.Secs]
;               CALL            .Hex

                CLD
                RET
.Hex:
                MOV             ECX, x86.DWORD.Size * 2
.Hex.Loop:
                MOV             AL, DL
                AND             AL, 0Fh
                ADD             AL, '0'
                CMP             AL, '9'
                JBE             .Hex.Not
                ADD             AL, 'A' - '9' - 1
.Hex.Not:
                STOSW
                SHR             EDX, 4
                LOOP            .Hex.Loop
                RET
%endif
