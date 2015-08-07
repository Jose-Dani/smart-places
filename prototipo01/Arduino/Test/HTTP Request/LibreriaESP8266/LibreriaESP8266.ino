#include <SoftwareSerial.h>
#include <ESP8266.h>

ESP8266 * wifi;
int ledpin = 13;
int baud = 19200;
void setup() {
  Serial.begin(baud);
  pinMode(ledpin, OUTPUT);
  wifi = new ESP8266(3,2,baud);
  wifi->init();
  digitalWrite(ledpin, HIGH);
  delay(200);
  digitalWrite(ledpin, LOW);

  
}

void loop() {
 // wifi->sendRequest("google.com", 80, "/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=off&q=hola\r\n\r\n", 2000);
 // wifi->sendRequest("smartplaces.esy.es", 80, "/", 2000);
//  String response = wifi->sendRequest("smartplaces.esy.es", 80, "/?action=status", 2000);  
    String response = wifi->sendRequest("smartplaces.esy.es", 80, "/?action=status&id=1", 600);  

  Serial.println(response);
  Serial.println("RESPONSE ");
  int lightStatus = getStatus(response);
  Serial.println(lightStatus);
  if(lightStatus == 1){
    digitalWrite(ledpin, HIGH);
  }else if(lightStatus == 0){
    digitalWrite(ledpin, LOW);
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
