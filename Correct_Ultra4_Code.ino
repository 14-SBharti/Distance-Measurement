#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "D2"; //SSID
char pass[] = "ramnayan"; // Password

int trigPin = D5;    // D5 Trigger, trigPin is variable
int echoPin = D6;    //D6  Echo, echoPin is also variable
long duration, cm, inches;// these are 3 variables, 
WiFiClient  client;
//duration variable saves the time between the emssion and reception of the signal.
//cm variable saves distance in centimeteres and inches saves distance in inch.
unsigned long myChannelField = 1386981; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "6WU75U6VOGYIL88A";
void setup()
{
  Serial.begin(115200);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);// it sends high frequency sound pulses.
  pinMode(echoPin, INPUT);// it receives the reflected sound pulese.
  //Serial Port begin
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  //Serial.begin (115200);// initialize the serial port at baud rate of 9600.
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

   if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  digitalWrite(trigPin, LOW);// clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  //pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

 
  // Convert the time into a distance
  cm = duration* 0.034/2;     // Divide by 29.1 or multiply by 0.0343
  //inches = duration*0.0135/2;   // Divide by 74 or multiply by 0.0135

  Serial.print("Time Duration: ");
  Serial.print(duration, 1);
  Serial.println(" microsec");
  Serial.println();

Serial.print("Distance: ");
Serial.print(cm, 1);
Serial.println(" cm"); 
Serial.println();
Serial.write(cm);


/*Serial.print("Distance in inches: ");
Serial.print(inches, 1);
Serial.println(" inch");
Serial.println();*/
if(cm>400  || cm<2) Serial.println("out of range \n");

else
{
  Serial.print("Sensor works prefectly");
  Serial.println('\n');
 /* Serial.print(duration);
  Serial.print("Microsec");
  Serial.println();
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");*/
}

    ThingSpeak.writeField(myChannelField, ChannelField, cm, myWriteAPIKey);
  delay(1000);
  //delay(2000);
}
