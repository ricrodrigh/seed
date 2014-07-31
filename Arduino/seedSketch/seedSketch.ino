#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MemoryFree.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

/*
Initialize Seed function pointers
*/

 
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
 
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
 
// Blueduino comunicate with BLE module through pin11, pin12 as soft serial.
// Remove Software serial, replace with normal serial
//SoftwareSerial mySerial(11, 12); //RX,TX
 
int i = 0;
String commandKey = "";         // a string to hold incoming data key
String commandValue = "";         // a string to hold incoming data value
boolean commandComplete = false;  // whether the string is complete
boolean readingKey = true;


/***********************************
** VALUES FOR THIS SEED COMPONENT **
************************************/
const int MAP_SIZE = 3;
const String keySet[MAP_SIZE] = {"b", "led1", "v"};
const int values[MAP_SIZE] = {-1, 13, 10};

/*
  b:{led1}={5} blink pin P five times (ex. b:led1:4, sending only b:4 does nothing since there is no key for b)
  v:5 (vibrate N times)
*/

const int blinkDuration = 100;
const int motorPin = 10;

//***********************************

void setup()   {
  // initialize serial:
  Serial.begin(9600);
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  
  // reserve 10 bytes for the inputString:
  commandKey.reserve(10);
  commandValue.reserve(10);
 
  // initialize serial:
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); //led1
  blink(13, 3);
  
  pinMode(motorPin, OUTPUT); //v
  
  // Clear the buffer.
  display.clearDisplay();
  printToScreen("");
}  
 
void loop() {
 
 if (commandComplete) {
    //printToScreen(commandKey + ":" + commandValue);
    interpretCommand(commandKey, commandValue);
    
    // clear the string:
    commandKey = "";
    commandValue = "";
    commandComplete = false;
  }
  // if there's any serial available, read it:
  while (Serial.available()) {
    char c = Serial.read();
    
    if (c == '\n') {
      commandComplete = true;
      readingKey = true;
      Serial.print(commandKey);
      Serial.print(":");
      Serial.println(commandValue);
    } else if (c == ':') {
      readingKey = false;
    } else {
      if(readingKey) {
        commandKey += c;
      } else {
        commandValue += c;
      }
    }
  }
}

void interpretCommand(String commandKey, String commandValue) {
  Serial.print("Interpreting: ");
  Serial.println(commandKey + ":" + commandValue);
  int key = get(commandKey);
  
  Serial.print("Key: ");
  Serial.println(key);
  switch (key) {
    case 0: //b
      if(containsNestedCommand(commandValue)){
        interpretCommand(getNestedKey(commandValue),getNestedValue(commandValue));
      } // No else, only provide else if both behavior are accepted
      break;
    case 1: //led1
      blink(values[key], commandValue.toInt());
      break;
    case 2: //v
      vibrate(commandValue.toInt());
      break;
  }
}

boolean containsNestedCommand(String command) {
  return command.indexOf("=") != -1 && command.length() > 2;
}

String getNestedKey(String command) {
  return command.substring(0, command.indexOf("="));
}

String getNestedValue(String command) {
  return command.substring(command.indexOf("=") + 1);
}

void printToScreen(String inputString) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(inputString);
  printFreeMemory();
  display.display();
}

void printFreeMemory() {
  display.setCursor(0,15);
  display.println(freeMemory());
}

void blink(int ledPin, int times) {
  for(int i = 0; i <= times; i++){
      digitalWrite(ledPin, HIGH);
      delay(blinkDuration);
      digitalWrite(ledPin, LOW);
      delay(blinkDuration);
  }
}

void vibrate(int times) {
  blink(13, times);
}

int get(String key) {
  for(int i = 0; i < MAP_SIZE; i++) {
    if(keySet[i] == key) {
      return i;
    }
  }
  return -1;
}
