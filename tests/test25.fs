9600 s" /dev/tty.usbmodem21301" UOPEN
clear UREADL 44 CSPLIT SREVERSE .S
0 var chunks
begin
  UREADL STRIPSTR DUP cs 44 csplit
  SREVERSE DUP 0 > IF
    ." \tchunks:\t"
    DUP chunks swap ! chunks ? cr
    swap DUP s" $GPGSV" S= IF
      ." \t-----> Satellite Info.\n"
    THEN
    ELSE
    clear
  THEN ELSE
  1 1 =
while
GPS fix data