
const char content[] PROGMEM = {
  "<body>"
    "<html>"
      "<form>"
        "SSID:"
          "<input type=\"text\" name=\"ssid\" />"
          "<br>"
          "Password:"
          "<input type=\"text\" name=\"password\" />"
          "<br>"
          "<input type=\"submit\" value=\"Save\">"
      "</form>"
    "</html>"
  "</body>"
};

int contentLen = strlen_P(content);
char contentLenChar[contentLen];
String(contentLen).toCharArray(contentLen, contentLen);

const char response[] PROGMEM = {
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "HTTP/1.1 200 OK\r\n"
  "Content-Length:"
  contentLen
  "\r\n\r\n"
};

void setup() {
  Serial.begin(9600);
  
  /*
  int k;
  char myChar;
  int len = strlen_P(prueba);
  for (k = 0; k < len; k++) {
    //myChar =  pgm_read_byte_near(prueba + k);
    
    myChar =  prueba[k];
    
    Serial.print(myChar);
  }*/
  
  //Serial.print(sizeof(prueba));
}

void loop() {
  // put your main code here, to run repeatedly:

}
