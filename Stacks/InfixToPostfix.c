#include<stdio.h>

//Theory:
//If we encounter an operand, we write it to the
//postfix string. If we encounter an operator,
//and the character in the stack has lower precedence,
//then we push the operator into the stack
//Otherwise, we pop the character from the stack
//and then push the opereator into the stack
//Parenthesis: When we encounter a forward
//brace, we push it into the stack
//When we encounter a back brace, we keep
//popping from the stack until we finally pop
//the forward brace

int input_prec(char);
int stack_prec(char);
char peep(char *, int);
void convert_postfix(char *, char *);
void push(char *, int *, char);
char pop(char *, int *);

int main(void)
{
	char infix[100], postfix[100];
	printf("Enter a valid infix expression:\n");
	scanf(" %s", infix);
	convert_postfix(infix, postfix);
	printf("The postfix equivalent = %s\n", postfix);
}

void convert_postfix(char *infix, char *postfix)
{
	char s[100];					//stack
	char ch;
	int top = -1;					//Top index of the stack

	int j = 0;

	//We use a # to indicate the bottom of the stack
	push(s, &top, '#');

	//Now, we scan through the infix string
	for (int i = 0; infix[i] != '\0'; i++) {
		ch = infix[i];

		//While the character in the stack has higher
		//priority than the symbol being scanned currently,
		//keep popping from the stack and placing the
		//characters in the postfix string
		while(stack_prec(peep(s,top)) > input_prec(ch))
			postfix[j++] = pop(s,&top);

		//If the priority of the input is higher than
		//the character at the top of the stack,
		//push the input into the stack
		if(input_prec(ch) > stack_prec(peep(s,top)))
			push(s, &top, ch);
		else
			//This is the case for parenthesis matching
			//A back brace in the input cancels
			//a forward brace in the stack
			pop(s, &top);
	}


	//After scanning through the string, pop all
	//the contents of the stack
	while(peep(s,top) != '#')
		postfix[j++] = pop(s,&top);
	postfix[j] = '\0';
}

//Returning the input's priority
int input_prec(char ch)
{
	switch(ch)
	{
		case '+': case '-':			return 1;

		case '*': case '/':			return 3;

		case '$':					return 6;

		case '(':					return 9;

		case ')':					return 0;

		default:					return 7;
	}
}


//Function to return the stack precedence
int stack_prec(char ch)
{
	switch(ch)
	{
		case '+': case '-':			return 2;

		case '*': case '/':			return 4;

		case '$':					return 5;

		case '(':					return 0;

		case '#':					return -1;

		default:					return 8;
	}
}


char peep(char * s, int t)
{
	//Returns the character at the top of the stack
	return s[t];
}

void push(char *s, int *t, char x)
{
	//Pushes a character into the stack
	//First we increase the index of the top
	//Then we assign number
	++*t;
	s[*t]=x;
}

char pop(char *s, int *t)
{
	//Returns the element at the top of the stack 
	//and decreases the index of the top
	//
	//First, the top number is assigned to a 
	//variable. Then we decrement the top index
	//and return the number
	char x;
	x=s[*t];
	--*t;
	return x;
}


