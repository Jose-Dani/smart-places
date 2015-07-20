
const char texts[] PROGMEM  = {"Prueba de textos guardados en memoria flash."};

void setup() {
  Serial.begin(9600);
  
  int k;
  char myChar;
  int len = strlen_P(texts);
  for (k = 0; k < len; k++) {
    myChar =  pgm_read_byte_near(texts + k);
    Serial.print(myChar);
  }
  
  Serial.print(sizeof(texts));
}

void loop() {
  // put your main code here, to run repeatedly:

}
