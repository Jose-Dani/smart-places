#include <SoftwareSerial.h>
 
const byte RxD = 3;
const byte TxD = 2;
const byte LEDPIN = 13; 
const int baudRate = 9600; 
SoftwareSerial BTSerial(RxD, TxD);
 
void setup() 
{
    pinMode(LEDPIN, OUTPUT);
 
    Serial.begin(baudRate);   
        delay(1000);

    BTSerial.begin(baudRate); 
 
    delay(1000);
 
    digitalWrite(LEDPIN, HIGH);  
     Serial.println("AT");

    BTSerial.println("AT");
 
    Serial.println("Enter AT commands");
}
 
void loop(){
  if (BTSerial.available()){  
     Serial.write(BTSerial.read());  
  } 
  if (Serial.available()){  
    
     BTSerial.write(Serial.read()); 
  }
}
