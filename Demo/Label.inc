;
; Demo/Label.inc
;

; This puts human-readable strings into the EPROM for versioning

                SEGMENT         Demo

                DB              Version.Author, "'s"
                ALIGN           Align.Para, DB ' '
                DB              Version.Demo
                ALIGN           Align.Para, DB ' '

                DB              'v', Version.String
                DB              ' ', Version.Copyright
                ALIGN           Align.Para, DB ' '

%substr         Demo.Date       __?DATE?__ 3,-1
                DB              Demo.Date
                DB              __?TIME?__

