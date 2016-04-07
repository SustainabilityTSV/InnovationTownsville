/*
  DHT_TO_LEDS
  Author: Dylan VanDerWal
  Licence: Open source
  feel free to modify and distrobute. No Warrenties.
  
  For video tutorial on this setup, Here:
*/

#include "DHT.h"

#define DHTPIN 8     // what digital pin we're connected to

#define DHTTYPE DHT22   // Define the type of DHT: DHT 22  (AM2302), AM2321

// Connect pin 1 (on the left) of the sensor(Front is the grided side) to the 3.3
// Connect pin 2 of the sensor to Digital PWM pin 8
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect Short leg of all LED's to a 220 Ohm resistor (RED, RED, BROWN, GOLD) and connect the other end of the resistors to GROUND
// Connect the long leg of the green LED to Pin 13
// Connect the long leg of the Yellow LED to Pin 12
// Connect the long leg of the red LED to Pin 11

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  dht.begin();
  
  // Comment out the following section if you don't want flashing startup for LED Testing
  // THis section was designed to test the LED's to make sure they are working, and plugged in the right way.
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(11, LOW)
  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


//Comment out the following section if you do not need to have the board outputting to serial
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Feels Like: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
// Stop Commenting

  if(t>25){
    // If temp is above 25 deg, turn on green LED
    digitalWrite(13, HIGH);
    }
    
  if(t<25){
    // If temp is Below 25 deg, turn off green LED
    digitalWrite(13, LOW);
    }
  if(t>30){
    // If temp is above 30 deg, turn on yellow LED
    digitalWrite(12, HIGH);
    }
    
  if(t<30){
    // If temp is Below 30 deg, turn off yellow LED
    digitalWrite(12, LOW);
    }

  if(t>35){
    // If temp is above 35 deg, turn on red LED
    digitalWrite(11, HIGH);
    }
    
  if(t<35){
    // If temp is Below 35 deg, turn off red LED
    digitalWrite(11, LOW);
    }
}
