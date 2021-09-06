;
; Boot/SDCard.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "SD", 0, 0

Boot.SDCard.Init:
                Boot.Table.Next  Boot.SDCard.Init
