#include <Wire.h>
#include "HT_SSD1306Wire.h"

#ifdef WIRELESS_STICK_V3
static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_64_32, RST_OLED);
// addr, freq, i2c group, resolution, rst
#else
static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);
// addr, freq, i2c group, resolution, rst
#endif

void VextON(void) {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) {
  //Vext default OFF
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, HIGH);
}

void drawLines() {
  display.clear();
  for (int16_t i = 0; i < display.getHeight(); i += 4) {
    display.drawLine(display.getWidth() - 1, 0, 0, i);
    display.display();
    delay(10);
  }
  for (int16_t i = 0; i < display.getWidth(); i += 4) {
    display.drawLine(display.getWidth() - 1, 0, i, display.getHeight() - 1);
    display.display();
    delay(10);
  }
  delay(250);
}

void initScreen() {
  Serial.println("initScreen");
  VextON();
  delay(100);
  display.init();
  display.clear();
  display.display();
  display.setContrast(255);
  drawLines();
  display.clear();
  display.display();
  display.setLogBuffer(4, 30);
}

void printText(char *txt) {
  display.println(txt);
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
}