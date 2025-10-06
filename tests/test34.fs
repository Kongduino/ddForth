1 -2 -3 4 5 -9 10 7 s" vv" varray
CR s" vv" DUP DUP alist CR ( we DUP 2x, once for alist )
len> 0 DO ( once for DO...LOOP )
	DUP DUP I swap IX>
	DUP 0 < IF
	  ABS swap I swap ( reposition to value index name )
	  >IX
	THEN
	ELSE
	depth 1 > IF ( clean up the stack if need be )
	begin ( We only need once instance of "vv" )
	  DROP
	  depth 1 >
	WHILE
	THEN
	ELSE
LOOP
alist CR ( Since "vv" is on the stack, might as well use it )
