//Circular Linked Lists
//
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	struct node *link;
};

typedef struct node node_t;

struct list
{
	node_t *last;
	//last points to the last node in the list
	//We can thus access the first node by executing last->link
};




typedef struct list clist_t;

void init_list(clist_t *);
void insert_front(clist_t *, int);
void insert_end(clist_t *, int);
void delete_node(clist_t *, int);
void display(clist_t *);




int main(void)
{
	int ch, key, pos;
	

	clist_t l;
	init_list(&l);


	for (;;) {
		display(&l);

		printf("1. Insert_head\n"
		"2. Insert tail\n"
		"3. Display\n"
		"4. Delete a node\n"
		"5. Exit\n\n");


		scanf("%d", &ch);

		switch(ch) {
			case 1:		printf("Enter the key: ");
				   		scanf(" %d", &key);
				   		insert_front(&l, key);
				   		break;

			case 2:		printf("Enter the key: ");
				   		scanf(" %d", &key);
				   		insert_end(&l, key);
				   		break;			 

			case 3:		display(&l);
				   		break;

			case 4:		printf("Enter the key: ");
				   		scanf(" %d", &key);
				   		delete_node(&l, key);	
				   		break;	

			case 5:		return 0;
		}
	}
}



void init_list(clist_t *ptr_list)
{
	//Initialize last to NULL
	ptr_list->last = NULL;
}

void insert_front(clist_t *ptr_list, int key)
{
	node_t *temp, *last;

	//Initialize new node
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->link = temp;

	last = ptr_list->last;

	//If the list is empty:
	//Make list's last pointer point to new node
	//Otherwise, make new node point to first node 
	//by temp->link = last->link and then make last
	//point to new node
	if (last == NULL)
		ptr_list->last = temp;
	else {
		temp->link = last->link;
		last->link = temp;
	}
}


void insert_end(clist_t *ptr_list, int key)
{
	node_t *temp, *last;

	//Initialize new node
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->link = temp;

	last = ptr_list->last;

	//If the list is empty:
	//Make list's last pointer point to new node
	//Otherwise, make new node point to first node 
	//by temp->link = last->link and then make last
	//point to new node
	if (last == NULL)
		ptr_list->last = temp;
	else {
		temp->link = last->link;
		last->link = temp;
		//The function is identical to insert_front
		//except this one line below:
		//This line assigns the new node to the
		//'last' pointer
		ptr_list->last = temp;
	}
}

void display(clist_t *ptr_list)
{
	node_t *last, *pres;

	last = ptr_list->last;


	//If the list is empty
	if (last == NULL)
		printf("The list is empty!\n");


	else {
		//List isn't empty
		//here, we start from the first node
		//and then keep iterating until 
		//we reach the last node

		for (pres = last->link; 
				pres != last; 
				pres = pres->link) 
			printf("%d -> ", pres->key);
			

		//After reaching the last node, print it's value
		printf("%d\n\n", pres->key);
	}
}		

void delete_node(clist_t *ptr_list, int key)
{

	//Uses trailing pointer
	node_t *last, *pres, *prev;

	last = ptr_list->last;

	//If the list is empty:
	if (last == NULL) {
		printf("The list is already empty!\n");
		return;
	}

	//Initializing other pointers
	prev = last;
	pres = last->link;


	//Iterating through the list until either the key is
	//found or we reach the last node (which means key
	//wasn't found)
	while (pres->key != key && pres != last) {
		prev = pres;
		pres = pres->link;
	}

	//If key was found
	if (pres->key == key) {

		//Case: Only one node
		//Then make last pointer point to NULL
		if(pres->link == pres)
			ptr_list->last = NULL;
		else {
			//Otherwise, make prev pointer point to
			//the node next to pres
			prev->link = pres->link;


			//If the node to be removed is the last node
			//Then make last pointer point to prev
			if (pres == last)
				ptr_list->last = prev;
		}
		
		//Finally, free the pres node
		free(pres);
	}
	else		
		printf("The key was not found in the list.\n");
}



