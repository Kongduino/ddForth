// #include <Wire.h>
// #include "HT_SSD1306Wire.h"

// bool lookup(string);
// bool lookupUC(string);
// bool lookupVAR(string);
// bool popFloatFromStack(float *);
// bool popFromLoopStack(int *);
// bool popIntegerFromJumpStack(int *);
// bool popIntegerFromStack(int *);
// bool popStringFromStack(string *);
// bool putFloatOnStack(float);
// bool putIntegerOnJumpStack(int);
// bool putIntegerOnStack(int);
// bool putStringOnStack(string);
// bool showStack();
// bool showVars();
// void initForth();
// void logJumpStackOverflow(char *);
// void logLoopStackOverflow(char *);
// void logUnknownBlock(char *);
// void logStack(char *);
// void logInconsistent(char *who);
// void logStackOverflow(char *who);
// void logThis();

// void initScreen();
// void printText(char *);
// void setColor(unsigned char);
// bool handleDrawLINE();

// #ifdef WIRELESS_STICK_V3
// static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_64_32, RST_OLED);
// // addr, freq, i2c group, resolution, rst
// #else
// static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);
// // addr, freq, i2c group, resolution, rst
// #endif

// void VextON(void) {
//   pinMode(Vext, OUTPUT);
//   digitalWrite(Vext, LOW);
// }

// void VextOFF(void) {
//   //Vext default OFF
//   pinMode(Vext, OUTPUT);
//   digitalWrite(Vext, HIGH);
// }

// void drawLines() {
//   display.clear();
//   for (int16_t i = 0; i < display.getHeight(); i += 4) {
//     display.drawLine(display.getWidth() - 1, 0, 0, i);
//     display.display();
//     delay(10);
//   }
//   for (int16_t i = 0; i < display.getWidth(); i += 4) {
//     display.drawLine(display.getWidth() - 1, 0, i, display.getHeight() - 1);
//     display.display();
//     delay(10);
//   }
//   delay(250);
// }

// void initScreen() {
//   Serial.println("initScreen");
//   VextON();
//   delay(100);
//   display.init();
//   display.clear();
//   display.display();
//   display.setContrast(255);
//   drawLines();
//   display.clear();
//   display.display();
//   display.setLogBuffer(4, 30);
// }

// void printText(char *txt) {
//   display.println(txt);
//   // Draw it to the internal screen buffer
//   display.drawLogBuffer(0, 0);
//   // Display it on the screen
//   display.display();
// }

// void setColor(unsigned char C) {
//   display.setColor((DISPLAY_COLOR)(C & 1));
// }

// bool handleDrawLINE() {
//   int x0, y0, x1, y1;
//   if (popIntegerFromStack(&y1) == false) {
//     logStackOverflow((char *)"handleDrawLINE y1");
//     return false;
//   }
//   if (popIntegerFromStack(&x1) == false) {
//     logStackOverflow((char *)"handleDrawLINE x1");
//     return false;
//   }
//   if (popIntegerFromStack(&y0) == false) {
//     logStackOverflow((char *)"handleDrawLINE y0");
//     return false;
//   }
//   if (popIntegerFromStack(&x0) == false) {
//     logStackOverflow((char *)"handleDrawLINE x0");
//     return false;
//   }
//   display.drawLine(x0, y0, x1, y1);
//   // display.display();
// }
