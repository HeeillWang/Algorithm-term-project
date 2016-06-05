#include "Theater.h"

const char movielist[NUM_THEATHER][30] = { "�", "�ޱ׸�����", "������ : ����Į����", "�ư���", "�� ���� ��" };
const int movietime[NUM_THEATHER] = { 236, 137, 223, 224, 150 }; //��ȭ ����Ʈ�� �󿵽ð�, 1�ð� 30�� => 130�� ����


//Ư�� ��¥�� Ÿ�����̺� ���� ���
void PrintTimetable(Timetable_of_Day timetable){
	int i, j;

	printf("************************%d�� %d���� ������************************\n", timetable.month, timetable.day);

	for (i = 0; i < NUM_THEATHER; i++){
		printf("<%d�� : %s>\n", timetable.theather[i].numTheater, timetable.theather[i].movieName);
		for (j = 0; j < MAX_SHOW; j++){
			printf("%d��%d�� ~ %d��%d�� / ",
				timetable.theather[i].resv[j].stime / 100, timetable.theather[i].resv[j].stime % 100,
				timetable.theather[i].resv[j].ftime / 100, timetable.theather[i].resv[j].ftime % 100);
		}
		printf("\n");
	}
}

//MAX_DAY��ġ�� Ÿ�����̺��� �ʱ�ȭ�Ѵ�.
void TimeTableInit(Timetable_of_Day timetable[]){
	int i, j, k, time;

	for (i = 0; i < MAX_DAY; i++){
		timetable[i].month = 6;
		timetable[i].day = 21 + i; //�󿵳�¥ : 6�� 21��~
		for (j = 0; j < NUM_THEATHER; j++){
			timetable[i].theather[j].numTheater = 1 + j; //�󿵰� ��ȣ : 1��~
			strcpy(timetable[i].theather[j].movieName, movielist[j]);
			time = 900;
			for (k = 0; k < MAX_SHOW; k++){
				timetable[i].theather[j].resv[k].stime = time;
				time += movietime[j]; //��ȭ �󿵽ð�
				timetable[i].theather[j].resv[k].ftime = time;
				time += 10; //û�ҽð�
			}
		}
	}

}