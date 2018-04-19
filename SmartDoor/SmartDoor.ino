
#define BTTN_PIN 0
#define SERV_PIN 2
#define REED_PIN 4
#define BUZZ_PIN 13
#define NEOP_PIN 15
#define BLYNK_PRINT Serial


#include <Servo.h>
#include <Temboo.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <BlynkSimpleEsp8266.h>


Servo lock;
WiFiClient client;
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, NEOP_PIN, NEO_GRB + NEO_KHZ800);


char auth[] = "3c3fc83636f148079aea3ad0faff4ed4";
char ssid[] = "CS390N";
char pass[] = "internetofthings";

const String CLIENT_SECRET = "FJBMzw-G97gS7n4yMSvR1VEJ";
const String REFRESH_TOKEN = "1/zPSHjpDgKxBLa2_JDO1JJt_aoJn9Ks_43kE5DDfm4sk";
const String SPREADSHEET_ID = "12vd2gqGDlKXt1H6KC7_yRNtsaz9mz0hOsU3UMQvCz1M";


bool is_door_open;
bool is_door_locked;
bool is_button_pressed = false;


void pixel_green() {
  pixel.setPixelColor(0, pixel.Color(0,255,0));
  pixel.show();
}

void pixel_red() {
  pixel.setPixelColor(0, pixel.Color(255,0,0));
  pixel.show();
}

void pixel_off() {
  pixel.setPixelColor(0, pixel.Color(0,0,0));
  pixel.show();
}


void button_ISR() {
  is_button_pressed = true;
}

void reed_switch_ISR() {
  if (digitalRead(REED_PIN) == HIGH) {
    is_door_open = true;
  }
  else {
    is_door_open = false;
  }
}


void send_google_update(String message) {
  TembooChoreo AppendValuesChoreo(client);
  // Invoke the Temboo client
  AppendValuesChoreo.begin(); 
  // Set Temboo account credentials
  AppendValuesChoreo.setAccountName("jakeseabass");
  AppendValuesChoreo.setAppKeyName("myFirstApp");
  AppendValuesChoreo.setAppKey("00FZ1KTzTKva8qJKSqXCKbsp7TYVbePg");
  // Identify the Choreo to run
  AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");
  // Set Choreo inputs
  AppendValuesChoreo.addInput("Scope", "https://spreadsheets.google.com/feeds/");
  AppendValuesChoreo.addInput("ClientID", "281013315187-9gegl1vnouk2ajfml3sdnptr7nc2j22u.apps.googleusercontent.com");
  AppendValuesChoreo.addInput("ClientSecret", CLIENT_SECRET);
  AppendValuesChoreo.addInput("RefreshToken", REFRESH_TOKEN);
  AppendValuesChoreo.addInput("SpreadsheetID", SPREADSHEET_ID);

  //Data
  String row_data =  "[[\"" +  String(millis()) + "\", \"" + message + "\"]]";
  AppendValuesChoreo.addInput("Values", row_data);
  
  // Run the Choreo; when results are available, print them to serial
  unsigned int returnCode = AppendValuesChoreo.run();
  if (returnCode == 0) {
    Serial.println("Success!");
  } 
  else {
    while (AppendValuesChoreo.available()) {
      char c = AppendValuesChoreo.read();
        Serial.print(c);
    }
    Serial.println();
  }
  AppendValuesChoreo.close();
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(BTTN_PIN ,INPUT_PULLUP);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(BUZZ_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTTN_PIN), button_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), reed_switch_ISR, CHANGE);

  lock.attach(SERV_PIN);
  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  reed_switch_ISR();
}

void loop() {
  Blynk.run();
}



































