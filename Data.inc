;
; Data.inc
;

; This is the definition for the global Data Segment. Note that some
; values are populated at Boot

                 SEGMENT        Data  START=0  ALIGN=16  NOBITS

                 USE32

Data.RAM         RESD           1       ; Beginning of available RAM
Data.RAMTop      RESD           1       ; Top of RAM

Data.Key.Code    RESB           1       ; Storage for key scan-code
Data.Key.Shifts  RESB           1       ; Storage for current Key Shift states
