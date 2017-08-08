#include <Wire.h>
#include "SSD1306.h"

SSD1306  display(0x3c, 5, 4);

#define STARS 500

float star_x[STARS], star_y[STARS], star_z[STARS]; 

void initStar(int i) {
  star_x[i] = random(-100, 100);
  star_y[i] = random(-100, 100);
  star_z[i] = random(100, 500);
}

void showStarfield() {
  int x,y;
  int centrex,centrey;
  
  centrex = DISPLAY_WIDTH / 2;
  centrey = DISPLAY_HEIGHT / 2; 
  
  for (int i = 0; i < STARS; i++) {
    star_z[i] = star_z[i] - 7;

    x = star_x[i] / star_z[i] * 100 + centrex;
    y = star_y[i] / star_z[i] * 100 + centrey;

    if(
        (x < 0)  ||        (x > DISPLAY_WIDTH) || 
        (y < 0)  ||        (y > DISPLAY_HEIGHT) ||
        (star_z[i] < 1)      
      )      initStar(i);
    display.setPixel(x, y);
  }
  display.display();
}  

void setup() {
  display.init();
  for (int i = 0; i < STARS; i++) 
    initStar(i);
}

void loop() {
display.clear();

showStarfield();
display.display();
delay(10);
}
