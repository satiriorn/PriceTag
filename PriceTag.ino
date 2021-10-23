//#define ENABLE_GxEPD2_GFX 0 // we won't need the GFX base class
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "cServer.hpp"
#include "bitmaps/Bitmaps104x212.h"
#include "bitmaps/Bitmaps3c104x212.h" // 2.13" b/w/r

// Instantiate the GxEPD2_BW class for our display type 
GxEPD2_BW<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW0213I5F

cServer* server;

void setup() {
  Serial.begin(115200);
  Serial.println(); 
  server = new cServer();
  server->ConnectWifi();
}
void loop() {

  //Serial.println("Wait 10s before next round...");
  //delay(10000);
}

const char HelloWorld[] = "Price Tag";
void helloWorld()
{
  //Serial.println("");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0); 
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  //Serial.println("helloWorld done");
}
