/* replace ? and add code in ???*/
#include <Arduino.h>
#include <DHT.h>
#include "NewPing.h"
#include <ESP32Servo.h>

// define DHT11 sensor pin


#define DHT_TYPE DHT11
DHT dht11(DHT_PIN, DHT_TYPE);

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

//define pins
#define LED_PIN 1
#define DHT_PIN   4
#define TRIG_PIN 5        
#define ECHO_PIN  6       
#define BUZZER_PIN 35     
#define Servo_PIN 16



void setup() {
  // Initialize Serial Monitor 
  Serial.begin(115200);    
  // initialize the DHT11 sensor
  dht11.begin();
  //attach servo pin
  Servo.attach(Servo_PIN);
  // config the pin mode of each pin
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  //
}

void loop() {

  // read humidity
  float humi  = dht11.readHumidity();
  // read temperature in Celsius
  float tempC = dht11.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht11.readTemperature(true);

  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else if (temp <= 30) {
      
        // servo motor stop 
        Servo.write(95);
       // Serial Monitor show Safe
        Serial.println("Status: SAFE");
       // buzzer no sound
        noTONE(BUZZER_PIN);
  } else if (humi >= 30) {
       // servo motor stop 
        Servo.write(95);
       // Serial Monitor show Caution
        Serial.println("Status: Caution");
       // buzzer continuously alarm
        TONE(BUZZER_PIN, 1000);
      // Measure distance to heat source
      float distance = sonar.ping_cm();
      if (distance == 0) distance = MAX_DISTANCE;  // handle out-of-range

      Serial.print("Heat source distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    } 
    else if (humi < 30)  {
      // servo motor run
        Servo.write(70);
       // Serial Monitor show Dangerous
        Serial.println("Status: Dangerous");
       // buzzer beep
        TONE(BUZZER_PIN, 1000);
        DELAY(300);
        NOTONE(BUZZER_PIN);
        DELAY(300);
  }
  

  // wait a 2 seconds between readings
  delay(2000);
}
