#include <SoftwareSerial.h>
 
const byte RxD = 10;
const byte TxD = 11;
const byte luz = 7;

const byte LEDPIN = 13; 
 
SoftwareSerial WSerial(RxD, TxD);
 
String  dir = "192.168.1.101",
        port = "9000",
        protocol = "TCP",
        request = "/getStatus";

bool state = false;

void setup() 
{
    pinMode(LEDPIN, OUTPUT);
    pinMode(luz, OUTPUT);

    Serial.begin(57600);   
    WSerial.begin(57600); 
 
    delay(5000);  //esp takes a while to restart

 
    
}
 
void loop(){
  delay(1000);  //esp takes a while to restart

  String cmd = "AT+CIPSTART=\"TCP\",\"";  //make this command: AT+CPISTART="TCP","146.227.57.195",80
  cmd += dir; 
  cmd += "\",9000";
  WSerial.println(cmd);  //send command to device
  delay(1000);  //wait a little while for 'Linked' response - this makes a difference
  if(WSerial.find("Linked"))  //message returned when connection established WEAK SPOT!! DOESN'T ALWAYS CONNECT
  {
    Serial.print("Connected to server at ");  //debug message
   // Serial.println(DST_IP);
  }
  else
  {
    Serial.println("'Linked' response not received");  //weak spot! Need to recover elegantly
  }

  cmd = "GET "+request+" HTTP/1.1\r\n";
  //  /webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=off&q=hola HTTP/1.1\r\n";  //construct http GET request
  cmd += "Host:"+dir+"\r\n\r\n";        //test file on my web
  WSerial.print("AT+CIPSEND=");                //www.cse.dmu.ac.uk/~sexton/test.txt
  WSerial.println(cmd.length());
  
  if(WSerial.find(">"))    //prompt offered by esp8266
  {
    Serial.println("found > prompt - issuing GET request");  //a debug message
    WSerial.println(cmd);  //this is our http GET request
  }
  else
  {
    WSerial.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }
  
  // Agrego un filtro, para que tome la respuesta a partir de la palabra indicada. 
  if(WSerial.find("lstatus:")){
    digitalWrite(LEDPIN, HIGH);
    for (int i=0;i<1;i++)  //this should capture the 'Date: ' line from the header    
    {
      if (WSerial.available())  //new cahracters received?      
      {
        char c=WSerial.read();  //print to console
        Serial.write(c);
        if(c=='1'){
          Serial.println("true"); 
          digitalWrite(luz,false);
        }else{
          Serial.println("false");          
          digitalWrite(luz,true);
        }
      }
      else i--;  //if not, keep going round loop until we've got all the characters
    }
  }else{
     Serial.println("No se encontraron datos");
  }
    
  
  digitalWrite(LEDPIN, LOW);
  delay(500);
  WSerial.println("AT+CIPCLOSE");  

  if(WSerial.find("Unlink"))  //rarely seems to find Unlink? :(
  {
    WSerial.println("Connection Closed Ok...");
  }
  else
  {
    Serial.println("connection close failure");
  }

}

