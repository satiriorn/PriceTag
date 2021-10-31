#include "cServer.hpp"
#include "cDisplay.hpp"

cDisplay* dspl;
cServer* server;

void setup() {
  Serial.begin(115200);
  Serial.println(); 
  server = new cServer();
  server->ConnectWifi();
  delay(1000);
  dspl = new cDisplay();
}

  void loop() { 
}
