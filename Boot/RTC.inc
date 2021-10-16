;
; Boot/RTC.inc
;


RTC.Clock.Len   EQU        8
RTC.Data.Len    EQU        31

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Data

RTC.Clock       RESB            RTC.Clock.Len
RTC.Data        RESB            RTC.Data.Len

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

Boot.RTC:
                MOV             EBX, `RTC\r`
                CALL            Hex
