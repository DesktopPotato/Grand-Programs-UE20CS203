//Application of Stack:
//
//Code to check if parenthesis match each other
//
//Theory: Whenenver we encounter a forward brace or '(', we push
//it into the stack. Whenever we encounter a back brace or ')', we
//pop an element from the stack.
//For a perfectly matched case, the stack would be empty by the end
//of the string and there should not be any errors in the middle (such
//as popping when the stack is already empty, or having a non-empty
//stack by the end of the string).
//Also, do not use spaces while typing the string as scanf
//will stop at the space



#include <stdio.h>




void push(char *, int *, char);
char pop(char *s, int *);
int isempty(int);
int match(char *);

int main(void)
{
	char expr[10];
	printf("Enter the expression: ");
	scanf(" %s", expr);

	if (match(expr))
		printf("Matching correct\n");
	else
		printf("Matching incorrect\n");

	return 0;
}




int match(char *expr)
{
	
	//Stack variable top initialized to -1
	int i, top = -1;
	//Array used for stack's contents
	char s[100];

	//Two characters used for traversing the string
	//and popping from the stack respectively
	char ch, x;
	

	// Three conditions for failure:
	// 1) Mismatch of parenthesis
	// 2) Extra closing parenthesis
	// 3) Non Empty stack at the end of the string
	 

	//For loop will traverse through the string
	for (i = 0; expr[i] != '\0'; i++) {
		ch = expr[i];
		switch (ch) {

			//If we encouter an opening parenthesis, 
			//we push into the stack
			case '(': case '{': case '[': 
							push(s, &top, ch);
							break;


			//If we encounter closing parenthesis,
			//we pop from the stack
			//Before popping, we make sure that the stack
			//is not empty, because our pop function
			//doesn't handle stack underflow case here
			//If the stack is empty, then matching is 
			//incorrect. Otherwise, pop from the stack.
			//After popping, if the brace doesn't match,
			//then the matching is incorrect
			//Otherwise, continue to the next character

			case ')': 		if (!isempty(top)){
								x = pop(s, &top);
								if (x != '(')
									return 0; 				//Mismatch of parenthesis
								break;
							} else 
								return 0; 					//Extra closing parenthesis condition

			case '}': 		if (!isempty(top)){
								x = pop(s, &top);
								if (x != '{')
									return 0; 				//Mismatch of parenthesis
								break;
							} else 
								return 0; 					//Extra closing parenthesis condition

			case ']': 		if (!isempty(top)){
								x = pop(s, &top);
								if (x != '[')
									return 0; 				//Mismatch of parenthesis
								break;
							} else 
								return 0; 					//Extra closing parenthesis condition



		}

	}
	
	//After traversing through the string, we see if the
	//stack is empty
	if (isempty(top))
		return 1;
	return 0;
}

void push(char *s, int *t, char c)
{
	//First increment the index, then assign the character to
	//the array's index
	++*t;
	s[*t] = c;
}

char pop(char *s, int *t)
{
	char x;
	//First grab the character from the array,
	//and then decrease the index
	x = s[*t];
	--*t;
	//Finally, return the number
	return x;
}

int isempty(int top)
{
	//Check if the index is -1
	if (top == -1)
		return 1;
	return 0;
}
