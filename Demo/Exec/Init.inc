;
; Exec/Init.inc
;

; This finalises the initialisation of the CPU now that we're in Protected Mode.
; The Segment registers are loaded with PM-friendly values, and other registers
; are set up as needed.
;
; This is also the time to initialise the global Data area - at least, that part
; that wasn't set up by Boot. There was no real need to store the data in the
; Boot image - most of it is run-time generated anyway.
;
; And since this is a multi-tasking system that uses TSSs, the Task Register
; needs to be set up, to store the current context before switching to the new
; one. That means allocating a TSS, and initialising it with sensible values.

Exec.Init:
                ; Initialise EFlags
                PUSH   DWORD    x86.EFlags.1
                POPFD

                ; Point to GDT. (With GS! How apt!)
                MOV             AX, x86.Selector(Demo.GDT.Alias, .GDT, .RPL0)
                MOV             GS, AX           ; Try to keep this here

                ; Point to SRAM
                MOV             AX, x86.Selector(Demo.GDT.SRAM, .GDT, .RPL0)
                MOV             FS, AX           ; Try to keep this here

                ; Point to global Data
                MOV             AX, x86.Selector(Demo.GDT.Data, .GDT, .RPL0)
                MOV             DS, AX           ; Try to keep this here

                ; Initialise RAM variables
                MOV    DWORD    [WORD Data.RAM], Demo.First
                INC             EBP                     ; Convert Limit to Size
%ifdef USE_DOUBLEBUFFER_DRAM
                SUB             EBP, ((Screen.Size + x86.PAGE.Size - 1) & ~x86.PAGE.Mask) - 1
%endif
                MOV             [WORD Data.RAMTop], EBP ; Save away new top of RAM

                XOR             EAX, EAX
                MOV             [WORD Data.Secs], EAX
                MOV             [WORD Data.Ticks], EAX

                ; Initialise Keyboard variables
                MOV     BYTE    [WORD Data.Key.Shifts], 0

%ifdef USE_DOUBLEBUFFER
                ; First, allocate Video double-buffer
%ifdef USE_DOUBLEBUFFER_DRAM
                MOV             EAX, EBP          ; Use (last) part of SRAM: it's faster than DRAM
%else
                MOV             EAX, (SRAM.Start + SRAM.Size - Screen.Size) & ~x86.PAGE.Mask
%endif
                MOV             ECX, Screen.Size
                MOV             DL, x86.Type.Mem(.Data, .DPL3, .RW) ; Allow anyone to access it
                MOV             DH, x86.Gran.Mem(.Byte, .Small)
                CALL            Exec.Alloc.GDT.Mem
;               CMP             AX, Demo.GDT.Video ; Assume this will work!
%endif ; USE_DOUBLEBUFFER

                ; Now allocate Exec's TSS. Use Exec's LDT!
                MOV             AX, x86.Selector(Demo.GDT.Exec.LDT, .GDT, .RPL0)
                CALL            Exec.Alloc.TSS   ; Assume this will work!
                MOV             AH, 0            ; Not a System TSS
                CALL            Exec.Alloc.TSS.Enable

                ; Now any Task Switch will let Exec resume later
                LTR             BX

                RET
