#ifndef _HOVIS_H
#define _HOVIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "drApi.h"

extern float g_fMotorPos[16];
extern unsigned char g_ucMotorGreenLed[16];
extern unsigned char g_ucMotorBlueLed[16];
extern unsigned char g_ucMotorRedLed[16];
extern unsigned char g_ucMotorStop[16];
extern int g_nDrcMelody;

extern int g_nBattery;
extern int g_nTemperature;
extern int g_nLight;
extern int g_nAdcType[2];
extern int g_nAdcDist[2];
extern int g_nAcc[3];
extern int g_nGyro[3];
extern int g_nButton;
extern int g_nRemoconLength;
extern int g_nRemoconData;
extern int g_nSoundCount;
extern int g_nSoundDirection;

int initialize(const TCHAR* pszPort, DWORD dwBaudRate);
void run(int nTime);
void motion(int nMotionNum, int nReady);
void motion_wait();
void read();
void delay(int nTime);
void terminate();

#ifdef __cplusplus
}
#endif

#endif
