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
  delay(1500);
  
  testGetSize();
  getAllValues();
  
//  /testLookupTable();
}
  
void testLookupTable () {
  Serial.print("Start: ");
  Serial.println(freeMemory());
  
  testGetSize();
  Serial.print("1: ");
  Serial.println(freeMemory());
  
  simpleInit();
  Serial.print("2: ");
  Serial.println(freeMemory());
  
  getAllValues();
  Serial.print("3: ");
  Serial.println(freeMemory());
  
  Serial.print("Done: ");
  Serial.println(freeMemory());
} 

void testGetSize() {
  Serial.print("Size: ");
  Serial.println(table.getSize());
  delay(2000);
}

void simpleInit() {
  String keySet[] = {VALUE_B, VALUE_C, VALUE_A, VALUE_D};
  for(int i = 0; i < MAP_SIZE + 1; i++) {
    Serial.print("Put: ");
    Serial.print(keySet[i]);
    Serial.print(" = ");
    Serial.println(table.put(keySet[i]));
  }
  delay(2000);
}

void getValue() {
  String keySet[] = {VALUE_A, VALUE_B, VALUE_C, VALUE_D};
  for(int i = 0; i < MAP_SIZE + 1; i++) {
    Serial.print("Get: ");
    Serial.print(keySet[i]);
    Serial.print(" = ");
    Serial.println(table.getValue(keySet[i]));
  }
  delay(2000);
}

void getAllValues() {
  table.printValues();  
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
