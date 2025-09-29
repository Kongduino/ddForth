: DEC2DMS STRFLOAT 100.0 / DUP INT DUP . ." \*\ " SWAP - DUP 60 * INT DUP . ." ' " swap 60 * - 60 * INT . ." \"" ;
: xxTXT cs ." \t-----> " 4 STRPICK cs cr clear ;
: xxGLL cs ." \t-----> No need." cr clear ;
: xxVTG cs ." \t-----> No need." cr clear ;
: xxRMC ." \t-----> " swap 1 - DUP 1- STRPICK s" " S= IF ." No data!" THEN cs ELSE cr clear ;
: xxGSV cs ." : message " 2 STRPICK cs ." / " 1 STRPICK strint . ." SIV: " 3 STRPICK strint dup . 0 > if ." PRN: " 4 STRPICK cs then else cr clear ;

: xxGSA s" \t-----> Mode MA: " STR+ cs 1 STRPICK cs ." , Mode 123: " 2 STRPICK dup cs strint 1 = IF ." : Fix not available" THEN ." D" ELSE cr clear ;

: xxGGA cs ." \t-----> UTC Time: " 1 STRPICK s" " S= IF ." Unknown!" cr clear THEN xxGGA1 ELSE ;
: xxGGA1 1 STRPICK 46 CSPLIT drop drop s" :" 2 DINSERT cs ." , Qulaity: " DUP  14 > IF 6 STRPICK dup cs strint 0 = IF ." : Fix not available" cr clear THEN xxGGA2 ELSE ;
: xxGGA2 ." , SIV: " 7 STRPICK strint . 2 STRPICK cs 3 STRPICK cs ." , " 4 STRPICK cs 5 STRPICK cs cr clear ;


: readDollar begin uReadC s" $" S= until CLEAR ureadl STRIPSTR DUP cs cr ;

: showStack DEPTH 0 DO 60 I posxy  ;

uclose 9600 s" /dev/tty.usbmodem21301" UOPEN
clean 1 30 posxy clear ." Hello there..."
2 sleep
readDollar ureadl
clear

0 var chunks
begin
  readDollar 44 csplit
  DUP 1 30 posxy . DUP
  0 > IF
    showStack 1 1 posxy 0 STRPICK s" \tchunks:\t" STR+ 1 29 posxy cs DUP . CR
    0 STRPICK 2 6 substr s" xx" +STR exec
  THEN
  ELSE
  clear
  1 1 =
while
uclose