#include "RBtree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help() {
	printf(
		"\t-----<Menu>------\n"
		"\tP   - 좌석 확인하기\n"
		"\tI   - 삽입하기\n"
		"\tD   - 삭제하기\n"
		"\tS   - 좌석 예매하기\n"
		"\tC   - 예매 취소하기\n"
		"\tH   - 메뉴 확인\n"
		"\tX   - 종료하기\n"
		);
}

/*   Search 알고리즘 만들고, 예매기능 넣기.
     트리 프린트할 때 어떤식으로 되는건지 확인하고, 노드 위치까지 프린트하기.
*/


int main() {
	RBtree * tree = NULL;
		
	int cmd = 0;
	char num;
	printf("프로그램 실행\n");
	printf("1. 접속하기  2. 종료하기 \n");
	scanf_s("%d", &cmd);

	if (cmd == 2) {
		printf("---종료합니다.---\n");
		return 0;
	}

	help();
	tree = RBcreate();
	while (cmd != 2) {
		int arg;
		
		num = getchar();

		switch (num) {
		case 'F':
		case 'f':
			/* If we already had a tree, we need to free up
			* the memory. */
			if (tree != NULL) {
				printf("Clear tree.\n");
				RBfree(tree);
			}
			else {
				printf("Tree is not exists.\n");
			}
			break;
		case 'P':
		case 'p':
			if (tree == NULL) {
				printf("Error: no tree loaded, cannot write.\n");
			}
			else {
				RBprint(tree);
			}
			break;
		case 'I':
		case 'i':
			printf("Key 입력: ");
			if (tree == NULL) {
				printf("No tree loaded - creating empty one.\n");
				tree = RBcreate();
			}
			if (scanf_s("%d", &arg) != 1) {
				printf("Error: must specify integer key to insert.\n");
			}
			else {
				RBinsert(tree, arg);
			}
			break;
		case 'D':
		case 'd':
			if (tree == NULL) {
				printf("Error: no tree loaded, cannot delete.\n");
			}
			else {
				if (scanf_s("%d", &arg) != 1) {
					printf("Error: must specify integer key to delete.\n");
				}
				else {
					RBdelete(tree, arg);
				}
			}
			break;
		case 'S':
		case 's':
			printf("예매 좌석: ");
			if (tree == NULL) {
				printf("Error: no tree loaded, cannot reserve.\n");
			}
			else {
				if (scanf_s("%d", &arg) != 1) {
					printf("Error: must specify integer key to reserve.\n");
				}
				else {
					RBSearch(tree, arg);
				}
			}
			break;
		case 'C':
		case 'c':
			printf("좌석 입력: ");
			if (tree == NULL) {
				printf("Error: no tree loaded, cannot reserve.\n");
			}
			else {
				if (scanf_s("%d", &arg) != 1) {
					printf("Error: must specify integer key to reserve.\n");
				}
				else {
					RBCancel(tree, arg);
				}
			}
			break;
		case 'H':
		case 'h':
			help();
			break;
		case 'X':
		case 'x':
			printf("-----종료합니다.-----\n");
			cmd = 2;
			break;
			/* Corresponds to an empty command */
		case '\n':
			printf("Input: ");
			break;
		default:
			printf("Error: unknown command `%c'.\n", num);
			help();
			break;
		}
		
	}

	/* We need to free the tree. */
	if (tree != NULL) {
		RBfree(tree);
	}
	RBcleanup();

	return 0;
}