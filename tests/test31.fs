: revhex 0 var mylen lenstr 2 / mylen swap ! mylen @ 0 do i 2 * 2 substr swap loop drop mylen @ sreverse s" " strjoin ;
: distance 5 pick 0 8 substr swap drop revhex hex2num 10 / ;
: cm2m 1.0 * 100.0 / floatstr s" ." splitd depth 2 - pick 0 2 substr swap drop depth 2 - place s" ." strjoin s" \ m" str+ ;

cr cr cr
clear

s" 436D644D3A345BF38C0200000000008801740800000000000000000000000000000000000000000000000000000000000000740400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000AF0D0A"

14 1000 substr swap DROP 8 4 4 2 2 64 2 64 2 2 2 2 8 8 8 2 4 17 slicer
distance ." Tag distance: " DUP 99 > IF
  cm2m .
THEN
  . ." cm"
ELSE

clear
