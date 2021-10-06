;
; Dev/SBC-386EX/VGA3.inc
;

; These are the definitions for the SBC-386EX VGA card

Dev.SBC386EX.VGA3:

Dev.SBC386EX.VGA3.Mem.Size    EQU             8000h
Dev.SBC386EX.VGA3.IO.Size     EQU             Dev.SBC386EX.VGA3.IO_size

                STRUC           Dev.SBC386EX.VGA3.IO
.KBD.Addr       RESB            1       ; Keyboard controller
.KBD.Data       RESB            1
.KBD            EQU             .KBD.Addr

.CRTC.Addr      RESB            1       ; CRT Controller
.CRTC.Data      RESB            1       ; CRT Controller
.CRTC           EQU             .CRTC.Addr

.CFG            RESB            1       ; Configuration

.MEM.Addr.Hi    RESB            1       ; High address for non-direct access
.MEM.Addr.Lo    RESB            1       ; Low address for non-direct access
.MEM.Data       RESB            1       ; Data (R/W) for non-direct access
                ENDSTRUC

Dev.SBC386EX.VGA3.IO.CFG.A15        EQU       1000_0000b
Dev.SBC386EX.VGA3.IO.CFG.Font.Addr  EQU       0111_0000b
Dev.SBC386EX.VGA3.IO.CFG.Font.Shift EQU       4
Dev.SBC386EX.VGA3.IO.CFG.Font.256   EQU       0000_0000b
Dev.SBC386EX.VGA3.IO.CFG.Font.512   EQU       0000_1000b
Dev.SBC386EX.VGA3.IO.CFG.Enable     EQU       0000_0100b
;Dev.SBC386EX.VGA3.IO.CFG.Rsvd      EQU       0000_0010b    ; Reserved
Dev.SBC386EX.VGA3.IO.CFG.Width.8    EQU       0000_0000b
Dev.SBC386EX.VGA3.IO.CFG.Width.9    EQU       0000_0001b

                STRUC           Dev.SBC386EX.VGA3.CRTC
.Nht            RESB            1       ; Number Horizontal Total (+1)
.Nhd            RESB            1       ; Number Horizontal Displayed
.Nhsp           RESB            1       ; Horizontal Sync Position
.Nhsw.Nvsw      RESB            1       ; Horizontal / Vertical Sync Width
.Nvt            RESB            1       ; Number Vertical Total (+1)
.Nadj           RESB            1       ; Number Vertical Adjust
.Nvd            RESB            1       ; Number Vertical Displayed
.Nvsp           RESB            1       ; Vertical Sync Position
.Int.Skew       RESB            1       ; Interlace Mode and Skew
.Nr             RESB            1       ; Maximum Raster Address
.Ncs1           RESB            1       ; Cursor 1 Start line
.Nce1           RESB            1       ; Cursor 1 End line
.Screen.1.Hi    RESB            1       ; Screen 1 start address (Hi)
.Screen.1.Lo    RESB            1       ; Screen 1 start address (Lo)
.Cursor.1.Hi    RESB            1       ; Cursor 1 address (Hi)
.Cursor.1.Lo    RESB            1       ; Cursor 1 address (Lo)
.LightPen.Hi    RESB            1       ; LightPen address (Hi)
.LightPen.Lo    RESB            1       ; LightPen address (Lo)
.Screen.2.Pos   RESB            1       ; Screen 2 start position (row)
.Screen.2.Hi    RESB            1       ; Screen 2 start address (Hi)
.Screen.2.Lo    RESB            1       ; Screen 2 start address (Lo)
.Screen.3.Pos   RESB            1       ; Screen 3 start position (row)
.Screen.3.Hi    RESB            1       ; Screen 3 start address (Hi)
.Screen.3.Lo    RESB            1       ; Screen 3 start address (Lo)
.Screen.4.Pos   RESB            1       ; Screen 4 start position (row)
.Screen.4.Hi    RESB            1       ; Screen 4 start address (Hi)
.Screen.4.Lo    RESB            1       ; Screen 4 start address (Lo)
.Nvad           RESB            1       ; Vertical sync position Adjust
.LightPen.Raster RESB           1       ; LightPen Raster
.Nss            RESB            1       ; Smooth Scrolling
.Control.1      RESB            1       ; Control 1
.Control.2      RESB            1       ; Control 2
.Status         EQU             .Control.2 ; Status
.Control.3      RESB            1       ; Control 3
.Nof            RESB            1       ; Memory width Offset
.Ncs2           RESB            1       ; Cursor 2 Start line
.Nce2           RESB            1       ; Cursor 2 End line
.Cursor.2.Hi    RESB            1       ; Cursor 2 address (Hi)
.Cursor.2.Lo    RESB            1       ; Cursor 2 address (Lo)
.Ncw1           RESB            1       ; Cursor 1 width
.Ncw2           RESB            1       ; Cursor 2 width
                ENDSTRUC

%if             Dev.SBC386EX.VGA3.CRTC_size != 40
%error          Incorrect Dev.SBC386EX.VGA3.CRTC size!
%endif
