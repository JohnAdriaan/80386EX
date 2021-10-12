;
; User/LDT.inc
;

; This defines the LDT that the User program needs.

                SEGMENT         Demo.User.LDT  START=0  ALIGN=Align.Para  NOBITS

                USE32

; All Stacks are Expand-Down. All Expand-Down segments need to either be
; 16-bit (Small) or Page-Granular. Since these aren't Page-sized, they have to
; be Small.
Demo.User.Stack3.Size EQU       0010h           ; Doesn't need much at all!
Demo.User.Stack0.Size EQU       0200h           ; Needs a bit more...

Demo.User.LDT:
Demo.User.LDT.Alloc  RESB       Demo.LDT.Alloc_size
Demo.User.LDT.Alias  RESB       x86.Desc.Size
Demo.User.LDT.Stack0 RESB       x86.Desc.Size
Demo.User.LDT.Stack3 RESB       x86.Desc.Size
Demo.User.LDT.Data   RESB       x86.Desc.Size
Demo.User.LDT.Code   RESB       x86.Desc.Size

%if (Demo.User.LDT.Alias-Demo.User.LDT) != Demo.DT.Alias
%error "Invalid User LDT alias"
%endif
