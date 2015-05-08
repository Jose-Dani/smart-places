
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
  //changeStatus(ringPin);
  changeStatusSwitch(ringPin);
  digitalWrite(ledPin, flag);
}

void changeStatus(int pin){
  reading = digitalRead(pin);
  if(reading){
    //Serial.write(digitalRead(buttonPin));
    flag = !flag;
    while(reading){
      reading = digitalRead(pin);
    }
    delay(500);
  }  
}

void changeStatusSwitch(int pin){
  if(digitalRead(pin) != switchStatus){
    flag = !flag;
    switchStatus = digitalRead(pin);
    delay(500);  
  }  
}


