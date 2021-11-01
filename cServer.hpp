#pragma once
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>

struct Data{
      String Description;
      String Title;
      float Price;
      float PromotionalPrice;
      bool Sale;
      String QRlink;
};
  
class cServer{
  public:
    void ConnectWifi();
    void Update();
    Data* Get_Data(){return &data;}
  private:
    HTTPClient https;
    ESP8266WiFiMulti WiFiMulti;
    Data data;

};
