;
; Exec/LDT.inc
;

; This is the Local Descriptor Table for the Executive

                SEGMENT         Demo.Exec.LDT   VSTART=0

                USE32

; This macro makes it easy to have a one-line invocation of LDT.Alloc
; The parameters are: GDT Entry, LDT Limit
%macro                    Demo.LDT.Vars   2
%00                       ISTRUC          Demo.LDT.Alloc
AT Demo.LDT.Alloc.Free,   DW              0
AT Demo.LDT.Alloc.Limit,  DW              %2
                          DB              0
AT Demo.LDT.Alloc.Type,   DB              x86.Desc.Sys.Type.LDT
AT Demo.LDT.Alloc.GDT,    DW              %1
                          IEND
%endmacro

Demo.Exec.LDT.Alias.Base  EQU        Demo.Exec.LDT.Base
Demo.Exec.LDT.Alias.Limit EQU        Demo.Exec.LDT.Limit
Demo.Exec.LDT.Alias.Type  EQU        x86.Type.Mem(.Data, .DPL0, .RW)
Demo.Exec.LDT.Alias.Gran  EQU        x86.Gran.Mem(.Byte, .Small)

Demo.Exec.LDT.IDT.Base    EQU        Demo.IDT.Base
Demo.Exec.LDT.IDT.Limit   EQU        x86.IDT.Size.Max - 1
Demo.Exec.LDT.IDT.Type    EQU        x86.Type.Mem(.Data, .DPL0, .RW)
Demo.Exec.LDT.IDT.Gran    EQU        x86.Gran.Mem(.Byte, .Small)

Demo.Exec.LDT.Stack.Top   EQU        Demo.Exec.Stack.Top  ; Let's play with Expand-Down Descriptors
Demo.Exec.LDT.Stack.Limit EQU        (0-Demo.Exec.Stack.Size) >> x86.PAGE.Shift - 1
Demo.Exec.LDT.Stack.Type  EQU        x86.Type.Mem(.Stack, .DPL0, .RW)
Demo.Exec.LDT.Stack.Gran  EQU        x86.Gran.Mem(.Page, .Big)

Demo.Exec.LDT.Code.Base   EQU        Demo.Exec.Base
Demo.Exec.LDT.Code.Limit  EQU        Demo.Exec.Limit
Demo.Exec.LDT.Code.Type   EQU        x86.Type.Mem(.Code, .DPL0, .RNoW)
Demo.Exec.LDT.Code.Gran   EQU        x86.Gran.Mem(.Byte, .Def32)

Demo.Exec.LDT:
Demo.Exec.LDT.Vars   Demo.LDT.Vars   Demo.GDT.Exec.LDT, Demo.Exec.LDT.Limit
Demo.Exec.LDT.Alias  x86.Desc.Mem    Demo.Exec.LDT.Alias.Base, Demo.Exec.LDT.Alias.Limit, Demo.Exec.LDT.Alias.Type, Demo.Exec.LDT.Alias.Gran
Demo.Exec.LDT.IDT    x86.Desc.Mem    Demo.Exec.LDT.IDT.Base,   Demo.Exec.LDT.IDT.Limit,   Demo.Exec.LDT.IDT.Type,   Demo.Exec.LDT.IDT.Gran
Demo.Exec.LDT.Stack  x86.Desc.Mem    Demo.Exec.LDT.Stack.Top,  Demo.Exec.LDT.Stack.Limit, Demo.Exec.LDT.Stack.Type, Demo.Exec.LDT.Stack.Gran
Demo.Exec.LDT.Code   x86.Desc.Mem    Demo.Exec.LDT.Code.Base,  Demo.Exec.LDT.Code.Limit,  Demo.Exec.LDT.Code.Type,  Demo.Exec.LDT.Code.Gran

Demo.Exec.LDT.Defined     EQU        $ - $$

%assign              Demo.Exec.LDT.Pos   Demo.Exec.LDT.Defined

Demo.Exec.LDT.NoSeg          EQU       Demo.Exec.LDT.Pos
Demo.Exec.LDT.NoSeg.TSS      EQU       Demo.Exec.LDT.Pos + x86.Desc.Size
;Demo.Exec.LDT.NoSeg.Stack    x86.Desc.Mem  0, 0, 0, 0 ; Stack for Segment Not Present handler
;Demo.Exec.LDT.NoSeg.TSS      x86.Desc.Mem  0, 0, 0, 0 ; Alias for TSS to read Backlink
;Demo.Exec.LDT.NoSeg.Alias    x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting TSS
;Demo.Exec.LDT.NoSeg.LDT      x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting LDT

%assign              Demo.Exec.LDT.Pos Demo.Exec.LDT.Pos + 4 * x86.Desc.Size

Demo.Exec.LDT.Double         EQU       Demo.Exec.LDT.Pos
Demo.Exec.LDT.Double.TSS     EQU       Demo.Exec.LDT.Pos + x86.Desc.Size
;Demo.Exec.LDT.Double.Stack   x86.Desc.Mem  0, 0, 0, 0 ; Stack for Double Fault handler
;Demo.Exec.LDT.Double.TSS     x86.Desc.Mem  0, 0, 0, 0 ; Alias for TSS to read Backlink
;Demo.Exec.LDT.Double.Alias   x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting TSS

%assign              Demo.Exec.LDT.Pos Demo.Exec.LDT.Pos + 3 * x86.Desc.Size

Demo.Exec.LDT.BadStack       EQU       Demo.Exec.LDT.Pos
Demo.Exec.LDT.BadStack.TSS   EQU       Demo.Exec.LDT.Pos + x86.Desc.Size
;Demo.Exec.LDT.BadStack.Stack x86.Desc.Mem  0, 0, 0, 0 ; Stack for BadStack Fault handler
;Demo.Exec.LDT.BadStack.TSS   x86.Desc.Mem  0, 0, 0, 0 ; Alias for TSS to read Backlink
;Demo.Exec.LDT.BadStack.Alias x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting TSS
;Demo.Exec.LDT.BadStack.LDT   x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting LDT

%assign              Demo.Exec.LDT.Pos Demo.Exec.LDT.Pos + 4 * x86.Desc.Size

Demo.Exec.LDT.BadTSS         EQU       Demo.Exec.LDT.Pos
Demo.Exec.LDT.BadTSS.TSS     EQU       Demo.Exec.LDT.Pos + x86.Desc.Size
;Demo.Exec.LDT.BadTSS.Stack   x86.Desc.Mem  0, 0, 0, 0 ; Stack for BadTSS Fault handler
;Demo.Exec.LDT.BadTSS.TSS     x86.Desc.Mem  0, 0, 0, 0 ; Alias for TSS to read Backlink
;Demo.Exec.LDT.BadTSS.Alias   x86.Desc.Mem  0, 0, 0, 0 ; Alias for Faulting TSS

%assign              Demo.Exec.LDT.Pos Demo.Exec.LDT.Pos + 3 * x86.Desc.Size

; Note that this LDT cannot grow during run-time - there's other stuff directly after it!

%if (Demo.Exec.LDT.Alias - Demo.Exec.LDT) != Demo.DT.Alias
%error "Invalid Executive LDT alias"
%endif
