//PROGRAM TO EVALUATE A GIVEN POSTFIX EXPRESSION
//INPUT IS OF THE FORM (eg. ABC*+ )
//
//Algorithm:
//If scanned symbol is an operand, push it into
//the stack
//If the scanned symbol is an operator, pop
//the last two elements of the stack and then
//evaluate the result of the operation
//After evaluating the result of the previous
//operation, push it back into the stack

#include <stdio.h>



void push(int *, int *, int);
int pop(int *, int *);
int isoper(char);
int postfix_eval(char *);



int main(void)
{
	char postfix[100];
	printf("Enter a valid postfix expression\n");
	scanf(" %s", postfix);
	int result = postfix_eval(postfix);
	printf("The result is %d\n", result);

}

int postfix_eval(char *expr)
{
	//Stack;
	int s[100];

	//Variables for operand 1, operand 2, 
	//r (result) for pushing into stack,
	//and x for setting values of characters
	//in the string
	int op1, op2, r, x;

	//Stack's top element index
	int top = -1;


	//Character variable for identification of 
	//operator or operand
	char ch;


	//Scanning the string
	for (int i = 0; expr[i]!='\0'; i++) {

		ch = expr[i];

		//If the character is an operator, pop
		//2 elements from the stack and perform
		//the corresponding operation on the 
		//two operands
		if (isoper(ch)) {
			op1=pop(s,&top);
			op2=pop(s,&top);
			switch(ch) {
				case '+':	r = op1 + op2;
						  	push(s, &top, r);
						  	break;

				case '-': 	r = op2 - op1;
						  	push(s, &top, r);
						  	break;

				case '*': 	r = op1 * op2;
						  	push(s, &top, r);
						  	break;

				case'/' :	r = op2 / op1;
						 	push(s, &top, r);
						 	break;

			} 
		} else {
			//If the character is an operand, 
			//ask the value of the character to
			//the user, and store it in the stack
			printf("Enter the value for %c: ",ch);
			scanf(" %d",&x);
			push(s, &top, x);
		}
	}


	//After scanning through the string, return the
	//only 1 remaining element in the stack
	//This is the result of the expression
	return(pop(s,&top));
}	   




void push(int *s,int *t,int x)
{
	//Pushes a character into the stack
	//First we increase the index of the top
	//Then we assign number
	++*t;						
	s[*t]=x;
}

int pop(int *s, int *t)
{
	//Returns the element at the top of the stack 
	//and decreases the index of the top
	//
	//First, the top number is assigned to a 
	//variable. Then we decrement the top index
	//and return the number
	int x;
	x=s[*t];
	--*t;
	return x;
}

int isoper(char ch)
{
	//Returns true if ch is an operator
	if (ch == '+' || ch=='-' || ch=='*' || ch=='/')
		return 1;
	return 0;
}






