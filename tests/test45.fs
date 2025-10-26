: drawstr VAR tempIMGname VAR tempFONTname s" " splitd DUP 0 DO I pick tempFONTname @ tempIMGname @ DRAWCHR LOOP s" tempFONTname" forget s" tempIMGname" forget ;

s" plugin/traversin.dylib" plugin
s" map" s" map.png" loadpng

clear
120 180 TEXTXY
255 0 0 255 DRAWRGBA
s" ABCD" s" FreeMono18pt7b" s" map" drawstr
s" map" s" map_text.png" savepng

clear
120 240 TEXTXY
255 0 0 127 DRAWRGBA
s" ABCD" s" FreeMonoBold18pt7b" s" map" drawstr

clear
320 280 TEXTXY
255 0 0 255 DRAWRGBA
s" Kongduino" s" FreeSansBold12pt7b" s" map" drawstr

clear
600 450 TEXTXY
255 0 0 255 DRAWRGBA
s" OVERFLOW xy" s" FreeMonoBold18pt7b" s" map" drawstr

s" map" s" map_textA.png" savepng
clear
