/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers
 
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98
 
This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)
 
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
 
Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
 
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
const int MAP_SIZE = 1;
const String keySet[MAP_SIZE] = {"led1"};
const int values[MAP_SIZE] = {13};

/*
   v:{N} - vibrate for N seconds (ex. v:5 will make seed vibrate for 5 seconds)
   b:{led1}={5} blink pin P five times (ex. b:led1:4)
*/

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
  //display.display();
  //delay(1000);
 
  // Clear the buffer.
  display.clearDisplay();
 
  // reserve 10 bytes for the inputString:
  commandKey.reserve(10);
  commandValue.reserve(10);
 
  // initialize serial:
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
  blink("led1");
}  
 
void loop() {
 
 if (commandComplete) {
    //printToScreen(commandKey + ":" + commandValue);
    
    if(containsNestedCommand(commandValue)) {
      String nestedKey = getNestedKey(commandValue);
      String nestedValue = getNestedValue(commandValue);
      Serial.println(nestedKey);
      Serial.println(nestedValue);
    }
    
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

void blink(String led) {
  int key = get(led);
  if(key != -1) {
    int ledPin = values[key];
    Serial.println("Found pin for " + led + ": " + ledPin);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
  }
}

int get(String key) {
  for(int i = 0; i < MAP_SIZE; i++) {
    if(keySet[i] == key) {
      return i;
    }
  }
  return -1;
}
