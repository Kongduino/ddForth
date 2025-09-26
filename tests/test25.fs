: DEC2DMS STRFLOAT 100.0 / DUP INT DUP . ." \*\ " SWAP - DUP 60 * INT DUP . ." ' " swap 60 * - 60 * INT . ." \"" ;
: GPTXT cs ." \t-----> " 4 spick cs cr clear ;
: GPGLL cs ." \t-----> No need." cr clear ;
: GPVTG cs ." \t-----> No need." cr clear ;
: GPRMC ." \t-----> " swap 1 - DUP 1- SPICK s" " S= IF ." No data!" THEN cs ELSE cr clear ;
: GPGSV cs ." : message " 2 spick cs ." / " 1 spick strint . ." SIV: " 3 spick strint dup . 0 > if ." PRN: " 4 spick cs then else cr clear ;

: GPGSA cs ." \t-----> Mode MA: " 1 spick cs ." , Mode 123: " 2 spick dup cs strint 1 = IF ." : Fix not available" THEN ." D" ELSE cr clear ;

: GPGGA cs ." \t-----> UTC Time: " 1 spick s" " S= IF ." Unknown!" cr clear THEN GPGGA1 ELSE ;
: GPGGA1 1 spick 46 CSPLIT drop drop s" :" 2 DINSERT cs ." , Quality: " 6 spick dup cs strint 0 = IF ." : Fix not available" cr clear THEN GPGGA2 ELSE
: GPGGA2 ." , SIV: " 7 spick strint . 2 spick cs 3 spick cs ." , " 4 spick cs 5 spick cs cr clear ;

9600 s" /dev/tty.usbmodem21301" UOPEN
clear UREADL DUP cs 44 CSPLIT
0 var chunks
begin
  UREADL STRIPSTR 44 csplit DUP 0 > IF
      0 spick s" \tchunks:\t" STR+ cs DUP . CR
      0 spick 1 6 substr exec
  THEN
  ELSE
  clear
  1 1 =
while
