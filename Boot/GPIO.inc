;
; Boot/GPIO.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "GPIO"

Boot.GPIO.Init:

                Boot.Table.Next Boot.GPIO.Init
