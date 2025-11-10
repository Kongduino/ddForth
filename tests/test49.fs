s" traversin" plugin
3 24 s" qr0" s" This is a longer text, I want to try something out..." QRCODE
s" square" s" square.png" loadpng
s" qr0" IMGSIZE drop drop 2 / ( center of image )
( remember: qr codes are square )
s" square" IMGSIZE drop drop 2 / - dup ( half the size of "square" )
s" qr0" s" square" COPYIMG
s" qr0" s" qr0.png" savepng
