#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>


#define dhtpin D2
#define dhttype DHT11


DHT dht(dhtpin, dhttype);



String sendGetRequest(String url){
  // Parameters are in the URL string
  HTTPClient http;
  WiFiClientSecure client;
  
  client.connect("yourwebsite.com", 443);

  // HTTPS
  // http.begin("yourwebsite.com", 443, url, SSL_THUMBPRINT);

  // HTTP
  http.begin(url);

  int httpCode = http.GET();

  Serial.println("http code: " + String(httpCode));
  
  if (httpCode > 0){
    String payload = http.getString();
    return payload;
  }
  
  http.end();
  delay(1000);
  return "";
}

boolean wifiIsOn(){
  // Tests connection
  return WiFi.status() == WL_CONNECTED;
}

void connectToWifi(){
  // Try to connect to wifi every 10s
  while(!wifiIsOn()){
    WiFi.begin("WIFI_NAME_SSID","WIFI_PASSWORD"); 
    delay(10000);
  }
}

String getTemperature(){
  double Vout, Rth, temperature, adc_value; 
  const double VCC = 3.3;
  const double R2 = 10000; 
  const double adc_resolution = 1023;
  const double A = 0.001129148;
  const double B = 0.000234125;
  const double C = 0.0000000876741; 
  adc_value = analogRead(A0);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));
  temperature = temperature - 273.15;
  return String(temperature);
}

void setup(){
  Serial.begin(9600);
  Serial.print("Starting...");
  dht.begin();
  connectToWifi();
}


void loop(){
  // Reconnect if wifi drops
  if(!wifiIsOn()){
    connectToWifi();
  }

  float t = dht.readTemperature();
  delay(5000);
  float h = dht.readHumidity();
  delay(5000);


  String resp = sendGetRequest("http://yourwebsite.com/t=" + String(t) + "&h=" + String(h));
  
  Serial.println("\tResponse: " + resp);
}
