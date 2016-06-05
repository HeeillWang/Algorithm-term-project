#include "Theater.h"

const char movielist[NUM_THEATHER][30] = { "곡성", "앵그리버드", "엑스맨 : 아포칼립스", "아가씨", "미 비포 유" };
const int movietime[NUM_THEATHER] = { 236, 137, 223, 224, 150 }; //영화 리스트의 상영시간, 1시간 30분 => 130의 형식


//특정 날짜의 타임테이블 정보 출력
void PrintTimetable(Timetable_of_Day timetable){
	int i, j;

	printf("************************%d월 %d일의 상영정보************************\n", timetable.month, timetable.day);

	for (i = 0; i < NUM_THEATHER; i++){
		printf("<%d관 : %s>\n", timetable.theather[i].numTheater, timetable.theather[i].movieName);
		for (j = 0; j < MAX_SHOW; j++){
			printf("%d시%d분 ~ %d시%d분 / ",
				timetable.theather[i].resv[j].stime / 100, timetable.theather[i].resv[j].stime % 100,
				timetable.theather[i].resv[j].ftime / 100, timetable.theather[i].resv[j].ftime % 100);
		}
		printf("\n");
	}
}

//MAX_DAY일치의 타임테이블을 초기화한다.
void TimeTableInit(Timetable_of_Day timetable[]){
	int i, j, k, time;

	for (i = 0; i < MAX_DAY; i++){
		timetable[i].month = 6;
		timetable[i].day = 21 + i; //상영날짜 : 6월 21일~
		for (j = 0; j < NUM_THEATHER; j++){
			timetable[i].theather[j].numTheater = 1 + j; //상영관 번호 : 1관~
			strcpy(timetable[i].theather[j].movieName, movielist[j]);
			time = 900;
			for (k = 0; k < MAX_SHOW; k++){
				timetable[i].theather[j].resv[k].stime = time;
				time += movietime[j]; //영화 상영시간
				timetable[i].theather[j].resv[k].ftime = time;
				time += 10; //청소시간
			}
		}
	}

}