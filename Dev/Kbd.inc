;
; Dev/Kbd.inc
;

; These are the definitions for the VT82C42 Keyboard & Mouse controller

                SEGMENT         IO

Dev.Kbd:

; The original PC I/O addresses
Dev.Kbd.Data    EQU             060h
Dev.Kbd.Stat    EQU             064h
Dev.Kbd.Cmd     EQU             .Stat

%define         Kbd.Data        Dev.Kbd.Data
%define         Kbd.Stat        Dev.Kbd.Stat
%define         Kbd.Cmd         Dev.Kbd.Cmd

Dev.Kbd.Stat.Parity    EQU   1000_0000b
Dev.Kbd.Stat.RXTimeOut EQU   0100_0000b
Dev.Kbd.Stat.TXTimeOut EQU   0010_0000b
Dev.Kbd.Stat.KeyLocked EQU   0001_0000b
Dev.Kbd.Stat.Commanded EQU   0000_1000b
Dev.Kbd.Stat.System    EQU   0000_0100b ; Starts zero; Follows Ctrl
Dev.Kbd.Stat.IBF       EQU   0000_0010b
Dev.Kbd.Stat.OBF       EQU   0000_0001b

Dev.Kbd.Ctrl.PC.Compatible EQU   0100_0000b
Dev.Kbd.Ctrl.Mouse.Disable EQU   0010_0000b
Dev.Kbd.Ctrl.Key.Disable   EQU   0001_0000b
Dev.Kbd.Ctrl.Inhib.Disable EQU   0000_1000b
Dev.Kbd.Ctrl.System        EQU   0000_0100b
Dev.Kbd.Ctrl.Mouse.Int     EQU   0000_0010b
Dev.Kbd.Ctrl.Key.Int       EQU   0000_0001b

Dev.Kbd.Cmd.Ctrl.Test     EQU   0AAh ; Should return 055h
Dev.Kbd.Cmd.Ctrl.Read     EQU   020h
Dev.Kbd.Cmd.Ctrl.Write    EQU   060h
Dev.Kbd.Cmd.Ctrl.Ver      EQU   0A1h
Dev.Kbd.Cmd.Password      EQU   0A4h ; Should return 0F1h
Dev.Kbd.Cmd.Key.Test      EQU   0ABh ; Should return 000h
Dev.Kbd.Cmd.Key.Disable   EQU   0ADh
Dev.Kbd.Cmd.Key.Enable    EQU   0AEh
Dev.Kbd.Cmd.Key.Buffer    EQU   0D2h ; Pretend came from Keyboard
Dev.Kbd.Cmd.Mouse.Test    EQU   0A9h ; Should return 000h
Dev.Kbd.Cmd.Mouse.Disable EQU   0A7h
Dev.Kbd.Cmd.Mouse.Enable  EQU   0A8h
Dev.Kbd.Cmd.Mouse.Buffer  EQU   0D3h ; Pretend came from Mouse
Dev.Kbd.Cmd.Version       EQU   0AFh
Dev.Kbd.Cmd.Mode.Read     EQU   0CAh ; XXXX_XXX1b = PS/2

