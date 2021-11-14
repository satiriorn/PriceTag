#pragma once
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

struct Data{
      String Description;
      String Title;
      float Price;
      float SalePrice;
      bool Sale;
      String Measurement;
};
  
class cServer{
  public:
    void ConnectWifi();
    void Update(int id);
    Data* Get_Data(){return &data;}
  private:
    HTTPClient https;
    ESP8266WiFiMulti WiFiMulti;
    Data data;

};
