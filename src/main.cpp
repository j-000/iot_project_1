// Custom files
#include <ATcommands.h>
#include <UtilFunctions.h>
#include <credentials.h>     // Contains SSID and PWD for wifi.

// Libraries
#include<Arduino.h>
#include <SoftwareSerial.h>

// TX and RX pins definitions
#define TX_PIN 2
#define RX_PIN 3

// Global variables
SoftwareSerial ESPSerial(TX_PIN, RX_PIN);
String host = "\"http://joalex.dev\"";
String port = "\"80\"";
String protocol = "\"TCP\"";
int oneMinute = 60000; 

// Thermistor pin and resistor definition
int thermistorPin = A0;
float thermistorResistor = 100000;


void setup() {
  // Start Serial and ESPSerial
  Serial.begin(9600);
  ESPSerial.begin(9600); 
  // Reset ESP
  espRunCommand(ESPSerial, AT_RESET, 1000);
  // Set Station Mode
  espRunCommand(ESPSerial, AT_SET_STATION_MODE, 1000);
  // Connect to wifi
  espRunCommand(ESPSerial, AT_CONNECT_TO_WIFI + SSID + "," + PWD, 1000);
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
  if (Serial.available()){
    ESPSerial.write(Serial.read());
  }   
  
 if (millis() % oneMinute == 0){
    // Test connection and reset if wifi is off
    boolean wifiIsOn = testWifiConnection(ESPSerial);

    if (wifiIsOn){
      // Get temperature
      String temperature = getTemperature(thermistorPin, thermistorResistor);
      Serial.println("\nTemperature: " + temperature);
    }else{
      resetWifi(ESPSerial);
    }
  }
}






