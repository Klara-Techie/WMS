/*
 Name:		WMS_2.ino
 Created:	2/28/2022 7:15:09 PM
 Author:	Karthik
 Status:	Under development 

 UPDATE		VERSION		DATE			Mod-BY
	1		 2.0.1		Mar 08, 2022	Karthik
	2		 2.0.2		Mar 13, 2022	Karthik
	3		 2.0.3		Apr 06, 2022	Karthik
	4		 2.1.0		May 04, 2022	Karthik
	5		 2.1.1		May 05, 2022	Karthik


 *{v2.1.0
 * OhSensor is connected with gnd --> Water is not available (0).
 * OhSensor is not connected with gnd --> Water is available (1). 
 * 
 * For sump Vice-Versa
 * 
 * SumpSensor is connected with gnd --> Water is available (1). 
 * SumpSensor is not connected with gnd --> Water is not available (0).
 * 
 * Critical timing updated --> For both sump and bore.
 * 
 * SWTOK
 * }v2.1.0
 * 
 * {v2.1.1
 * Code readability increased 
 * }v2.1.1
 * 
*/


#include <WMS.h>
#include <SimpleTimer.h>
#include "define.h"

SimpleTimer timer;

// the setup function runs once when you press reset or power the board
void setup() {
	WMS.pinInit(OhSensor, SumpSensor, autoPin, manualPin, trigPin, echoPin, 
				buzzer, errorLed, sumpMotorPin, contactorPin, startingCapPin);
	mode = WMS.getMode();
	currentTime = millis();
#if DEBUG_MODE
	Serial.println("Code Initialized.....");
#endif // DEBUG_MODE
}

