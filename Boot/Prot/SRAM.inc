;
; Boot/SRAM.inc
;

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Prot

                USE32

%ifdef USE_SRAM
Boot.Prot.SRAM:
; Initialise SRAM with known value - then test for it
                CLD
                MOV             EAX, "SRAM"
                MOV             ECX, SRAM.Size / 4
                MOV             EDI, SRAM.Start
                REP             STOSD

                MOV             ECX, SRAM.Size / 4
                MOV             EDI, SRAM.Start
                REPE            SCASD
                MOV             EBX, `S!\r\n`
                LEA             ESI, [EDI - x86.DWORD.Size]
                JNE             Boot.Fatal.Hex

                MOV             EBX, `S:= `
                MOV             ESI, SRAM.Start
                CALL            Hex
                MOV             EBX, `0x\r\n`
                MOV             ESI, SRAM.Size
                CALL            Hex
%endif
