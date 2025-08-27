;
; Dev/PIC.inc
;

; These are the definitions for the Priority Interrupt Controllers

                SEGMENT         IO

Dev.PIC:

Dev.PIC.A.Cmd   EQU             020h
Dev.PIC.A.Mask  EQU             021h
Dev.PIC.A.Ctrl  EQU             Dev.PIC.A.Mask

Dev.PIC.B.Cmd   EQU             0A0h
Dev.PIC.B.Mask  EQU             0A1h
Dev.PIC.B.Ctrl  EQU             Dev.PIC.B.Mask

Dev.PIC.Cmd.EOI   EQU           20h
Dev.PIC.Cmd.IRR   EQU           0Ah             ; Access Interrupt Request Register
Dev.PIC.Cmd.ISR   EQU           0Bh             ; Access In-Service Register
Dev.PIC.Spurious  EQU           1000_0000b      ; Mask: ZERO means spurious

Dev.PIC.Cmd.ICW1.A75M80  EQU    1110_0000b      ; A7-A5 for MCS 8080/8085 only
Dev.PIC.Cmd.ICW1.ICW1    EQU    0001_0000b      ; This is the ICW1 Command
Dev.PIC.Cmd.ICW1.Edge    EQU    0000_0000b      ; LTIM: Edge-triggered mode
Dev.PIC.Cmd.ICW1.Level   EQU    0000_1000b      ; LTIM: Level-triggered mode
Dev.PIC.Cmd.ICW1.AInt8   EQU    0000_0000b      ; Address interval (MCS 80/85)
Dev.PIC.Cmd.ICW1.AInt4   EQU    0000_0100b      ; Address interval (MCS 80/85)
Dev.PIC.Cmd.ICW1.Cascade EQU    0000_0000b      ; SNGL: Cascaded PICs
Dev.PIC.Cmd.ICW1.Single  EQU    0000_0010b      ; SNGL: Single PIC
Dev.PIC.Cmd.ICW1.ICW4    EQU    0000_0001b      ; IC4: Need ICW4

%ifdef PIC_LEVEL
%define       Dev.PIC.ICW1.Trigger Dev.PIC.Cmd.ICW1.Level
%else
%define       Dev.PIC.ICW1.Trigger Dev.PIC.Cmd.ICW1.Edge
%endif

%define       Dev.PIC.Cmd.ICW1  Dev.PIC.Cmd.ICW1.ICW1 |    \
                                Dev.PIC.ICW1.Trigger  |    \
                                Dev.PIC.Cmd.ICW1.Cascade | \
                                Dev.PIC.Cmd.ICW1.ICW4

Dev.PIC.Cmd.ICW4.SFNM          EQU 0001_0000b      ; Special Fully Nested Mode
Dev.PIC.Cmd.ICW4.Buffer        EQU 0000_1100b      ; Buffer mask
Dev.PIC.Cmd.ICW4.Buffer.None   EQU 0000_0000b      ; No Buffer
Dev.PIC.Cmd.ICW4.Buffer.Slave  EQU 0000_1000b      ; Buffered Slave
Dev.PIC.Cmd.ICW4.Buffer.Master EQU 0000_1100b      ; Buffered Master
Dev.PIC.Cmd.ICW4.AEOI          EQU 0000_0010b      ; Automatic End-of-Interrupt
Dev.PIC.Cmd.ICW4.8080          EQU 0000_0000b      ; MCS 8080/8085
Dev.PIC.Cmd.ICW4.8086          EQU 0000_0001b      ; MCS 8086

%define      Dev.PIC.Init.ICW4     Dev.PIC.Cmd.ICW4.8086

Dev.PIC.A.Cascade EQU           0000_0100b      ; PIC.A has slave on IRQ2
Dev.PIC.B.Cascade EQU           02h             ; PIC.B is slaved on IRQ2

Dev.PIC.A.Timer   EQU           0000_0001b
Dev.PIC.A.Key     EQU           0000_0010b
Dev.PIC.A.COM2    EQU           0000_1000b
Dev.PIC.A.COM1    EQU           0001_0000b
Dev.PIC.A.Floppy  EQU           0100_0000b
Dev.PIC.A.Printer EQU           1000_0000b

Dev.PIC.B.RTC     EQU           0000_0001b
Dev.PIC.B.Video   EQU           0000_0010b
Dev.PIC.B.Mouse   EQU           0001_0000b
Dev.PIC.B.IDE0    EQU           0100_0000b
Dev.PIC.B.IDE1    EQU           1000_0000b

%macro            Dev.PIC.A.Enable 1
                  IN               AL,  Dev.PIC.A.Mask
                  AND              AL, ~Dev.PIC.A%1
                  OUT              Dev.PIC.A.Mask, AL
%endmacro

%macro            Dev.PIC.B.Enable 1
                  IN               AL,  Dev.PIC.B.Mask
                  AND              AL, ~Dev.PIC.B%1
                  OUT              Dev.PIC.B.Mask, AL
%endmacro

%macro            Dev.PIC.A.EOI    0
                  MOV              AL, Dev.PIC.Cmd.EOI ; Acknowledge interrupt in PIC
                  OUT              Dev.PIC.A.Cmd, AL
%endmacro

%macro            Dev.PIC.B.EOI    0
                  MOV              AL, Dev.PIC.Cmd.EOI ; Acknowledge interrupt in PIC
                  OUT              Dev.PIC.B.Cmd, AL   ; Acknowledge slave PIC first
                  OUT              Dev.PIC.A.Cmd, AL
%endmacro
