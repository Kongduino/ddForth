clean 1 1 posxy ." Enter a password"
clear s" " var result

1 3 posxy
BEGIN
  QKEY DUP DUP 60 1 posxy . 10 = SWAP CHR result @ +STR DUP result swap !
  42 cfill
  1 3 posxy cs
  result @ LENSTR 3 posxy DROP ( LENSTR preserves the string )
UNTIL CR
result @
1 17 posxy cs
1 3 posxy 
s" \ " result @ lenstr multstr drop
