#include "RBtree.h"
#include <stdlib.h>
#include <stdio.h>


/*------------------------------Creation------------------------------*/

//RBtree ����
RBtree * RBcreate() {
	RBtree * rbtree; 
	if ((rbtree = malloc(sizeof(*rbtree))) == NULL) {
		printf("Error: out of memory.\n");
		return NULL;
	}


	if ((rbtree->nil = malloc(sizeof(*rbtree->nil))) == NULL) {
		printf("Error: out of memory.\n");
		free(rbtree);
		return NULL;
	}
	rbtree->nil->color = BLACK;
	rbtree->nil->left = rbtree->nil;
	rbtree->nil->right = rbtree->nil;
	rbtree->nil->parent = rbtree->nil;
	rbtree->root = rbtree->nil;
	rbtree->num = 0;

	return rbtree;
}

//�Ҵ�� rbtree�� �����Ѵ�.
void RBfree(RBtree * tree) {
	rb_free_subtree(tree, tree->root);
	free(tree->nil);
	free(tree);
}

//���� Ʈ������ free�Ѵ�
static void rb_free_subtree(RBtree * tree, Node * node) {
	if (node == tree->nil) return; /* We only free tree->nil once */
	rb_free_subtree(tree, node->left);
	rb_free_subtree(tree, node->right);
	free(node);
}

//���ο� ��带 �����Ͽ� ��ȯ�Ѵ�.
static Node * rb_new_node(RBtree * tree, int key) {
	Node * ret;

	if ((ret = malloc(sizeof(*ret))) == NULL) {
		printf("Error: out of memory.\n");
		return NULL;
	}

	ret->key = key;
	ret->parent = tree->nil;
	ret->left = tree->nil;
	ret->right = tree->nil;
	ret->color = RED;
	return ret;
}



/*------------------------------Insertion------------------------------*/

/*
key���� ���� ��带 �����Ͽ� rbtree�� �߰��Ѵ�.
������ 1, ���н� 0�� ��ȯ
���� ���� ���� key�� �̹� �����ϴ� ��쿡�� 0�� ��ȯ�Ѵ�.
*/
int RBinsert(RBtree * tree, int key) {
	Node * newnode;
	Node * newparent = tree->nil;
	Node * pos = tree->root;
	
	//���Ե� ��ġ�� ã�´�.
	while (pos != tree->nil) {
		newparent = pos;
		if (key < pos->key) {
			pos = pos->left;
		}
		else if (key > pos->key) {
			pos = pos->right;
		}
		else {
			printf("Error: node %d already in the tree.\n", key);
			return 0;
		}
	}

	//key�� ���� ��带 ����
	newnode = rb_new_node(tree, key);
	if (newnode == NULL) {
		return 0;
	}

    //�θ� ��忡 ���� ����
	newnode->parent = newparent;
	if (newparent == tree->nil) {
		tree->root = newnode;
	}
	else if (key < newparent->key) {
		newparent->left = newnode;
	}
	else {
		newparent->right = newnode;
	}
	
	rb_insert_fix(tree, newnode); //���� �� rbtree�� Ư���� ��Ű�� ���� ����

	tree->num++;
	RBPrint_info(tree);
	return 1;
}

//���� ����, rbtree�� Ư���� �������ش�.
static void rb_insert_fix(RBtree * tree, Node * n) {
	Node * gp = n->parent->parent; //���θ� ���
    Node * uncle = rb_get_uncle(tree, n); //���� ���

	//������ RED�� ���
	while (n->parent->color == RED && uncle->color == RED) {
		gp->color = RED;
		uncle->color = BLACK;
		n->parent->color = BLACK;
		n = gp;
		gp = n->parent->parent;
		uncle = rb_get_uncle(tree, n);
	}

	if (n->parent->color == BLACK) {
		if (n == tree->root) {
			n->color = BLACK;
		}
		return;
	}

	//��尡 ���̰� "����� ���"
	if ((n->parent->left == n) == (gp->left == uncle)) {
		Node * new_n = n->parent;
		rb_rotate(tree, new_n, new_n->right == n);
		n = new_n;
	} /* Fall through */
	
	//��尡 ���̰� "�� ���"
	n->parent->color = BLACK;
	gp->color = RED;
	rb_rotate(tree, gp, gp->left == uncle);
	tree->root->color = BLACK;
}

