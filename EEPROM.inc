;
; EEPROM.inc
;

; To maintain EEPROM health, the wide unused area between the bottom and top of
; the code should be set to 0FFh rather than 000h. That's what this segment does.

                SEGMENT         EEPROM  ALIGN=1
