#include "RBtree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help() {
	printf(
		"\t-----<Menu>------\n"
		"\tP   - �¼� Ȯ���ϱ�\n"
		"\tI   - �����ϱ�\n"
		"\tD   - �����ϱ�\n"
		"\tS   - �¼� �����ϱ�\n"
		"\tC   - ���� ����ϱ�\n"
		"\tH   - �޴� Ȯ��\n"
		"\tX   - �����ϱ�\n"
		);
}

/*   Search �˰��� �����, ���ű�� �ֱ�.
     Ʈ�� ����Ʈ�� �� ������� �Ǵ°��� Ȯ���ϰ�, ��� ��ġ���� ����Ʈ�ϱ�.
*/


int main() {
	RBtree * tree = NULL;
		
	int cmd = 0;
	char num;
	printf("���α׷� ����\n");
	printf("1. �����ϱ�  2. �����ϱ� \n");
	scanf_s("%d", &cmd);

	if (cmd == 2) {
		printf("---�����մϴ�.---\n");
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
			printf("Key �Է�: ");
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
			printf("���� �¼�: ");
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
			printf("�¼� �Է�: ");
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
			printf("-----�����մϴ�.-----\n");
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