#include "cServer.hpp"
#include "cDisplay.hpp"

cDisplay* dspl;
cServer* server;

void setup() {
  Serial.begin(115200);
  Serial.println(); 
  server = new cServer();
  server->ConnectWifi();
  Data* data = server->Get_Data();
  delay(1000);
  dspl = new cDisplay();
  dspl->DrawText(data);
  delay(1000);
}

  void loop() { 
}
