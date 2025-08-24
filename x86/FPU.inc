;
; x86/FPU.inc
;

; These are the definitions for the 80x87 Floating Point Unit

x86.FPU:

x86.FPU.Status.Busy        EQU       1000_0000_0000_0000b
x86.FPU.Status.ToS         EQU       0011_1000_0000_0000b ; Top of Stack
x86.FPU.Status.Condition   EQU       0100_0111_0000_0000b
x86.FPU.Status.Cond.C3     EQU       0100_0000_0000_0000b
x86.FPU.Status.Cond.C2     EQU       0000_0100_0000_0000b
x86.FPU.Status.Cond.C1     EQU       0000_0010_0000_0000b
x86.FPU.Status.Cond.C0     EQU       0000_0001_0000_0000b
x86.FPU.Status.Error       EQU       0000_0000_1000_0000b
x86.FPU.Status.StackFault  EQU       0000_0000_0100_0000b
x86.FPU.Status.Exception       EQU       0000_0000_0011_1111b
x86.FPU.Status.Exc.Precision   EQU       0000_0000_0010_0000b
x86.FPU.Status.Exc.Underflow   EQU       0000_0000_0001_0000b
x86.FPU.Status.Exc.Overflow    EQU       0000_0000_0000_1000b
x86.FPU.Status.Exc.ZeroDivide  EQU       0000_0000_0000_0100b
x86.FPU.Status.Exc.Denormal    EQU       0000_0000_0000_0010b
x86.FPU.Status.Exc.Invalid     EQU       0000_0000_0000_0001b

                STRUC           x86.FPU.FSTENV
.Control        RESW            1               ; Control Word
                RESW            1
.Status         RESW            1               ; Status Word
                RESW            1
.Tag            RESW            1               ; Tag Word
                RESW            1
.Inst           RESD            1               ; Instruction offset
.Inst.Selector  RESW            1               ; Instruction selector
.Opcode         RESW            1               ; Opcode
.Operand        RESD            1               ; Operand pointer
.Op.Selector    RESW            1               ; Operand Selector
                RESW            1
                ENDSTRUC

                STRUC           x86.FPU.FSAVE
.Env            RESB            x86.FPU.FSTENV_size
.Stack          REST            8
                ENDSTRUC

; Candidate for FPU detection. Not all implementations will work without an FPU
; This macro returns Z flag set if the FPU is detected
%macro          x86.FPU.Detect  0
                MOV             AX, 55AAh
                FNINIT                            ; Init FPU (No Wait)
                FNSTSW          AX                ; Store status in AX
                TEST            AX,AX             ; Should be zero
%endmacro

%define         FPU.Detect      x86.FPU.Detect

; This macro tells the x86 to use the floating point chip: don't emulate it
%macro          x86.FPU.Enable  0
                SMSW            AX                ; '387 found!
                OR              AX, x86.CR0.MP    ; Enable Math Present bit
                AND             AX, ~x86.CR0.EM   ; Disable EMulate bit
                LMSW            AX                ; In Machine Status Word (CR0)
%endmacro

%define         FPU.Enable      x86.FPU.Enable
