#include <MemoryFree.h>
#include <LookupTable.h>

/*
Initialize Seed function pointers
*/

String commandKey = "";         // a string to hold incoming data key
String commandValue = "";         // a string to hold incoming data value
boolean commandComplete = false;  // whether the string is complete
boolean readingKey = true;


/***********************************
** VALUES FOR THIS SEED COMPONENT **
************************************/
const int MAP_SIZE = 3;
LookupTable table(MAP_SIZE);

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
  
  table.blinks();
  
  // reserve 10 bytes for the inputString:
  commandKey.reserve(10);
  commandValue.reserve(10);
  
  pinMode(13, OUTPUT); //led1
  pinMode(motorPin, OUTPUT); //v
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
        Serial.print("Do=>");
        interpretCommand(getNestedKey(commandValue),getNestedValue(commandValue));
      } // No else, only provide else if both behavior are accepted
      break;
    case 1: //led1
      Serial.println("Do=>led1");
      blink(values[key], commandValue.toInt());
      break;
    case 2: //v
      Serial.println("Do=>Vibrate");
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

void printFreeMemory() {
  Serial.print(freeMemory());
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

/** Some cool pointer code
void loop()
{
  byte data[2];

  getdat(&data[0]);
}

void getdat(byte *pdata)
{
  pdata[0] = 'a';
  pdata[1] = 'b';
} 
*/
