//#define ENABLE_GxEPD2_GFX 1 
#include "cDisplay.hpp"
// Instantiate the GxEPD2_BW class for our display type 
GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT> display(GxEPD2_213c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW0213I5F
//GxEPD2_BW<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW0213I5F
#define SMALL_FONT u8g2_font_6x12_t_cyrillic//u8g2_font_cu12_t_cyrillic//u8g2_font_unifont_t_cyrillic//
#define MIDL_FONT  u8g2_font_10x20_t_cyrillic
#define LARGE_FONT u8g2_font_inr24_t_cyrillic

#define GxEPD_YELLOW 0xFFE0

cDisplay::cDisplay(){
  display.init(115200); 
  u8g2Fonts.begin(display);
}

void cDisplay::DrawText(Data* data){
  display.setRotation(1);
  u8g2Fonts.setFont(LARGE_FONT);
  if (display.epd2.WIDTH < 104) display.setFont(0); 
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    u8g2Fonts.setCursor(0, 30);
    u8g2Fonts.print(data->Title);
    u8g2Fonts.setCursor(0, 60);
    u8g2Fonts.print(String(data->Price));
    u8g2Fonts.setCursor(107, 60);
    u8g2Fonts.setFont(SMALL_FONT);
    u8g2Fonts.print("грн/шт");
    DrawQRcode(data);
    /*
    u8g2Fonts.setFont(MIDL_FONT);
    u8g2Fonts.print("Білий без ГМО");
    u8g2Fonts.setCursor(107, 60);
    u8g2Fonts.setFont(LARGE_FONT);
    u8g2Fonts.print("$15,50");
    */
  }
  while (display.nextPage());
}

void cDisplay::DrawQRcode(Data* data){
  uint8_t qrcodeData[qrcode_getBufferSize(5)];
  qrcode_initText(&qrcode, qrcodeData, 5, 0, data->QRlink.c_str());
  int offset_x = 5;
  int offset_y = 65;
  int p_width  = 1.25;
  for (int y = 0; y < qrcode.size; y++) {
    for (int x = 0; x < qrcode.size; x++) {
      int new_x = offset_x + (x * p_width);
      int new_y = offset_y + (y * p_width);
      if (qrcode_getModule(&qrcode, x, y)) 
          display.fillRect( new_x, new_y, p_width, p_width, GxEPD_BLACK);
        else 
          display.fillRect( new_x, new_y, p_width, p_width, GxEPD_WHITE);
     }
   }
}
