#ifndef __THEATER_H__
#define __THEATER_H__

#include "RBtree.h"


#include <string.h>

#define NUM_THEATHER 5 //상영관의 갯수
#define MAX_SHOW 3 //하나의 상영관에서 하루에 상영될 수 있는 최대 횟수
#define MAX_DAY 7 //타임테이블에 저장될 최대 날짜
#define ROW 15  //상영관의 가로 길이
#define COL 20  //상영관의 세로 길이



//특정 시간대 하나의 예매 정보
typedef struct _resv_info{
	RBtree rsvSeat; //예약된 좌석
	
	//시간은 14:35 => 1435와 같은 형태로 저장된다.
	int stime; //상영 시작 시간
	int ftime; //상영 종료 시간
}Resv_info;	

//상영관 하나의 정보
typedef struct _theater{
	int numTheater; //상영관 번호
	char movieName[50]; //영화 명

	Resv_info resv[MAX_SHOW]; //이 상영관의 예매 정보
}Theater;

//특정 날짜 하나의 정보
typedef struct _timetable_of_day{
	//날짜 정보
	int month;
	int day;

	Theater theather[NUM_THEATHER]; 
}Timetable_of_Day;

//특정 날짜의 타임테이블 정보 출력
void PrintTimetable(Timetable_of_Day timetable);

//MAX_DAY일치의 타임테이블을 초기화한다.
void TimeTableInit(Timetable_of_Day timetable[]);

int GetRow(int key);

int GetCol(int key);


#endif