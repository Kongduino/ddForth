( TAG SETUP )
uclose supp_args 0 pick strint 1 pick ( 115200 s" /dev/tty.usbserial-110" ) UOPEN
( Let's use the supplementary args )
clean

: SETUP_TAG s" AT+SETCFG=3,0,1,1\r\n" DUP cs cr uwrite 1 sleep ;
: SAVE_CFG S" AT+SAVE\r\n" DUP cs cr 3 sleep ;
: GET_SENSOR S" AT+GETSENSOR\r\n" DUP cs cr 3 sleep ;

SETUP_TAG UINQ DUP . ." bytes waiting" CR
UREADRAW hexdump cr UFLUSH
SAVE_CFG UINQ DUP . ." bytes waiting" CR
UREADRAW hexdump cr
GET_SENSOR UINQ DUP . ." bytes waiting" CR
UREADRAW hexdump cr
