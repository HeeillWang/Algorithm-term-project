#include "RedBlackTree.h"


//tree�� �ʱ�ȭ
void RBinit(RBtree * rbtree) {
	rbtree->num = 0;
	rbtree->root = NULL;
}

//node�� key�� ��ȯ
int Getkey(Node * node) {
	return (node->col * MAXROW) + node->row; //key�� ��*100 + ��
}

//�־��� ����� ���θ� ��ȯ
Node * GrandParent(Node * node) {
	if (node != NULL && node->parent != NULL)
		return node->parent->parent;
	else
		return NULL;
}

//�־��� ����� ���� ��ȯ
Node * Uncle(Node * node) {
	Node * g = GrandParent(node);

	if (g == NULL)
		return NULL;
	else if (node->parent == g->left)
		return g->right;
	else
		return g->left;

}

//������ �ڽ� ��尡 NIL�̸� -1 ��ȯ
int is_leaf(Node * node)
{
	if (node->right != NULL)
		return 0;
	else
		return -1;

	//Node * child = is_leaf(delNode->right) ? delNode->left : delNode->right;
}

//�־��� ���ڷ� ��� ����
Node * SetNode(int col, int row) {
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->col = col;
	newNode->row = row;
	newNode->color = RED;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

//�־��� ��带 �������� ����ȸ��
void LRotate(Node * node) {
	Node * r = node->right;
	Node * p = node->parent;

	if (r->left != NULL)
		r->left->parent = node;

	node->right = r->left;
	node->parent = r;
	r->left = node;
	r->parent = p;

	if (p != NULL) {
		if (p->left == node)
			p->left = r;
		else
			p->right = r;
	}
}

//�־��� ��带 �������� ������ȸ��
void RRotate(Node * node) {
	Node * l = node->left;
	Node * p = node->parent;

	if (l->right != NULL)
		l->right->parent = node;

	node->left = l->right;
	node->parent = l;
	l->right = node;
	l->parent = p;

	if (p != NULL) {
		if (p->left == node)
			p->left = l;
		else
			p->right = l;
	}
}

//�̹� tree�� �����ϴ� key�� �Է��ϸ� -1�� ��ȯ
int RBInsert(RBtree * rbtree, Node * newNode) {
	Node * cur; //������ ��ġ
	Node * p; //cur�� �θ���
	int key = Getkey(newNode);

	if (rbtree->root == NULL) {
		newNode->color = BLACK;
		rbtree->root = newNode;
		rbtree->num++;
		return 0;
	}
	else {
		cur = rbtree->root;

		while (1) {
			if (Getkey(cur) > key) {
				p = cur;
				cur = cur->left;
			}
			else if (Getkey(cur) < key) {
				p = cur;
				cur = cur->right;
			}
			else //�̹� �����ϴ� key��
				return -1;

			if (cur == NULL) { //Ʈ���� �������� �ٴٸ� ��Ȳ�̸� bewNode�� �������ش�.
				if (Getkey(p) > key)
					p->left = newNode;
				else if (Getkey(p) < key)
					p->right = newNode;
				else //�̹� �����ϴ� key ��
					return -1;

				newNode->parent = p;

				break;
			}
		}
	}

	InsertCase1(rbtree, newNode);

	rbtree->num++;
	return 0;
}

//�����Ϸ��� ��ġ�� root�� ���
void InsertCase1(RBtree * rbtree, Node * newNode) {
	if (newNode->parent == NULL)
		newNode->color = BLACK;
	else
		InsertCase2(rbtree, newNode);
}

//�����Ϸ��� ��ġ�� �θ��尡 BLACK�� ���
void InsertCase2(RBtree * rbtree, Node * newNode) {
	if (newNode->parent->color == BLACK)
		return;
	else
		InsertCase3(rbtree, newNode);
}

//�θ���� ���̳�尡 ��� RED�� ���
//�θ��尡 BLACK�� ���� �̹� case2���� �ٷ�����Ƿ� ���⼭�� �θ��尡 RED���� ������ �� �ִ�.
void InsertCase3(RBtree * rbtree, Node * newNode) {
	Node * u = Uncle(newNode);
	Node * g = GrandParent(newNode);

	//�θ�� ���� ��带 BLACK���� �����ϰ�, ���θ� ��带 RED�� �����Ѵ�. ���� ���θ� ��忡 ���� Insert�� �����Ѵ�
	if ((u != NULL) && (u->color == RED)) {
		newNode->parent->color = BLACK;
		u->color = BLACK;
		g->color = RED;

		InsertCase1(rbtree, g);
	}
	else
		InsertCase4(rbtree, newNode);
}


/*
�θ��尡 RED�̰� ���̳�尡 BLACK�� ��쿡��
newNode�� �θ����� ������ �ڽ��̸� �θ���� ���θ� ����� ���� �ڽ��� ���� (1)
newNode�� �θ����� ���� �ڽ��̸� ���θ� ����� ������ �ڽ��� ��� 2������ �ٷ�Եȴ�. (2)
�θ��带 �������� (1)�� ��쿣 ���� ȸ���� ���ְ� (2)�� ��쿣 ������ ȸ���� �Ͽ� newNode�� �θ����� ������ �ٲ��صڿ� case5�� �ѱ��.
�θ���� ���̳�尡 ��� RED�� ���� case3���� �ٷ�����Ƿ� ���⼭�� �θ��尡 RED ���̳�尡 BLACK���� ������ �� �ִ�.
*/
void InsertCase4(RBtree * rbtree, Node * newNode) {
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if ((newNode == p->right) && (p == g->left)) { //(1)�� ���
		LRotate(p);
		newNode = newNode->left; //����� ��ġ�� p��带 ����
	}
	else if ((newNode == p->left) && (p == g->right)) { //(2)�� ���
		RRotate(p);
		newNode = newNode->right; //����� ��ġ�� p��带 ����
	}

	InsertCase5(rbtree, newNode);
}

/*
�θ��尡 RED�̰� ���̳�尡 BLACK�̸�
newNode�� �θ����� ������ �ڽ��̸� �θ���� ���θ� ����� ������ �ڽ��� ����(1)
newNode�� �θ����� ���� �ڽ��̸� �θ���� ���θ� ����� ���� �ڽ��� ��� 2������ �ٷ�� �ȴ�(2)
���θ� ��带 RED��, �θ��带 BLACK���� �����ѵڿ�
���θ� ��带 �������� (1)�� ��쿣 ���� ȸ���� (2)�� ��쿣 ������ ȸ���� ���ش�.
�̷ν� RBtree�� ��� Ư���� �����ϰ� �ȴ�.
*/
void InsertCase5(RBtree * rbtree, Node * newNode) {
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if (g != NULL)
		g->color = RED;

	p->color = BLACK;

	if (newNode == p->right) {//(1)�� ���
		LRotate(g);

		if (rbtree->root == g) //��Ʈ��尡 ����� ���
			rbtree->root = p;
	}
	else { //(2)�� ��� 
		RRotate(g);

		if (rbtree->root == g) //��Ʈ��尡 ����� ���
			rbtree->root = p;
	}
}

//rbtree���� key���� ���� ��带 ã�´�.
//��带 �˻��ϴµ� ������ ��� �� ����� �ּҰ� ��ȯ
//�˻��� ������ ���(key���� ���� ��尡 ���� ���) NULL��ȯ
Node * RBSearch(RBtree * rbtree, int key) {
	Node * cur = rbtree->root;

	while (1) {
		if (Getkey(cur) == key)
			return cur;
		else if (Getkey(cur) > key)
			cur = cur->left;
		else
			cur = cur->right;

		if (cur == NULL)
			return NULL;
	}
}

/* -------------------- Deletion -------------------- */


//��� �ȿ� �ִ� ���� ���ΰ� ���� ������ Key ���� ��´�.
Node * rb_get_node_by_key(RBtree * haystack, int needle) {
	Node * pos = haystack->root; /* our current position */
	while (pos != NULL) {
		if (Getkey(pos) == needle) {
			return pos;
		}
		else if (needle < Getkey(pos)) {
			pos = pos->left;
		}
		else {
			pos = pos->right;
		}
	}
	return NULL;
}

//����Ʈ���� �ּҰ��� ��ȯ�Ѵ�.
Node * rb_min(RBtree * tree, Node * node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}

//�Էµ� Key ���� �����Ѵ�.
int RBdelete(RBtree * tree, int key) {

	Node * fixit = tree->root;

	Node * dead = rb_get_node_by_key(tree, key);

	int orig_col = dead->color;

	if (dead == NULL) {
		printf("Error: node %d does not exist.\n", key);
		return 0;
	}

	if (dead->left == NULL && dead->right != NULL) {
		fixit = dead->right;
		replace_node(tree, dead, fixit);
	}
	else if (dead->right == NULL && dead->left != NULL) {
		fixit = dead->left;
		replace_node(tree, dead, fixit);
	}
	else if (dead->right == NULL && dead->left == NULL) {
		fixit = NULL;
		replace_node(tree, dead, fixit);
	}
	else {

		Node * successor = rb_min(tree, dead->right);
		orig_col = successor->color;
		if (successor->right != NULL)
			fixit = successor->right;
		if (successor->parent == dead) {
			fixit->parent = successor;
		}
		else {

			replace_node(tree, successor, successor->right);
			successor->right = dead->right;
			successor->right->parent = successor;
		}
		replace_node(tree, dead, successor);
		successor->left = dead->left;
		successor->left->parent = successor;
		successor->color = dead->color;
	}

	if (orig_col == BLACK) {
		delete_one_child(tree, fixit);
	}
	return 1;
}

//������ Key ���� ������ Ȯ���Ѵ�.
Node * sibling(RBtree * rbtree, Node * delNode)
{
	Node * p = delNode->parent;

	if (delNode == p->left)
		return p->right;
	else
		return p->left;
}

//Key�� ������ ���� ��ȭ�ϴ� �ٸ� ������ Ű���� ���Ӱ� �ٲ��ش�.
void replace_node(RBtree * rbtree, Node * delNode, Node * child)
{
	if (delNode->parent == NULL)
	{
		rbtree->root = child;
	}
	else
	{
		if (delNode == delNode->parent->left)
			delNode->parent->left = child;
		else
			delNode->parent->right = child;
	}
	if (child != NULL)
	{
		child->parent = delNode->parent;
	}
}

//������ Key�� ��ġ�� ��带 ã�Ƴ���.
void delete_one_child(RBtree * rbtree, Node * delNode)
{
	Node * child = is_leaf(delNode->right) ? delNode->left : delNode->right;

	replace_node(rbtree, delNode, child);
	if (delNode->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_case1(rbtree, child);
	}
	free(delNode);
}

void delete_case1(RBtree * rbtree, Node * delNode)
{
	if (delNode->parent != NULL)
		delete_case2(rbtree, delNode);
}

void delete_case2(RBtree * rbtree, Node * delNode)
{
	Node * s = sibling(rbtree, delNode);
	Node * p = delNode->parent;

	if (s->color == RED) {
		p->color = RED;
		s->color = BLACK;
		if (delNode == p->left)
			LRotate(p);
		else
			RRotate(p);
	}
	delete_case3(rbtree, delNode);
}

void delete_case3(RBtree * rbtree, Node * delNode)
{
	Node * s = sibling(rbtree, delNode);
	Node * p = delNode->parent;

	if ((p->color == BLACK) &&
		(s->color == BLACK) &&
		(s->left->color == BLACK) &&
		(s->right->color == BLACK)) {
		s->color = RED;
		delete_case1(rbtree, p);
	}
	else
		delete_case4(rbtree, delNode);
}

void delete_case4(RBtree * rbtree, Node * delNode)
{
	Node *s = sibling(rbtree, delNode);
	Node * p = delNode->parent;

	if ((p->color == RED) &&
		(s->color == BLACK) &&
		(s->left->color == BLACK) &&
		(s->right->color == BLACK)) {
		s->color = RED;
		p->color = BLACK;
	}
	else
		delete_case5(rbtree, delNode);
}

void delete_case5(RBtree * rbtree, Node * delNode)
{
	Node * s = sibling(rbtree, delNode);
	Node * p = delNode->parent;

	if (s->color == BLACK)
	{
		if ((delNode == p->left) &&
			(s->right->color == BLACK) &&
			(s->left->color == RED)) {
			s->color = RED;
			s->left->color = BLACK;
			RRotate(s);
		}
		else if ((delNode == p->right) &&
			(s->left->color == BLACK) &&
			(s->right->color == RED)) {
			s->color = RED;
			s->right->color = BLACK;
			LRotate(s);
		}
	}
	delete_case6(rbtree, delNode);
}

void delete_case6(RBtree * rbtree, Node * delNode)
{
	Node * s = sibling(rbtree, delNode);
	Node * p = delNode->parent;

	s->color = p->color;
	p->color = BLACK;

	if (delNode == p->left) {
		s->right->color = BLACK;
		LRotate(p);
	}
	else {
		s->left->color = BLACK;
		RRotate(p);
	}
}

/* --------------------- Print --------------------------- */

/*
int PrintTree(Node* tree)
{
// TODO:
if (tree == NULL)
return 1;

PrintTree(tree->left);
printf("%d ", tree->data);
PrintTree(tree->right);

return 0;
}
*/

/*
void RBPrint(Node * n, int depth)
{
for (int i = 0; i < depth; i++)
{
printf("  ");
}

//if (n->parent == NULL)
//{
//	printf("[Root)");
//}
//else
//{
if (n->parent == n)
printf("[(Left)");
else
printf("[(Right)");
//}

printf("Data: %d(%d)", Getkey(n), n->color);
printf(",Parent");
if (n->parent != NULL)
printf("%d", Getkey(n));
else
printf(" ");

RBPrint(n->left, depth + 1);
RBPrint(n->right, depth + 1);
}
*/

//������� ���� �뵵 �ӽ� ����Ʈ, preorder����
//���� �ÿ� ����
void RBTest_Print(Node * node, int depth) {
	int tmp;
	if (node == NULL)
		return;

	printf("                   ");

	for (int i = 0; i < depth; i++)
	{
		printf("     ");
	}

	printf("[%d(%d)]", Getkey(node), node->color); //key(��)

	printf("\n");

	//RBTest_Print(node->left, depth);
	//RBTest_Print(node->right, depth);

	RBTest_Print(node->left, depth / 2);
	RBTest_Print(node->right, (depth / 2) + depth + depth);
	//RBTest_Print(node->right, (depth*2) + depth + depth + depth);
}
