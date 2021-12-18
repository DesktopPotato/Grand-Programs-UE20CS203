//binary search tree using array
//
//Forumlae:
//If i is the parent index, and j is the left child
//then j = 2*i + 1
//if j is the right child
//then j = 2*i + 2
//Similarly, if i is a non-root node, then (i-1)/2 gives
//you the index of the parent node


#include <stdio.h>
#include <stdlib.h>

void insert(int *, int);
void preorder(int *, int);
void postorder(int *, int);
void inorder(int *, int);
int minimum(int *);
int maximum(int *);
void levelorder(int *t, int i);


int main(void)
{
	//Array to work as our tree:
	int t[100];
	int ch, num, k, i;

	//Initialize all elements of array to be -1
	for (i = 0; i < 100; i++)
		t[i] = -1;

	for (;;) {
		printf("Enter code:\n"
			" 1. Insert\n"
			" 2. Preorder\n"   
			" 3. Postorder\n"
			" 4. Inorder\n"
			" 5. Levelorder\n"
			" 6. Minimum\n"
			" 7. Maximum\n"
			"-1. Exit\n");

		scanf("%d",&ch);
		switch(ch) {
			case 1:		printf("Enter element to be inserted: ");
						scanf(" %d", &num);
						insert(t, num);
						break;

			case 2: 	preorder(t, 0);
						printf("\n");
						break; 

			case 3: 	postorder(t, 0);
						printf("\n");
						break;

			case 4:		inorder(t, 0);
						printf("\n");
				   		break;

			case 5:		levelorder(t, 0);
						printf("\n");
						break;

			case 6: 	k = minimum(t);
				    	printf("The smallest element is %d\n", k);
				    	break;

			case 7: 	k = maximum(t);
						printf("The largest element is %d\n", k);
						break;  

			case -1:	return 0;
		}
	}
}    

void insert(int *t, int key)
{
	int i = 0;
	//While node is not NULL
	while (t[i] != -1) {
		if (key < t[i])
			i = 2*i + 1; //move left
		else
			i = 2*i + 2;// move right
	}
	//Insert the new key
	t[i]=key;
}

void preorder(int *t, int i)
{
	//First print node, then 
	//do the same with left and right
	//children
	if (t[i]!= -1) {
		printf("%d ", t[i]);
		preorder(t, 2*i + 1);
		preorder(t, 2*i + 2);
	}
}

void postorder(int *t, int i)
{
	//First execute function on
	//both left and right children,
	//do print the node
	if(t[i]!=-1) {
		postorder(t, 2*i+1);
		postorder(t, 2*i+2);
		printf("%d ",t[i]);
	}
}

void inorder(int *t, int i)
{
	//First execute function on left
	//children, then print node,
	//then execute function on right
	//children
	if(t[i]!=-1) {
		inorder(t, 2*i+1);
		printf("%d ",t[i]);
		inorder(t, 2*i+2);
	}
}

int minimum(int *t)
{
	//Go as far left as possible
	int i = 0;
	while (t[2*i+1] != -1) 
		i = 2*i + 1;
	return t[i];
}

int maximum(int *t)
{
	//Go as far right as possible
	int i=0;
	while(t[2*i+2]!=-1) 
		i=2*i+2;
	return t[i];
}

void levelorder(int *t, int i)
{
	//Traverse through the array and print 
	//the elements
	while (i < 100) {
		printf("%d ", t[i]);
		i++;
	}
}
