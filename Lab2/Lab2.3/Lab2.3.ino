
#include <Adafruit_NeoPixel.h>

#define POT_PIN A0
#define LED_PIN 5
#define LED_NUM 20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

int analogValue = 0;

void setup() {

  strip.begin();
  strip.setBrightness(80);
  strip.show();

}

void loop() {

  analogValue = analogRead(POT_PIN);
  
  int specialPixel = (int)(analogValue/51);

  for(int i = 0; i < LED_NUM; i++) {

    if (i == specialPixel) {
      strip.setPixelColor(i, strip.Color(0, 255, 0));
    }
    else {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    
  // end for loop
  }

  strip.show();

}
