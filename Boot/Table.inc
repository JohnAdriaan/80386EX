;
; Boot/Table.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Table  ALIGN=2

Boot.Table.Start:                          ; Beginning of Boot Table

;-------------------------------------------------------------------------------

; This macro puts an Entry into the Boot Table
%macro          Boot.Table.Entry 1
                SEGMENT         Boot.Table
                DW              %1
%endmacro

; This macro finishes the current module and calls the next one.
; It also puts the passed-in Entry (%1) onto the Boot Table
%macro          Boot.Table.Next 1
                ADD             BP,2       ; Point to next JMP Table entry
                JMP             [CS:BP]    ; JMP to it

                Boot.Table.Entry %1
%endmacro
