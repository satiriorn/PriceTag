#include "cServer.hpp"
#include "cDisplay.hpp"

cDisplay dspl;
cServer server;
Data* data;

const int id = 1;
int hour = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  server.ConnectWifi();
}


void loop() {
  server.Update(id);
  data = server.Get_Data();
  dspl.DrawText(data, id);
  hour = data->Time.toInt()+2;
  Serial.println(hour);
  Serial.println("DEEP SLEEEP");
  (hour>21)?ESP.deepSleep(432e10):ESP.deepSleep(3600000000UL); 
}
