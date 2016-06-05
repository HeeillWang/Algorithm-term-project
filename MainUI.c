#include "Theater.h"


//test.c에서 레드블랙트리 디버깅 끝나면 main.c로 변경
int main(void){
	Timetable_of_Day timetable[MAX_DAY];
	int i;

	TimeTableInit(timetable);

	/**/
	for (i = 0; i < MAX_DAY; i++)
		PrintTimetable(timetable[i]);

}