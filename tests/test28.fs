uclose supp_args 0 pick strint 1 pick ( 115200 s" /dev/tty.usbserial-110" ) UOPEN
( Let's use the supplementary args )
clean

: SETUP_BASE s" AT+SETCFG=0,0,1,1\r\n" uwrite 1 sleep ;
: SAVE_CFG S" AT+SAVE\r\n" 3 sleep ;


SETUP_BASE UINQ DUP . ." bytes waiting" CR
UREADRAW hexdump cr 3 sleep
SAVE_CFG UINQ DUP . ." bytes waiting" CR
UREADRAW hexdump cr
