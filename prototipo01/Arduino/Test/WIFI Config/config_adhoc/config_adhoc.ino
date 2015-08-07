#include <SoftwareSerial.h>
#define DEBUG true

#define BAUDRATE 9600
SoftwareSerial esp8266(3, 2);

// Libreria SpSetup
//#include <Arduino.h>
/**
 * 
 */
class SpSetup {
  private:
    bool _debug;
    SoftwareSerial * _serial;
    
    String sendData(String command, const int timeout, boolean debug);
  public:
    SpSetup(SoftwareSerial &serial);
    void enableDebug();
    void disableDebug();
    void init();
    void listen();
};

SpSetup::SpSetup(SoftwareSerial &serial) {
  _debug = false;
  _serial = &serial;
}

void SpSetup::enableDebug() {
  _debug = true;
}

void SpSetup::disableDebug() {
  _debug = false;
}

void SpSetup::init() {
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}

void SpSetup::listen() {
  if(_serial->available()) {
    if(_serial->find("+IPD,"))
    {
     delay(1000);
 
     char connectionId = _serial->read();
     
     String content = "<body><html><form>SSID:<input type=\"text\" name=\"ssid\" /><br>Password:<input type=\"text\" name=\"password\" /><br><input type=\"submit\" value=\"Save\"></form></html></body>";
     
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
     
     
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
}

String SpSetup::sendData(String command, const int timeout, boolean debug) {
    String response = ""; 
    _serial->print(command); // send the read character to the esp8266
    long int time = millis();
    
    while( (time+timeout) > millis()) {
      while(_serial->available()) {
        // The esp has data so display its output to the serial window 
        char c = _serial->read(); // read the next character.
        response+=c;
      }  
    }
    
    if(_debug) {
      Serial.print(response);
    }
    return response;
}
// Fin de libreria


SpSetup spSetup = SpSetup(esp8266);

void setup() {
    Serial.begin(BAUDRATE);   
    esp8266.begin(BAUDRATE);
    
    spSetup.enableDebug();
    spSetup.init();
}
 
void loop() {
  spSetup.listen();
}
