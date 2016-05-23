#include <stdio.h>

//rbtree�� ���
typedef struct _node{
	Node * parent; //�θ� ���
	Node * left; //���� �ڽ� ���
	Node * right; //������ �ڽ� ���
	char redFlag; //����� 1, ���尡 �ƴϸ� 0 

	//������ �ʵ�
	int col;
	int row;
}Node;

//rbtree
typedef struct _rbtree{
	int num; //����� ����

	Node * root;
}RBtree;


void RBinit(RBtree * rbtree);

void Getkey(Node * node);

Node * SetNode(int col, int right);

void RBDelete(RBtree * rbtree, Node delNode);

void RBInsert(RBtree * rbtree, Node newNode);

void RBPrint(RBtree * rbtree);

void RBSearch(RBtree * rbtree, Node searchNode);

