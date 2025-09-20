255 255 255 CLS
0 0 0 DRAWCOLOR
0 150 400 150 DRAWLINE
0 151 400 151 DRAWLINE
48 0 48 185 DRAWLINE
49 0 49 185 DRAWLINE



0 1 s" saveY0" VARRAY
0 1 s" saveY1" VARRAY

50 ( X index )
random 30 mod 10.0 / 28.0 + ( random Y index )
INT 150 swap - DUP 0 s" saveY0" >IX
DRAWPIXEL
50 ( X index )
random 50 mod 10.0 / 53.0 + ( random Y index )
INT 150 swap - DUP 0 s" saveY1" >IX
DRAWPIXEL

150 51 DO
255 0 0 DRAWCOLOR
  I 1 - ( X index )
  0 s" saveY0" IX>
  I
  random 30 mod 10.0 / 28.0 + ( random Y index )
  INT 150 swap - DUP 0 s" saveY0" >IX
  DRAWLINE

0 0 255 DRAWCOLOR
  I 1 - ( X index )
  0 s" saveY1" IX>
  I
  random 50 mod 10.0 / 53.0 + ( random Y index )
  INT 150 swap - DUP 0 s" saveY1" >IX
  DRAWLINE
LOOP
