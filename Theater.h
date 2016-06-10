#ifndef __THEATER_H__
#define __THEATER_H__

#include "RBtree.h"


#include <string.h>

#define NUM_THEATHER 5 //�󿵰��� ����
#define MAX_SHOW 3 //�ϳ��� �󿵰����� �Ϸ翡 �󿵵� �� �ִ� �ִ� Ƚ��
#define MAX_DAY 7 //Ÿ�����̺� ����� �ִ� ��¥
#define ROW 15  //�󿵰��� ���� ����
#define COL 20  //�󿵰��� ���� ����



//Ư�� �ð��� �ϳ��� ���� ����
typedef struct _resv_info{
	RBtree rsvSeat; //����� �¼�
	
	//�ð��� 14:35 => 1435�� ���� ���·� ����ȴ�.
	int stime; //�� ���� �ð�
	int ftime; //�� ���� �ð�
}Resv_info;	

//�󿵰� �ϳ��� ����
typedef struct _theater{
	int numTheater; //�󿵰� ��ȣ
	char movieName[50]; //��ȭ ��

	Resv_info resv[MAX_SHOW]; //�� �󿵰��� ���� ����
}Theater;

//Ư�� ��¥ �ϳ��� ����
typedef struct _timetable_of_day{
	//��¥ ����
	int month;
	int day;

	Theater theather[NUM_THEATHER]; 
}Timetable_of_Day;

//Ư�� ��¥�� Ÿ�����̺� ���� ���
void PrintTimetable(Timetable_of_Day timetable);

//MAX_DAY��ġ�� Ÿ�����̺��� �ʱ�ȭ�Ѵ�.
void TimeTableInit(Timetable_of_Day timetable[]);

int GetRow(int key);

int GetCol(int key);


#endif