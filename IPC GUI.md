# IPC GUI in ddForth

The principle stays more of less the same, but in reverse: the Xojo app is the server (it uses .Listen() and sits there). The C++ code needs to listen() instead of connect() – check that's how it works.

After that, ddForth must take over: the second half of the C++ code must be rewritten in ddForth (plus some C++).

```forth
	<client_fd> GUI_Start
	( Add some code to check that we're ready to go... )
	s" TAGADA" s" Click me!" 20 320 -1 -1 GUI_Button
	s" TOGODO" 20 20 400 300 3 GUI_Listbox
	s" PM00" 120 320 120 -1 GUI_PopupMenu
	5 0 DO
		s" PM00" s" Choice " I INTSTR STR+ ( "PM00" "Choice x" ) GUI_AddPMrow
	LOOP
	
	BEGIN
		GUI_ANY ( is there a string – or more – incoming? )
		IF
			GUI_READLINE 124 ( | ) CSPLIT
			( s0 s1 s2 s3... n )
			0 PICK ( BT / LB / etc )
			DUP s" BT" = IF
				DROP BT_CALLBACK ( user defined )
			THEN
				DUP s" LB" = IF
					DROP LB_CALLBACK ( user defined )
				THEN
					DUP s" PM" = IF
						DROP PM_CALLBACK ( user defined )
					THEN
					ELSE
				ELSE
			ELSE ( until I fix case... )
		THEN
		ELSE
	1 WHILE
```




