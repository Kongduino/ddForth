: getkey
  qkey
  dup 27 =
  IF
    qkey qkey
    * * DUP DUP . 167076 =
    IF
      DROP 14 ( left arrow )
    THEN
      DUP 164619 =
      IF
        DROP 15 ( right arrow )
      THEN
        DUP 159705 =
        IF
          DROP 16 ( up arrow )
        THEN
          DUP 162162 =
          IF
            DROP 17 ( down arrow )
          THEN
          ELSE
        ELSE
      ELSE
    ELSE
  THEN
  ELSE
;

clean
." Enter text: "
BEGIN
  getkey
  DUP . EMIT 32 emit


1 TRUE WHILE


