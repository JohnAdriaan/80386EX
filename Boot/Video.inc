;
; Boot/Video.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "Vid", 0

Boot.Video.Init:
                RET

                Boot.Table.Entry Boot.Video.Init
