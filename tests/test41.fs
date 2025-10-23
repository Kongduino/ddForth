s" plugin/traversin.dylib" plugin
640 480 s" IMG" IMAGE
640 480 255 255 255 s" IMG" FILLIMG
30000 0 do 640 480 randomi 640 mod randomi 480 mod random random random 255 s" IMG" pixel loop
100 0 do 640 480 randomi 320 mod randomi 480 mod randomi 320 mod random random random 255 s" IMG" hline loop
100 0 do 640 480 randomi 640 mod randomi 240 mod randomi 240 mod random random random 255 s" IMG" vline loop
150 50 do 640 480 320 240 I random random random 255 s" IMG" circle 3 +loop
150 50 do 640 480 randomi 500 mod randomi 400 mod I I random random random 255 s" IMG" rect 3 +loop

640 480 s" IMG" s" tagada.png" savepng
