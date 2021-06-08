#include <ESP8266WiFi.h>
 

int trigPin = D5;    // D5 Trigger, trigPin is variable
int echoPin = D6;    //D6  Echo, echoPin is also variable
long duration, cm, inches;// these are 3 variables for storing time and distance in cm and inches respectively.

void setup()
 {
 Serial.begin(115200);
 //Define inputs and outputs
 pinMode(trigPin, OUTPUT);// it sends high frequency sound pulses.
 pinMode(echoPin, INPUT);// it receives the reflected sound pulese.
 }
 
void loop() 
 {
  
  digitalWrite(trigPin, LOW);// clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  
  duration = pulseIn(echoPin, HIGH);

 
 // Convert the time into a distance
 cm = duration* 0.034/2;     // Divide by 29.1 or multiply by 0.0343
 inches = duration*0.0135/2;   // Divide by 74 or multiply by 0.0135

Serial.print("Time Duration: ");
Serial.print(duration, 1);
Serial.println("microsecond");
Serial.println();

Serial.print("Distance: ");
Serial.print(cm, 1);
Serial.println(" cm"); 
Serial.println();
Serial.write(cm);


Serial.print("Distance in inches: ");
Serial.print(inches, 1);
Serial.println(" inch");
Serial.println();
if(cm>400  || cm<2) Serial.println("out of range \n");

else
{
  Serial.print("Sensor works prefectly");
  Serial.println('\n');
  Serial.print(duration);
  Serial.print("Microsecond");
  Serial.println();
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
  }

  delay(1000);
  //delay(2000);
}
