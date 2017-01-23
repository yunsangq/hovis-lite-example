#include <stdio.h>
#include <stdlib.h>
#include "hovis.h"

float g_fMotorPos[16] = {45., 90., 0., 45., 90., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
unsigned char g_ucMotorGreenLed[16] = {0};
unsigned char g_ucMotorBlueLed[16] = {0};
unsigned char g_ucMotorRedLed[16] = {0};
unsigned char g_ucMotorStop[16] = {0};
int g_nDrcMelody = 0;

int g_nBattery = 0;
int g_nTemperature = 0;
int g_nLight = 0;
int g_nAdcType[2] = {0};
int g_nAdcDist[2] = {0};
int g_nAcc[3] = {0};
int g_nGyro[3] = {0};
int g_nButton = 0;
int g_nRemoconLength = 0;
int g_nRemoconData = 0xFE;
int g_nSoundCount = 0;
int g_nSoundDirection = 0;

HANDLE g_hDr = NULL;

typedef enum EHovisControllerAddr_t{
	_HOVIS_CONTROLLER_RAM_ADDR_BTN			= 73,
	_HOVIS_CONTROLLER_RAM_ADDR_RMCLENGTH	= 74,
	_HOVIS_CONTROLLER_RAM_ADDR_RMCDATA		= 75,
	_HOVIS_CONTROLLER_RAM_ADDR_BATT			= 76,
	_HOVIS_CONTROLLER_RAM_ADDR_TEMP			= 77,
	_HOVIS_CONTROLLER_RAM_ADDR_LIGHT		= 78,
	_HOVIS_CONTROLLER_RAM_ADDR_ADCTYPE1		= 79,
	_HOVIS_CONTROLLER_RAM_ADDR_ADCTYPE2		= 80,
	_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL1		= 81,
	_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL2		= 83,
	_HOVIS_CONTROLLER_RAM_ADDR_ACCGYROCON	= 85,
	_HOVIS_CONTROLLER_RAM_ADDR_ACCX			= 86,
	_HOVIS_CONTROLLER_RAM_ADDR_ACCY			= 88,
	_HOVIS_CONTROLLER_RAM_ADDR_ACCZ			= 90,
	_HOVIS_CONTROLLER_RAM_ADDR_GYROX		= 92,
	_HOVIS_CONTROLLER_RAM_ADDR_GYROY		= 94,
	_HOVIS_CONTROLLER_RAM_ADDR_GYROZ		= 96,
	_HOVIS_CONTROLLER_RAM_ADDR_SOUNDCNT		= 98,
	_HOVIS_CONTROLLER_RAM_ADDR_SOUNDDIR		= 99,

	_HOVIS_CONTROLLER_RAM_ADDR_START		= _HOVIS_CONTROLLER_RAM_ADDR_BTN,
	_HOVIS_CONTROLLER_RAM_ADDR_END			= _HOVIS_CONTROLLER_RAM_ADDR_SOUNDDIR,
} EHovisControllerAddr_t;

int initialize(const TCHAR* pszPort, DWORD dwBaudRate){
	int nResult;

	dr_common_destroy( g_hDr );

	nResult = dr_common_initialize( &g_hDr );
	if(nResult != _DR_SUCCESS){
		terminate();
		return 0;
	}

	nResult = dr_common_connect( g_hDr, pszPort, dwBaudRate ) ;
	if(nResult != _DR_SUCCESS){
		terminate();
		return 0;
	}

	dr_motor_init(g_hDr);

	dr_motor_set_param_dir(1, 1);
	dr_motor_set_param_dir(2, 1);

	dr_motor_set_param_dir(3, 1);

	dr_motor_set_param_dir(7, 1);
	dr_motor_set_param_dir(8, 1);
	dr_motor_set_param_dir(10, 1);

	dr_motor_set_param_dir(11, 1);
	dr_motor_set_param_dir(14, 1);

	return 1;
}

void run(int nTime){
	int i;
	static float fLastPos[16] = { 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
	static unsigned char ucLastGreenLed[16] = {0};
	static unsigned char ucLastBlueLed[16] = {0};
	static unsigned char ucLastRedLed[16] = {0};
	static unsigned char ucLastStop[16] = {0};
	static int nFirst = 0;

	if(nFirst == 0){
		dr_motor_send_driver_servo_on_off( g_hDr, 254, 1, 1 );
		dr_motor_set_command_init();
		for(i=0;i<16;i++){
			dr_motor_set_command_angle( i, g_fMotorPos[i] );
			dr_motor_set_command_flag( i, g_ucMotorStop[i], 0, g_ucMotorGreenLed[i], g_ucMotorBlueLed[i], g_ucMotorRedLed[i], 0 );
			fLastPos[i] = g_fMotorPos[i];
			ucLastGreenLed[i] = g_ucMotorGreenLed[i];
			ucLastBlueLed[i] = g_ucMotorBlueLed[i];
			ucLastRedLed[i] = g_ucMotorRedLed[i];
			ucLastStop[i] = g_ucMotorStop[i];
		}
		dr_motor_send_move(g_hDr, nTime);
		nFirst = 1;
	}
	else{
		dr_motor_set_command_init();
		for(i=0;i<16;i++){
			if(ucLastGreenLed[i] != g_ucMotorGreenLed[i]){
				dr_motor_set_command_flag( i, g_ucMotorStop[i], 0, g_ucMotorGreenLed[i], g_ucMotorBlueLed[i], g_ucMotorRedLed[i], 1 );
				ucLastGreenLed[i] = g_ucMotorGreenLed[i];
			}
			if(ucLastBlueLed[i] != g_ucMotorBlueLed[i]){
				dr_motor_set_command_flag( i, g_ucMotorStop[i], 0, g_ucMotorGreenLed[i], g_ucMotorBlueLed[i], g_ucMotorRedLed[i], 1 );
				ucLastBlueLed[i] = g_ucMotorBlueLed[i];
			}
			if(ucLastRedLed[i] != g_ucMotorRedLed[i]){
				dr_motor_set_command_flag( i, g_ucMotorStop[i], 0, g_ucMotorGreenLed[i], g_ucMotorBlueLed[i], g_ucMotorRedLed[i], 1 );
				ucLastRedLed[i] = g_ucMotorRedLed[i];
			}
			if(ucLastStop[i] != g_ucMotorStop[i]){
				dr_motor_set_command_flag( i, g_ucMotorStop[i], 0, g_ucMotorGreenLed[i], g_ucMotorBlueLed[i], g_ucMotorRedLed[i], 1 );
				ucLastStop[i] = g_ucMotorStop[i];
			}
			if(fLastPos[i] != g_fMotorPos[i]){
				dr_motor_set_command_angle( i, g_fMotorPos[i] );
				fLastPos[i] = g_fMotorPos[i];
			}
		}
		dr_motor_send_move(g_hDr, nTime);
	}

	if(g_nDrcMelody){
		dr_controller_send_play_ledbuzz( g_hDr, 253, 0, g_nDrcMelody );
		g_nDrcMelody = 0;
	}
}

void motion(int nMotionNum, int nReady)
{
	dr_controller_send_play_motion( g_hDr, 253, nMotionNum, nReady);
}

void motion_wait()
{
	int nResult;
	unsigned char ucPlayingMotion = 1;

	while(ucPlayingMotion){
		dr_controller_receive_ram_playing_motion( g_hDr, 253 );
		nResult = dr_wait_busy( g_hDr, 100 );
		if( nResult == _DR_SUCCESS ){
			dr_controller_get_ram_playing_motion( g_hDr, &ucPlayingMotion );
		}
		else{
			printf("Communication Error\n");
			break;
		}
	}
}

void read(){
	unsigned char aucData[100];

	dr_controller_receive_ram( g_hDr, 253, _HOVIS_CONTROLLER_RAM_ADDR_START,
		_HOVIS_CONTROLLER_RAM_ADDR_END-_HOVIS_CONTROLLER_RAM_ADDR_START+1 );

	if(dr_wait_busy( g_hDr, 100 )==_DR_SUCCESS){
		dr_controller_get_ram( g_hDr, _HOVIS_CONTROLLER_RAM_ADDR_START,
			_HOVIS_CONTROLLER_RAM_ADDR_END-_HOVIS_CONTROLLER_RAM_ADDR_START+1, aucData);

		g_nBattery = aucData[_HOVIS_CONTROLLER_RAM_ADDR_BATT-_HOVIS_CONTROLLER_RAM_ADDR_START];

		g_nTemperature = aucData[_HOVIS_CONTROLLER_RAM_ADDR_TEMP-_HOVIS_CONTROLLER_RAM_ADDR_START];

		g_nLight = aucData[_HOVIS_CONTROLLER_RAM_ADDR_LIGHT-_HOVIS_CONTROLLER_RAM_ADDR_START];

		g_nAdcType[0] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCTYPE1-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nAdcType[1] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCTYPE2-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nAdcDist[0] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL1-_HOVIS_CONTROLLER_RAM_ADDR_START] |
						(aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL1+1-_HOVIS_CONTROLLER_RAM_ADDR_START]<<8);
		g_nAdcDist[1] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL2-_HOVIS_CONTROLLER_RAM_ADDR_START] |
						(aucData[_HOVIS_CONTROLLER_RAM_ADDR_ADCVAL2+1-_HOVIS_CONTROLLER_RAM_ADDR_START]<<8);

		if(aucData[_HOVIS_CONTROLLER_RAM_ADDR_ACCGYROCON-_HOVIS_CONTROLLER_RAM_ADDR_START]==1){
			g_nAcc[0] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ACCX-_HOVIS_CONTROLLER_RAM_ADDR_START];
			g_nAcc[1] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ACCY-_HOVIS_CONTROLLER_RAM_ADDR_START];
			g_nAcc[2] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_ACCZ-_HOVIS_CONTROLLER_RAM_ADDR_START];
			g_nGyro[0] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_GYROX-_HOVIS_CONTROLLER_RAM_ADDR_START];
			g_nGyro[1] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_GYROY-_HOVIS_CONTROLLER_RAM_ADDR_START];
			g_nGyro[2] = aucData[_HOVIS_CONTROLLER_RAM_ADDR_GYROZ-_HOVIS_CONTROLLER_RAM_ADDR_START];
		}
		else{
			g_nAcc[0] = 0;
			g_nAcc[1] = 0;
			g_nAcc[2] = 0;
			g_nGyro[0] = 0;
			g_nGyro[1] = 0;
			g_nGyro[2] = 0;
		}

		g_nButton = aucData[_HOVIS_CONTROLLER_RAM_ADDR_BTN-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nRemoconLength = aucData[_HOVIS_CONTROLLER_RAM_ADDR_RMCLENGTH-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nRemoconData = aucData[_HOVIS_CONTROLLER_RAM_ADDR_RMCDATA-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nSoundCount = aucData[_HOVIS_CONTROLLER_RAM_ADDR_SOUNDCNT-_HOVIS_CONTROLLER_RAM_ADDR_START];
		g_nSoundDirection = (char)aucData[_HOVIS_CONTROLLER_RAM_ADDR_SOUNDDIR-_HOVIS_CONTROLLER_RAM_ADDR_START];
	}
	else{
		printf("Communication Error\n");
	}
}

void delay(int nTime){
	dr_wait_delay(nTime);
}

void terminate(){
	dr_common_disconnect( g_hDr );
	dr_wait_delay(100);
	dr_motor_destroy();
	dr_common_destroy( g_hDr );
}
