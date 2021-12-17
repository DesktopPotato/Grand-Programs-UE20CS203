//Linked List implementation of stack
//
#include <stdio.h>
#include <stdlib.h>

//------------------------STACK-PROPERTIES-------------------------------

struct node 
{
	int data;
	struct node *next;
};

typedef struct node node_t;

struct stack
{
	node_t *head;
};

typedef struct stack stack_t;


//---------------------Functions prototypes for the stack------------------



void push(stack_t *steck, int number_to_be_pushed);
int pop(stack_t *steck);
void display(stack_t *steck);
int empty(stack_t *steck);
int peep(stack_t *steck);
void init(stack_t *steck);

//Theory behind linked list implementation:
//We use simple head insertion and head deletion for
//pushing and popping from the stack.
//Stack is empty if the head points to NULL
//Stack can overflow only if malloc returns NULL 
//(which indicates lack of free space in memory)



//--------------------Client Part of the Program---------------------------


int main(void)
{
	stack_t *st;
	int ch, key, k;


	st = malloc(sizeof(stack_t));
	init(st);

	for (;;){

		printf(
			"1. Push\n"
			"2. Pop\n"
			"3. Display\n"
			"4. Peep\n"
			"-1. Quit\n\n"
			"Code: ");

		scanf(" %d", &ch);


		switch (ch) {
			case 1: 		printf("Enter element: ");
							scanf(" %d", &key);
							push(st, key);
							break;

			case 2:			k = pop(st);
							if (k == -1)
								printf("ERR: Stack underflow detected! The stack is already emtpy!\n");
							else
								printf("The number at the top was: %d\n", k);
							break;

			case 3:			display(st);
							break;

			case 4:			key = peep(st);

							if (key == -1) 
								printf("ERR: Stack underflow detected! The stack is already emtpy!\n");
							else
								printf("The number at the top is: %d\n", peep(st));
							break;

			case -1: 		return 0;

			default:		printf("Invalid operation!\n\n");

		}
	}
}

//----------------------------Functions------------------------------------

void init(stack_t *st)
{
	st->head = NULL;
	//Initializing head to NULL
}


void push(stack_t *st, int key){
	//Create a new node
	node_t *temp = malloc(sizeof(node_t));

	//Stack overflow condition (not enough memory space)
	if (temp == NULL) {
		printf("ERR: Not enough memory! Stack Overflow Detected!\n");
		return;
	}

	//Otherwise, proceed with insertion of node to the list
	temp->data = key;
	temp->next = st->head;
	st->head = temp;
}


int pop(stack_t *st)
{
	node_t *front;
	int key;


	//Popping from the stack is the same as 
	//deleting the head node
	
	//Case: If the stack is empty
	if (st->head == NULL) {
		return -1;
	}

	//All other cases: remove front node and return it's value
	
	front = st->head;
	key = front->data;
	st->head = front->next;
	free(front);

	return (key);

}

int peep(stack_t *st)
{
	//Get the data of the head node and return it
	
	//Case: Stack is empty
	if (st->head == NULL)
		return -1;

	//Other cases:
	return (st->head->data);
}


void display(stack_t *st)
{
	//Loop throgh the list until we reach the end
	
	for (node_t *pres = st->head;
		pres != NULL;
		pres = pres->next)
		printf("%d -> ", pres->data);

	//Print NULL at the end, to indicate bottom of stack
	
	printf("NULL\n");

}
