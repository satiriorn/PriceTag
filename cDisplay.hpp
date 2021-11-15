#pragma once
#include <GxEPD2_3C.h>
//#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "bitmaps/Bitmaps3c104x212.h" // 2.13" b/w/r
#include "cServer.hpp"
#include <qrcode.h>

class cDisplay{
  public:
    cDisplay();
    void DrawQRcode(int id);
    void DrawText(Data* data, int id);
  private:
    void DrawSaleMode(Data* data);
    void DrawDescription(Data* data);
    void DrawWithoutSaleMode(Data* data);
    void DrawTitle(Data* data);
    void DrawMeasurement(Data* data);
    int Percent(float x, float y);
    String ReplaceFloat(String s);
    U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
    QRCode qrcode;
};
