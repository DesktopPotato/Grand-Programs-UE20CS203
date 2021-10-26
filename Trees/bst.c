//GRAND PROGRAM FOR TREES
//Please send any bugs reports, queries or doubts to Aditya Rao, PES1UG20CS022
//

#include <stdio.h>
#include <stdlib.h>
#define CLEANLINE while ((CH = getchar()) != '\n' && CH != EOF)

struct tnode {
	int data;
	struct tnode *left;
	struct tnode *right;
};

typedef struct tnode node_t;

void inorder(node_t *node);				//Print in in-order
void preorder(node_t *node);			//Print in pre-order
void postorder(node_t *node);			//Print in pre-order
void insert(node_t **node, int key);	//Inserts a node
int count(node_t *node);				//Counts the number of nodes
int leafcount(node_t *node);			//Counts number of leaves
int height(node_t *node);				//Prints height of tree
int minimum(node_t *t);					//Prints minimum number in tree
int maximum(node_t *t);					//Prints maximum number in tree
node_t *rinsert(node_t *t, int key);	//Recursively insert
node_t *tdelete(node_t *t, int key);	//Delete a node 
int search(node_t *t, int key);			//Searches a tree for a given key
int rsearch(node_t *t, int key);		//Recusively searches a tree
//void printtree(node_t *node);			//UNDER DEVELOPMENT(MIGHT BE REMOVED)	





int main(void)
{
	int ch, key, CH;
	node_t *root = NULL;

	for (;;) {
		printf("\nChoose:\n"
		" 1. Insert\n"
		" 2. Preorder\n"
		" 3. Postorder\n"
		" 4. Inorder\n"
		" 5. No of nodes\n"
		" 6. No of leaf nodes\n"
		" 7. Height of the tree\n"
		" 8. Delete a node\n"
		" 9. Recursively insert\n"
		"10. Search\n"
		"11. Search using recursion\n"
		"13. Find smallest\n"
		"14. Find Largest\n"
		"-1. Exit\n\n"
		"Choice:");
		scanf(" %d", &ch);
		printf("\n");
		CLEANLINE;					//Similar to fflush

		switch (ch) {

			case 1:		printf("Enter number to be inserted: ");
						scanf(" %d", &key);
						insert(&root, key);
						break;

			case 2:		preorder(root);
						printf("\n\n");
						break;

			case 3:		postorder(root);
						printf("\n\n");
						break;

			case 4: 	inorder(root);
						printf("\n\n");
						break;

			case 5:		printf("The tree has %d nodes\n", count(root));
						break;

			case 6:		printf("The number of leaves in the tree are: %d\n", 
						leafcount(root));
						break;

			case 7:		printf("The height of the tree is %d\n", 
						height(root));
						break;
			
			case 8:		printf("Enter node to be deleted: ");
						scanf(" %d", &key);
						root = tdelete(root, key);
						break;

			case 9: 	printf("Enter number to be inserted: ");
						scanf(" %d", &key);
						root = rinsert(root, key);
						break; 

			case 10:	printf("Enter number to be searched: ");
						scanf(" %d", &key);
						key = search(root, key);
						key ? printf("The number exists in the tree\n"):
							  printf("The number does not exist in the tree\n");
						break;

			case 11:	printf("Enter number to be searched: ");
						scanf(" %d", &key);
						key = rsearch(root, key);
						key ? printf("The number exists in the tree\n"):
							  printf("The number does not exist in the tree\n");
						break;

			case 13:	minimum(root);
						break;

			case 14:	maximum(root);
						break;

			// case 15:	printtree(root);
			// 			break;

			case -1:	return 0;
						break;

			default:	printf("Invalid choice\n");
						break; 			
		}
		CLEANLINE;
	}
}

void insert(node_t **t, int key)
{
	node_t *prev, *curr, *temp;
	temp = malloc(sizeof(node_t));	
	temp->data = key;
	temp->left = temp->right = NULL;

	if (*t == NULL)					//Empty tree
		*t = temp;
	else {
		prev = NULL;
		curr = *t;

		while (curr != NULL) {
			prev = curr;
			if (key < curr->data)
				curr = curr->left;
			else 
				curr = curr->right;
		}

		if (key < prev->data)
			prev->left = temp;
		else 
			prev->right = temp;
	}
}


