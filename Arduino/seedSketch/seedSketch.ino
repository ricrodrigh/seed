#include <HashMap.h>
#include <MemoryFree.h>

/*
Initialize Seed function pointers
*/

String commandKey = "";         // a string to hold incoming data key
String commandValue = "";         // a string to hold incoming data value
boolean commandComplete = false;  // whether the string is complete
boolean readingKey = true;

unsigned int i = 9;

/***********************************
** VALUES FOR THIS SEED COMPONENT **
************************************/
const int HASH_SIZE = 3;

char BLINK[] = "b";
char LED_1[] = "led1";
char MOTOR_PIN[] = "v";

//storage 
HashType<char*,int> hashRawArray[HASH_SIZE]; 
//handles the storage [search,retrieve,insert]
HashMap<char*,int> hashMap = HashMap<char*,int>( hashRawArray , HASH_SIZE ); 

/*
  b:{led1}={5} blink pin P five times (ex. b:led1=10, sending only b:4 does nothing since there is no key for b)
  v:5 (vibrate N times)
*/

/************************
** Some default values **
*************************/
const int blinkDuration = 100;

void setup()   {
  int index = 0;
  // initialize serial:
  Serial.begin(9600);
    
  // reserve 10 bytes for the inputString:
  commandKey.reserve(10);
  commandValue.reserve(10);
  
  //Init led1
  hashMap[index++](BLINK, 0);
  hashMap[index++](LED_1, 13);
  pinMode(13, OUTPUT); //led1
  
  // Init vibrating motor
  hashMap[index++](MOTOR_PIN, 10);
  pinMode(10, OUTPUT); //v
  
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
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
  
  byte keyIndex = get(commandKey); 
  
  Serial.print("Foung Key in map: ");
  Serial.println(keyIndex);
  
  switch (keyIndex) {
    case 0: //blink
      if(containsNestedCommand(commandValue)){
        Serial.print("Do=>");
        interpretCommand(getNestedKey(commandValue),getNestedValue(commandValue));
      } // No else, only provide else if both behavior are accepted
      break;
    case 1: //led1
      Serial.println("Do=>led1");
      blink(hashMap.getValueOf(LED_1), commandValue.toInt());
      break;
    case 2: //vibrate motor
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

/*
 *
*/
byte get(String commandKey) {
  int str_len = commandKey.length() +  1; 
  char char_array[str_len];
  commandKey.toCharArray(char_array, str_len);
  return hashMap.getIndexOf(char_array);
}
