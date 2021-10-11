;
; x86/EX/CSU.inc
;

; These are the definitions for the 80386EX Chip Select Unit

                SEGMENT         IO

; Pin Configuration
x86.EX.CSU.PINCFG         EQU   0_F826h           ; CS6, CS5 pins

; OR these together to form correct PINCFG value
x86.EX.CSU.PINCFG.CS6     EQU   0
x86.EX.CSU.PINCFG.REFRESH EQU   x86.EX.PIN.6
x86.EX.CSU.PINCFG.PE      EQU   0
x86.EX.CSU.PINCFG.TMR2    EQU   x86.EX.PIN.5
x86.EX.CSU.PINCFG.DACK0   EQU   0
x86.EX.CSU.PINCFG.CS5     EQU   x86.EX.PIN.4
x86.EX.CSU.PINCFG.EOP     EQU   0
x86.EX.CSU.PINCFG.CTS1    EQU   x86.EX.PIN.3
x86.EX.CSU.PINCFG.DACK1   EQU   0
x86.EX.CSU.PINCFG.TXD1    EQU   x86.EX.PIN.2
x86.EX.CSU.PINCFG.SRXCLK  EQU   0
x86.EX.CSU.PINCFG.DTR1    EQU   x86.EX.PIN.1
x86.EX.CSU.PINCFG.SSIOTX  EQU   0
x86.EX.CSU.PINCFG.RTS1    EQU   x86.EX.PIN.0

; Chip Select group port addresses
x86.EX.CSU.CS0  EQU             0_F400h              ; Chip Select 0
x86.EX.CSU.CS1  EQU             0_F408h              ; Chip Select 1
x86.EX.CSU.CS2  EQU             0_F410h              ; Chip Select 2
x86.EX.CSU.CS3  EQU             0_F418h              ; Chip Select 3
x86.EX.CSU.CS4  EQU             0_F420h              ; Chip Select 4
x86.EX.CSU.CS5  EQU             0_F428h              ; Chip Select 5
x86.EX.CSU.CS6  EQU             0_F430h              ; Chip Select 6
x86.EX.CSU.UCS  EQU             0_F438h              ; Upper Chip Select

; Chip Select port group
                STRUC           x86.EX.CS
.ADL            RESW            1                    ; Address Low
.ADH            RESW            1                    ; Address High
.MSKL           RESW            1                    ; Mask Low
.MSKH           RESW            1                    ; Mask High
                ENDSTRUC

; Chip Select Address High field values
x86.EX.CSU.ADH.Mask       EQU   0_03FFh        ; AND Mask

%define         x86.EX.CSU.ADH.Value.Mem(addr)          \
                    (addr >> x86.DWORD.Hi) & x86.EX.CSU.ADH.Mask
%define         x86.EX.CSU.ADH.Value.IO(addr)           \
                    (addr >>  6) & x86.EX.CSU.ADH.Mask

; Chip Select Address Low field values
x86.EX.CSU.ADL.Mask       EQU   0_F800h              ; AND Mask

x86.EX.CSU.ADL.NOSMM      EQU   0000_0000_0000_0000b ; Not in SMM mode
x86.EX.CSU.ADL.CASMM      EQU   0000_0100_0000_0000b ; Only in SMM mode
x86.EX.CSU.ADL.BS8        EQU   0000_0000_0000_0000b ; Always 8-bit accesses
x86.EX.CSU.ADL.BS16       EQU   0000_0010_0000_0000b ; Default to 16-bit bus
x86.EX.CSU.ADL.IO         EQU   0000_0000_0000_0000b ; I/O access
x86.EX.CSU.ADL.MEM        EQU   0000_0001_0000_0000b ; Memory access
x86.EX.CSU.ADL.NORDY      EQU   0000_0000_0000_0000b ; Wait for Bus READY
x86.EX.CSU.ADL.RDY        EQU   0000_0000_1000_0000b ; Wait for Bus READY
x86.EX.CSU.ADL.Wait       EQU   0000_0000_0001_1111b ; Number of wait states

%define         x86.EX.CSU.ADL.Value.Mem(addr, smm, bus, rdy, wait) \
                    ((addr << 0) & x86.EX.CSU.ADL.Mask) | \
                    x86.EX.CSU.ADL. %+ smm     | \
                    x86.EX.CSU.ADL. %+ bus     | \
                    x86.EX.CSU.ADL.MEM         | \
                    x86.EX.CSU.ADL. %+ rdy     | \
                    (wait & x86.EX.CSU.ADL.Wait)
%define         x86.EX.CSU.ADL.Value.IO(addr, smm, bus, rdy, wait) \
                    ((addr << 10) & x86.EX.CSU.ADL.Mask) | \
                    x86.EX.CSU.ADL. %+ smm     | \
                    x86.EX.CSU.ADL. %+ bus     | \
                    x86.EX.CSU.ADL.IO          | \
                    x86.EX.CSU.ADL. %+ rdy     | \
                    (wait & x86.EX.CSU.ADL.Wait)

; Chip Select Mask High values
x86.EX.CSU.MSKH.Mask      EQU   x86.EX.CSU.ADH.Mask  ; AND Mask

%define         x86.EX.CSU.MSKH.Value.Mem(mask) \
                    (mask >> x86.DWORD.Hi) & x86.EX.CSU.MSKH.Mask
%define         x86.EX.CSU.MSKH.Value.IO(mask) \
                    (mask >>  6) & x86.EX.CSU.MSKH.Mask

; Chip Select Mask Low field values
x86.EX.CSU.MSKL.Mask      EQU   x86.EX.CSU.ADL.Mask  ; AND Mask

x86.EX.CSU.MSKL.NOSMM     EQU   x86.EX.CSU.ADL.NOSMM ; SMM as per ADL
x86.EX.CSU.MSKL.CSSMM     EQU   x86.EX.CSU.ADL.CASMM ; In SMM or normal mode
x86.EX.CSU.MSKL.CSDIS     EQU   0000_0000_0000_0000b ; Disable chip select
x86.EX.CSU.MSKL.CSEN      EQU   0000_0000_0000_0001b ; Enable chip select

%define         x86.EX.CSU.MSKL.Value.Mem(mask, smm, cs) \
                    ((mask << 0) & x86.EX.CSU.MSKL.Mask) | \
                    x86.EX.CSU.MSKL. %+ smm | \
                    x86.EX.CSU.MSKL. %+ cs

%define         x86.EX.CSU.MSKL.Value.IO(mask, smm, cs) \
                    ((mask << 10) & x86.EX.CSU.MSKL.Mask) | \
                    x86.EX.CSU.MSKL. %+ smm | \
                    x86.EX.CSU.MSKL. %+ cs
