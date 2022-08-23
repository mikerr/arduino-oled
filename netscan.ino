#include "WiFi.h"
#include"SSD1306.h"
#include <ESP32Ping.h>

SSD1306  display(0x3c, 5, 4);

const char* ssid = "ssid";
const char* password = "password";

void initWiFi() {
  int x=0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  display.drawString(0,10, String( "Connecting.."));
  display.display(); 
  while (WiFi.status() != WL_CONNECTED) {
    display.drawString(x*10,20, String( "."));
    display.display(); 
    x++;
    delay(1000);
  }
}
void setup() {
  
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  
  initWiFi();
  display.clear();
  display.drawString(0,0, String("Connected: " + String(ssid)));
  display.drawString(0,30, String( "IP address: " + WiFi.localIP().toString() ) );
  display.drawString(0,40, String( "IP gateway: " + WiFi.gatewayIP().toString() ) );
  display.display();

  delay(3000);
}

void loop() {
int line = 0;
   IPAddress testip = WiFi.localIP();
   display.clear();
   for (int subnet=1;subnet<255;subnet++) {
     testip[3] = subnet;
     //display.drawString(subnet / 2,50, String("."));
     display.drawLine(0, 60, subnet /2 , 60);
     bool success = Ping.ping(testip, 1);
     if (success){
       display.drawString(0,line*8, testip.toString());  
       line++;
       if (line > 6) {
         line = 0;
         display.clear();
         }
       }
     display.display();
  }
}
