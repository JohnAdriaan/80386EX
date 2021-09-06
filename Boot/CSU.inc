;
; Boot/CSU.inc
;

                SEGMENT         Boot.Code

                ALIGN           4
                DB              "CSU", 0

Boot.CSU.Init:
                Boot.Table.Next Boot.CSU.Init
