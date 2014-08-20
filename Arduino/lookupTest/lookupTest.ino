/* 
== Lookup Test ==

Test the LookupTable functionality with memory
consumption evaluation

*/
#include <LookupTable.h>
#include <MemoryFree.h>


/***********************************
** VALUES FOR THIS SEED COMPONENT **
************************************/
const int MAP_SIZE = 3;
LookupTable table(MAP_SIZE);

const String VALUE_A = "aValue";
const String VALUE_B = "b";
const String VALUE_C = "V";
const String VALUE_D = "dVal";

void setup()   {
  // initialize serial:
  Serial.begin(9600);
  delay(2500);
  
  testLookupTable();
}
  
void testLookupTable () {
  Serial.println("=Printall=");
  printAll();
  Serial.println("=modify=");
  modify();
  Serial.println("=print after modify=");
  printAll();

  Serial.println("=Get All value=");
  getAllValues();
} 

void getAllValues() {
  Serial.println("Index\t Value");
  for(int i = 0; i < MAP_SIZE + 1; i++) {
      getOneValue(i);
  }
}

void getOneValue(int indexPosition) {
    int value = table.getValue(indexPosition);
    Serial.print(indexPosition);
    Serial.print("\t");
    Serial.println(value);
}

void modify() {
  String  inputKey = "modifyKey";
  int newValue = 150;
  table.setKey(inputKey);
  Serial.println();
  table.setValue(newValue);
}

void printAll() {
  String  inputKey = "inputKey";
  int tableSize = table.getSize();
  String key = table.getKey(inputKey);
  int value = table.getValue();
  
  Serial.println("Size\t Key \t Value");
  Serial.print(tableSize);
  Serial.print("\t");
  Serial.print(key);
  Serial.print("\t");
  Serial.println(value);
}

void loop() {
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
