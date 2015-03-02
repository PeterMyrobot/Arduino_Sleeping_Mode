// AVR_Sleep.ino 
//Example from   === http://swf.com.tw/?p=525  ===
#include <Enerlib.h>

Energy energy; //宣告"Energy"程式物件

const byte swPin = 2;
const byte ledPin = 13;
byte times = 0;
volatile byte state = 0;

void wakeISR(){
	if(energy.WasSleeping()){
		state = 1;	    
	}
	else{
		state = 2;
	}
}

void setup() {
	Serial.begin(9600);

	pinMode(ledPin, OUTPUT);
	pinMode(swPin, INPUT);
	digitalWrite(swPin, HIGH);

	attachInterrupt(0, wakeISR, CHANGE);

	Serial.println("Running...");
}

void loop() {
	if(state == 1){
		Serial.println("Was WasSleeping...");
	}
	else if(state == 2){
		Serial.println("Was awake...");
	}
	state = 0;

	digitalWrite(ledPin, !digitalRead(ledPin) );
	delay(500);
	times ++ ;
	Serial.println(times);

	if(times > 5 ){
		times = 0;
		Serial.println("Go to sleep...");
		energy.PowerDown();
	}

}

