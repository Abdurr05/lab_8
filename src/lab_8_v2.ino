
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include <Wire.h>
#include "oled-wing-adafruit.h"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
VCNL4040 proximitySensor;

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
}

void loop() {
  display.loop();

  //get proximity and light level
  int proxValue = proximitySensor.getProximity(); 
  int ambientValue = proximitySensor.getAmbient();

  //display proximity when pressed a on the oled display
  if (display.pressedA()) {
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("Proximity Value: ");
    display.print(proxValue);
		display.display();
	}
  //display light level when pressed b on the oled display
	if (display.pressedB()) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Ambient Value: ");
    display.print(ambientValue);
    display.display();
	}
  //display i2c address when pressed c on the oled display
	if (display.pressedC()) {
    display.clearDisplay();
    display.setCursor(0,0);
		display.println("I2C address: 0x60");
    display.display();
	}

  // if the proximity value is less than 200 (far away) switch the green led on
  if(proxValue < 200){
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,HIGH);
  }
  // if the proximity value is between 200 and 1000 (close) switch the blue led on
  if (200 <= proxValue && proxValue <= 1000 ){
    digitalWrite(D6,LOW);
    digitalWrite(D5,HIGH);
    digitalWrite(D7,LOW);
  }
  // if the proximity value is more than 1000 (very close) switch the orange led on
  if (proxValue > 1000){
    digitalWrite(D7,LOW);
    digitalWrite(D6,HIGH);
    digitalWrite(D5,LOW);
  }

}