/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Abdurrahman/Documents/labs/lab_8_v2/src/lab_8_v2.ino"

#include "SparkFun_VCNL4040_Arduino_Library.h"
#include <Wire.h>
#include "oled-wing-adafruit.h"
void setup();
void setColor(int red, int green, int blue);
void loop();
#line 5 "c:/Users/Abdurrahman/Documents/labs/lab_8_v2/src/lab_8_v2.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
VCNL4040 proximitySensor;
// setup() runs once, when the device is first turned on.
void setup() {
  Wire.begin();
  display.setup();
	display.clearDisplay();
	display.display();
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  proximitySensor.begin();
  proximitySensor.powerOnAmbient();
  // Put initialization like pinMode and begin functions here.

}
void setColor(int red, int green, int blue){
  analogWrite(D6, red);
  analogWrite(D5, green);
  analogWrite(D7, blue);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  int proxValue = proximitySensor.getProximity(); 
  int ambientValue = proximitySensor.getAmbient();

  if (display.pressedA()) {
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("Proximity Value: ");
    display.print(proxValue);
		display.display();
	}
	if (display.pressedB()) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Ambient Value: ");
    display.print(ambientValue);
    display.display();
	}

	if (display.pressedC()) {
    display.clearDisplay();
    display.setCursor(0,0);
		display.println("I2C address: 0x60");
    display.display();
	}
  if(proxValue < 200){
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,HIGH);
  }
  if (200 <= proxValue && proxValue <= 1000 ){
    digitalWrite(D6,LOW);
    digitalWrite(D5,HIGH);
    digitalWrite(D7,LOW);
  }
  if (proxValue > 1000){
    digitalWrite(D7,LOW);
    digitalWrite(D6,HIGH);
    digitalWrite(D5,LOW);
  }

// digitalWrite(D5,HIGH);
// digitalWrite(D6,HIGH);
// digitalWrite(D4,HIGH);
  // The core of your code will likely live here.

}