;
; Boot/Reset.inc
;

; This is the CPU Reset entry point. Point to JMP table and start!

                SEGMENT        Boot.Reset  START=x86.Reset  ALIGN=1

Boot.Reset:
                MOV            BP, Boot.Table.Start ; First JMP Table entry
                JMP            [CS:BP]              ; JMP to it
