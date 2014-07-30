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
  #include <SoftwareSerial.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
 
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
 
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
 
// Blueduino comunicate with BLE module through pin11, pin12 as soft serial.
SoftwareSerial mySerial(11, 12); //RX,TX
 
int i = 0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
 
// pins for the LEDs:
const int greenPin = 4;
const int redPin = 5;
 
void setup()   {
  // initialize serial:
  mySerial.begin(9600);
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
 
  // Clear the buffer.
  display.clearDisplay();
 
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Awaiting input");
  display.display();
 
  // initialize serial:
  mySerial.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(100);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
}
 
void loop() {
 
 if (stringComplete) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(inputString);
    display.display();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  // if there's any serial available, read it:
  while (mySerial.available()) {
    digitalWrite(greenPin, HIGH);
    char c = mySerial.read();
    inputString += c;
    if(c == 0) {
      digitalWrite(redPin, LOW);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(inputString);
      display.display();
      inputString = "";
    } else {
      digitalWrite(redPin, HIGH);
    }
    if (c == 1) {
      stringComplete = true;
    }
  }
  digitalWrite(greenPin, LOW);
}
 
void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
 
  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}
