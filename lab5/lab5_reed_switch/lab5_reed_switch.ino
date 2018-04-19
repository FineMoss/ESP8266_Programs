#include <Adafruit_NeoPixel.h>

#define NEO_PIN 15
#define REED_PIN 4
#define HIGH_PIN 5

int val = 0;

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, NEO_PIN, NEO_GRB + NEO_KHZ800);

void green() {
  pixel.setPixelColor(0, pixel.Color(0,255,0));
  pixel.show();
}

void red() {
  pixel.setPixelColor(0, pixel.Color(255,0,0));
  pixel.show();
}

void alarm() {

  delay(500);
  
}

void setup() {
  // set up the NeoPixel
  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();
  // set up the reed switch
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(HIGH_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  val = digitalRead(REED_PIN);
  
  if (val == HIGH) {
    red();
  }
  if (val == LOW) {
    green();
  }

  Serial.println(val);

  delay(100);

}
