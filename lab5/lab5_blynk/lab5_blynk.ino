
#define BLYNK_PRINT Serial
#define NEO_PIN 15


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>


char auth[] = "3c3fc83636f148079aea3ad0faff4ed4";
char ssid[] = "CS390N";
char pass[] = "internetofthings";


WidgetTerminal terminal(V1);
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, NEO_PIN, NEO_GRB + NEO_KHZ800);


BLYNK_WRITE(V1) {
  int shift = param.asInt();
  
  if (shift >= 1) {
    pixel.setPixelColor(0, pixel.Color(255,0,0));
    pixel.show(); 
  }
  if (shift < 1) {
    pixel.setPixelColor(0, pixel.Color(0,255,0));
    pixel.show();
  }
  Serial.println(shift);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();



}


