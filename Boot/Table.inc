;
; Boot/Table.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Table

Boot.Table.Start:

;-------------------------------------------------------------------------------
%macro          Boot.Table.Entry 1
                SEGMENT         Boot.Table
                DW              %1
%endmacro