void preorder(node_t *node)
{
	if (node != NULL) {
		printf("%d ", node->data);
		preorder(node->left);
		preorder(node->right);
	}
}


void inorder(node_t *node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%d ", node->data);
		inorder(node->right);
	}
}

void postorder(node_t *node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%d ", node->data);
	}
}

// void printtree(node_t *node)				//Some stuff that I decided to implement on my own
// {
// 	if (node != NULL) {
// 		printf("%d\n", node->data);
// 		printf("-->");
// 		printtree(node->left);
// 		printf("-->");
// 		printtree(node->right);
// 	}
// }


int count(node_t *node)
{
	if (node == NULL)
		return 0;
	else 
		return (1 + count(node->left) + count(node->right));
}

int minimum(node_t *t) 
{
	for (	; 
		t->left != NULL; 
		t = t->left)
		;
	return t->data;
}

int maximum(node_t *t)
{
	for (	; 
		t->right != NULL; 
		t = t->right)
		;
	return t->data;
}

int leafcount(node_t *t)
{
	int left, right;
	if (t == NULL)								//If root is the only node
		return 0;								
	if (t->left == NULL && t->right == NULL)	//All other leaf nodes
		return 1;
	
	left = leafcount(t->left);
	right = leafcount(t->right);
	return (left + right);
}

int height(node_t *t)
{
	int l, r;
	if (t == NULL) 
		return -1;
	if (t->left == NULL && t->right == NULL)
		return 0;

	l = height(t->left);
	r = height(t->right);

	return (1 + (l>r ? l : r));

}

int search(node_t *t, int key)			
{
	while (t != NULL && t->data != key) {		//Will stop only if t is null
		if (key < t->data)						//or if key is found
			t = t->left;
		else 
			t = t->right;
	}

	if (t == NULL)								//If t is null, key wasn't found
		return 0;
	return 1;
}

int search_two(node_t *t, int key)				//A second version of search
{
	while (t != NULL) {							//Keeps searching until key is found
		if (t->data == key)						//If key wasn't found, 
			return 1;							//returns 0
		if (key < t->data)
			t = t->left;
		else 
			t = t->right;
	}

	return 0;
}

int rsearch(node_t *t, int key)
{
	if (t == NULL)								//Base cases (only two possible)
		return 0;
	if (t->data == key)
		return 1;
	if (key < t->data)
		return rsearch(t->left, key);
	else 
		return rsearch(t->right, key);
	
} 

node_t *rinsert(node_t *t, int key)
{

	node_t *temp;

	if (t == NULL)
	{
		temp = malloc(sizeof(node_t));
		temp->data = key;
		temp->left = temp->right = NULL;
		return temp;
	}

	if (key < t->data) 
		t->left = rinsert(t->left, key);
	else 
		t->right = rinsert(t->right, key);
	return t;

}

node_t *tdelete(node_t *t, int key)					
{
	node_t *temp, *curr, *prev, *parent, *child;
	
	curr = t;
	prev = NULL;

	while (curr != NULL && curr->data != key) {
		prev = curr;
		curr = (key < curr->data) ? curr->left: curr->right;
	}

	if (curr == NULL) {
		printf("Key not found\n");
		return t;
	}

	//Key found
	//If only one subtree is present or no subtree is present
	
	if (curr->left == NULL || curr->right == NULL) {
		//Finding which side of the node is empty
		//If both sides are empty, then child will be NULL
		child = (curr->left == NULL) ? curr->right : curr->left;

		if (prev == NULL){		//Deleting root with one subtree
			free(curr);
			return child;
		}

		if (curr == prev->right)	//If the current node is to the
			prev->right = child;		//right of it's parent
		else
			prev->left = child;

		free(curr);

	} else {				//Both subtrees are present
		//Find the in-order successor
		parent = NULL;
		temp = curr->right;

		for (parent = NULL, temp = curr->right;		//Temp will the sucecssor
			temp->left != NULL;
			parent = temp, temp = temp->left)
			;
		
		curr->data = temp->data;			//

		if (parent != NULL) 
			parent->left = temp->right;
		else
			curr->right = temp->right;
		free(temp);
	}

	return t;
}




