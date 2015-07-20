void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your mai
  n code here, to run repeatedly:

}

bool setCipMux(int value){
  Serial1.println("AT+CIPMUX="+value);
  return isResponseOK(0,"OK");
}

bool setCwMode(int value){
  WSerial.println("AT+CWMODE="+value);
  return isResponseOK(0,"no change");
}

bool setCipMode(int value){
  WSerial.println("AT+CIPMODE="+value);
  return isResponseOK(0,"OK");
}

bool setCwJap(String wifi, String pass){
  String cmd="AT+CWJAP=\"";
  cmd+= wifi;
  cmd+= "\",\"";
  cmd+= pass;
  cmd+= "\"";
  WSerial.println(cmd);
  return isResponseOK(5000, "OK");
}

void setCwLap(){
  WSerial.println("AT+CWLAP");
}

bool resetWifi(){
  WSerial.println("AT+RST");
  return isResponseOK(0, "ready");
}

bool isResponseOK(int delayTime, String finder){
 delay(delayTime);
 if(WSerial.find(finder)) {
    return true;
  }else{
    return false;
  } 
}
