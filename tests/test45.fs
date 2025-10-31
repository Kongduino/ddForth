: drawstr VAR tempIMGname s" " splitd DUP 0 DO I pick tempIMGname @ DRAWCHR LOOP 0 DO drop loop s" tempIMGname" forget ;

s" traversin" plugin
s" map" s" map.png" loadpng

clear
120 180 TEXTXY
255 0 0 255 DRAWRGBA
s" FreeMono18pt7b" SETFONT
s" ABCD" s" map" drawstr

clear
s" FreeMonoBold18pt7b" SETFONT
120 240 TEXTXY
255 0 0 127 DRAWRGBA
s" ABCD" s" map" drawstr
600 450 TEXTXY
255 0 0 255 DRAWRGBA
s" OVERFLOW xy" s" map" drawstr

clear
320 280 TEXTXY
255 0 0 255 DRAWRGBA
s" FreeSansBold12pt7b" SETFONT
s" Kongduino" s" map" drawstr

s" map" s" map_text.png" savepng
clear
