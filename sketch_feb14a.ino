#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>
#include <SPI.h>
#include <SevSeg.h>

 


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

 


char auth[] = "O_kJMDCsNfFn6rtnrnbN_vjgmQpZLDUF";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Samsungs10";
char pass[] = "nepal123";
WiFiClient client;

 

String latitude;
String longitude;
int button_pressed=D4;
int isButtonPressed;
BLYNK_WRITE(V0) { // Read Virtual Pin 0 for coordinates.
  GpsParam gps(param);

 

  Blynk.virtualWrite(V0, param[0].asString());
  Blynk.virtualWrite(V0, param[1].asString());

 

  latitude = param[0].asString(); // THIS IS A CHANGE FROM LAST CODE
  longitude = param[1].asString(); // THIS IS A CHANGE FROM LAST CODE

 

  // Print 6 decimal places for Lat, Lon

 

  Serial.print("Lat: ");
  Serial.println(gps.getLat(), 7);

 

  Serial.print("Lon: ");
  Serial.println(gps.getLon(), 7);

 

  // Print 2 decimal places for Alt, Speed
  Serial.print("Altitude: ");
  Serial.println(gps.getAltitude(), 2);

 

  Serial.print("Speed: ");
  Serial.println(gps.getSpeed(), 2);
}

 


void emailOnButtonPress()
{
 
isButtonPressed=digitalRead(button_pressed);
  //int isButtonPressed = !digitalRead(2); // Invert state, since button is "Active LOW"

 

  if (isButtonPressed==0) // You can write any condition to trigger e-mail sending
  {
    Serial.println("Button is pressed. Locating Phone!"); // This can be seen in the Serial Monitor

 

    //String toSend is the string that will be sent as the emails body
    String toSend = "Phone Located! \n received co-ordinates \n";
    toSend += " LAT ";
    toSend += latitude;
    toSend += " LONG ";
    toSend += longitude;
    toSend += ". View location on Maps: ";
    toSend += "http://maps.google.com/?q=";
    toSend += latitude;
    toSend += ",";
    toSend += longitude;
    Blynk.notify("Alert: Mobile lost");
    digitalWrite(button_pressed,HIGH);

 

    Blynk.email("abhishek.basnet.92@gmail.com", "Subject: Phone Locator", toSend);
  }else{
    Serial.println("stay cool");
    digitalWrite(button_pressed,LOW);
  }
}

 

void setup()
{
  // Debug console
  Serial.begin(115200);

 

  Blynk.begin(auth, ssid, pass);

 

  // Send e-mail when your hardware gets connected to Blynk Server
  // Just put the recepient's "e-mail address", "Subject" and the "message body"

 

  Blynk.email("abhishek.basnet.92@gmail.com", "PhoneLocator Activated");

 

  // Setting the button
  pinMode(2, INPUT_PULLUP);
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(2), emailOnButtonPress, CHANGE);
}

 

void loop()
{
  Blynk.run();
}
