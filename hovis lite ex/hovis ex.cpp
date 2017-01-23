#include <stdio.h>
#include "hovis.h"

#pragma comment(lib, "drapi.lib")

//PSD센서와 소리센서를 사용해서 특정 조건일 경우 모터 하나가 동작하는 예제

int main()
{
	int nResult; //PC와 연결 결과값 리턴
	int i;
	int nDistance; //거리 값 저장	
	int select_mode; //PSD센서, 소리센서 선택

	nResult = initialize(TEXT("COM3"), 115200); //COM3에 보드레이트 115200으로 연결
	if(nResult == 0) //연결에 이상이 있는경우
	{
		printf("Hovis와 연결에 실패\n");
		return 0;
	}
	
	for(i=0;i<16;i++) //여기서 i는 모터의 번호로 모터의 아래쪽에 모터 번호가 새겨져있다.
	{
		g_fMotorPos[i]=0; //g_fMotorPos[모터번호]=모터의 위치 로 모든 모터를 0으로 초기화시킨다.
	}
	run(1000); //모터 동작(설정한 위치까지 이동하는 속도 즉, 모터의 속도)
	delay(1000); //동작대기
	
	printf("====Hovis Lite 강의용 프로그램====\n");
	printf("1. PSD센서 프로그램\n");
	printf("2. 소리센서 프로그램\n");
	printf("===================================\n");
	printf("선택: ");
	scanf("%d",&select_mode);

	if(select_mode==1) //PSD센서 프로그램
	{
		//PSD센서가 DRC의 어느 쪽 포트에 연결되었는지 확인
		read(); //센서 변수들이 자동으로 업데이트 된다.
		printf("\n\n");
		if(g_nAdcType[0]==1)
		{
			printf("PSD센서는 왼쪽에 장착되어있습니다.\n");
		}
		else if(g_nAdcType[1]==1)
		{
			printf("PSD센서는 오른쪽에 장착되어있습니다.\n");
		}
		else
		{
			printf("PSD센서가 인식되지 않습니다.\n");
			terminate(); //호비스와 연결을 해제하는 함수
			return 0;
		}
		printf("엔터를 누르면 센서로 거리 측정을 시작 합니다.\n");
		printf("이 프로그램은 거리가 10cm이하가 되면 5번 모터가 50위치로 이동합니다.\n");
		getchar();
		getchar(); //센서 연결상태 확인


		//PSD값을 nDistance에 저장하고 만약 10cm이내일 경우 특정 동작을 취하도록 함.
		do{ 
			read();
			if(g_nAdcType[0]==1) //PSD 왼쪽
			{
				nDistance=g_nAdcDist[0];
				printf("거리 = %d cm\n", nDistance);
			}
			else if(g_nAdcType[1]==1) //PSD 오른쪽
			{
				nDistance=g_nAdcDist[1];
				printf("거리 = %d cm\n", nDistance);
			}
			else
			{
				printf("PSD센서가 인식되지 않습니다.\n");
				terminate(); //호비스와 연결을 해제하는 함수
				return 0;
			}
		}while(nDistance > 10);

		g_fMotorPos[5]=50; //ID 5번 모터를 50위치로 설정
		run(1000); //모터 동작
		delay(1000); //동작 대기
	}
	else if(select_mode==2) //소리센서 프로그램
	{
		printf("\n\n");
		while(1) //소리센서를 계속 작동시킨 상태
			//주의!!! 만약 프로그램에서 동시에 사용하려면 소리센서는 쓰레드 사용을 추천
		{
			while(1) //소리센서 작동 확인
			{
				read();//소리센서와 통신
				if(g_nSoundCount)//소리센서가 정상 작동할 경우
					break; //소리센서 값이 0이 아닌 즉, 작동시 탈출
			}

			printf("소리 방향 = %d\n",g_nSoundDirection); //소리 감지 방향
			//-2 : 왼쪽
			//2 : 오른쪽
			if(g_nSoundDirection==-2)//왼쪽에서 소리가 난 경우
			{
				g_fMotorPos[5]=50;
				run(1000);
				delay(1000);
			}
			else if(g_nSoundDirection==2)//오른쪽에서 소리가 난 경우
			{
				g_fMotorPos[5]=-50;
				run(1000);
				delay(1000);
			}
			else
			{
				g_fMotorPos[5]=0;
				run(1000);
				delay(1000);
			}			
		}
		terminate(); //호비스와 연결을 해제하는 함수
		return 0;
	}

	return 0;
}