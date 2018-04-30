#include <Servo.h>

#define SERVO_PIN 2 

Servo servo;
int pos1 = 0;

void setup() {
  // put your setup code here, to run once:
  
  servo.attach(SERVO_PIN, 771, 1798);
  

}

void loop() {
  servo.write(0); // Min
  delay(2000);
  servo.write(65); // Midpoint
  delay(2000);
  servo.write(180); // Max
  delay(2000);
}
