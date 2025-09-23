100 var startCol
255 255 255 CLS
BLACK DRAWCOLOR
0 150 WIDTH 150 DRAWLINE
0 151 WIDTH 151 DRAWLINE
startCol @ 2 - 0 startCol @ 2 - 210 DRAWLINE
startCol @ 1 - 0 startCol @ 1 - 210 DRAWLINE

0 1 s" saveY0" VARRAY
0 1 s" saveY1" VARRAY

: dottedLine ( py lastX firstX ) DO DUP I SWAP DUP I 5 + SWAP DRAWLINE STACK I 5 + >R LOOP clear ;

startCol @ 20 - 150 75 1.5 * INT - 8 - 0 0 66 .DT" 75"
startCol @ 20 - 150 50 1.5 * INT - 8 - 0 0 66 .DT" 50"
startCol @ 20 - 150 25 1.5 * INT - 8 - 0 0 66 .DT" 25"

99 99 99 DRAWCOLOR
75 1.5 * 150 SWAP - INT WIDTH startCol @ STACK dottedLine
50 1.5 * 150 SWAP - INT WIDTH startCol @ dottedLine
25 1.5 * 150 SWAP - INT WIDTH startCol @ dottedLine

startCol @ ( X index )
random 80 mod 40 - 10.0 / 28.0 + ( random Y index )
1.5 * INT 150 swap - DUP 0 s" saveY0" >IX
DRAWPIXEL
startCol @ ( X index )
random 100 mod 50 - 10.0 / 73.0 + ( random Y index )
1.5 * INT 150 swap - DUP 0 s" saveY1" >IX
DRAWPIXEL

WIDTH 50 - startCol @ 1 + DO
255 0 0 DRAWCOLOR
  I 1 - ( X index )
  0 s" saveY0" 0 IX>
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

255 0 0 DRAWCOLOR
startCol @ 20 + 160 48 16 FILLRECT

0 0 255 DRAWCOLOR
startCol @ 20 + 190 48 16 FILLRECT

startCol @ 75 + 160 RED .DT" Temperature"
startCol @ 75 + 190 BLUE .DT" RH%"

WIDTH 2 / 210 BLACK s" THE END" .DST

