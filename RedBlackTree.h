#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__

#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
#define MAXROW 100

//rbtree�� ���
typedef struct _node {
	struct _node * parent; //�θ� ���
	struct _node * left; //���� �ڽ� ���
	struct _node * right; //������ �ڽ� ���
	char color; //����� 1, ���尡 �ƴϸ� 0 

	//������ �ʵ�
	int col;
	int row;
}Node;

//rbtree
typedef struct _rbtree {
	int num; //����� ����

	Node * root;
}RBtree;


void RBinit(RBtree * rbtree);

int Getkey(Node * node);

Node * GrandParent(Node * node);

Node * Uncle(Node * node);

int is_leaf(Node * node);   //
Node * SetNode(int col, int right);

void LRotate(Node * node);

void RRotate(Node * node);

int RBInsert(RBtree * rbtree, Node * newNode);
void InsertCase1(RBtree * rbtree, Node * newNode);
void InsertCase2(RBtree * rbtree, Node * newNode);
void InsertCase3(RBtree * rbtree, Node * newNode);
void InsertCase4(RBtree * rbtree, Node * newNode);
void InsertCase5(RBtree * rbtree, Node * newNode);

//void RBPrint(Node * n, int depth);

Node * RBSearch(RBtree * rbtree, int key);

/* --------------------------------
Deletion Function
--------------------------------  */
Node * rb_get_node_by_key(RBtree * haystack, int needle);
Node * rb_min(RBtree * tree, Node * node);

int RBdelete(RBtree * tree, int key);

Node * sibling(RBtree * rbtree, Node * delNode);
void replace_node(RBtree * rbtree, Node * delNode, Node * child);
void delete_one_child(RBtree * rbtree, Node * delNode);

void delete_case1(RBtree * rbtree, Node * delNode);
void delete_case2(RBtree * rbtree, Node * delNode);
void delete_case3(RBtree * rbtree, Node * delNode);
void delete_case4(RBtree * rbtree, Node * delNode);
void delete_case5(RBtree * rbtree, Node * delNode);
void delete_case6(RBtree * rbtree, Node * delNode);


//����ÿ� ����
void RBTest_Print(Node * node, int depth);

#endif