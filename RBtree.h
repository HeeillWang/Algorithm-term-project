#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>

#define RED 1
#define BLACK 0

typedef struct _node {
	int key;

	struct _node * parent;
	struct _node * left, * right;
	int color;

}Node;

typedef struct _rbtree {
	Node * root;
	Node * nil;

	int num;
}RBtree;


/* Section 1: Creating and freeing trees and nodes */
/* Helper routine: frees a subtree rooted at specified node. */
static void rb_free_subtree(RBtree * tree, Node * node);
/* Creates a new node, taking from the memory pool if available. */
static Node * rb_new_node(RBtree * tree, int data);


/* Section 2: Insertion */
/* Corrects for properties violated on an insertion. */
static void rb_insert_fix(RBtree * tree, Node * n);
/* Helper routine: returns the uncle of a given node. */
static Node * rb_get_uncle(RBtree * tree, Node * n);

/* Section 3: Deletion */
/* Helper routine: transplants node `from' into node `to's position. */
static void rb_transplant(RBtree * tree, Node * to, Node * from);
/* Corrects for properties violated on a deletion. */
static void rb_delete_fix(RBtree * tree, Node * n);

/* Section 4: I/O */
/* Helper routine: write an entire subtree to stdout. */
static void rb_preorder_write(RBtree * tree, Node * n);

/* Section 5: General helper routines */
/* Returns a node with the given key. */
static Node * rb_get_node_by_key(RBtree * haystack, int needle);
/* Rotates a tree around the given root. */
static void rb_rotate(RBtree * tree, Node * root, int go_left);
/* Returns minimum node in the given subtree. */
static Node * rb_min(RBtree * tree, Node * node);
/* Computes height of the tree rooted at node n. */
static int rb_height(RBtree * tree, Node * n);


/* Creates an empty Red-Black tree. */
RBtree * RBcreate();
/* Frees an entire tree. */
void RBfree(RBtree * tree);
/* Cleans up. Call this when you won't be using any more Red-Black trees. */
void RBcleanup();

/* Inserts an element with specified key into tree. */
int RBinsert(RBtree * tree, int key);

/* Deletes an element with a particular key. */
int RBdelete(RBtree * tree, int key);

/* Writes a tree to stdout in preorder format.
* Outputs everything on the same line. */
void RBprint(RBtree * tree);

Node * RBSearch(RBtree * rbtree, int key);

void RBPrint_info(RBtree * tree);

//rbtree의 leaf들을 출력한다.
void Print_leaves(RBtree * tree, Node * cur);


#endif /* RBTREE_H */