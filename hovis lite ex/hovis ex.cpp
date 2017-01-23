#include <stdio.h>
#include "hovis.h"

#pragma comment(lib, "drapi.lib")

//PSD������ �Ҹ������� ����ؼ� Ư�� ������ ��� ���� �ϳ��� �����ϴ� ����

int main()
{
	int nResult; //PC�� ���� ����� ����
	int i;
	int nDistance; //�Ÿ� �� ����	
	int select_mode; //PSD����, �Ҹ����� ����

	nResult = initialize(TEXT("COM3"), 115200); //COM3�� ���巹��Ʈ 115200���� ����
	if(nResult == 0) //���ῡ �̻��� �ִ°��
	{
		printf("Hovis�� ���ῡ ����\n");
		return 0;
	}
	
	for(i=0;i<16;i++) //���⼭ i�� ������ ��ȣ�� ������ �Ʒ��ʿ� ���� ��ȣ�� �������ִ�.
	{
		g_fMotorPos[i]=0; //g_fMotorPos[���͹�ȣ]=������ ��ġ �� ��� ���͸� 0���� �ʱ�ȭ��Ų��.
	}
	run(1000); //���� ����(������ ��ġ���� �̵��ϴ� �ӵ� ��, ������ �ӵ�)
	delay(1000); //���۴��
	
	printf("====Hovis Lite ���ǿ� ���α׷�====\n");
	printf("1. PSD���� ���α׷�\n");
	printf("2. �Ҹ����� ���α׷�\n");
	printf("===================================\n");
	printf("����: ");
	scanf("%d",&select_mode);

	if(select_mode==1) //PSD���� ���α׷�
	{
		//PSD������ DRC�� ��� �� ��Ʈ�� ����Ǿ����� Ȯ��
		read(); //���� �������� �ڵ����� ������Ʈ �ȴ�.
		printf("\n\n");
		if(g_nAdcType[0]==1)
		{
			printf("PSD������ ���ʿ� �����Ǿ��ֽ��ϴ�.\n");
		}
		else if(g_nAdcType[1]==1)
		{
			printf("PSD������ �����ʿ� �����Ǿ��ֽ��ϴ�.\n");
		}
		else
		{
			printf("PSD������ �νĵ��� �ʽ��ϴ�.\n");
			terminate(); //ȣ�񽺿� ������ �����ϴ� �Լ�
			return 0;
		}
		printf("���͸� ������ ������ �Ÿ� ������ ���� �մϴ�.\n");
		printf("�� ���α׷��� �Ÿ��� 10cm���ϰ� �Ǹ� 5�� ���Ͱ� 50��ġ�� �̵��մϴ�.\n");
		getchar();
		getchar(); //���� ������� Ȯ��


		//PSD���� nDistance�� �����ϰ� ���� 10cm�̳��� ��� Ư�� ������ ���ϵ��� ��.
		do{ 
			read();
			if(g_nAdcType[0]==1) //PSD ����
			{
				nDistance=g_nAdcDist[0];
				printf("�Ÿ� = %d cm\n", nDistance);
			}
			else if(g_nAdcType[1]==1) //PSD ������
			{
				nDistance=g_nAdcDist[1];
				printf("�Ÿ� = %d cm\n", nDistance);
			}
			else
			{
				printf("PSD������ �νĵ��� �ʽ��ϴ�.\n");
				terminate(); //ȣ�񽺿� ������ �����ϴ� �Լ�
				return 0;
			}
		}while(nDistance > 10);

		g_fMotorPos[5]=50; //ID 5�� ���͸� 50��ġ�� ����
		run(1000); //���� ����
		delay(1000); //���� ���
	}
	else if(select_mode==2) //�Ҹ����� ���α׷�
	{
		printf("\n\n");
		while(1) //�Ҹ������� ��� �۵���Ų ����
			//����!!! ���� ���α׷����� ���ÿ� ����Ϸ��� �Ҹ������� ������ ����� ��õ
		{
			while(1) //�Ҹ����� �۵� Ȯ��
			{
				read();//�Ҹ������� ���
				if(g_nSoundCount)//�Ҹ������� ���� �۵��� ���
					break; //�Ҹ����� ���� 0�� �ƴ� ��, �۵��� Ż��
			}

			printf("�Ҹ� ���� = %d\n",g_nSoundDirection); //�Ҹ� ���� ����
			//-2 : ����
			//2 : ������
			if(g_nSoundDirection==-2)//���ʿ��� �Ҹ��� �� ���
			{
				g_fMotorPos[5]=50;
				run(1000);
				delay(1000);
			}
			else if(g_nSoundDirection==2)//�����ʿ��� �Ҹ��� �� ���
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
		terminate(); //ȣ�񽺿� ������ �����ϴ� �Լ�
		return 0;
	}

	return 0;
}