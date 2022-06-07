/* =====> HIGHLY CONFIDENTIAL <==
 Name:		WMS.cpp
 Created:	2/26/2022 11:22:27 AM
 Author:	Karthik
*/

#include "WMS.h"

void WMSclass::WMStype(uint8_t type)
{
	_type = type;
	switch (_type)
	{
	case BORE_1_3:
		Serial.println("BORE_1_3 Activated .....");
		break;
	case SUMP:
		Serial.println("SUMP Activated .....");
		break;
	case SUMP_BORE_1_3:
		Serial.println("SUMP_BORE_1_3 Activated .....");
		break;
	case BORE_1_3_TO_SUMP_TO_OH:
		Serial.println("BORE_1_3_TO_SUMP_TO_OH Activated .....");
		break;
	default:
		break;
	}
}

void WMSclass::pinInit(uint8_t OH_SENSOR, uint8_t SUMP_SENSOR,uint8_t autoPin, uint8_t manualPin, unsigned int TRIG_PIN,
	unsigned int ECHO_PIN, uint8_t buzzer, uint8_t error_led, uint8_t sump_motor, uint8_t contactor, uint8_t starting_cap)
{
	Serial.begin(9600);
	//Serial.println("Initiated.....");
	
	 _OH_SENSOR = OH_SENSOR;
	 _SUMP_SENSOR = SUMP_SENSOR;
	 _autoPin = autoPin;
	 _manualPin = manualPin;
	 _TRIG_PIN = TRIG_PIN;
	 _ECHO_PIN = ECHO_PIN;
	 _buzzer = buzzer;
	 _error_led = error_led;
	 _sump_motor = sump_motor;
	 _contactor = contactor;
	 _starting_cap = starting_cap;

	 pinMode(_OH_SENSOR, INPUT);
	 pinMode(_OH_SENSOR, INPUT_PULLUP);
	 pinMode(_SUMP_SENSOR, INPUT);
	 pinMode(_SUMP_SENSOR, INPUT_PULLUP);
	 pinMode(_autoPin, INPUT);
	 pinMode(_autoPin, INPUT_PULLUP);
	 pinMode(_manualPin, INPUT);
	 pinMode(_manualPin, INPUT_PULLUP);
	 pinMode(_ECHO_PIN, INPUT);
	 pinMode(_TRIG_PIN, OUTPUT);
	 pinMode(_buzzer, OUTPUT);
	 pinMode(_error_led, OUTPUT);
	 pinMode(_sump_motor, OUTPUT);
	 pinMode(_contactor, OUTPUT);
	 pinMode(_starting_cap, OUTPUT);
}

uint8_t WMSclass::readFloatSensor(uint8_t sensor_pin)
{
	int sensor_value = digitalRead(sensor_pin);
	if (sensor_value == 0)
		return 0;
	else
		return 1;
}
uint8_t WMSclass::readOhSensor()
{
	return readFloatSensor(_OH_SENSOR);
}

uint8_t WMSclass::readSumpSensor()
{
/*
	int sensor_value = digitalRead(_SUMP_SENSOR);
	if (sensor_value == 0)
		return 1;
	else
		return 0;
*/
	return readFloatSensor(_SUMP_SENSOR);
}

void WMSclass::On(uint8_t motor_pin)
{
	digitalWrite(motor_pin, ON);
}

void WMSclass::Off(uint8_t motor_pin)
{
	digitalWrite(motor_pin, OFF);
}

void WMSclass::boreOn()
{
	if (boreMotorStatus == 0)
	{
		boreMotorStatus = 1;
		On(_starting_cap);
		On(_contactor);
		delay(400);
		Off(_starting_cap);
	}
}
void WMSclass::boreOff()
{
	if (boreMotorStatus == 1)
	{
		boreMotorStatus = 0;
		Off(_contactor);
	}
}

void WMSclass::sumpOn()
{
	if (sumpMotorStatus == 0)
	{
		sumpMotorStatus = 1;
		On(_sump_motor);
	}	
}

void WMSclass::sumpOff()
{
	if (sumpMotorStatus == 1)
	{
		sumpMotorStatus = 0;
		Off(_sump_motor);
	}
}

void WMSclass::readOnlineCommand()
{
	_onlineData = Serial.readStringUntil('\n');

	if (_onlineData == "SUMP_MOTOR_ON")
	{
		sumpOn();
		//Serial.println("SUMP_MOTOR_ON.....");
	}
	else if (_onlineData == "SUMP_MOTOR_OFF")
	{
		sumpOff();
		//Serial.println("SUMP_MOTOR_OFF.....");
	}

	if (_onlineData == "BORE_MOTOR_ON")
	{
		boreOn();
		//Serial.println("BORE_MOTOR_ON.....");
	}
	else if (_onlineData == "BORE_MOTOR_OFF")
	{
		boreOff();
		//Serial.println("BORE_MOTOR_OFF.....");
	}
}

String WMSclass::getMode()
{
	int auto_value = digitalRead(_autoPin);
	int manual_value = digitalRead(_manualPin);

	if (auto_value == 0)
	{
		return "AUTO_MODE";
	}
	else if (manual_value == 0)
	{
		return "MANUAL_MODE";
	}
	else
	{
		return "IDLE";
	}
}

uint8_t WMSclass::readUsSensor()
{
	digitalWrite(_TRIG_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(_TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(_TRIG_PIN, LOW);

	const unsigned long duration = pulseIn(_ECHO_PIN, HIGH);
	int distance = duration / 29 / 2;
	if (duration == 0)
	{
		/* do nothing */
	}
	else if (distance != 1030)
	{
		/* do nothing */
	}
	else
	{
		return distance;
	}
}

void WMSclass::errorDetection(uint8_t errorFlag, uint8_t sumpFlag)
{
	if (errorFlag == 1)
	{
		On(_buzzer);
		On(_error_led);
		delay(800);
		Off(_buzzer);
		Off(_error_led);
	}
	else if (sumpFlag == 1)
	{
		On(_buzzer);
		On(_error_led);
	}
	else
	{
		Off(_buzzer);
		Off(_error_led);
	}
}

WMSclass WMS;

