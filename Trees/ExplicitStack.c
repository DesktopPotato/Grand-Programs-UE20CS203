//Program for iterative inorder traversal
//
//Theory: We move to the leftmost node, and push
//every node into a stack as we do so
//When we reach NULL, we pop from the stack to get
//the leftmost node, and then we print it,
//and then go to it's right. Then, we keep 
//going left again (to get the inorder successor),
//as we do so, we push more nodes into the stack
//and pop them as we come back up


#include <stdio.h>
#include <stdlib.h>

struct tnode
{
	int data;
	struct tnode *left;
	struct tnode *right;
};

typedef struct tnode tnode_t;

void insert(tnode_t **, int);
void inorder(tnode_t *);
void push(tnode_t *);
tnode_t *pop(void);
int isempty(void);


//stack, global variable
tnode_t *stk[100];
// pointer to top element of stack
int top; 

int main(void)
{
	int num, r, m, k;
	tnode_t *root;
	root = NULL;

	//Keep asking the user for elements
	//until the user enters -1
	for (;;) {
		printf("Enter number for insertion (-1 to stop): ");
		scanf(" %d", &num);
		if (num == -1)
			break;
		insert(&root, num);
	}

	printf("Inorder traversal of the tree:\n"); inorder(root);

	printf("\n");
}


void inorder(tnode_t *t)
{
	//Initialize the stack's index
	top = -1;
	//While the current node is not NULL
	//keep going to the left, while pushing
	//the node into the stack
	while (t != NULL) {
		push(t);
		t = t->left;
	}
	//Now we are at the left most node
	//or the smallest number in the tree

	//While the stack is not empty
	while (!isempty()) {
		//Pop from the stack, and print it's data
		t = pop();
		printf("%d ", t->data);

		//If the right child exists, go right
		if (t->right != NULL) {
			t = t->right;

			//Now, keep going left to find the
			//inorder successor of the previously
			//popped node
			while(t != NULL) {
				push(t);
				t = t->left;	 
			}
		}
	}
}

void insert(tnode_t **t, int x)
{
	tnode_t *temp, *prev, *curr;

	//Create and initialize node
	temp = malloc(sizeof(tnode_t));
	temp->data = x;
	temp->left = temp->right = NULL;

	//If the tree is empty
	if(*t == NULL)
		*t = temp;	//Assign the new node to the root pointer
	else {
		//prev will point to the parent of the newly 
		//inserted node (which is pointed to by curr)
		prev = NULL;
		curr = *t;
		while (curr != NULL) {
			prev = curr;
			if (x < curr->data)
				curr = curr->left;//move left
			else
				curr = curr->right;//move right
		}
		if (x < prev->data)
			prev->left = temp;
		else
			prev->right = temp;
	}
}   


int isempty()
{
	return (top == -1);
}


void push(tnode_t* temp)
{
	//First increment top, then assign element
	++top;
	stk[top] = temp;
}

tnode_t *pop()
{
	//First get the element, then decrement top
	//Then return the element
	tnode_t *temp;
	temp = stk[top];
	--top;
	return temp;
}

