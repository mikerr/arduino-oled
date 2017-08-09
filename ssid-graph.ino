
// Display nearby Wifi networks, and their strengths on a graph

#include <Wire.h>
#include"SSD1306.h"

#include <SPI.h>
#include <WiFi.h>

SSD1306  display(0x3c, 5, 4);
boolean open_net=false;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Button 1 on ESP ("boot")
  pinMode(0, INPUT_PULLUP);
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
 
}
#define WIDTH 128
#define HEIGHT 64

#define GRAPH_BASELINE (HEIGHT - 1)
#define GRAPH_HEIGHT (HEIGHT)
#define CHANNEL_WIDTH (WIDTH / 16)

// RSSI RANGE
#define RSSI_CEILING -40
#define RSSI_FLOOR -100

void loop() {
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
  delay(2000);

  // detect button press
  uint8_t pinState = digitalRead(0);
  if (pinState != 0) open_net = true;
  else open_net= false;

  uint8_t ap_count[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int32_t max_rssi[] = {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100};
for (int l=0;l<5;l++){
int n = WiFi.scanNetworks();
display.clear();
for (int i = 0; i < n; i++) {
      int32_t channel = WiFi.channel(i);
      int32_t rssi = WiFi.RSSI(i);

      int height = constrain(map(rssi, RSSI_FLOOR, RSSI_CEILING, 1, GRAPH_HEIGHT), 1, GRAPH_HEIGHT);

      // channel stat
      ap_count[channel - 1]++;
      if (rssi > max_rssi[channel - 1]) {
        max_rssi[channel - 1] = rssi;
      }
      
      display.drawLine(channel * CHANNEL_WIDTH, GRAPH_BASELINE - height, (channel - 1) * CHANNEL_WIDTH, GRAPH_BASELINE + 1);
      display.drawLine(channel * CHANNEL_WIDTH, GRAPH_BASELINE - height, (channel + 1) * CHANNEL_WIDTH, GRAPH_BASELINE + 1);

      String ssid = WiFi.SSID(i).substring(0,8);
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(channel * CHANNEL_WIDTH,GRAPH_BASELINE - height - 10, ssid);
}
display.display();
delay(1000);
}

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
   display.drawStringMaxWidth(0,thisNet * fit, 128, WiFi.SSID(thisNet) + String ((WiFi.encryptionType(thisNet) == WIFI_AUTH_OPEN)?"*":" "));
   display.setTextAlignment(TEXT_ALIGN_RIGHT);
   display.drawString(128,thisNet * fit, String (WiFi.channel(thisNet)) + " " + String( WiFi.RSSI(thisNet)) + "");
   
  } 
  display.drawLogBuffer(0, 0);
  display.display();
}



