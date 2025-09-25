9600 s" /dev/tty.usbmodem21301" UOPEN
clear UREADL 44 CSPLIT SREVERSE
0 var chunks
begin
  UREADL LENSTR 0 > IF
    STRIPSTR DUP cs 44 csplit
    SREVERSE DUP 0 > IF
      ." \tchunks:\t"
      DUP chunks swap ! chunks ? cr
      swap DUP s" $GPGSV" S= IF
        ." \t-----> Satellite Info.\n"
        clear
      THEN
        DUP s" $GPTXT" S= IF
          ." \t-----> " cs ." : "
          drop drop drop drop drop 42 csplit drop drop cs clear cr
        THEN
          DUP s" $GPRMC" S= IF
            ." \t-----> GPS specific information.\n" clear
          THEN
          ELSE
        ELSE
      ELSE
      clear
    THEN ELSE
    clear
  ELSE
  1 1 =
while
GPS fix data
