;
; Boot/RTC.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "RTC", 0

Boot.RTC.Init:
                Boot.Table.Next Boot.RTC.Init
