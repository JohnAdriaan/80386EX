;
; Ints/Debug/Init.inc
;

; This module handles the Debug interrupt Init and Done routines.

;...............................................................................
Ints.Debug.Init:
                MOV             AX, x86.Selector(Demo.GDT.Screen, .GDT, .RPL0) ; No double-buffering
                MOV             ES, AX           ; Point to Screen, for STOSW
                MOV             AX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             FS, AX           ; Point to global (Key) Data

                ; Default Show.Row format
                CALL            Ints.Debug.Key.Format.Bytes
                CALL            Ints.System.Init
                RET

;...............................................................................
Ints.Debug.Done:
                CLD                             ; Work forwards
                MOV             AH, Debug.Colour.Blank
                MOV             AL, ' '
                MOV             DH, Debug.VGA.Height
                MOV             DI, (Debug.VGA.Top * Screen.Cols + Debug.VGA.Left) * 2
.Loop:
                MOV             ECX, Debug.VGA.Width
                REP             STOSW
                ADD             DI, (Screen.Cols - Debug.VGA.Width) * 2
                DEC             DH
                JNZ             .Loop

                CALL            Ints.System.Done
                RET
