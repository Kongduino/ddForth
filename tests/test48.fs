s" ls" plugin
s" ./" ls
s" .cpp" FILSTR
( Only *.cpp files are now on the stack )
s" myLS" varray s" myLS" sortv
( Let's use this to create a VARRAY: file0 file1 file2 file3 file4 5 s" vName" VARRAY )

s" myLS" len> 0 do
  ( From 0 to length of varray )
  i . ( Prints number )
  i s" myLS" IX> . cr ( Prints line I and CR )
loop
