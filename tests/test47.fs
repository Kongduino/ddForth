s" traversin" plugin
3 8 s" qr1" s" This is a text" QRCODE
s" qr1" s" qr1.png" savepng
s" qr1" imgsize .S
drop var myHeight var myWidth
myHeight @ . cr
myHeight @ 0 do
myWidth @ 0 DO I J s" qr1" pixel? drop drop drop drop
255 = IF 32 emit 32 emit THEN ." *" ELSE
LOOP cr loop
