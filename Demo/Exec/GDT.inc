;
; Exec/GDT.inc
;

; The GDT is the only Descriptor Table that can store certain system tables,
; like Local Descriptor Tables and TSSes. If you think about it, that's because
; at Task Switch time, the GDT is the only place those entries will be guaranteed
; to be, regardless of which Task is currently running.
; That logic also applies to Code Segments for interrupt handlers.
; And those Interrupt handlers may need access to global Data, and the Screen...
; Everything else can be stored in each Task's Local Descriptor Table.
;
; That means that the Executive has nothing: no Code to run, no Stacks to use,
; and no Data to reference. To solve this, we gave the Executive its own LDT.

                SEGMENT         Demo.GDT

                USE32

; This macro makes it easy to have a one-line invocation of GDT.Alloc
; The parameters are: GDT Base, GDT Limit
%macro                          Demo.GDT.Vars  2
%00                             ISTRUC         Demo.GDT.Alloc
AT Demo.GDT.Alloc.Free,         DW             0
AT Demo.GDT.Alloc.Limit,        DW             %2
AT Demo.GDT.Alloc.Pseudo.Base,  DD             %1
                                IEND
%endmacro

Demo.GDT.Alias.Base  EQU        Demo.GDT.Base
Demo.GDT.Alias.Limit EQU        (x86.GDT.Size.Max-1) >> x86.PAGE.Shift  ; Let's use Granular limits
Demo.GDT.Alias.Type  EQU        x86.Type.Mem(.Data, .DPL0, .RW)
Demo.GDT.Alias.Gran  EQU        x86.Gran.Mem(.Page, .Small)

Demo.GDT.Data.Base   EQU        Demo.Data.Base
Demo.GDT.Data.Limit  EQU        Demo.Data.Limit
Demo.GDT.Data.Type   EQU        x86.Type.Mem(.Data, .DPL0, .RW)
Demo.GDT.Data.Gran   EQU        x86.Gran.Mem(.Byte, .Big)

Demo.GDT.Screen.Base  EQU       Screen.Base
Demo.GDT.Screen.Limit EQU       Screen.Rows * Screen.Cols * 2 - 1
Demo.GDT.Screen.Type  EQU       x86.Type.Mem(.Data, .DPL0, .RW)
Demo.GDT.Screen.Gran  EQU       x86.Gran.Mem(.Byte, .Small)

Demo.GDT.Ints.Base   EQU        Demo.Ints.Base
Demo.GDT.Ints.Limit  EQU        Demo.Ints.Limit
Demo.GDT.Ints.Type   EQU        x86.Type.Mem(.Code, .DPL0, .RW) ; Uses lookup tables
Demo.GDT.Ints.Gran   EQU        x86.Gran.Mem(.Byte, .Def32)

Demo.GDT.Exec.LDT.Base  EQU     Demo.Exec.LDT.Base
Demo.GDT.Exec.LDT.Limit EQU     Demo.Exec.LDT.Limit
Demo.GDT.Exec.LDT.Type  EQU     x86.Type.Sys(.LDT, .DPL0, .286)
Demo.GDT.Exec.LDT.Gran  EQU     x86.Gran.Mem(.Byte, .Small)

Demo.GDT:
Demo.GDT.NULL     Demo.GDT.Vars Demo.GDT.Base, Demo.GDT.Limit
Demo.GDT.Alias    x86.Desc.Mem  Demo.GDT.Alias.Base,    Demo.GDT.Alias.Limit,    Demo.GDT.Alias.Type,    Demo.GDT.Alias.Gran
Demo.GDT.Data     x86.Desc.Mem  Demo.GDT.Data.Base,     Demo.GDT.Data.Limit,     Demo.GDT.Data.Type,     Demo.GDT.Data.Gran
Demo.GDT.Screen   x86.Desc.Mem  Demo.GDT.Screen.Base,   Demo.GDT.Screen.Limit,   Demo.GDT.Screen.Type,   Demo.GDT.Screen.Gran
Demo.GDT.Ints     x86.Desc.Mem  Demo.GDT.Ints.Base,     Demo.GDT.Ints.Limit,     Demo.GDT.Ints.Type,     Demo.GDT.Ints.Gran
Demo.GDT.Exec.LDT x86.Desc.Mem  Demo.GDT.Exec.LDT.Base, Demo.GDT.Exec.LDT.Limit, Demo.GDT.Exec.LDT.Type, Demo.GDT.Exec.LDT.Gran
Demo.GDT.Video    EQU           $

%if (Demo.GDT.Alias-Demo.GDT) != Demo.DT.Alias
%error "Invalid GDT alias"
%endif
