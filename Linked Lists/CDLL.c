#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *prev;
	struct node *next;
};

typedef struct node node_t;

struct list
{
	node_t *last;
};

typedef struct list list_t;




void init(list_t *l);
void insert_head(list_t *l, int key);
void insert_rear(list_t *l, int key);
void display(list_t *l);
int delete_head(list_t *l);
int delete_rear(list_t *l);





int main(void)
{
	int key, code;
	list_t *l = malloc(sizeof(list_t));
	init(l);
	
	for (;;) {
		printf("Enter choice:\n"
				"1. Insert head\n"
				"2. Insert at rear\n"
				"3. Delete from head\n"
				"4. Delete from rear\n"
				"5. Display\n"
				"-1. Exit\n"
				"Code: ");
		scanf(" %d", &code);

		switch (code) {
			case 1:		printf("Type a number to insert: ");
						scanf(" %d", &key);
						insert_head(l, key);
						break;

			case 2:		printf("Type a number to insert: "); 
						scanf(" %d", &key);
						insert_rear(l, key);	
		                break;
						
			case 3:		key = delete_head(l);
						if (key == -1) 
							printf("The list is already empty!\n");
						else 
							printf("The deleted element was %d\n", key);
            			break;
                                    
            case 4:		key = delete_rear(l);	
						if (key == -1) 
							printf("The list is already empty!\n");
						else 
							printf("The deleted element was %d\n", key);
						break;

			case 5:		display(l);
						break;

			case -1:	return 0;

			default:	printf("Invalid code!\n");

		}                                                          
	}                   
}



void init(list_t *l)
{
	//Initialize list to point to NULL
	l->last = NULL;
}


void insert_head(list_t *l, int key)
{
	node_t *newnode = malloc(sizeof(node_t));
	newnode->data = key;
	newnode->next = newnode->prev = newnode;

	//Case where the list is empty
	if (l->last == NULL) {
		l->last = newnode;
		return;
	}
	

	//All other cases
	l->last->next->prev = newnode;
	newnode->next = l->last->next;
	newnode->prev = l->last;
	l->last->next = newnode;
}

void insert_rear(list_t *l, int key)
{
	node_t *newnode = malloc(sizeof(node_t));
	newnode->data = key;
	newnode->next = newnode->prev = newnode;

	//Case where the list is empty
	if (l->last == NULL) {
		l->last = newnode;
		return;
	}
	

	//All other cases
	l->last->next->prev = newnode;
	newnode->next = l->last->next;
	newnode->prev = l->last;
	l->last->next = newnode;
	//Only difference between front insertion
	//and rear insertion is the line below:
	l->last = newnode;
}

void display(list_t *l)
{
	node_t *temp = l->last;
	
	//Case where list is empty
	if (temp == NULL) {
		printf("The list is empty!\n");
		return;
	}

	//Initializing temp to move to first node
	temp = temp->next;

	//Printing every element except last one
	while (temp != l->last) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}

	//Printing the last element
	printf("%d\n", temp->data);
}


int delete_head(list_t *l)
{
	node_t *temp = l->last;
	int data;

	//Case where list is already empty
	if (l->last == NULL) 
		return -1;
	
	//Getting the first node's data
	temp = l->last->next;
	data = temp->data;

	//Case with only one node
	if (l->last == l->last->next) {
		free(temp);
		l->last = NULL;
		return data;
	}
	
	//All other cases:
	l->last->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
	return data;

}

int delete_rear(list_t *l)
{
	node_t *temp = l->last;
	int data;

	//Case where list is already empty
	if (l->last == NULL) 
		return -1;
	
	//Getting the last node's data
	temp = l->last;
	data = temp->data;

	//Case with only one node
	if (l->last == l->last->next) {
		free(temp);
		l->last = NULL;
		return data;
	}
	
	//All other cases:
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	l->last = temp->prev;
	return data;

}