// the loop function runs over and over again until power down or reset
void loop()
{
	timer.run();
	currentTime = millis();
	mode = WMS.getMode();


#if		WITHOUT_WIFI
	
	WMS.errorDetection(errorFlag, 0);

	if (mode IS "AUTO_MODE")
	{
    criticalMode();
    
#if	  SUMP
		if (OH_TANK IS EMPTY)
		{
			if ((SUMP_TANK IS FULL) && (errorFlag IS OFF))
			{
				if (SUMP_MOTOR IS OFF)
				{
					lastTime = currentTime;
					Serial.println("Last time is setted...");
				}
				WMS.sumpOn();
				WMS.Off(errorLed);
			}
			else
			{
				WMS.sumpOff();
				WMS.On(errorLed);
			}

		}
		else
		{
			WMS.sumpOff();
		}

#if DEBUG_MODE
		Serial.println("\n...Without WiFi - AUTO MODE - SUMP ENABLED...");
		Serial.print("\nWater Status in OH:\t");
		Serial.println(OH_TANK);
		Serial.print("Water Status in SUMP:\t");
		Serial.println(SUMP_TANK);
		Serial.print("Error Flag Status:\t");
		Serial.println(errorFlag);
		Serial.print("SUMP Motor Status:\t");
		Serial.println(SUMP_MOTOR);
    Serial.println("---------------------------------------------------");
    delay(2000);
#endif // DEBUG_MODE
   
#elif BORE_1_3
		if (OH_TANK IS EMPTY)
		{
			if ((BORE_MOTOR IS OFF) && (errorFlag IS OFF))
			{
				lastTime = currentTime;
				Serial.println("Last time is setted...");
				WMS.boreOn();
			}
		}
		else
		{
			WMS.boreOff();
		}

#if DEBUG_MODE
		Serial.println("\n...Without WiFi - AUTO MODE - BORE_1_3 ENABLED...");
		Serial.print("\nWater Status in OH:\t");
		Serial.println(OH_TANK);
		Serial.print("Error Flag Status:\t");
		Serial.println(errorFlag);
		Serial.print("Bore Motor Status:\t");
		Serial.println(BORE_MOTOR);
		Serial.print("Starting Cap Status:\t");
		Serial.println(digitalRead(startingCapPin));
		Serial.print("Contactor Status:\t");
		Serial.println(digitalRead(contactorPin));
		Serial.println("---------------------------------------------------");
		delay(2000);
#endif // DEBUG_MODE

#elif SUMP_BORE_1_3
		if (OH_TANK IS EMPTY)
		{
			if (SUMP_TANK IS FULL)
			{
				if ((SUMP_MOTOR IS OFF) && (errorFlag IS OFF))
				{
					lastTime = currentTime;
					Serial.println("Last time is setted...");
					WMS.sumpOn();
					WMS.boreOff();
				}

				WMS.Off(errorLed);
			}
			else
			{
				WMS.sumpOff();
				WMS.On(errorLed);
				if ((BORE_MOTOR IS OFF) && (errorFlag IS OFF))
				{
					lastTime = currentTime;
					Serial.println("Last time is setted...");
					WMS.boreOn();
				}
			}
		}
		else
		{
			WMS.sumpOff();
			WMS.boreOff();
		}

#if DEBUG_MODE
		Serial.println("\n...Without WiFi - AUTO MODE - SUMP_BORE_1_3 ENABLED...");
		Serial.print("\nWater Status in OH:\t");
		Serial.println(OH_TANK);
		Serial.print("Water Status in SUMP:\t");
		Serial.println(SUMP_TANK);
		Serial.print("Error Flag Status:\t");
		Serial.println(errorFlag);
		Serial.print("SUMP Motor Status:\t");
		Serial.println(SUMP_MOTOR);
		Serial.print("Bore Motor Status:\t");
		Serial.println(BORE_MOTOR);
		Serial.print("Starting Cap Status:\t");
		Serial.println(digitalRead(startingCapPin));
		Serial.print("Contactor Status:\t");
		Serial.println(digitalRead(contactorPin));
		Serial.println("--------------------------------------------------------");
		delay(2000);
#endif // DEBUG_MODE

#elif BORE_1_3_TO_SUMP_TO_OH

		if (SUMP_TANK IS FULL)
		{
			WMS.boreOff();
			WMS.Off(errorLed);

			if (OH_TANK IS EMPTY)
			{
				if ((SUMP_MOTOR IS OFF) && (errorFlag IS OFF))
				{
					lastTime = currentTime;
					Serial.println("Last time is setted...");
					WMS.sumpOn();
					WMS.boreOff();
				}

			}
			else
			{
				WMS.sumpOff();
			}
		}
		else if (SUMP_TANK IS EMPTY)
		{
			WMS.sumpOff();
			WMS.On(errorLed);
			if ((BORE_MOTOR IS OFF) && (errorFlag IS OFF))
			{
				lastTime = currentTime;
				Serial.println("Last time is setted...");
				WMS.boreOn();
			}
		}

#if DEBUG_MODE
		Serial.println("\n...Without WiFi - AUTO MODE - SUMP_BORE_1_3 ENABLED...");
		Serial.print("\nWater Status in OH:\t");
		Serial.println(OH_TANK);
		Serial.print("Water Status in SUMP:\t");
		Serial.println(SUMP_TANK);
		Serial.print("Error Flag Status:\t");
		Serial.println(errorFlag);
		Serial.print("SUMP Motor Status:\t");
		Serial.println(SUMP_MOTOR);
		Serial.print("Bore Motor Status:\t");
		Serial.println(BORE_MOTOR);
		Serial.print("Starting Cap Status:\t");
		Serial.println(digitalRead(startingCapPin));
		Serial.print("Contactor Status:\t");
		Serial.println(digitalRead(contactorPin));
		Serial.println("--------------------------------------------------------");
		delay(3000);
#endif // DEBUG_MODE

#endif // Type Selection (SUMP, BORE_1_3, SUMP_BORE_1_3, BORE_1_3_TO_SUMP_TO_OH)

	}
	else if (mode IS "MANUAL_MODE")
	{
#if BORE_1_3
	WMS.boreOn();
#else
	WMS.sumpOn();
#endif // BORE_1_3

	}
	else if (mode IS "IDLE")
	{
		WMS.sumpOff();
		WMS.boreOff();
	}
	else
	{
		/* Do Nothing */
	}


#elif	WITH_WIFI



#endif // WITHOUT_WIFI

}

void criticalMode(void)
{
	if ((currentTime - lastTime >= delayTime) && ((BORE_MOTOR IS ON) || (SUMP_MOTOR IS ON)))
	{
		WMS.sumpOff();
		WMS.boreOff();
		errorFlag = ON;
		Serial.println("Motor OFF: Sensor has problem...");
	}
}
