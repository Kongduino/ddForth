s" plugin/traversin.dylib" plugin
s" map" s" map.png" loadpng
s" A B C D" ssplit
DUP 0 DO
  I 21 * 120 + 180 255 0 0 255 
  I pick s" FreeMonoBold18pt7b" s" map"
  DRAWCHR
LOOP
s" map" s" map_text.png" savepng

