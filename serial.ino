#include <SoftwareSerial.h>
#include "Akeru.h"

int incomingByte = 0;
unsigned long time;

// L LED is connected to pin 13, give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {

	// initialize the digital pin of L led as an output
	pinMode(led, OUTPUT);

	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	Serial.println("Starting...");

	// Wait 1 second for the modem to warm
	delay(1000);

	// Init modem
	Akeru.begin();
}

void loop() {

	// Wait for availability of the modem
	while (!Akeru.isReady()) {
		Serial.println("Modem not ready");
		delay(1000);
	}

	time = millis();
	//prints time since program started
	Serial.print("Waiting for read at ");
	Serial.println(time);

	char inbuf[16];
	int charCtr = 0;

	// send data only when you receive data:
	while (charCtr < 12) {
		if (Serial.available() > 0) {

			// read (and block) the incoming byte:
			incomingByte = Serial.read();

			if(incomingByte == '\n') {
				break;
			}

			inbuf[charCtr++] = incomingByte;

			Serial.print("I received: ");
			Serial.println(incomingByte, DEC);
		}
	}
	Serial.println("DEBUG START");
	Serial.println(charCtr);
	Serial.println(inbuf);
	Serial.println("DEBUG END");

	inbuf[charCtr] = 0;

	Serial.print("Whole string: ");
	Serial.println(inbuf);
	Serial.flush();

	// LED is on
	digitalWrite(led, HIGH);

	// Send in the mighty internet!
	if(Akeru.send(&inbuf,sizeof(inbuf))) {
		Serial.print("Sending message:");
		Serial.println(inbuf);
	} else {
		Serial.println("Message DO NOT SEND");
	}

	// LED is off
	digitalWrite(led, LOW);

}
