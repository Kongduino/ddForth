uclose supp_args 0 pick strint 1 pick ( 115200 s" /dev/tty.usbserial-110" ) UOPEN
( Let's use the supplementary args )
clean clear

: revhex 0 var mylen lenstr 2 / mylen swap ! mylen @ 0 do i 2 * 2 substr swap loop drop mylen @ sreverse s" " strjoin ;
: distance 5 pick 0 8 substr swap drop DUP . ." : " revhex hex2num 10 / ;
: cm2m 1.0 * 100.0 / floatstr s" ." splitd depth 2 - pick 0 2 substr swap drop depth 2 - place s" ." strjoin s" \ m" str+ ;
: cmORm DUP 99 > IF cm2m . THEN . ." cm" ELSE CR CR ;

clean clear

( s" 436D644D3A345B1748000000000000BA018C0F000000000000000000000000000000000000000000000000000000000000008C0F00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000BF0D0A" )

UFLUSH
BEGIN
  UINQ 0> IF
    10 UDISCARDUNTIL
    1 sleep
    ureadhexl UPPERSTR 0 14 substr
  THEN
    s" "
  ELSE
  s" 436D644D3A345B" s= IF
    14 188 substr swap drop
    8 4 4 2 2 64 2 64 2 2 2 2 8 8 8 2 4 17 slicer
    distance
    ." Tag distance: " cmORm
  THEN
  ELSE
  clear
  1 1 =
WHILE