//�־��� ����� ���� ��带 ��ȯ�Ѵ�.
static Node * rb_get_uncle(RBtree * tree, Node * n) {
	Node * gp;
	if (n->parent == tree->nil || n->parent->parent == tree->nil) {
		return tree->nil;
	}
	gp = n->parent->parent;
	return (gp->left == n->parent) ? gp->right : gp->left;
}





/*----------------------------Deletion---------------------------------*/

/*
rbtree���� key���� ���� ��带 �����Ѵ�.
������ 1, ���н� 0�� ��ȯ
key���� ��尡 �������� ���� ��쿡�� 0�� ��ȯ
*/
int RBdelete(RBtree * tree, int key) {
	Node * dead = rb_get_node_by_key(tree, key); //������ ���
	Node * fixit;
	char orig_col = dead->color;

	//key���� ��尡 �������� ���� ��
	if (dead == tree->nil) {
		printf("Error: node %d does not exist.\n", key);
		return 0;
	}
	

	//���� Ʈ���� ������ �����Ѵ�.
	if (dead->left == tree->nil) {
		fixit = dead->right;
		rb_transplant(tree, dead, fixit);
	}
	else if (dead->right == tree->nil) {
		fixit = dead->left;
		rb_transplant(tree, dead, fixit);
	}
	else {
		//������ ��带 successor�� ��ü�Ѵ�.
		Node * successor = rb_min(tree, dead->right);
		orig_col = successor->color;
		fixit = successor->right;
		if (successor->parent == dead) {
			fixit->parent = successor;
		}
		else {
			//successor�� ������ �ڽ��� ��ġ�� �����ء���.
			rb_transplant(tree, successor, successor->right);
			successor->right = dead->right;
			successor->right->parent = successor;
		}
		rb_transplant(tree, dead, successor);
		successor->left = dead->left;
		successor->left->parent = successor;
		successor->color = dead->color;
	}
	free(dead);
	
	//������ ��尡 BLACK�� ���, rbtree�� ��Ģ�� ��Ű�� ���� ������ �ʿ��ϴ�.
	if (orig_col == BLACK) {
		rb_delete_fix(tree, fixit);
	}

	tree->num--;
	RBPrint_info(tree);

	return 1;
}
/* Helper routine: transplants node `from' into node `to's position. */
static void rb_transplant(RBtree * tree, Node * to, Node * from) {
	if (to->parent == tree->nil) {
		tree->root = from;
	}
	else if (to == to->parent->left) {
		to->parent->left = from;
	}
	else {
		to->parent->right = from;
	}
	from->parent = to->parent;
}
/* Corrects for properties violated on a deletion. */
static void rb_delete_fix(RBtree * tree, Node * n) {
	/* It's always safe to change the root black, and if we reach a red
	* node, we can fix the tree by changing it black. */
	while (n != tree->root && n->color == BLACK) {
		/* Instead of duplicating code, we just have a flag to test
		* which direction we are dealing with. */
		int is_left = (n == n->parent->left);
		Node * sibling = (is_left) ? n->parent->right : n->parent->left;
		/* Case 1: sibling red */
		if (sibling->color == RED) {
			sibling->color = BLACK;
			sibling->parent->color = RED;
			rb_rotate(tree, sibling->parent, is_left);
			sibling = (is_left) ? n->parent->right : n->parent->right;
		}
		/* Case 2: sibling black, both sibling's children black */
		if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
			sibling->color = RED;
			n = n->parent;
		}
		else {
			/* Case 3: sibling black, "far" child black */
			if ((is_left && sibling->right->color == BLACK) ||
				(!is_left && sibling->left->color == BLACK)) {
				if (is_left) {
					sibling->left->color = BLACK;
				}
				else {
					sibling->right->color = BLACK;
				}
				sibling->color = RED;
				rb_rotate(tree, sibling, !is_left);
				sibling = (is_left) ? n->parent->right : n->parent->left;
			} /* Fall through */
			  /* Case 4: sibling black, "far" child red */
			sibling->color = n->parent->color;
			n->parent->color = BLACK;
			if (is_left) {
				sibling->right->color = BLACK;
			}
			else {
				sibling->left->color = BLACK;
			}
			rb_rotate(tree, n->parent, is_left);
			/* We're done, so set n to the root node */
			n = tree->root;
		}
	}
	n->color = BLACK;
}


