// define.h

#ifndef _DEFINE_h
#define _DEFINE_h

/* Among these two, one must be enabled. And all must not be disabled */
#define		WITH_WIFI					DISABLE		//If the device is with wifi, Enable this and diable without wifi 
#define		WITHOUT_WIFI				ENABLE		//If the device is with without wifi, Enable this and diable with wifi

/* Among these four, one must be enabled. And all must not be disabled*/
#define		SUMP						DISABLE		//If the device for sump, Enable this and diable others in this four 
#define		BORE_1_3					DISABLE		//If the device for bore single phase or three phase, Enable this and diable others in this four 
#define		SUMP_BORE_1_3				DISABLE		//If the device for sump(to OH) and bore(to OH) single phase or three phase, Enable this and diable others in this four 
#define		BORE_1_3_TO_SUMP_TO_OH		ENABLE		//If the device for sump(to OH) and bore(to SUMP) single phase or three phase, Enable this and diable others in this four

/* If need to debug or see the serial monitor this should be enabled. Otherwise it must be disabled. */
#define		DEBUG_MODE					ENABLE

/*Const Macros for code readability*/
#define		OH_TANK						WMS.readOhSensor()
#define		SUMP_TANK					WMS.readSumpSensor()
#define     SUMP_MOTOR					WMS.sumpMotorStatus
#define		BORE_MOTOR					WMS.boreMotorStatus
#define		FULL						1
#define		EMPTY						0
#define		ON							1
#define		OFF							0
#define		IS							==

/* When water is not there, the float switch should be in continuity. This way it has to be connected */
#define		OhSensor					11			//Atmega Pin Number 17
#define		SumpSensor					12			//Atmega Pin Number 18
#define		autoPin						A0			//Atmega Pin Number 23
#define		manualPin					A5			//Atmega Pin Number 28
#define		buzzer						A2			//Atmega Pin Number 25
#define		errorLed					A4			//Atmega Pin Number 27

#define		ENABLE						1
#define		DISABLE						0

#if	  SUMP
	#define		sumpMotorPin			10			//Atmega Pin Number 16
	#define		contactorPin			5			//Atmega Pin Number 11
	#define		startingCapPin			A3			//Atmega Pin Number 26
#elif BORE_1_3
	#define		sumpMotorPin			A3
	#define		contactorPin			10
	#define		startingCapPin			5
#elif SUMP_BORE_1_3
	#define		sumpMotorPin			10			
	#define		contactorPin			5
	#define		startingCapPin			A3
#elif BORE_1_3_TO_SUMP_TO_OH
	#define		sumpMotorPin			10
	#define		contactorPin			5
	#define		startingCapPin			A3
#endif // 0
							
String mode = "";

unsigned int trigPin = 6;
unsigned int echoPin = 7;

unsigned long currentTime;
unsigned long lastTime;
unsigned long delayTime = 30000;    /* 45 minutes = 2700000, 30 ses = 30000, Use 5 minutes = 300000 While testing*/

uint8_t errorFlag = 0;
uint8_t sumpFlag = 0;

void criticalMode(void);

#endif
