#include <Arduino.h>
#include <SoftwareSerial.h>

String espRunCommand(SoftwareSerial ESPSerial, String command, const int timeout);
String getTemperature(uint8_t thermistorPin, int thermistorResistor);
boolean testWifiConnection(SoftwareSerial ESPSerial);
void resetWifi(SoftwareSerial ESPSerial);