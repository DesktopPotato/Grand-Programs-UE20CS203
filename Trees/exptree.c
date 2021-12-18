//Program to create an expression tree
//And then evaluate it

#include <stdio.h>
#include <stdlib.h>


struct tnode
{
	char data;
	struct tnode *left;
	struct tnode *right;
};



void inorder(struct tnode *);
void preorder(struct tnode *);
void postorder(struct tnode *);
struct tnode *create_exptree(char *);
int isoper(char);
void push(struct tnode **, int *, struct tnode *);
struct tnode *pop(struct tnode **, int *);
int evaluate(struct tnode *);



int main(void)
{
	struct tnode *root;
	int ch, num, k;

	//String for expression
	char exp[100];

	//Initializing root
	root = NULL;

	printf("Enter a postfix expression (do not use spaces): ");
	scanf(" %s", exp);

	root = create_exptree(exp);
	printf("Infix form: ");
	inorder(root);
	printf("\nPrefix form: ");
	preorder(root);
	printf("\nThe postfix form: ");
	postorder(root);
	printf("\n\n");
	int result = evaluate(root);
	printf("\nThe evaluation of the expression = %d\n", result);

	return 0;

}

int evaluate(struct tnode *t)
{
	int a;
	//Recursive function
	//If the node has an operator, then calls evaluate on left
	//node and right node and evaluates the result 
	//If the node has an operand, asks it's value to the user
	switch (t->data) {
		case '+':	return(evaluate(t->left) + evaluate(t->right));

		case '-': 	return(evaluate(t->left) - evaluate(t->right));

		case '*': 	return(evaluate(t->left) * evaluate(t->right));

		case '/': 	return(evaluate(t->left) / evaluate(t->right));

		default:	printf("Enter value for %c: ", t->data);
					scanf("%d", &a);
					return a;
	}
}



struct tnode *create_exptree(char  *exp)
{
	//Creates an expression tree
	//Uses an explicit stack of node structures
	struct tnode *stk[100];
	struct tnode *temp;

	//Stack index
	int top = -1;
	char ch;

	//Traversing through the string
	for (int i = 0; exp[i] != '\0'; i++) {
		ch = exp[i];
		//Initialize a new node for every character
		temp = malloc(sizeof(struct tnode));
		temp->data = ch;
		temp->left = temp->right = NULL;

		//If the character is an operator, pop two elements from
		//the stack and connect them together with the left
		//and right pointers
		//Then push the operator back into the stack
		if (isoper(ch)) {
			temp->right = pop(stk, &top);
			temp->left = pop(stk, &top);
			push(stk, &top, temp);
		} else  
			//If operand, then push the node into the stack
			push(stk, &top, temp);
	}
	return(pop(stk, &top)); // return root of the tree
} 


void push(struct tnode **s, int *t, struct tnode *temp)
{
	//First increment the top, then assign
	++*t;
	s[*t] = temp;
}

struct tnode *pop(struct tnode **s, int *t)
{
	//First get the element from the stack, then decrement
	struct tnode *temp;

	temp=s[*t];
	--*t;
	return temp;
}

int isoper(char ch)
{
	//Returns true if character is an operator
	switch(ch)
	{
		case '+':
		case '-':
		case '*':
		case '/':	return 1;

		default: 	return 0;
	}
}



//Standard traversal techniques:

void preorder(struct tnode *t)
{
	if (t != NULL)
	{
		printf("%c ",t->data);
		preorder(t->left);
		preorder(t->right);
	}
}

void postorder(struct tnode *t)
{
	if(t!=NULL)
	{

		postorder(t->left);
		postorder(t->right);
		printf("%c ",t->data);
	}
}

void inorder(struct tnode *t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		printf("%c ",t->data);
		inorder(t->right);
	}
}

















































