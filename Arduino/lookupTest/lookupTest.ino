/* 
== Lookup Test ==

Test the LookupTable functionality with memory
consumption evaluation

*/
#include <HashMap.h>
#include <MemoryFree.h>

/***********************************
** VALUES FOR THIS SEED COMPONENT **
************************************/
const int HASH_SIZE = 3;

char VALUE_A[] = "aValue";
char VALUE_B[] = "b";
char VALUE_C[] = "V";

//storage 
HashType<char*,int> hashRawArray[HASH_SIZE]; 
//handles the storage [search,retrieve,insert]
HashMap<char*,int> hashMap = HashMap<char*,int>( hashRawArray , HASH_SIZE ); 

void setup()   {
  // initialize serial:
  Serial.begin(9600);
  delay(2500);
  
  //setup hashmap
  hashMap[0](VALUE_A, 180);
  hashMap[1]("b", 198);
  hashMap[2]("c", -1);
  hashMap.debug();
  
  Serial.println("--");
  //Reset value
   hashMap[1]("b", 100);
   hashMap.debug();
   
   
   Serial.println("--");
   //Index not exist
   int index = hashMap.getIndexOf("someValue");
   Serial.print("index of someValue ");
   Serial.println(index);
   boolean containsKey = hashMap.containsKey("someValue");
   Serial.print("Contains someValue ?");
   Serial.println(containsKey);
   containsKey = hashMap.containsKey(VALUE_A);
   Serial.print("Contains VALUE_A ?");
   Serial.println(containsKey);
}

void loop() {
  int index = hashMap.getIndexOf(VALUE_A);
  int value = hashMap.getValueOf(VALUE_A);
  
  for(int i = 0; i < 10; i++) {
    hashMap[index](VALUE_A, ++value);
    Serial.println( hashMap.getValueOf(VALUE_A) );
  }
  
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  delay(1000);
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
