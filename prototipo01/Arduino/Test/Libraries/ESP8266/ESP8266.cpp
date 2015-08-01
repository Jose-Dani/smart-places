#include "ESP8266.h"

ESP8266::ESP8266(int RX, int TX, int baudRate){
	wifi = new SoftwareSerial(RX, TX);
  wifi->begin(baudRate);
  delay(1000);
  init();
}

String ESP8266::sendData(String command, const int timeout){
	String response = ""; 
  wifi->print(command); // send the read character to the esp8266
  long int time = millis();
    
  while( (time+timeout) > millis()) {
    while(wifi->available()) {
      char c = wifi->read();
      response+=c;
    }  
  }
  Serial.println(response);
  return response;
}

void ESP8266::init() {
  sendData("AT+CWMODE=3\r\n",1000); // configure as access point
  sendData("AT+CIFSR\r\n",1000); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000); // turn on server on port 80
//  sendData("AT+CWJAP=?\r\n",1000);
}

String ESP8266::connect(String user, String pass){
  return sendData("AT+CWJAP=\""+user+"\",\""+pass+"\"\r\n",9000);
}

String ESP8266::sendRequest(String dir, int port, String sendRequest, const int timeout){
  String cmd = "AT+CIPSTART= \"TCP\",\""+dir+"\", "+port+"\r\n"; 
  sendData(cmd, 1000);

  cmd = "AT+CIPSEND=";
  String req = "GET / HTTP/1.1\r\n";
  req += sendRequest;
  cmd += req.length();

  //cmd += "\r\n";
  String response = sendData(cmd, 1000);
  response = sendData(sendRequest, timeout);

  if(response.indexOf('>') >= 0){
    response = sendData(sendRequest, timeout);
  }else{
    Serial.println("data not send");
    response = "data not send";
  }



  sendData("AT+CIPCLOSE", 1000);
  return response;
}

