#include <stdio.h>
#include <stdlib.h>


//Two types of nodes:
//1) Row node
//2) Column node

struct col_node {
	int col;
	int data;
	struct col_node *next_col;
};

typedef struct col_node colnode_t;

struct row_node {
	int row;
	struct col_node *next_col;
	struct row_node *next_row;
};

typedef struct row_node rownode_t;


rownode_t *create_rows(int);
void insert_end(rownode_t *, int, int);
void insert_matrix(rownode_t *, int(*)[], int, int);
void display(rownode_t *);


int main(void)
{
	//The matrix itself
	int a[10][10];

	//Loop variables, and number of rows
	//and columns
	int i, j, row, col;

	//First row
	rownode_t *head, *p;
	head = NULL;


	printf("Enter the rows and the columns:");
	scanf(" %d %d", &row, &col);


	printf("Enter data for the matrix:\n");


	for (i = 0; i< row; i++) {
		for (j = 0; j < col; j++)
			scanf(" %d", &a[i][j]);
	}

	//Storing the matrix as a multilist
	head = create_rows(row);
	insert_matrix(head, a, row, col);


	//displaying the matrix as a list

	display(head);
}

void display(rownode_t *p)
{

	
	colnode_t *q;
	
	//While rownode pointer isn't NULL
	//Print each column node for each row
	while (p != NULL) {

		printf("Row %d: ", p->row);
		q = p->next_col;

		//While the colnode pointer isn't NULL
		//iterate through the columns and print
		//each value
		
		while (q != NULL) {
			printf("(%d, %d) -> ", q->col, q->data);
			q = q->next_col;
		}

		printf("NULL\n");
		p = p->next_row;
	}
}	

void insert_matrix(rownode_t *head, int a[][10], int r, int c)
{
	//Iterates through each row to find out about
	//columns with non-zero values
	//
	//If such a column is found, insert a colnode
	//with the column number
	//
	//Insertion of colnodes insert a node at the rear
	//
	//Variables i and j for iterating through row 
	//and column
	int i, j;
	rownode_t *p = head;

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++)			//Checking every column
			if (a[i][j] != 0)			//If the column is non-zero
				insert_end(p, a[i][j], j);
		p = p->next_row;				//Increment row number
	}
}	 

void insert_end(rownode_t *p, int key, int col)
{
	//Standard rear insertion
	//node temp for new node, pres for
	//iterating through the already present
	//nodes (during insertion)
	colnode_t *temp, *pres;

	temp = malloc(sizeof(colnode_t));
	temp->col = col;
	temp->data = key;
	temp->next_col = NULL;

	//first element in that row
	if (p->next_col == NULL)		
		p->next_col = temp;
	else {
		pres = p->next_col;
		//move to last node
		while (pres->next_col != NULL)
			pres = pres->next_col;

		pres->next_col = temp;
	}
}

rownode_t *create_rows(int r)
{
	rownode_t *p,*q;
	rownode_t *temp;

	//p is variable for first row insertion
	//q is for connecting the subsequent rows 
	p = NULL;
	q = NULL;


	//Create r number of row nodes
	for (int i = 0; i < r; i++) {
		temp = malloc(sizeof(rownode_t));
		temp->row = i;
		temp->next_row = NULL;
		temp->next_col = NULL;

		//First row insertion
		if (p == NULL) {
			p = temp;
			q = temp;
		} else {	
			//Insertion of subsequent rows
			q->next_row = temp;
			//Increment q
			q = temp;
		}
	}

	//Return the address of the first row node
	return p;
}












