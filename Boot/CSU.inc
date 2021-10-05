;
; Boot/CSU.inc
;

; Enable appropriate pins with their relevant peripheral

;-------------------------------------------------------------------------------
                SEGMENT         Boot.Real

                USE16

Boot.CSU:
                MOV             DX, x86.EX.CSU.PINCFG
                MOV             AX, x86.EX.CSU.PINCFG.REFRESH | \
                                    x86.EX.CSU.PINCFG.PE      | \
                                    x86.EX.CSU.PINCFG.CS5     | \
                                    x86.EX.CSU.PINCFG.EOP     | \
                                    x86.EX.CSU.PINCFG.DACK1   | \
                                    x86.EX.CSU.PINCFG.SRXCLK  | \
                                    x86.EX.CSU.PINCFG.SSIOTX
                OUT             DX, AX
