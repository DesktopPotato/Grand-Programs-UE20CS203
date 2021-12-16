//Doubly Linked List
//
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *next;
	struct node *prev;
};

typedef struct node node_t;

struct dlist
{
	node_t* head;
};

typedef struct dlist dlist_t;

void init_list(dlist_t **);						
void insert_head(dlist_t *, int);
void display(dlist_t *);
void insert_tail(dlist_t *, int);
void remove_head(dlist_t *);
void delete_last(dlist_t  *);
void delete_node(dlist_t *, int);
void delete_pos(dlist_t *, int);
void insert_pos(dlist_t *, int, int);
void delete_all(dlist_t *ptr_list, int key);


//Client part
int main(void)
{
	int ch, key, pos;
	dlist_t *l;
	init_list(&l);

	for (;;)
	{
		printf("The list is currently: ");
		display(l);
		printf("Choose one of the following options:\n"
			" 1. Insert_head\n"
			" 2. Insert_tail\n"
			" 3. Display\n"
			" 4. delete first node\n"
			" 5. Delete Last Node\n"
			" 6. Delete a node given value\n"
			" 7. Delete at a position\n"
			" 8. Insert at a Given Position\n"
			"-1. Exit\n"
			"Enter choice: ");
		scanf("%d",&ch);

		switch(ch) {
			case 1:		printf("Enter the key: ");
						scanf(" %d", &key);
						insert_head(l, key);
						break;

			case 2:		printf("Enter the key: ");
						scanf(" %d", &key);
						insert_tail(l, key);
						break;
			
			case 3:		display(l);
						break;
			
			case 4:		remove_head(l);
						break;

			case 5:		delete_last(l);
						break;
			
			case 6:		printf("Enter the key: ");
						scanf(" %d", &key);
						delete_node(l, key);
						break;
			
			case 7:		printf("Enter the position: ");
						scanf(" %d", &pos);
						delete_pos(l, pos);
						break;
			
			case 8:		printf("Enter the key and position: ");
						scanf(" %d %d", &key, &pos);
						insert_pos(l, key, pos);
						break;
			
			case -1:	return 0;
						break;

			default: 	printf("Invalid operation\n");
						break;
		}
	}
}


void init_list(dlist_t **ptr_list)
{
	//Creating a structure to contain a list
	//Pointer to the list pointer is used to change
	//the value of the list pointer itself
	*ptr_list = malloc(sizeof(dlist_t));	
	(*ptr_list)->head=NULL;
}

void delete_node(dlist_t *ptr_list, int key)
{
	node_t *pres;

	//Move forward until the key is found
	//or if you go beyond the last node
	for (pres = ptr_list->head; 
		pres!=NULL && pres->key!=key; 
		pres = pres->next)
		;

	if (pres!=NULL) {							//key found

		//Case with only one node
		if(pres->next == NULL && pres->prev == NULL)
			ptr_list->head = NULL;

		else if(pres->prev == NULL){			//First node
			pres->next->prev = NULL;
			ptr_list->head=pres->next;
		}

		else if(pres->next == NULL)				//Last node
			pres->prev->next = NULL;

		else {									//Middle node
			pres->prev->next = pres->next;
			pres->next->prev = pres->prev;
		}

		free(pres);							//Freeing the allocated memory 
											//for the node
	} 
	else									//Node wasn't found	
		printf("Node not found");
}	


void insert_pos(dlist_t *ptr_list, int key, int pos)
{
	node_t *temp, *pres;
	int i = 1;						//Keeping track of position

	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	pres = ptr_list->head;

	//Incrementing the position index until we reach our
	//desired position. If we cannot reach the required position
	//then display that the position is invalid and free the 
	//allocated memory
	while (i < pos && pres->next != NULL) {
		i++;
		pres=pres->next;
	}

	if (i == pos) {							//Position found

		if (pres->prev == NULL) {			//First position
			pres->prev=temp;
			temp->next=pres;
			ptr_list->head=temp;
		} else {							//Middle position
			pres->prev->next=temp;
			temp->prev=pres->prev;
			temp->next=pres;
			pres->prev=temp;
		}
	} else if (i == pos-1) {				//Insert at end
		pres->next=temp;
		temp->prev=pres;
	} else {								
		//Given position is beyond last node
		//Hence, position is invalid
		
		printf("Not a valid position!");
		free(temp);							//Freeing the allocated memory

		//If the memory is not freed, it will result in memory leak
	}
}


void delete_pos(dlist_t *ptr_list, int pos)
{
	node_t *pres;
	int i = 1;		//Counter for keeping track of position

	pres = ptr_list->head;

	//Move forward until the position is found
	//Or you go beyond the last node

	while(pres != NULL && i<pos) {
		i++;
		pres=pres->next;
	}

	//position found
	if (pres != NULL) {

		//Case where only one node is present:
		if(pres->next == NULL && pres->prev == NULL)
			ptr_list->head=NULL;
		
		//There are these cases:
		//First node
		else if(pres->prev==NULL)	{
			pres->next->prev=NULL;
			ptr_list->head=pres->next;

		} else if(pres->next==NULL)			//Last node
			pres->prev->next=NULL;

		else {								//Middle node
			pres->prev->next=pres->next;
			pres->next->prev=pres->prev;
		}
		//Free the node that was found
		free(pres);
	} 
	else //The node was not found (position out of bounds)
		printf("Node not found");
}		  


void delete_last(dlist_t *ptr_list)
{
	node_t *pres;

	pres = ptr_list->head;
	
	//If list is empty
	if (pres == NULL) {
		printf("The list is already empty!\n");
		return;
	}

	//If only one node
	if (pres->next == NULL)
		ptr_list->head = NULL;
	else
	{ 
		//Go to last node.
		//Loop: If pres is not the last node, keep
		//going to the next node
		while (pres->next! = NULL)
			pres = pres->next;

		//After reaching the last node, make the node
		//behind point to NULL
		pres->prev->next = NULL;
	}
	//Finally, free the node
	free(pres);
}		


void remove_head(dlist_t *ptr_list)
{
	node_t *pres = ptr_list->head;

	//Case:
	//Only one node
	//Then make list's head point to NULL
	if (pres->next == NULL)
		ptr_list->head = NULL;
	else {							
		//Any other no of nodes
		//Make head point to the next node
		pres->next->prev = NULL;
		ptr_list->head = pres->next;
	}
	free(pres);						
}


void insert_head(dlist_t *ptr_list, int key)
{
	node_t *temp;
	
	//Initializing new node
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	//If the list is empty, make head point to new node
	if (ptr_list->head == NULL)
		ptr_list->head = temp;
	else {
		//If the list is not empty, make new node point to the
		//next node in the list and then make head point
		//to the new node
		temp->next = ptr_list->head;
		ptr_list->head->prev = temp;
		ptr_list->head = temp;
	}
}

void display(dlist_t *ptr_list)
{
	//Iterate through the list until we reach the end
	for (node_t *pres = ptr_list->head; pres!=NULL; pres=pres->next)
		printf("%d<=>",pres->key);
	//Then print the NULL value
	printf("NULL\n");
}

void insert_tail(dlist_t *ptr_list, int key)
{
	node_t *temp, *pres;
	//Initializing new node
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	//Empty list condition
	if(ptr_list->head==NULL)
		ptr_list->head=temp;	
	else {
		//Go to the last node
		pres = ptr_list->head;
		while (pres->next != NULL)
			pres=pres->next;
		//Keep looping until we reach the last node
		//After reaching last node, make last node point
		//to the new one and make the new node's prev pointer
		//point to the last node
		pres->next=temp;
		temp->prev=pres;
	}
}






