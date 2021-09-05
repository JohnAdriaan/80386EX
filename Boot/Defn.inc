;
; Boot/Defn.inc
;

ROM.Size        EQU             8 * 1024

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Code      ALIGN=16

                ORG             1_0000h - ROM.Size
