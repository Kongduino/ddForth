s" plugin/traversin.dylib" plugin
s" map.png"
s" tests/test43.prefs" fload
s" https://maptoolkit.p.rapidapi.com/staticmap/?maptype=terrain&size=640x480&center=22.473167,113.960138&zoom=10&rapidapi-key="
mykey str+
CURLGETF
s" map" s" map.png" loadpng
30 25 do 318 238 I 255 0 0 255 s" map" circle LOOP
s" map" s" mapC.png" savepng
CR
