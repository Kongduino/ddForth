: TestAction
VAR myAction ( Each of these commands )
VAR myTest   ( Takes the top of the stack )
VAR myArray  ( And saves it in a variable )
CR myArray @ DUP alist CR
( DUP is probably slightly faster, and less verbose than myArray @ )
len> 0 DO ( DUP for len>, the max of DO...LOOP )
	I myArray @ IX> ( Get the value at index I )
	DUP myTest @ EXEC IF ( Make a copy in case test is successful )
	  myAction @ EXEC I myArray @ ( reposition to value index name )
	  >IX
	THEN
	  DROP ( We didn't use the copy of the value, let's drop it )
	ELSE
LOOP
myArray @ alist CR
s" myAction" forget
s" myTest" forget
s" myArray" forget ( Clean up after yourself! )
;

1 -2 -3 4 5 -9 10 7 s" vv" varray

s" vv" s" 0 <" s" ABS 2 /"

.S TestAction