
#include <Wire.h>
#include"SSD1306.h"

#include <SPI.h>
#include <WiFi.h>

SSD1306  display(0x3c, 5, 4);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  // Print WiFi MAC address:
  printMacAddress();
}

void loop() {
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
  delay(2000);
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }
   display.clear();
     
  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the SSID and strength for each network found:

  int fit = 64 / numSsid;
  fit = constrain ( fit,9, 12);
  
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");

   Serial.println("");
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   display.drawStringMaxWidth(0,thisNet * fit, 128, WiFi.SSID(thisNet));
   display.setTextAlignment(TEXT_ALIGN_RIGHT);
   display.drawString(128,thisNet * fit, String( WiFi.RSSI(thisNet)) + " dB");
   
  } 
  display.drawLogBuffer(0, 0);
  display.display();
}



