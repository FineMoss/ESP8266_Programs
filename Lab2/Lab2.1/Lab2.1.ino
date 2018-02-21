 #define LED 2 // the digital pin the LED is attached to
void setup() {
  // declare pin 4 to be an output:
  pinMode(LED, OUTPUT);
} 
void loop() {
  

  for(int i = 0; i < 5; i++) {
    analogWrite(LED, 255);
    delay(500);
    analogWrite(LED, 0);
    delay(500); 
  }
  
  analogWrite(LED, 255);
  delay(500);

  int intensity = 255;
  while(intensity > 0) {
    intensity = intensity-1;
    analogWrite(LED, intensity);
    delay(20);
  }
  delay(500);

  
} 
