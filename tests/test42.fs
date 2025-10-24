s" plugin/traversin.dylib" plugin
640 640 s" IMG" IMAGE
255 255 255 s" IMG" FILLIMG
639 0 do
  I 0 639 I
  0 255 0 255
  s" IMG" dline
  639 I - 639 0 639 I -
  255 255 0 127
  s" IMG" dline
3 +LOOP

100 0 do
  270 270 I + 100
  255 0 255 127
  s" IMG" HLINE
loop

280 260 100 100
43 25 128 128
s" IMG" FILLRECT

s" IMG" s" test3.png" savepng
