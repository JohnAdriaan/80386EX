;
; Boot/Prot/Video.inc
;

                SEGMENT         Boot.Prot

                USE32

Boot.Prot.Video:
                MOV             AX, Dev.VGA.CharAttr(' ', Boot.Text.Colour)
                MOV             ECX, Vid.Font.Addr / x86.WORD.Size ; Blank up to Font page
                MOV             DX, Vid.IO.Start + Dev.SBC386EX.VGA3.IO.CFG
                MOV             EDI, Vid.Mem.Start
.Blank:
                REP             STOSW                ; Blank video pages

                SHRD            EBX, EDI, 8          ; Get Vid.Mem.A15 into BL
                AND             BL, Dev.SBC386EX.VGA3.IO.CFG.A15

                MOV             ESI, section.Boot.Font.start
%if Font.Height == Dev.SBC386EX.VGA3.Font.Max
                MOV             CX, Boot.Font.Size / x86.DWORD.Size
             CS REP             MOVSD                ; Copy font from Boot.Font
%else
                XOR             EAX,EAX              ; Zero AH (256 count) and AL (blank bits)
.Font:
                MOV             CL, Font.Height
             CS REP             MOVSB
                MOV             CL, Dev.SBC386EX.VGA3.Font.Max - Font.Height
                REP             STOSB
                DEC             AH                    ; 256 characters in font
                JNZ             .Font
%endif

                MOV             AL, BL
                OR              AL, Vid.Font.CFG | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Font.256 | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Enable   | \
                                    Dev.SBC386EX.VGA3.IO.CFG.Width.%[Font.Width]
                OUT             DX, AL
