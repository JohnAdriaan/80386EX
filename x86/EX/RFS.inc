;
; x86/EX/RFS.inc
;

; These are the definitions for the 80386EX Refresh Control Unit

                SEGMENT         IO
                
; Refresh Registers
x86.EX.RFS.BAD  EQU             0_F4A0h     ; Refresh Base ADdress register
x86.EX.RFS.CIR  EQU             0_F4A2h     ; Refresh Clock Interval Register
x86.EX.RFS.CON  EQU             0_F4A4h     ; Refresh Control
x86.EX.RFS.ADD  EQU             0_F4A6h     ; Refresh ADDress register

; Refresh Base Address field values
x86.EX.RFS.BAD.RA      EQU      0000_1111_1111_1111b    ; Refresh Address
x86.EX.RFS.BAD.Shift   EQU      14                      ; Base address Shift

; Clock Interval field values
x86.EX.RFS.CIR.RC      EQU      0000_0011_1111_1111b    ; Refresh Counter

; Refresh Control field values
x86.EX.RFS.CON.REN     EQU      1000_0000_0000_0000b    ; Refresh ENable
x86.EX.RFS.CON.CV      EQU      0000_0011_1111_1111b    ; Counter Value (read)

; Refresh Address field values
x86.EX.RFS.ADD.RA      EQU      0011_1111_1111_1110b    ; Refresh Address
