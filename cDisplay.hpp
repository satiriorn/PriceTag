#pragma once
#include <GxEPD2_3C.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "bitmaps/Bitmaps3c104x212.h" // 2.13" b/w/r
#include <qrcode.h>


class cDisplay{
  public:
    cDisplay();
    void DrawQRcode();
    void DrawText();
    
  private:
    U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
    QRCode qrcode;
};
