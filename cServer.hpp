#pragma once
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>


class cServer{
  public:
    explicit cServer();
    void ConnectWifi();
    void Update();
  private:
    HTTPClient https;
    ESP8266WiFiMulti WiFiMulti;
    //auto client;
};
