#include "Theater.h"


//test.c���� �����Ʈ�� ����� ������ main.c�� ����
int main(void){
	Timetable_of_Day timetable[MAX_DAY];
	int i;

	TimeTableInit(timetable);

	/**/
	for (i = 0; i < MAX_DAY; i++)
		PrintTimetable(timetable[i]);

}