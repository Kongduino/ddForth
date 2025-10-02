( LISTENING )
uclose supp_args 0 pick strint 1 pick ( 115200 s" /dev/tty.usbserial-110" ) UOPEN
( Let's use the supplementary args )
clean clear

: ISPACKET UREADRAW DUP 0 6 substr s" CmdM:4" S= IF STEP2 THEN drop ." Pfui!\n\n" ELSE ;
: STEP2 ." STEP2\n" .S 7 91 substr .S ;

: DISTANCE 17 4 substr s" " ssplit ;

BEGIN
  UINQ DUP 0> IF
    ISPACKET clear
  THEN
    ( DROP )
  ELSE
1 1 = WHILE
