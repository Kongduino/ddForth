: DEC2DMS STRFLOAT 100.0 / DUP INT DUP . ." \*\ " SWAP - DUP 60 * INT DUP . ." ' " swap 60 * - 60 * INT . ." \"" ;

: xxGGA 60 1 posxy cs ." \ =====> UTC Time: " 1 STRPICK s" " S= IF ." Unknown!" clear THEN GPGGA1 ELSE ;
: GPGGA1 1 STRPICK 46 CSPLIT drop drop s" :" 2 DINSERT cs ." , Quality: " 6 STRPICK dup cs strint 0 = IF ." : Fix not available" clear THEN GPGGA2 ELSE ;
: GPGGA2 ." , SIV: " 7 STRPICK strint . 2 STRPICK cs 3 STRPICK cs ." , " 4 STRPICK cs 5 STRPICK cs cr clear ;

: xxGLL cr clear ;

: xxGSA 1 8 posxy .S 60 3 posxy cs ." \ =====> Mode MA: " 1 STRPICK cs ." , Mode 123: " 2 STRPICK dup cs strint 1 = IF ." : Fix not available" THEN ." D" ELSE cr clear ;

: xxGSV 1 8 posxy .S 60 5 posxy cs ." : message " 2 STRPICK cs ." / " 1 STRPICK strint . ." SIV: " 3 STRPICK strint dup . 0 > if ." PRN: " 4 STRPICK cs then else cr clear ;

: xxRMC 60 7 posxy cs ." \ =====>" 1 STRPICK s" " S= IF ." No data!" THEN ( 1 8 posxy .S ) 1 STRPICK 46 CSPLIT 74 7 posxy drop drop S" :" 2 dinsert cs ELSE cr clear ;

: xxTXT 1 8 posxy .S 60 9 posxy cs ." \ =====> " 4 STRPICK cs cr clear ;
: xxVTG cr clear ;
: xxZDA cr clear ;

: readDollar begin uReadC s" $" S= until CLEAR ureadl STRIPSTR DUP cs cr ;

uclose 9600 s" /dev/tty.usbmodem21301" UOPEN
clean 1 30 posxy clear ." Hello there..."
readDollar
readDollar
readDollar ureadl
clear
0 var chunks
begin
  readDollar
  1 30 posxy ." \                                  " 1 30 posxy
  .S DUP s" " S= IF
  THEN
    .S DUP CS 44 csplit
    0 STRPICK .S s" \tchunks:\t" STR+ cs DUP . CR
    0 STRPICK 2 6 substr s" xx" +STR exec
  ELSE
  clear
  1 1 =
while