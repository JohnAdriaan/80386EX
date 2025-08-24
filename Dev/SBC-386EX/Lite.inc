;
; Dev/SBC-386EX/Lite.inc
;

; These are the definitions for the SBC-386EX Lites

Dev.SBC386EX.Lite:

Dev.SBC386EX.Lite.Out   EQU  x86.EX.P1 + x86.EX.GPIO.LTC     ; Out port

Dev.SBC386EX.Lite.0     EQU  x86.EX.PIN.4      ; Pin
Dev.SBC386EX.Lite.1     EQU  x86.EX.PIN.5
Dev.SBC386EX.Lite.2     EQU  x86.EX.PIN.6
Dev.SBC386EX.Lite.3     EQU  x86.EX.PIN.7
Dev.SBC386EX.Lite.Mask  EQU  .0 | .1 | .2 | .3
Dev.SBC386EX.Lite.Shift EQU  4

%macro         Dev.Lites       1
               MOV             DX, Dev.SBC386EX.Lite.Out
               MOV             AL, (~%1 << Dev.SBC386EX.Lite.Shift) & Dev.SBC386EX.Lite.Mask
               OUT             DX, AL
%endmacro

%macro         Dev.Lites.Count 0
%if __BITS__ == 16
               XOR             CX, CX
%else
               XOR             ECX, ECX
%endif
               MOV             DX, Dev.SBC386EX.Lite.Out
               IN              AL, DX

%%Loop:
               ADD             AL, Dev.SBC386EX.Lite.0
               OUT             DX, AL
           A16 LOOP            $
               JMP             %%Loop
%endmacro

; All these macros assume:
; 1) DX has been loaded with Dev.SBC386EX.Lite.Out
; 2) AL will be destroyed

; Perform Op (%1) on passed-in Lite/s (%2)
%macro       Dev.SBC386EX.Lite.Op   2
             IN           AL, DX
             %1           AL, %2
             OUT          DX, AL
%endmacro

; Turn passed-in Lite (%1) on
%macro       Dev.SBC386EX.Lite.On 1
             Dev.SBC386EX.Lite.Op AND, ~Dev.SBC386EX.Lite.%{1}
%endmacro

; Turn passed-in Lite (%1) off
%macro       Dev.SBC386EX.Lite.Off 1
             Dev.SBC386EX.Lite.Op OR, Dev.SBC386EX.Lite.%{1}
%endmacro

; Toggle passed-in Lite (%1)
%macro       Dev.SBC386EX.Lite.Toggle 1
             Dev.SBC386EX.Lite.Op XOR, Dev.SBC386EX.Lite.%{1}
%endmacro
