#include "ESP8266.h"

ESP8266::ESP8266(int RX, int TX, int baudRate){
	_baudRate = baudRate;
  Serial.println("init esp8266");
  wifi = new SoftwareSerial(RX, TX);
  wifi->begin(baudRate);
  delay(2000);
  commonDelay = 100;
  
// init();
}

String ESP8266::sendData(String command, const int timeout){
	String response = ""; 
  wifi->print(command); // send the read character to the esp8266
  long int time = millis();
    
  while( (time+timeout) > millis()) {
    while(wifi->available()) {
      char c = wifi->read();
      response+=c;      
      Serial.write(c);
    }  
  }
 // Serial.println(response);
  return response;
}

void ESP8266::init() {
  sendData("AT+CWMODE=3\r\n",commonDelay); // configure as access point
  sendData("AT+CIFSR\r\n",commonDelay); // get ip address
  sendData("AT+CIPMUX=0\r\n",commonDelay); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",commonDelay); // turn on server on port 80
  String cmd = "AT+CIOBAUD="+_baudRate;
  cmd += "\r\n";
  sendData(cmd,commonDelay);
//  sendData("AT+CWJAP=?\r\n",1000);
}

String ESP8266::connect(String user, String pass){
  return sendData("AT+CWJAP=\""+user+"\",\""+pass+"\"\r\n",9000);
}

String ESP8266::sendRequest(String dir, int port, String sendRequest, const int timeout){
  int count = 0;
  String cmd = "AT+CIPSTART=\"TCP\",\""+dir+"\","+port+"\r\n"; 
  String response = "";
  

  while(! (response.indexOf("CONNECT") > 0) && count != 5){
      response = sendData(cmd, commonDelay);
      wifi->flush();
      count++;
  }
  if(count == 5){
    Serial.println("cannot connect");
    return response;
  }
  Serial.print("Conn "); 
  count = 0;
  response = "";
  cmd = "GET "+sendRequest+" HTTP/1.1\r\n";
  cmd += "Host:"+dir+"\r\n\r\n";

  String query = "AT+CIPSEND=";
  query += cmd.length();
  query += "\r\n";
  while(! (response.indexOf(">") >= 0) && count != 3){
      response = sendData(query,commonDelay);
      count++;

  }
  response = findResponse(cmd+"\r\n", timeout);

  sendData("AT+CIPCLOSE", commonDelay);
  wifi->flush();
  return response;
}

String ESP8266::findResponse(String command, const int timeout){
  String response = ""; 
  wifi->print(command); // send the read character to the esp8266
  long int time = millis();

  if(wifi->find("text/html")){ 
    while( (time+timeout) > millis()) {
      while(wifi->available()) {
        char c = wifi->read();
        response+=c;
         Serial.write(c);
      }  
    }    
  }
 // Serial.println(response);
  return response;
}




void ESP8266::printAvailable(){
  while (wifi->available()){
        char c=wifi->read();  
        Serial.write(c);
  }
}