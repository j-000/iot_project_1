#include <ATcommands.h>
#include <UtilFunctions.h>
#include <stdlib.h>

#include<Arduino.h>
#include <SoftwareSerial.h>
#include <WiFi.h>


#define TX_PIN 2
#define RX_PIN 3


SoftwareSerial ESPSerial(TX_PIN, RX_PIN);



// Wifi Module
String SSID = "\"\"";
String PWD = "\"\"";
String host = "\"http://joalex.dev\"";
String port = "\"80\"";
String protocol = "\"TCP\"";
int oneMinute = 30000;


WiFiClient client;

// Temperature Module
int thermistorPin = A0;
float thermistorResistor = 100000;




void setup() {
  Serial.begin(9600);
  ESPSerial.begin(9600); 
  
  espRunCommand(ESPSerial, AT_RESET, 1000);                                // Reset Chip
  espRunCommand(ESPSerial, AT_SET_STATION_MODE, 1000);                     // Set station mode
  espRunCommand(ESPSerial, AT_CONNECT_TO_WIFI + SSID + "," + PWD, 1000);   // Connect to wifi
  
  delay(1000);
}


void loop(){
  // Prints out any response from ESP module
  if (ESPSerial.available()){
    while(ESPSerial.available()){
      char c = ESPSerial.read();
      Serial.print(c);
    }
  }
  
  // Manual input from Serial Monitor
  if (Serial.available()){ESPSerial.write(Serial.read());}   
  
  

//  if (millis() % oneMinute == 0){
//
//    // Test connection and reset if wifi is off
//    boolean wifiIsOn = testWifiConnection(ESPSerial);
//
//    if (wifiIsOn){
//      // Get temperature
//      String temperature = getTemperature();
//      Serial.println("\nTemperature: " + temperature);
//    }else{
//      resetWifi(ESPSerial);
//    }
// 
//  }
  
}






