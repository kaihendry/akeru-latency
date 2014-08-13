int incomingByte = 0;   // for incoming serial data

void setup() {
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
	Serial.println("Setting up");
}

void loop() {

	char inbuf[16];
	int charCtr = 0;

	// send data only when you receive data:
	while (charCtr < 12) {
		if (Serial.available() > 0) {

			// read the incoming byte:
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
}
