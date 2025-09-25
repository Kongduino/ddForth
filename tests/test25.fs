: GPRMC ." \t-----> " swap 1 - DUP 1- SPICK s" " S= IF ." No data!" THEN cs ELSE cr clear ;
: GPGSV cs ." : " 1 spick STRINT . ." message" 1 spick strint 1 > IF ." s.\n" then ." .\n" else ( .S ) clear ;
: GPGSA cs cr ;
: GPTXT cs ." \t-----> " 4 spick cs cr clear ;
: GPGLL cs ." \t-----> No need." cr clear ;
: GPVTG cs ." \t-----> No need." cr clear ;
: GPGGA cs ." \t-----> " 1 spick cs cr clear ;

9600 s" /dev/tty.usbmodem21301" UOPEN
clear UREADL 44 CSPLIT
0 var chunks
begin
  UREADL STRIPSTR 44 csplit DUP 0 > IF
      0 spick cs ." \tchunks:\t" DUP . CR
      0 spick 1 6 substr exec
  THEN
  ELSE
  clear
  1 1 =
while
