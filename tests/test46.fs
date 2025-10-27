: drawstr VAR tempIMGname s" " splitd DUP 0 DO I strpick tempIMGname @ DRAWCHR LOOP 0 DO drop loop s" tempIMGname" forget ;
s" plugin/traversin.dylib" plugin
800 800 s" IMG" IMAGE
255 255 255 s" IMG" FILLIMG
s" FreeSans12pt7b" SETFONT

30 0 do randomi 600 mod 200 + randomi 800 mod loop
30 dup 1 - 0 do
  ." Color: " random 127 MOD 127 + dup . random 80 mod dup . random 128 mod dup . 255 DRAWRGBA CR
  ." \tFrom: " i 2 * pick dup . i 2 * 1 + pick dup . ." to "
  i 2 * 2 + pick dup . i 2 * 3 + pick dup . cr
  s" IMG" DLINE
  ." \tFrom: " i 2 * pick 1 + dup . i 2 * 1 + pick dup . ." to "
  i 2 * 2 + pick 1 + dup . i 2 * 3 + pick dup . cr
  s" IMG" DLINE
  ." \tFrom: " i 2 * pick 1 - dup . i 2 * 1 + pick dup . ." to "
  i 2 * 2 + pick 1 - dup . i 2 * 3 + pick dup . cr
  s" IMG" DLINE
  10 I 1 + 25 * TEXTXY
  s" From: " i 2 * pick INTSTR STR+ s" , " STR+ i 2 * 1 + pick INTSTR STR+ s" \ to " STR+
  i 2 * 2 + pick INTSTR STR+ s" , " STR+ i 2 * 3 + pick INTSTR STR+ s" IMG"
  drawstr
loop
s" IMG" s" map_poly.png" savepng
clear
