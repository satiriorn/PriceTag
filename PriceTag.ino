#include "cServer.hpp"
#include "cDisplay.hpp"
#define EEPROM_SIZE 2

#include <EEPROM.h>
#include <Arduino.h>

cDisplay* dspl;
cServer* server;
int id;

inline int readIntFromEEPROM(int address)
{
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

void writeIntIntoEEPROM(int address, int number)
{ 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println();
  delay(100);
    
  id = readIntFromEEPROM(1);
  Serial.println(id); 
  server = new cServer();
  server->ConnectWifi();
  server->Update(&id);
  Data* data = server->Get_Data();
  delay(1000);
  
  dspl = new cDisplay();
  dspl->DrawText(data, &id);
  delay(1000);
}


void loop() {

}
