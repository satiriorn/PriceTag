#define ENABLE_GxEPD2_GFX 0 
#include "cDisplay.hpp"
// Instantiate the GxEPD2_BW class for our display type 
GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT> display(GxEPD2_213c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW0213I5F
//GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display(GxEPD2_213_B72(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEH0213B72
//#define SMALL_FONT u8g2_font_4x6_t_cyrillic//u8g2_font_6x12_t_cyrillic//u8g2_font_4x6_t_cyrillic//u8g2_font_cu12_t_cyrillic//u8g2_font_unifont_t_cyrillic//
#define MIDL_FONT  u8g2_font_7x13_t_cyrillic//u8g2_font_haxrcorp4089_t_cyrillic//u8g2_font_7x13_t_cyrillic//u8g2_font_unifont_t_cyrillic //
#define LARGE_FONT u8g2_font_inr24_t_cyrillic

#define GxEPD_YELLOW 0xFFE0

cDisplay::cDisplay(){
  display.init(115200);  
  u8g2Fonts.begin(display);
  display.setRotation(-1);
}

void cDisplay::DrawText(Data* data, int id){
  u8g2Fonts.setFont(LARGE_FONT);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);
  display.setFullWindow();
  display.firstPage();
  display.fillScreen(GxEPD_WHITE);
  DrawTitle(data);
  if(data->Sale)
    DrawSaleMode(data);
  else
    DrawWithoutSaleMode(data);
  DrawMeasurement(data);
  DrawDescription(data);
  DrawQRcode(id);
  display.nextPage();
}

void cDisplay::DrawTitle(Data* data){
    int pos = u8g2Fonts.getUTF8Width(String(data->Title).c_str());
    u8g2Fonts.setCursor((display.width() - pos)/ 2, 30);
    u8g2Fonts.print(data->Title);
  }

void cDisplay::DrawSaleMode(Data* data){
    u8g2Fonts.setFont(MIDL_FONT);
    u8g2Fonts.setForegroundColor(GxEPD_YELLOW);
    u8g2Fonts.setCursor(0, 45);  
    int pos = u8g2Fonts.getUTF8Width(ReplaceFloat(String(data->Price)).c_str()) + 2;
    u8g2Fonts.print(ReplaceFloat(String(data->Price)));
    for(int x = 0; x<pos;x++){
        display.fillRect( x, 40, 1, 1, GxEPD_BLACK);
        display.fillRect( x, 40, 2, 2, GxEPD_BLACK);
      }
    u8g2Fonts.setCursor(0, 60);
    u8g2Fonts.print("-"+String(Percent(data->SalePrice, data->Price))+"%");
    u8g2Fonts.setFont(LARGE_FONT);
    u8g2Fonts.setCursor(pos, 60);
    u8g2Fonts.print(ReplaceFloat(String(data->SalePrice)));
    int i = u8g2Fonts.getUTF8Width(ReplaceFloat(String(data->SalePrice)).c_str()) + 2 + pos;
    u8g2Fonts.setCursor(i, 60);
  }
  
void cDisplay::DrawWithoutSaleMode(Data* data){
    u8g2Fonts.setCursor(0, 60);
    u8g2Fonts.setForegroundColor(GxEPD_YELLOW); 
    int pos = u8g2Fonts.getUTF8Width(String(data->Price).c_str()) + 2;
    u8g2Fonts.print(String(data->Price));
    u8g2Fonts.setCursor(pos, 60);
  } 
  
void cDisplay::DrawMeasurement(Data* data){
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);
    u8g2Fonts.setFont(MIDL_FONT);
    u8g2Fonts.print(data->Measurement);
  }
  
void cDisplay::DrawDescription(Data* data){
  u8g2Fonts.setCursor(50, 75);
  int pos = u8g2Fonts.getUTF8Width(data->Description.c_str());
  Serial.println(pos);
  int space_for_text = display.width()-50;
  Serial.println(space_for_text);
  if(pos>space_for_text){
      int count_symbol = 42;//(space_for_text/7.5f)*2;
      Serial.println(count_symbol);
      Serial.println(data->Description);
      String first_part = data->Description.substring(0, count_symbol);
      String second_part = data->Description.substring(count_symbol);
      u8g2Fonts.print(first_part);
      u8g2Fonts.setCursor(50, 88);
      if(u8g2Fonts.getUTF8Width(second_part.c_str())>space_for_text){
          second_part = second_part.substring(0, count_symbol);
          Serial.println(second_part);
          count_symbol = 86;
          
          String third_part = data->Description.substring(count_symbol);
          Serial.println(third_part);
          u8g2Fonts.print(second_part);
          u8g2Fonts.setCursor(50, 100);
          u8g2Fonts.print(third_part);
        }
      else
          u8g2Fonts.print(second_part);
    }
    else
      u8g2Fonts.print(data->Description);
  }
  
int cDisplay::Percent(float x, float y){
    float result = 0;
    result = ((y - x) * 100) / y;
    return result;
  }
  
String cDisplay::ReplaceFloat(String s){
    s.replace(".00", "");
    return s;
  }
  
void cDisplay::DrawQRcode(int id){
  uint8_t qrcodeData[qrcode_getBufferSize(5)];
  String c = "https://price-tag-database.herokuapp.com/"+ String(id);
  qrcode_initText(&qrcode, qrcodeData, 5, 0, c.c_str());
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
