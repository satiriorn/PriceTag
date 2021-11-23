#include "cServer.hpp"
#include "cDisplay.hpp"

cDisplay dspl;
cServer server;
Data* data;
const int id = 1;

void setup() {
  Serial.begin(115200);
  delay(100);
  server.ConnectWifi();
}


void loop() {
  server.Update(id);
  data = server.Get_Data();
  dspl.DrawText(data, id);
  delay(100);
  Serial.println("DEEP SLEEEP");
  ESP.deepSleep(3600000000UL); 
  //delay(1000000);

}
