#include <stdio.h>

//Theory behind towers of hanoi:
//Recursion is used to divide one large problem
//into smaller subproblems, and then find the solution and
//aggregate them up
//Here, we divide our large problem (of moving n disks)
//by dividing each movement into smaller movements (of n-1
//disks) across a source, temporary and destination poles

void hanoi(int, char, char, char);

int main(void)
{	
	int n;
	printf("Enter the number of disks: ");
	scanf(" %d", &n);

	hanoi(n, 'A', 'B', 'C');

}

void hanoi(int n, char s, char t, char d) 
{
	if (n == 1) {			//only one disk
		printf("Move disk %d from %c to %c\n", n, s, d);
		return;
	}			

	hanoi(n-1, s, d, t);			//Moves n-1 disks from source to temporary
	printf("Move disk %d from %c to %c\n", n, s, d);
	hanoi(n-1, t, s, d);			//Move those n-1 disks from temporary to destination


}
