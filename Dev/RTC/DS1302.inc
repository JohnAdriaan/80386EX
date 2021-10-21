;
; Dev/RTC/DS1302.inc
;

Dev.RTC.DS1302:

Dev.RTC.DS1302.Data.Len     EQU             31
Dev.RTC.DS1302.Clock.Len    EQU             8   ; Can't burst Trickle

Dev.RTC.DS1302.Cmd.Enable       EQU         1000_0000b
Dev.RTC.DS1302.Cmd.Data         EQU         0100_0000b
Dev.RTC.DS1302.Cmd.Clock        EQU         0000_0000b
Dev.RTC.DS1302.Cmd.Addr.Mask    EQU         0011_1110b
Dev.RTC.DS1302.Cmd.Addr.Shift   EQU         1
Dev.RTC.DS1302.Cmd.Addr.Burst   EQU         .Cmd.Addr.Mask
Dev.RTC.DS1302.Cmd.Read         EQU         0000_0001b
Dev.RTC.DS1302.Cmd.Write        EQU         0000_0000b

                STRUC           Dev.RTC.DS1302.Clock
.Sec            RESB            1
.Min            RESB            1
.Hour           RESB            1
.Date           RESB            1
.Month          RESB            1
.Day            RESB            1
.Year           RESB            1
                ENDSTRUC

Dev.RTC.DS1302.Sec      EQU         Dev.RTC.DS1302.Clock.Sec   << 1
Dev.RTC.DS1302.Min      EQU         Dev.RTC.DS1302.Clock.Min   << 1
Dev.RTC.DS1302.Hour     EQU         Dev.RTC.DS1302.Clock.Hour  << 1
Dev.RTC.DS1302.Date     EQU         Dev.RTC.DS1302.Clock.Date  << 1
Dev.RTC.DS1302.Month    EQU         Dev.RTC.DS1302.Clock.Month << 1
Dev.RTC.DS1302.Day      EQU         Dev.RTC.DS1302.Clock.Day   << 1
Dev.RTC.DS1302.Year     EQU         Dev.RTC.DS1302.Clock.Year  << 1
Dev.RTC.DS1302.WP       EQU         0000_1110b   ; Write Protect
Dev.RTC.DS1302.Trickle  EQU         0001_0000b

Dev.RTC.DS1302.Sec.CH   EQU         1000_0000b   ; Clock Halt
Dev.RTC.DS1302.Sec.10   EQU         0111_0000b   ; Seconds Tens
Dev.RTC.DS1302.Sec.1    EQU         0000_1111b   ; Seconds Ones

Dev.RTC.DS1302.Min.10   EQU         0111_0000b   ; Minutes Tens
Dev.RTC.DS1302.Min.1    EQU         0000_1111b   ; Minutes Ones

Dev.RTC.DS1302.Hour.10  EQU         0011_0000b   ; Hour Tens
Dev.RTC.DS1302.Hour.1   EQU         0000_1111b   ; Hour Ones
Dev.RTC.DS1302.Hour.AM  EQU         0000_0000b   ; Hour AM
Dev.RTC.DS1302.Hour.PM  EQU         0010_0000b   ; Hour PM
Dev.RTC.DS1302.Hour.12  EQU         1000_0000b   ; 12 Hour Time
Dev.RTC.DS1302.Hour.24  EQU         0000_0000b   ; 24 Hour Time

Dev.RTC.DS1302.Date.10  EQU         0011_0000b   ; Date Tens
Dev.RTC.DS1302.Date.1   EQU         0000_1111b   ; Date Ones

Dev.RTC.DS1302.Month.10 EQU         0001_0000b   ; Month Tens
Dev.RTC.DS1302.Month.1  EQU         0000_1111b   ; Month Ones

Dev.RTC.DS1302.Day.1    EQU         0000_0111b   ; Day Ones

Dev.RTC.DS1302.Year.10  EQU         1111_0000b   ; Year Tens
Dev.RTC.DS1302.Year.1   EQU         0000_1111b   ; Year Ones

Dev.RTC.DS1302.WP.Deny  EQU         1000_0000b
Dev.RTC.DS1302.WP.Allow EQU         0000_0000b

Dev.RTC.DS1302.Trickle.TCS          EQU     1010_0000b
Dev.RTC.DS1302.Trickle.Diode.1      EQU     0000_0100b
Dev.RTC.DS1302.Trickle.Diode.2      EQU     0000_1000b
Dev.RTC.DS1302.Trickle.Resistor.2   EQU     0000_0001b
Dev.RTC.DS1302.Trickle.Resistor.4   EQU     0000_0010b
Dev.RTC.DS1302.Trickle.Resistor.8   EQU     0000_0011b
Dev.RTC.DS1302.Trickle.Disable      EQU     0101_1100b
