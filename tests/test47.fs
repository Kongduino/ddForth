: drawstr VAR tempIMGname s" " splitd DUP 0 DO I pick tempIMGname @ DRAWCHR LOOP 0 DO drop loop s" tempIMGname" forget ;

s" traversin" plugin
3 8 s" qr0" s" This is a text" QRCODE
s" qr0" s" qr0.png" savepng
800 600 s" qr1" image
255 255 255 s" qr1" FILLIMG
10 10 s" qr1" s" qr0" COPYIMG
252 1 2 255 drawrgba
30 s" qr0" IMGSIZE drop swap drop 30 + .S TEXTXY
s" This is a text" s" qr1" drawstr
s" qr1" s" qr1.png" savepng
