#include <SoftwareSerial.h>
#define DEBUG true
const byte LEDPIN = 13; 
 
SoftwareSerial WSerial(3, 2);
 
String  dir = "google.com",
        port = "9000",
        protocol = "TCP";

void setup() 
{
    pinMode(LEDPIN, OUTPUT);
 
    Serial.begin(9600);   
    WSerial.begin(9600); 
 
    
   delay(5000);  //esp takes a while to restart

    sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
    sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
    sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
    sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop(){
  server();
/*
  while(!cipStart("TCP", dir, 80)){}
  while(!cipSend("/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=off&q=hola\r\n\r\n"));
  
  finder("<HTML>", 254);
    
  digitalWrite(LEDPIN, LOW);
  delay(500);
  
  cipClose();
*/
}

void server() {
  if(WSerial.available()) // check if the esp is sending a message 
  {
    if(WSerial.find("+IPD,"))
    {
     delay(1000);
 
     char connectionId = WSerial.read(); // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
                                           
  Serial.print("ConnectionId: ");
  Serial.println(connectionId);
  /*
     String header;
    header =  "HTTP/1.1 200 OK\r\n";
    header += "Content-Type: text/html\r\n";
    header += "Connection: close\r\n";  
    String content;
    content = "Hola";
    header += "Content-Length: ";
    header += (int)(content.length());
    header += "\r\n\r\n";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=header.length()+content.length();
     cipSend +="\r\n";     
     sendData(cipSend,1000,DEBUG);
     
     if (WSerial.find(">")) {     
       sendData(header+content,1000,DEBUG);
     }*/
     
     String content = "<body><html>SSID:<input type=\"text\" name=\"ssid\" /><br>Password:<input type=\"text\" name=\"password\" /><br><input type=\"button\" value=\"Save\"></html></body>";
     
     String texto = "";
     texto += "HTTP/1.1 200 OK\r\n";
     texto += "Content-Type: text/html\r\n";
     texto += "HTTP/1.1 200 OK\r\n";
     texto += "Content-Length: ";
     texto += content.length();
     texto += "\r\n\r\n";
     texto += content;
     
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=texto.length();
     cipSend +="\r\n";
     sendData(cipSend,1000,DEBUG);
     sendData(texto,1000,DEBUG);
     
     
     /*String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
     */
    }
  }
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

  cmd = "GET / HTTP/1.1\r\n";
  cmd += request; 
  
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

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    WSerial.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(WSerial.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = WSerial.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}



