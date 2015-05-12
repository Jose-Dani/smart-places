#include <SoftwareSerial.h>
 
const byte RxD = 10;
const byte TxD = 11;
const byte LEDPIN = 13; 
 
SoftwareSerial BTSerial(RxD, TxD);
 
void setup() 
{
    pinMode(LEDPIN, OUTPUT);
 
    Serial.begin(19200);   
    BTSerial.begin(19200); 
 
    delay(1000);
 
    digitalWrite(LEDPIN, HIGH);  
 
    Serial.println(" ");
    Serial.println("AT mode.");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
 
    Serial.print("BT STATE = ");
    BTSerial.println("AT+STATE" );
 
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

