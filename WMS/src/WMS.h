/* =====> HIGHLY CONFIDENTIAL <==
 Name:		WMS.h
 Created:	2/26/2022 11:22:27 AM
 Author:	Karthik
*/

#ifndef _WMS_h
#define _WMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define		ON							HIGH
#define		OFF							LOW

#define		BORE_1_3					1
#define		SUMP						2
#define		SUMP_BORE_1_3				3
#define		BORE_1_3_TO_SUMP_TO_OH		4

class WMSclass
{
public:

	uint8_t boreMotorStatus = 0;
	uint8_t sumpMotorStatus = 0;

	void WMStype(uint8_t type);
	void pinInit(uint8_t OH_SENSOR, uint8_t SUMP_SENSOR,uint8_t autoPin, uint8_t manualPin, unsigned int TRIG_PIN,
		unsigned int ECHO_PIN, uint8_t buzzer, uint8_t error_led, uint8_t sump_motor, uint8_t contactor, uint8_t starting_cap);
	uint8_t readFloatSensor(uint8_t sensor_pin);
	uint8_t readOhSensor();
	uint8_t readSumpSensor();
	void On(uint8_t motor_pin);
	void Off(uint8_t motor_pin);
	void boreOn();
	void boreOff();
	void sumpOn();
	void sumpOff();
	void readOnlineCommand();
	String getMode();
	uint8_t readUsSensor();
	void errorDetection(uint8_t errorFlag, uint8_t sumpFlag);

private:
	uint8_t _type;
	uint8_t _OH_SENSOR;
	uint8_t _SUMP_SENSOR;
	uint8_t _autoPin;
	uint8_t _manualPin;
	unsigned int _TRIG_PIN;
	unsigned int _ECHO_PIN;
	uint8_t _buzzer;
	uint8_t _error_led;
	uint8_t _sump_motor;
	uint8_t _contactor;
	uint8_t _starting_cap;
	String _onlineData;

};

extern WMSclass WMS;


#endif

