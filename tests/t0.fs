255 255 255 CLS
0 0 0 DRAWCOLOR
0 150 WIDTH 150 DRAWLINE
0 151 WIDTH 151 DRAWLINE
48 0 48 185 DRAWLINE
49 0 49 185 DRAWLINE

0 1 s" saveY0" VARRAY
0 1 s" saveY1" VARRAY

: dottedLine ( py lastX firstX ) DO DUP I SWAP DUP I 5 + SWAP DRAWLINE .S I 5 + >R LOOP clear ;

10 0 24 12 0 0 66 .DT" 100"
10 150 75 1.5 * INT - 6 - 24 12 0 0 66 .DT" 75"
10 150 50 1.5 * INT - 6 - 24 12 0 0 66 .DT" 50"
10 150 25 1.5 * INT - 6 - 24 12 0 0 66 .DT" 25"

99 99 99 DRAWCOLOR
75 1.5 * 150 SWAP - INT WIDTH 50 .S dottedLine
50 1.5 * 150 SWAP - INT WIDTH 50 dottedLine
25 1.5 * 150 SWAP - INT WIDTH 50 dottedLine

50 ( X index )
random 80 mod 40 - 10.0 / 28.0 + ( random Y index )
1.5 * INT 150 swap - DUP 0 s" saveY0" >IX
DRAWPIXEL
50 ( X index )
random 100 mod 50 - 10.0 / 73.0 + ( random Y index )
1.5 * INT 150 swap - DUP 0 s" saveY1" >IX
DRAWPIXEL

WIDTH 50 - 51 DO
255 0 0 DRAWCOLOR
  I 1 - ( X index )
  0 s" saveY0" IX>
  I
  random 80 mod 40 - 10.0 / 28.0 + ( random Y index )
  1.5 * INT 150 swap - DUP 0 s" saveY0" >IX
  DRAWLINE

0 0 255 DRAWCOLOR
  I 1 - ( X index )
  0 s" saveY1" IX>
  I
  random 100 mod 50 - 10.0 / 73.0 + ( random Y index )
  1.5 * INT 150 swap - DUP 0 s" saveY1" >IX
  DRAWLINE
LOOP
