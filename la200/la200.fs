: drawstr VAR tempIMGname s" " splitd DUP 0 DO I pick tempIMGname @ DRAWCHR LOOP 0 DO drop loop s" tempIMGname" forget ;

clean
s" traversin" plugin
3 12 s" temp" s" https://discord.gg/btnZ8BcH" QRCODE
s" temp" IMGSIZE drop drop 40 + DUP
s" CALM" image
255 255 255 s" CALM" FILLIMG
39 dup s" CALM" s" temp" COPYIMG
s" CALM" IMGSIZE drop 2 * swap s" final" image

s" FreeMonoBold18pt7b" SETFONT
68 32 TEXTXY
255 0 0 127 DRAWRGBA
s" Et le Discord ?" s" CALM" drawstr
0 0 255 255 DRAWRGBA
s" On y pense ?" s" " SPLITD dup
0 do 22 i 24 * 98 + TEXTXY i pick s" CALM" DRAWCHR loop clear
s" CALM" IMGSIZE drop drop 2 / 20 +
( center of image with offset: 20 = offset 40 ÷ 2 )
( remember: qr codes are square only need one size and DUP )
s" logo" s" la200/logo_s.png" loadpng
s" logo" IMGSIZE drop drop 2 / - DUP
( half the size of "square" )
s" CALM" s" logo" COPYIMG
." Copy CALM0\n"
0 0 .S s" final" s" CALM" COPYIMG

s" CALM" s" la200/CALM0.png" savepng

s" temp" IMGSIZE drop drop 40 + DUP
s" CALM1" image
255 255 255 s" CALM1" FILLIMG
39 dup s" CALM1" s" temp" COPYIMG
68 32 TEXTXY
255 0 0 127 DRAWRGBA
s" A chaque fois" s" CALM1" drawstr
0 0 255 255 DRAWRGBA
s" Tu oublies !" s" " SPLITD dup
0 do 22 i 24 * 98 + TEXTXY i pick s" CALM1" DRAWCHR loop clear

s" CALM1" IMGSIZE drop drop 2 / 20 +
( center of image with offset: 20 = offset 40 ÷ 2 )
s" logo1" s" la200/OuAlors.png" loadpng
s" logo1" IMGSIZE drop drop 2 / - DUP
( half the size of "square" )
s" CALM1" s" logo1" COPYIMG
." Copy CALM1\n"
s" CALM1" IMGSIZE drop drop 0 s" final" s" CALM1" COPYIMG

s" CALM1" s" la200/CALM1.png" savepng
s" final" s" la200/CALM2.png" savepng
s" la200/CALM2.png" fopen






."   /\\\\\\                               /\\\\\\\\\\\\\\\\\\         /\\\\\\\\\\\\\\        /\\\\\\\\\\\\\\        /\\\\\\            \n"
."   \\/\\\\\\                             /\\\\\\///////\\\\\\     /\\\\\\/////\\\\\\    /\\\\\\/////\\\\\\    /\\\\\\\\\\\\\\         \n"
."    \\/\\\\\\                            \\///      \\//\\\\\\   /\\\\\\    \\//\\\\\\  /\\\\\\    \\//\\\\\\  /\\\\\\\\\\\\\\\\\\       \n"
."     \\/\\\\\\              /\\\\\\\\\\\\\\\\\\              /\\\\\\/   \\/\\\\\\     \\/\\\\\\ \\/\\\\\\     \\/\\\\\\ \\//\\\\\\\\\\\\\\       \n"
."      \\/\\\\\\             \\////////\\\\\\          /\\\\\\//     \\/\\\\\\     \\/\\\\\\ \\/\\\\\\     \\/\\\\\\  \\//\\\\\\\\\\       \n"
."       \\/\\\\\\               /\\\\\\\\\\\\\\\\\\\\      /\\\\\\//        \\/\\\\\\     \\/\\\\\\ \\/\\\\\\     \\/\\\\\\   \\//\\\\\\       \n"
."        \\/\\\\\\              /\\\\\\/////\\\\\\    /\\\\\\/           \\//\\\\\\    /\\\\\\  \\//\\\\\\    /\\\\\\     \\///       \n"
."         \\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\//\\\\\\\\\\\\\\\\/\\\\  /\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  \\///\\\\\\\\\\\\\\/    \\///\\\\\\\\\\\\\\/       /\\\\\\     \n"
."          \\///////////////   \\////////\\//  \\///////////////     \\///////        \\///////        \\///     \n"

