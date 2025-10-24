s" plugin/traversin.dylib" plugin
640 480 s" IMG" IMAGE
255 255 255 s" IMG" FILLIMG
30000 0 do
  randomi 640 mod ( x )
  randomi 480 mod ( y )
  random random random 255 ( r g b a )
  s" IMG" pixel
loop
100 0 do
  randomi 320 mod ( x )
  randomi 480 mod ( y )
  randomi 320 mod ( length )
  random random random 255 ( r g b a )
  s" IMG" hline
loop
100 0 do
  randomi 640 mod ( x )
  randomi 240 mod ( y )
  randomi 240 mod ( height )
  random random random 255 ( r g b a )
  s" IMG" vline
loop
150 50 do
  320 240 ( x y )
  I ( radius )
  random random random 255 ( r g b a )
  s" IMG" circle
3 +loop
150 50 do
  I I ( x y )
  I I ( width height )
  random random random 255 ( r g b a )
  s" IMG" rect
3 +loop

s" IMG" s" tagada.png" savepng
