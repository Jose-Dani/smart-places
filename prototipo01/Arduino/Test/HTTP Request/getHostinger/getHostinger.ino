#include <SoftwareSerial.h>
 
const byte LEDPIN = 13; 
 
SoftwareSerial WSerial(3, 2);
 
String  dir = "smartplaces.esy.es",
        port = "9000",
        protocol = "TCP";

void setup() 
{
    pinMode(LEDPIN, OUTPUT);
 
    Serial.begin(9600);   
    WSerial.begin(9600); 
 
    
   delay(5000);  //esp takes a while to restart

    
}
 
void loop(){

  while(!cipStart("TCP", dir, 80)){}
  while(!cipSend("/?action=status\r\n\r\n"));
  
  finder("<HTML>", 35);
    
  digitalWrite(LEDPIN, LOW);
  delay(500);
  
  cipClose();

}



bool cipStart(String protocol, String dir, int port){
  String cmd = "AT+CIPSTART=\"TCP\",\"";  
  cmd += dir; 
  cmd += "\",80";
  WSerial.println(cmd); 
  delay(500); 
  if(WSerial.find("CONNECT")){
    Serial.print("Connected to server at "); 
   return true; 
  } else {
    Serial.println("'Linked' response not received"); 
    return false;
  }
}

bool cipSend(String request){
 String cmd;

  cmd = "GET /?action=status HTTP/1.1";
  //cmd += request; 
  
  WSerial.print("AT+CIPSEND=");                
  WSerial.println(cmd.length());
  
  if(WSerial.find(">"))  {
    Serial.println("found > prompt - issuing GET request"); 
    WSerial.println(cmd);  
    return true;
  } else {
    WSerial.println("AT+CIPCLOSE"); 
    Serial.println("No '>' prompt received after AT+CPISEND");
    return false;
  } 
}

void finder(char* finding, int responseLength){
  if(WSerial.find(finding)){
    digitalWrite(LEDPIN, HIGH);
    Serial.write(finding);

    for (int i=0;i<responseLength;i++)  
    {
      if (WSerial.available())      
      {
        char c=WSerial.read();  
        Serial.write(c);
      }
      else i--;  
    }
  } 
}

void cipClose(){
   WSerial.println("AT+CIPCLOSE");  

  if(WSerial.find("OK"))  {
    WSerial.println("Connection Closed Ok...");
  } else {
    Serial.println("connection close failure");
  } 
}



