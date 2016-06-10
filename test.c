#include "Theater.h"

int main(void){

	int n, col, row;
	int key;
	RBtree * rbtree = RBcreate();
	Node * temp;

	scanf("%d", &n);

	for (; n > 0; n--){
		scanf("%d %d", &col, &row);
	
		RBinsert(rbtree, col*100 + row);
	}


	printf("\nkey : ");
	scanf("%d", &key);

	if (RBdelete(rbtree, key) == 0)
		printf("찾는 key가 없음\n");
	else
		printf("삭제 성공!\n");
}
	
