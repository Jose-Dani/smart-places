/*
Esta aplicación tiene como objetivo probar la interacción entre dos 
elementos que cambian el estado de la misma luz. 
En este caso, buttonPin representa un botón y ringPin un timbre o switch.
En el caso real, en lugar del botón, la interacción se dará mediante un servicio web
por medio de wifi.
*/


int ledPin = 7;
int buttonPin = 9;
int ringPin = 8;

boolean reading;
boolean flag = false;
boolean switchStatus = false;


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);  
  pinMode(ringPin, INPUT);
  Serial.begin(9600);
  switchStatus = digitalRead(ringPin);
}

void loop(){
  changeStatus(buttonPin);
  //changeStatus(ringPin); Se elige si está conectado un timbre
  changeStatusSwitch(ringPin); // Se elige si está conectado un Switch
  digitalWrite(ledPin, flag);
}
// Para botones (timbres)
void changeStatus(int pin){
  reading = digitalRead(pin);
  if(reading){
    flag = !flag;
    while(reading){
      reading = digitalRead(pin);
    }
    delay(500);
  }  
}

// Para switches
void changeStatusSwitch(int pin){
  if(digitalRead(pin) != switchStatus){
    flag = !flag;
    switchStatus = digitalRead(pin);
    delay(500);  
  }  
}


