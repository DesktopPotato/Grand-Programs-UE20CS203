//Program to implement a threaded binary search tree
//And perform inorder traversal

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tnode
{
	int data;
	struct tnode *left;
	struct tnode *right;
	//Bools lthread and rthread:
	//lthread and rthread are false if the
	//node has child nodes on left side and 
	//right side respectively. Otherwise, true
	bool lthread;
	bool rthread;
};

typedef struct tnode tnode_t;

tnode_t *insert(tnode_t *, int);
void inorder(tnode_t *);
tnode_t *inordersuccessor(tnode_t *);


int main(void)
{
	tnode_t *root;
	int ch, num, k;
	root = NULL;

	for (;;)
	{
		printf("Enter choice:\n"
			" 1. Insert\n"
			" 2. Inorder Traversal\n"
			"-1. Exit\n\n");

		scanf("%d",&ch);

		switch(ch) {
			case 1:		printf("Enter the element: ");
						scanf(" %d", &num);
						root = insert(root, num);
						break;

			case 2:		printf("Inorder traversal:\n");
				   		inorder(root);
						printf("\n");
				   		break;

			case -1:	return 0;
		}
	}
}    

void inorder(tnode_t *t)
{
	tnode_t *curr;
	curr = t;

	//Go the the leftmost node
	while (curr->lthread == false)
		curr = curr->left;

	//While curr is not null, keep printing curr
	//and increment curr to it's inorder successor
	while (curr != NULL) {
		printf("%d ", curr->data);
		curr = inordersuccessor(curr);
	}
}


tnode_t *inordersuccessor(tnode_t *t)
{
	//If the node is right-threaded,
	//return the t->right
	if (t->rthread == true)
		return t->right;

	//Otherwise, find the leftmost child of
	//the right child of the given node
	//(This leftmost child is the inorder
	//successor)
	
	t = t->right;
	while (t->lthread == false)
		t = t->left;


	return t;
}

tnode_t* insert(tnode_t *t, int key)
{
	tnode_t *curr, *temp;

	curr = t;

	temp = malloc(sizeof(tnode_t));
	temp->data = key;
	temp->left = temp->right = NULL;
	temp->lthread = temp->rthread = true;

	if (curr == NULL) //First element,
		return temp;

	//Traverse through the tree 
	for (;;) {
		//Traversing to the left
		if (key < curr->data) {
			if (curr->lthread == false)
				curr = curr->left;
			else
				break;
		} else if (key > curr->data) {
			//Traversing to the right
			if (curr->rthread == false)
				curr = curr->right;
			else
				break;
		}
	}


	//Assigning temp as the child node to curr:
	//since temp is being assigned as a child to curr,
	//curr will lose it's thread on the side where temp 
	//will be assigned
	//temp, however, will point towards curr (even though
	//it is a child node).
	if (key < curr->data) {
		//temp->left is assigned curr->left as
		//curr->left will become the inorder predecessor
		//to temp
		temp->left = curr->left;
		temp->right = curr;
		curr->left = temp;
		curr->lthread = false;
	} else {
		//temp->right is assigned curr->right as
		//curr->right will become the inorder successor
		//to temp
		temp->right = curr->right;
		temp->left = curr;
		curr->right = temp;
		curr->rthread = false;
	}
	return t;
}


