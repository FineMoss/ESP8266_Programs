#include <Servo.h>

Servo s1;
int pos1 = 0;

void setup() {
  // put your setup code here, to run once:
  
  s1.attach(9);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  for (pos1; pos1 < 180; pos1 +=1) {
    s1.write(pos1);
    delay(5);
  }

  delay(100);
  
  for (pos1; pos1 > 0; pos1 -=1) {
    s1.write(pos1);
    delay(5);
  }

  delay(100);
  

}
