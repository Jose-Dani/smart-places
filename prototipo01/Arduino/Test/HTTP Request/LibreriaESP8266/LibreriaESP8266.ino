#include <SoftwareSerial.h>
#include <ESP8266.h>

ESP8266 * wifi;
int ledpin = 13;
int rele = 6;
int baud = 9600;
void setup() {
  Serial.begin(baud);
  pinMode(ledpin, OUTPUT);
  pinMode(rele, OUTPUT);

  wifi = new ESP8266(3,2,baud);
  //wifi->init();
  wifi->connect("Telecentro-2a2a","tele-3033573");
  digitalWrite(ledpin, HIGH);
  delay(200);
  digitalWrite(ledpin, LOW);

  
}

void loop() {
 // wifi->sendRequest("google.com", 80, "/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=off&q=hola\r\n\r\n", 2000);
 // wifi->sendRequest("smartplaces.esy.es", 80, "/", 2000);
//  String response = wifi->sendRequest("smartplaces.esy.es", 80, "/?action=status", 2000);  
  //  String response = wifi->sendRequest("smartplaces.esy.es", 80, "/?action=status&id=1", 1000);  
 //   String response = wifi->sendRequest("192.168.0.32", 3000, "/getone", 1000);  
   String response = wifi->sendRequest("192.168.0.29", 8888, "/smartplaces/index.php?action=status&id=2", 500);  

 // Serial.println(response);
  Serial.print("RES ");
  int lightStatus = getStatus(response);
  Serial.println(lightStatus);
  if(lightStatus == 1){
    digitalWrite(ledpin, HIGH);
    digitalWrite(rele, HIGH);
  }else if(lightStatus == 0){
    digitalWrite(ledpin, LOW);
    digitalWrite(rele, LOW);
  }
}


int getStatus(String response){
  int from = response.indexOf("0");    
  if(from == -1){
    if(response.indexOf("1") != -1 ){
      return 1;
    }else{
      return -1;
    }
    return 1;
  }
  return 0;   
}
