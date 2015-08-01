
#ifndef ESP8266_h
#define ESP8266_h
#include "Arduino.h"
#include "SoftwareSerial.h"


class ESP8266 {
	public:
		ESP8266(int RX, int TX, int baudRate);
		String sendData(String command, const int timeout);
		String connect(String user, String pass);
		String sendRequest(String dir, int port, String sendRequest, const int timeout);
	private:
		SoftwareSerial * wifi;
	    void init();
};

#endif