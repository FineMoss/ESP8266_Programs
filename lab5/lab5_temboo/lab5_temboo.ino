#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Temboo.h>
#include "TembooAccount.h"
WiFiClient client;


int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);


  WiFi.begin("CS390N", "internetofthings"); //connecting to the router Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  } 
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running GeocodeByAddress - Run #" + String(calls++));
    
    TembooChoreo GeocodeByAddressChoreo(client);

    // Invoke the Temboo client
    GeocodeByAddressChoreo.begin();

    // Set Temboo account credentials
    GeocodeByAddressChoreo.setAccountName("jakeseabass");
    GeocodeByAddressChoreo.setAppKeyName("myFirstApp");
    GeocodeByAddressChoreo.setAppKey("00FZ1KTzTKva8qJKSqXCKbsp7TYVbePg");
    
    // Set Choreo inputs
    GeocodeByAddressChoreo.addInput("Address", "amherst, MA");
    
    // Identify the Choreo to run
    GeocodeByAddressChoreo.setChoreo("/Library/Google/Geocoding/GeocodeByAddress");
    
    // Run the Choreo; when results are available, print them to serial
    GeocodeByAddressChoreo.run();
    
    while(GeocodeByAddressChoreo.available()) {
      char c = GeocodeByAddressChoreo.read();
      Serial.print(c);
    }
    GeocodeByAddressChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between GeocodeByAddress calls
}
