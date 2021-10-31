#include "cServer.hpp"
#include "badge.hpp"
#include "StringSplitter.h"

struct Data{
    String Description;
    String Title;
    uint32_t Price;
    uint32_t PromotionalPrice;
    bool Sale;
}data;

void cServer::ConnectWifi(){
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password_wifi);
  int i = 0;
  while (WiFiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Update();
}

void cServer::Update(){
  if(WiFiMulti.run()== WL_CONNECTED){
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, serverName)) {  // HTTPS
      https.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "api_key=" + apiKeyValue + "&id="+1;
      int httpCode = https.POST(httpRequestData);// start connection and send HTTP header
      // httpCode will be negative on error
      if (httpCode > 0) {// HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {// file found at server
          String payload = https.getString();
          payload.replace("<tr> <td>","");
          payload.replace("</td> </tr>", "");
          StringSplitter *splitter = new StringSplitter(payload, ';', 5);
          data.Description = splitter->getItemAtIndex(0);
          data.Title = splitter->getItemAtIndex(1);
          data.Price = splitter->getItemAtIndex(2).toInt();
          data.PromotionalPrice = splitter->getItemAtIndex(3).toInt();
          data.Sale = bool(splitter->getItemAtIndex(4));
          Serial.println(payload);
          Serial.println(data.Description);
          Serial.println(data.Title);
          Serial.println(data.Price);
          Serial.println(data.PromotionalPrice);
          Serial.println(data.Sale);

          }   
        }
        else 
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      } 
      https.end();
  }
}
