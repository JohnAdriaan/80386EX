;
; Boot/Video.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "Vid", 0

Boot.Video.Init:
                Boot.Table.Next  Boot.Video.Init
