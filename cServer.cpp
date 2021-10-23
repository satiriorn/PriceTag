#include "cServer.hpp"
#include "badge.hpp"

cServer::cServer(){

}

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
          Serial.println(payload);
          } 
        }
        else 
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      } 
      https.end();
  }
}
