;
; Boot/GPIO.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "GPIO"

Boot.GPIO.Init:
                RET

                Boot.Table.Entry Boot.GPIO.Init
