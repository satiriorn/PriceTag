#include "cServer.hpp"
#include "cDisplay.hpp"
#define EEPROM_SIZE 2

#include <EEPROM.h>
#include <Arduino.h>

cDisplay dspl;
cServer server;
Data* data;
const int id = 1;

void setup() {
  Serial.begin(115200);
  delay(100);
  server.ConnectWifi();
  delay(1000);
}


void loop() {
  server.Update(id);
  data = server.Get_Data();
  delay(1000);
  dspl.DrawText(data, id);
  delay(1000000);

}
