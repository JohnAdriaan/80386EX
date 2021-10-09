;
; Boot/Font.inc
;

                SEGMENT         Boot.Font   ALIGN=Align.Para

%if Font.Height == 16
                INCBIN          "8x16.font"
%elif Font.Height == 11
                INCBIN          "8x11.font"
%elif Font.Height == 8
                INCBIN          "8x8.font"
%endif
