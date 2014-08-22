#include <Led.h>

//create a LED object at digital pin 13
byte pin = 13;
Led led = Led(pin);

void setup(){
  Serial.begin(9600);
  delay(2000);
  
  Serial.println("Turning On");
  led.turnOn();
  delay(1000);
  
  Serial.println("Turning Off");
  led.turnOff();
  delay(1000);
  
  Serial.println("Blink");
  led.blink(2000);  
  delay(1000);

  Serial.println("Blink faster, 3 times");
  // Blink on/off in 2000ms, 3 times
  led.blink(200, 3);
  delay(1000);
  
  Serial.println("FadeIn fast");
  led.fadeIn(500);
  delay(1000);
  
  Serial.println("FadeOut slow");
  led.fadeOut(5000);
  
  Serial.println("Toggle on to off");
  led.toggle();
  delay(1000);
  
  Serial.println("Toggle off to on");
  led.toggle();
  delay(1000);
  
  Serial.println("Done");
}

void loop(){
}
