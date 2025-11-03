s" traversin" plugin
3 8 s" qr0" s" This is a text" QRCODE
s" qr0" s" qr0.png" savepng
s" qr1" s" qr0.png" loadpng
s" qr1" imgsize .S
drop 8 / var myHeight 8 / var myWidth
myHeight @ . cr
myWidth @ 0 do
  myWidth @ 0 DO
    I . J . 
    I 8 * J 8 * s" qr1" pixel? drop drop drop drop
    dup .
    1 AND 48 + emit ELSE cr ." \t"
  LOOP qkey
  cr
LOOP
