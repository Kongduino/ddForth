  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  display.setRotation(1);
  display.setTextWrap(true);
  display.setTextSize(1.0);
  display.setTextFont(&fonts::FreeMono12pt7b);
  display.setTextColor(TFT_WHITE);
  xxxxxx = snprintf(
    (char *)msg, 255,
    " ddForth %d.%d", v0, v1);
  Matrix();
  delay(2000);
  display.clear();
  xxxxxx = snprintf(
    (char *)msg, 255,
    "ddForth v%d.%d.%d", v0, v1, v2);
  cout << msg << endl;
  display.println(msg);
