s" plugin/traversin.dylib" plugin
s" map" s" map.png" loadpng
s" A B C D" ssplit
120 180 TEXTXY
DUP 0 DO
  255 0 0 255
  I pick s" FreeMono18pt7b" s" map"
  DRAWCHR
LOOP
s" map" s" map_text.png" savepng

clear s" A L P H A" ssplit
120 240 TEXTXY
DUP 0 DO
  I 21 * 120 + 240 TEXTXY
  255 0 0 127
  I pick s" FreeMonoBold18pt7b" s" map"
  DRAWCHR
LOOP

clear s" K o n g d u i n o" ssplit
294 273 TEXTXY
DUP 0 DO
  255 0 0 255
  I pick s" FreeSansBold12pt7b" s" map"
  DRAWCHR
LOOP

clear s" O V E R F L O W x y" ssplit
600 450 TEXTXY
DUP 0 DO
  255 0 0 255
  I pick s" FreeMonoBold18pt7b" s" map"
  DRAWCHR
LOOP



s" map" s" map_textA.png" savepng

s" FreeMonoBold18pt7b" fontinfo