/*------------------------Print----------------------------------*/

//rbtree�� ���� �������� ����Ѵ�.
void RBPrint_info(RBtree * tree){
	printf("Number of Nodes : %d\n", tree->num);
	printf("Root : %d\n", tree->root->key);
	printf("Leaves : ");
	Print_leaves(tree,tree->root);
	printf("\n");
	printf("Height : %d\n", rb_height(tree, tree->root));
}

//rbtree�� leaf���� ����Ѵ�.
void Print_leaves(RBtree * tree, Node * cur){
	if (cur->left == tree->nil && cur->right == tree->nil)
		printf("%d ", cur->key);
	else if (cur->left != tree->nil && cur->right != tree->nil){
		Print_leaves(tree, cur->right);
		Print_leaves(tree, cur->left);
	}
	else if (cur->left == tree->nil)
		Print_leaves(tree, cur->right);
	else if (cur->right == tree->nil)
		Print_leaves(tree, cur->left);
}


/*------------------------��Ÿ �Լ���--------------------------------*/


/* Returns a node with the given key. */
static Node * rb_get_node_by_key(RBtree * haystack, int needle) {
	Node * pos = haystack->root; /* our current position */
	while (pos != haystack->nil) {
		if (pos->key == needle) {
			return pos;
		}
		else if (needle < pos->key) {
			pos = pos->left;
		}
		else {
			pos = pos->right;
		}
	}
	return haystack->nil;
}
/* Rotates a tree around the given root. */
static void rb_rotate(RBtree * tree, Node * root, int go_left) {
	/* Instead of duplicating code, we just
	* have a flag to indicate the direction to rotate. */
	/* The new top node */
	Node * newroot = (go_left) ? root->right : root->left;
	/* We swap the center child and the old top node */
	if (go_left) {
		root->right = newroot->left;
		if (root->right != tree->nil) {
			root->right->parent = root;
		}
		newroot->left = root;
	}
	else {
		root->left = newroot->right;
		if (root->left != tree->nil) {
			root->left->parent = root;
		}
		newroot->right = root;
	}
	/* Now we set up the parent nodes */
	newroot->parent = root->parent;
	root->parent = newroot;
	/* We update old top node's parent to point to the new top node */
	if (newroot->parent == tree->nil) {
		tree->root = newroot;
	}
	else if (newroot->parent->left == root) {
		newroot->parent->left = newroot;
	}
	else {
		newroot->parent->right = newroot;
	}
}
/* Returns minimum node in the given subtree. */
static Node * rb_min(RBtree * tree, Node * node) {
	while (node->left != tree->nil)
		node = node->left;
	return node;
}
/* Computes height of the tree rooted at node n. */
static int rb_height(RBtree * tree, Node * n) {
	int l, r;
	if (n == tree->nil) return 0;
	l = rb_height(tree, n->left);
	r = rb_height(tree, n->right);
	return 1 + ((l > r) ? l : r);
}

//rbtree���� key���� ���� ��带 ã�´�.
//��带 �˻��ϴµ� ������ ��� �� ����� �ּҰ� ��ȯ
//�˻��� ������ ���(key���� ���� ��尡 ���� ���) NULL��ȯ
Node * RBSearch(RBtree * rbtree, int key) {
	Node * cur = rbtree->root;

	while (1) {
		if (cur->key == key)
			return cur;
		else if (cur->key > key)
			cur = cur->left;
		else
			cur = cur->right;

		if (cur == NULL)
			return NULL;
	}
}

