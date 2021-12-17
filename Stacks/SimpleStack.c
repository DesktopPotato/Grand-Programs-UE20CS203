//Array implementation of stack
//
#include <stdio.h>
#include <stdlib.h>

//------------------------STACK-PROPERTIES-------------------------------

struct stack
{
	int *s;				//Array for the stack contents
	int size;			//Size of stack 
	int top;			//The top index of the stack
};

typedef struct stack stack_t;


//---------------------Functions prototypes for the stack------------------



void push(stack_t *steck, int number_to_be_pushed);
int pop(stack_t *steck);
void display(stack_t *steck);
int empty(stack_t *steck);
int peep(stack_t *steck);
void init(stack_t *steck);




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
								printf("The stack is empty!\n");
							else
								printf("The number at the top was: %d\n", k);
							break;

			case 3:			display(st);
							break;

			case 4:			key = peep(st);

							if (key == -1) 
								printf("The stack is empty!\n");
							else
								printf("The number at the top is: %d\n", peep(st));
							break;

			case -1: 		return 0;

			default:		printf("Invalid operation!\n\n");

		}
	}
}


//----------------------------Functions------------------------------------

void init(stack_t *ptr_st)
{
	//Stack size is asked due to array implementation
	//Arrays have fixed size
	printf("Enter the size: ");

	scanf(" %d", &ptr_st->size);
	ptr_st->s = malloc(sizeof(int[ptr_st->size]));

	//The index of the stack is initialized to -1
	ptr_st->top = -1;
}

void push(stack_t *ptr_st, int key)
{
	//Convention states that whenever we push
	//an element, we increment the index and then
	//assign a number to that element
	if (ptr_st->top == ptr_st->size - 1)				//Checking for Stack Overflow 
		printf("The stack is full!\n");
	else {
		(ptr_st->top)++;								//Increment Top
		(ptr_st->s)[ptr_st->top] = key;					//Inserting the element
	}
	
	//Insertion can also be done in a single line
	//by 
	//(ptr_st->s)[++(ptr_st->top)] = key;
}


int pop(stack_t *ptr_st)
{
	int key;
	//Whenever we pop, we first assign the element 
	//to key and then decrement the index

	if (ptr_st->top == -1){								//Stack underflow
		return -1;
	}

	key = (ptr_st->s)[ptr_st->top];						//Get the element
	(ptr_st->top)--;									//Decrement Top

	return key;

	//The above can be done in a single line by
	//return (ptr_st->s)[(ptr_st->top)--];
}

int peep(stack_t *ptr_st)
{
	//Return the element at the top of the stack
	//
	//if the stack is empty, return -1
	//otherwise return the element at the top
	return (ptr_st->top == -1) ? -1 : (ptr_st->s)[ptr_st->top];
}

void display(stack_t *ptr_st)
{
	//If the stack is empty, tell so
	if (ptr_st->top == -1)								//Empty Stack Condition
		printf("The stack is empty!\n");
	else {
		//Use a for loop from the top of the stack 
		//to the bottom
		for (int i = ptr_st->top;						//Display all numbers
			i >= 0;
			i--)
		{
			printf(" %d\n", (ptr_st->s)[i]);
		}
		printf("\n");
	}
}
