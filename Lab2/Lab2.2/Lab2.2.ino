
#include <Adafruit_NeoPixel.h>

#define LED 15
#define POT A0

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED, NEO_GRB + NEO_KHZ800);

int analogValue = 0;

void setup() {

  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();

}

void loop() {

  analogValue = analogRead(POT);

//  pixel.setPixelColor(0, pixel.Color(255,0,0));
  pixel.show();

  
  if (analogValue < 512) {
    pixel.setPixelColor(0, pixel.Color(255-analogValue/2,analogValue/2,0));
  }

  if (analogValue >= 512) {
     pixel.setPixelColor(0, pixel.Color(0,255-analogValue%512/2,analogValue%512/2));
  }
  

  delay(10);

}
