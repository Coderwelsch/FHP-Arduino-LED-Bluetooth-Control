// includes
#include <FastLED.h>
#include <EEPROM.h>

// defines
#define RX_PIN 10
#define TX_PIN 11
#define DATA_PIN 3
#define NUM_LEDS 120
#define LED_TYPE WS2812B

#define MAX_BRIGHTNESS 100

#define SAVE_ADDR_BRIGHT 0
#define SAVE_ADDR_COLOR 1

// global vars
String btData;
CRGB leds[ NUM_LEDS ];


// functions
void setup () {
	// stripe safe start
	delay( 3000 );

	Serial.begin( 9600 );
	Serial.println( "Bluetooth available" );

	initLED();
}

void loop () {
	btData = getSerialData();

	if ( btData != "" ) {
		int indexOfDelimeter = btData.indexOf( "=" );
		String key = btData.substring( 0, indexOfDelimeter );
		String value = btData.substring( indexOfDelimeter + 1 );

		processStatement( key, value );
	}

	delay( 100 );
}

void initLED () {
	int brightness = ( int ) EEPROM.read( SAVE_ADDR_BRIGHT );
	String color = String( EEPROM.read( SAVE_ADDR_COLOR ) );

	FastLED.addLeds< LED_TYPE, DATA_PIN >( leds, NUM_LEDS );

	processStatement( "BRIGHT", String( brightness ) );
	// processStatement( "COLOR", color );

	for ( int i = 0; i < NUM_LEDS; i++ ) {
		leds[ i ] = CRGB::White;
	}

	FastLED.show();
}

void processStatement ( String key, String value ) {
	if ( key == "BRIGHT" ) {
		int bright = value.toInt();

		if ( ( bright < 0 ) || ( bright > MAX_BRIGHTNESS ) ) {
			bright = ( int )( MAX_BRIGHTNESS / 2 );
		}

		EEPROM.write( SAVE_ADDR_BRIGHT, bright );

		FastLED.setBrightness( bright );
		FastLED.show();

		Serial.println( "BRIGHTNESS: " + String( bright ) );
	} else if ( key == "COLOR" ) {
		String hexstring = value;

		// EEPROM.write( SAVE_ADDR_COLOR, String( value ) );

		long number = strtol( &hexstring[1], NULL, 16);
		long r = number >> 16;
		long g = number >> 8 & 0xFF;
		long b = number & 0xFF;

		for ( int i = 0; i < NUM_LEDS; i++ ) {
			leds[ i ].r = g;
			leds[ i ].g = r;
			leds[ i ].b = b;
		}

		FastLED.show();

		Serial.println( "COLOR: " + value );
	}
}

String getSerialData () {
	String junk;
	String returnValue = "";

	if ( Serial.available() ) {
		while ( Serial.available() ) {
			returnValue += (char) Serial.read();
		}

		// clear left junk
		while ( Serial.available() > 0 ) {
			junk = Serial.read();
		}
	}

	return returnValue;
}
