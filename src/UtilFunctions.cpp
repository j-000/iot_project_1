#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ATcommands.h>


String getTemperature(uint8_t thermistorPin, int thermistorResistor){
  /*
    This functions reads the analogue pin thermistorPin, connected 
    with a given resistor thermistorResistor, and returns the 
    current temperature in Celsius.
  */
  int Vo;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  Vo = analogRead(thermistorPin);
  R2 = thermistorResistor * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  return String(T);
}


boolean testWifiConnection(SoftwareSerial ESPSerial){
  /*
    This functions takes an ESPSerial variable type SoftwareSerial and 
    tests if it is connected. Returns boolean.

    AT+CIPSTATUS returns:
    2 - OK (WiFi conected to AP and IP Obtained)
    3 - Created TCP / UDP transmission
    4 - Disconnected
    5 - Station does NOT connect to AP
  */
  boolean wifiIsOn = false;
  Serial.print("[Checking WiFi Connection]");
  String response = espRunCommand(ESPSerial, AT_CHECK_STATUS, 2000);
  return response.indexOf("2") > 0;
}

void resetWifi(SoftwareSerial ESPSerial){
  /*
    This function runs the AT+RST command to 
    reset the wifi - runs setup();
  */
  espRunCommand(ESPSerial, AT_RESET, 2000);
}


String espRunCommand(SoftwareSerial ESPSerial, String command, const int timeout){
  /*
    This function takes a ESPSerial reference and runs a command. 
    The function waits timeout millisencond for a response and then returns.
  */
  String response = "";
  long int time = millis();
  Serial.print("\n[Running: " + command + "]\n");
  ESPSerial.println(command);
  while ((time + timeout) > millis()) {
    while (ESPSerial.available()) {
      char c = ESPSerial.read();
      response += c;
    }
  }
  return response;
}
