;
; x86/EX/CSU.inc
;

; These are the definitions for the 80386EX Chip Select Unit

; Pin Configuration
x86.EX.CSU.PINCFG         EQU   0_F826h           ; CS6-CS5 pins

; OR these together to form correct PINCFG value
x86.EX.CSU.PINCFG.C6      EQU   0
x86.EX.CSU.PINCFG.REFRESH EQU   x86.EX.PIN6
x86.EX.CSU.PINCFG.PE      EQU   0
x86.EX.CSU.PINCFG.TMR2    EQU   x86.EX.PIN5
x86.EX.CSU.PINCFG.DACK0   EQU   0
x86.EX.CSU.PINCFG.CS5     EQU   x86.EX.PIN4
x86.EX.CSU.PINCFG.EOP     EQU   0
x86.EX.CSU.PINCFG.CTS1    EQU   x86.EX.PIN3
x86.EX.CSU.PINCFG.DACK1   EQU   0
x86.EX.CSU.PINCFG.TXD1    EQU   x86.EX.PIN2
x86.EX.CSU.PINCFG.SRXCLK  EQU   0
x86.EX.CSU.PINCFG.DTR1    EQU   x86.EX.PIN1
x86.EX.CSU.PINCFG.SSIOTX  EQU   0
x86.EX.CSU.PINCFG.RTS1    EQU   x86.EX.PIN0

; Chip Select n Address High ports
x86.EX.CSU.CS0ADH         EQU   0_F402h              ; CS0 High Addr
x86.EX.CSU.CS1ADH         EQU   0_F40Ah              ; CS0 High Addr
x86.EX.CSU.CS2ADH         EQU   0_F412h              ; CS0 High Addr
x86.EX.CSU.CS3ADH         EQU   0_F41Ah              ; CS0 High Addr
x86.EX.CSU.CS4ADH         EQU   0_F422h              ; CS0 High Addr
x86.EX.CSU.CS5ADH         EQU   0_F42Ah              ; CS0 High Addr
x86.EX.CSU.CS6ADH         EQU   0_F432h              ; CS0 High Addr
x86.EX.CSU.UCSADH         EQU   0_F43Ah              ; Upper CS High Addr

; Chip Select Address High values
x86.EX.CSU.ADH.Shift      EQU   6                    ; Num bits SHR Addr
x86.EX.CSU.ADH.Mask       EQU   0_03FFh              ; Then AND Mask

; Chip Select Address Low ports
x86.EX.CSU.CS0ADL         EQU   0_F400h              ; CS0 low Addr
x86.EX.CSU.CS1ADL         EQU   0_F408h              ; CS0 Low Addr
x86.EX.CSU.CS2ADL         EQU   0_F410h              ; CS0 Low Addr
x86.EX.CSU.CS3ADL         EQU   0_F418h              ; CS0 Low Addr
x86.EX.CSU.CS4ADL         EQU   0_F420h              ; CS0 Low Addr
x86.EX.CSU.CS5ADL         EQU   0_F428h              ; CS0 Low Addr
x86.EX.CSU.CS6ADL         EQU   0_F430h              ; CS0 Low Addr
x86.EX.CSU.UCSADL         EQU   0_F43Ah              ; Upper CS Low Addr

; Chip Select Address Low values
x86.EX.CSU.ADL.Shift      EQU   10                   ; Num bits SHL Addr
x86.EX.CSU.ADL.Mask       EQU   0_F800h              ; Then AND Mask

x86.EX.CSU.ADL.CASMM      EQU   0000_0100_0000_0000b ; Only in SMM mode
x86.EX.CSU.ADL.BS8        EQU   0000_0000_0000_0000b ; Always 8-bit accesses
x86.EX.CSU.ADL.BS16       EQU   0000_0010_0000_0000b ; Default to 16-bit bus
x86.EX.CSU.ADL.IO         EQU   0000_0000_0000_0000b ; I/O access
x86.EX.CSU.ADL.MEM        EQU   0000_0001_0000_0000b ; Memory access
x86.EX.CSU.ADL.RDY        EQU   0000_0000_1000_0000b ; Wait for Bus READY
x86.EX.CSU.ADL.Wait       EQU   0000_0000_0001_1111b ; Number of wait states

; Chip Select Mask High ports
x86.EX.CSU.CS0MSKH        EQU   0_F406h              ; CS0 High Mask
x86.EX.CSU.CS1MSKH        EQU   0_F40Eh              ; CS0 High Mask
x86.EX.CSU.CS2MSKH        EQU   0_F416h              ; CS0 High Mask
x86.EX.CSU.CS3MSKH        EQU   0_F41Eh              ; CS0 High Mask
x86.EX.CSU.CS4MSKH        EQU   0_F426h              ; CS0 High Mask
x86.EX.CSU.CS5MSKH        EQU   0_F42Eh              ; CS0 High Mask
x86.EX.CSU.CS6MSKH        EQU   0_F436h              ; CS0 High Mask
x86.EX.CSU.UCSMSKH        EQU   0_F43Eh              ; Upper CS High Mask

; Chip Select Mask High values
x86.EX.CSU.MSKH.Shift     EQU   x86.EX.CSU.ADH.Shift ; Num bits SHR Addr
x86.EX.CSU.MSKH.Mask      EQU   x86.EX.CSU.ADH.Mask  ; Then AND Mask

; Chip Select Mask Low ports
x86.EX.CSU.CS0MSKL        EQU   0_F404h              ; CS0 low Mask
x86.EX.CSU.CS1MSKL        EQU   0_F40Ch              ; CS0 Low Mask
x86.EX.CSU.CS2MSKL        EQU   0_F414h              ; CS0 Low Mask
x86.EX.CSU.CS3MSKL        EQU   0_F41Ch              ; CS0 Low Mask
x86.EX.CSU.CS4MSKL        EQU   0_F424h              ; CS0 Low Mask
x86.EX.CSU.CS5MSKL        EQU   0_F42Ch              ; CS0 Low Mask
x86.EX.CSU.CS6MSKL        EQU   0_F434h              ; CS0 Low Mask
x86.EX.CSU.UCSMSKL        EQU   0_F43Ch              ; Upper CS Low Mask

; Chip Select Mask Low values
x86.EX.CSU.MSKL.Shift     EQU   x86.EX.CSU.ADL.Shift ; Num bits SHL Addr
x86.EX.CSU.MSKL.Mask      EQU   x86.EX.CSU.ADL.Mask  ; Then AND Mask

x86.EX.CSU.MSKL.CSSMM     EQU   x86.EX.CSU.ADL.CASMM ; In SMM or normal mode
x86.EX.CSU.MSKL.CSDIS     EQU   0000_0000_0000_0000b ; Disable chip select
x86.EX.CSU.MSKL.CSEN      EQU   0000_0000_0000_0001b ; Enable chip select
