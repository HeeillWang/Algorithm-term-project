#include "RedBlackTree.h"


//tree를 초기화
void RBinit(RBtree * rbtree) {
	rbtree->num = 0;
	rbtree->root = NULL;
}

//node의 key값 반환
int Getkey(Node * node) {
	return (node->col * MAXROW) + node->row; //key는 열*100 + 열
}

//주어진 노드의 조부모 반환
Node * GrandParent(Node * node) {
	if (node != NULL && node->parent != NULL)
		return node->parent->parent;
	else
		return NULL;
}

//주어진 노드의 삼촌 반환
Node * Uncle(Node * node) {
	Node * g = GrandParent(node);

	if (g == NULL)
		return NULL;
	else if (node->parent == g->left)
		return g->right;
	else
		return g->left;

}

//오른쪽 자식 노드가 NIL이면 -1 반환
int is_leaf(Node * node)
{
	if (node->right != NULL)
		return 0;
	else
		return -1;

	//Node * child = is_leaf(delNode->right) ? delNode->left : delNode->right;
}

//주어진 인자로 노드 생성
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

//주어진 노드를 기준으로 왼쪽회전
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

//주어진 노드를 기준으로 오른쪽회전
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

//이미 tree에 존재하는 key를 입력하면 -1을 반환
int RBInsert(RBtree * rbtree, Node * newNode) {
	Node * cur; //삽입할 위치
	Node * p; //cur의 부모노드
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
			else //이미 존재하는 key값
				return -1;

			if (cur == NULL) { //트리의 종점까지 다다른 상황이면 bewNode를 삽입해준다.
				if (Getkey(p) > key)
					p->left = newNode;
				else if (Getkey(p) < key)
					p->right = newNode;
				else //이미 존재하는 key 값
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

//삽입하려는 위치가 root일 경우
void InsertCase1(RBtree * rbtree, Node * newNode) {
	if (newNode->parent == NULL)
		newNode->color = BLACK;
	else
		InsertCase2(rbtree, newNode);
}

//삽입하려는 위치의 부모노드가 BLACK인 경우
void InsertCase2(RBtree * rbtree, Node * newNode) {
	if (newNode->parent->color == BLACK)
		return;
	else
		InsertCase3(rbtree, newNode);
}

//부모노드와 삼촌노드가 모두 RED인 경우
//부모노드가 BLACK인 경우는 이미 case2에서 다루었으므로 여기서는 부모노드가 RED임을 가정할 수 있다.
void InsertCase3(RBtree * rbtree, Node * newNode) {
	Node * u = Uncle(newNode);
	Node * g = GrandParent(newNode);

	//부모와 삼촌 노드를 BLACK으로 변경하고, 조부모 노드를 RED로 변경한다. 이후 조부모 노드에 대해 Insert를 진행한다
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
부모노드가 RED이고 삼촌노드가 BLACK인 경우에는
newNode가 부모노드의 오른쪽 자식이며 부모노드는 조부모 노드의 왼쪽 자식인 경우와 (1)
newNode가 부모노드의 왼쪽 자식이며 조부모 노드의 오른쪽 자식인 경우 2가지를 다루게된다. (2)
부모노드를 기준으로 (1)의 경우엔 왼쪽 회전을 해주고 (2)의 경우엔 오른쪽 회전을 하여 newNode와 부모노드의 역할을 바꿔준뒤에 case5로 넘긴다.
부모노드와 삼촌노드가 모드 RED인 경우는 case3에서 다루었으므로 여기서는 부모노드가 RED 삼촌노드가 BLACK임을 가정할 수 있다.
*/
void InsertCase4(RBtree * rbtree, Node * newNode) {
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if ((newNode == p->right) && (p == g->left)) { //(1)의 경우
		LRotate(p);
		newNode = newNode->left; //변경된 위치의 p노드를 지정
	}
	else if ((newNode == p->left) && (p == g->right)) { //(2)의 경우
		RRotate(p);
		newNode = newNode->right; //변경된 위치의 p노드를 지정
	}

	InsertCase5(rbtree, newNode);
}

/*
부모노드가 RED이고 삼촌노드가 BLACK이며
newNode가 부모노드의 오른쪽 자식이며 부모노드는 조부모 노드의 오른쪽 자식인 경우와(1)
newNode가 부모노드의 왼쪽 자식이며 부모노드는 조부모 노드의 왼쪽 자식인 경우 2가지를 다루게 된다(2)
조부모 노드를 RED로, 부모노드를 BLACK으로 변경한뒤에
조부모 노드를 기준으로 (1)의 경우엔 왼쪽 회전을 (2)의 경우엔 오른쪽 회전을 해준다.
이로써 RBtree의 모든 특성을 만족하게 된다.
*/
void InsertCase5(RBtree * rbtree, Node * newNode) {
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if (g != NULL)
		g->color = RED;

	p->color = BLACK;

	if (newNode == p->right) {//(1)의 경우
		LRotate(g);

		if (rbtree->root == g) //루트노드가 변경된 경우
			rbtree->root = p;
	}
	else { //(2)의 경우 
		RRotate(g);

		if (rbtree->root == g) //루트노드가 변경된 경우
			rbtree->root = p;
	}
}

//rbtree에서 key값을 갖는 노드를 찾는다.
//노드를 검색하는데 성공할 경우 그 노드의 주소값 반환
//검색에 실패할 경우(key값을 갖는 노드가 없는 경우) NULL반환
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


//노드 안에 있는 가로 세로가 계산된 형태의 Key 값을 얻는다.
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

//서브트리의 최소값을 반환한다.
Node * rb_min(RBtree * tree, Node * node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}

//입력된 Key 값을 삭제한다.
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

//삭제할 Key 값의 방향을 확인한다.
Node * sibling(RBtree * rbtree, Node * delNode)
{
	Node * p = delNode->parent;

	if (delNode == p->left)
		return p->right;
	else
		return p->left;
}

//Key값 삭제로 인해 변화하는 다른 노드들의 키값을 새롭게 바꿔준다.
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

//삭제될 Key가 위치한 노드를 찾아낸다.
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

//디버깅을 위한 용도 임시 프린트, preorder형식
//제출 시엔 삭제
void RBTest_Print(Node * node, int depth) {
	int tmp;
	if (node == NULL)
		return;

	printf("                   ");

	for (int i = 0; i < depth; i++)
	{
		printf("     ");
	}

	printf("[%d(%d)]", Getkey(node), node->color); //key(색)

	printf("\n");

	//RBTest_Print(node->left, depth);
	//RBTest_Print(node->right, depth);

	RBTest_Print(node->left, depth / 2);
	RBTest_Print(node->right, (depth / 2) + depth + depth);
	//RBTest_Print(node->right, (depth*2) + depth + depth + depth);
}
