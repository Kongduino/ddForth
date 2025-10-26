: drawstr VAR tempIMGname s" " splitd DUP 0 DO I pick tempIMGname @ DRAWCHR LOOP s" tempIMGname" forget ;

s" plugin/traversin.dylib" plugin
s" map" s" map.png" loadpng

clear
120 180 TEXTXY
255 0 0 255 DRAWRGBA
s" FreeMono18pt7b" SETFONT
s" ABCD" s" map" drawstr
s" map" s" map_text.png" savepng

clear
120 240 TEXTXY
255 0 0 127 DRAWRGBA
s" FreeMonoBold18pt7b" SETFONT
s" ABCD" s" map" drawstr

clear
320 280 TEXTXY
255 0 0 255 DRAWRGBA
s" FreeSansBold12pt7b" SETFONT
s" Kongduino" s" map" drawstr

clear
600 450 TEXTXY
255 0 0 255 DRAWRGBA
s" FreeMonoBold18pt7b" SETFONT
s" OVERFLOW xy" s" map" drawstr

s" map" s" map_textA.png" savepng
clear
