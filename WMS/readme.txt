=====> HIGHLY CONFIDENTIAL <==

/*
 Name:		readme.txt
 Created:	2/26/2022 11:22:27 AM
 Author:	Karthik
*/




----------------------------------------------------------------------------------------------------------------------------------------
Baud Rate = 9600
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t boreMotorStatus = 0;
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t sumpMotorStatus = 0;
----------------------------------------------------------------------------------------------------------------------------------------
void WMStype(uint8_t type);
----------------------------------------------------------------------------------------------------------------------------------------
pinInit(uint8_t _OH_SENSOR, uint8_t SUMP_SENSOR,uint8_t _autoPin, uint8_t _manualPin, const unsigned int _TRIG_PIN,
	const unsigned int _ECHO_PIN, uint8_t _buzzer, uint8_t _error_led, uint8_t _sump_motor, uint8_t _contactor, uint8_t _starting_cap)
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t readFloatSensor(uint8_t sensor_pin);
return:
	0 - Water is not there 
	1 - Water is there 
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t readOhSensor();
return:
	0 - Water is not there 
	1 - Water is there  
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t readSumpSensor();
return:
	0 - Water is not there 
	1 - Water is there  
----------------------------------------------------------------------------------------------------------------------------------------
void On(uint8_t motor_pin);
----------------------------------------------------------------------------------------------------------------------------------------
void Off(uint8_t motor_pin);
----------------------------------------------------------------------------------------------------------------------------------------
void boreOn();
----------------------------------------------------------------------------------------------------------------------------------------
void boreOff();
----------------------------------------------------------------------------------------------------------------------------------------
void sumpOn();
----------------------------------------------------------------------------------------------------------------------------------------
void sumpOff();
----------------------------------------------------------------------------------------------------------------------------------------
void readOnlineCommand();
----------------------------------------------------------------------------------------------------------------------------------------
String getMode();
return:
	AUTO_MODE
	MANUAL_MODE
	IDLE
----------------------------------------------------------------------------------------------------------------------------------------
uint8_t readUsSensor();
return:
	The distance between the water and sensor in cm
----------------------------------------------------------------------------------------------------------------------------------------
void errorDetection(uint8_t errorFlag, uint8_t sumpFlag);






