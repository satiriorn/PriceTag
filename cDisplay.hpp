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
    void DrawQRcode(Data* data);
    void DrawText(Data* data);
    
  private:
    U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
    QRCode qrcode;
};
