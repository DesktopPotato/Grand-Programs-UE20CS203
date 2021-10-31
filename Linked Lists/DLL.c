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
						scanf(" %d",&key);
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
						scanf(" %d" , &pos);
						delete_pos(l, pos);
						break;
			
			case 8:		printf("Enter the key and position: ");
						scanf(" %d %d" , &key, &pos);
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
	*ptr_list = malloc(sizeof(dlist_t));	
	(*ptr_list)->head=NULL;
}

void delete_node(dlist_t *ptr_list, int key)
{
	node_t *pres;

	//Move forward until the key is found
	//or if you go beyond the last node
	//
	for (pres = ptr_list->head; 
		pres!=NULL && pres->key!=key; 
		pres = pres->next)
		;

	if (pres!=NULL)								//key found
	{
		//Case with only one node
		if(pres->next == NULL && pres->prev == NULL)
			ptr_list->head = NULL;
		else if(pres->prev == NULL)				//First node
		{
			pres->next->prev = NULL;
			ptr_list->head=pres->next;
		}
		else if(pres->next == NULL)				//Last node
			pres->prev->next = NULL;
		else									//Middle node
		{
			pres->prev->next = pres->next;
			pres->next->prev = pres->prev;
		}
		free(pres);
	} 
	else									//Node wasn't found	
		printf("Node not found");
}	


void insert_pos(dlist_t *ptr_list, int key, int pos)
{
	node_t *temp,*pres;
	int i;
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	pres = ptr_list->head;
	i = 1;
	while(i<pos && pres->next != NULL)
	{
		i++;
		pres=pres->next;
	}
	if(i==pos)							//position found
	{
		if(pres->prev==NULL)			//first position
		{
			pres->prev=temp;
			temp->next=pres;
			ptr_list->head=temp;
		}
		else							//middle position
		{
			pres->prev->next=temp;
			temp->prev=pres->prev;
			temp->next=pres;
			pres->prev=temp;
		}
	}
	else if  (i==pos-1)					//insert at end
	{ 
		pres->next=temp;
		temp->prev=pres;
	}
	else
		printf("not valid position..");
}


void delete_pos(dlist_t *ptr_list, int pos)
{
	node_t *pres;
	int i;

	pres=ptr_list->head;

	//move forward until the positionis found
	//or you go beyond the last node
	i=1;

	while((pres!=NULL)&&(i<pos))
	{
		i++;
		pres=pres->next;
	}

	if(pres!=NULL)//position found
	{
		//where ?
		//if only one node
		if((pres->next==NULL)&&(pres->prev==NULL))
			ptr_list->head=NULL;
		else if(pres->prev==NULL)//first node
		{
			pres->next->prev=NULL;
			ptr_list->head=pres->next;
		}
		else if(pres->next==NULL)//last node
			pres->prev->next=NULL;
		else//middle node
		{
			pres->prev->next=pres->next;
			pres->next->prev=pres->prev;
		}
		free(pres);
	} 
	else //pres=NULL
		printf("Node not found");
}		  


void delete_last(dlist_t *ptr_list)
{
	node_t *pres;

	pres = ptr_list->head;

	//if only one node
	if(pres->next == NULL)
		ptr_list->head = NULL;
	else
	{ 
		//go to last node
		while(pres->next! = NULL)
			pres = pres->next;

		pres->prev->next = NULL;
	}
	free(pres);
}		


void remove_head(dlist_t *ptr_list)
{

	node_t* pres;

	pres = ptr_list->head;

	if(pres->next == NULL)////only one node
		ptr_list->head = NULL;
	else
	{
		pres->next->prev = NULL;
		ptr_list->head = pres->next;
	}
	free(pres);
}


void insert_head(dlist_t *ptr_list, int key)
{
	node_t *temp;

	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	//Empty list
	if(ptr_list->head == NULL)
		ptr_list->head = temp;
	else		
	{
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
	node_t *temp,*pres;

	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;

	//Empty list condition
	if(ptr_list->head==NULL)
		ptr_list->head=temp;	
	else
	{
		//Go to the last node
		pres=ptr_list->head;
		while(pres->next!=NULL)
			pres=pres->next;
		pres->next=temp;
		temp->prev=pres;
	}
}






