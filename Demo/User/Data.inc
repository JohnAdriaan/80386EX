;
; User/Data.inc
;

; This module defines the Data Segment for the User Code. There will be one copy
; of this for every running program.

                  SEGMENT       Demo.User.Data  START=0  ALIGN=Align.Para  NOBITS

                  USE32

User.Data.Left    RESB          1               ; Left X co-ordinate
User.Data.Top     RESB          1               ; Top Y co-ordinate
User.Data.Width   RESB          1               ; Width of area
User.Data.Height  RESB          1               ; Height of area
User.Data.Row     RESD          1               ; Delta from one row to the next
User.Data.Num     RESD          1               ; Screen position for Num
User.Data.Turns   RESD          1               ; Number of Turns
User.Data.Ball    RESB          1               ; The ball to display
