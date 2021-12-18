//Double Ended Queues:
//Very similar to Doubly Linked List
//(main difference is that DLL has only one
//rear pointer but DE Queues have both front
//and rear pointer)

#include <stdlib.h>
#include <stdio.h>


struct node
{
	int key;
	struct node *next, *prev;
};

typedef struct node node_t;

struct dequeue
{
	node_t *front;
	node_t *rear;
};

typedef struct dequeue dequeue_t ;

void qdisplay(dequeue_t *);
void qinsert_head(dequeue_t *, int);
void qinsert_tail(dequeue_t *, int);
int qdelete_head(dequeue_t *);
int qdelete_tail(dequeue_t *);
void init( dequeue_t *p);


int main(void)
{
	int k, x, ch;
	dequeue_t dq; 
	init(&dq);

	for (;;) {
		qdisplay(&dq);

		printf("Enter choice:\n"
		"1. Insert head\n"
		"2. Insert Tail\n"
		"3. Delete Head\n"
		"4. Delete Tail\n"
		"5. Display\n"
		"6. Exit\n\n");

		scanf("%d",&ch);
		switch(ch) {
			case 1:		printf("Enter data:");
				   		scanf(" %d", &x);
				   		qinsert_head(&dq, x);
				   		break;

			case 2:		printf("Enter data:");
				   		scanf(" %d", &x);
				   		qinsert_tail(&dq, x);      
				   		break;

			case 3:		k = qdelete_head(&dq);
				   		if (k >= 0)
				   		    printf("Element deleted = %d\n",k);
						else 
							printf("The queue is already empty!\n");
				   		break;

			case 4:		k = qdelete_tail(&dq);
				   		if (k >= 0)
				   		    printf("Element deleted = %d\n",k);
						else 
							printf("The queue is already empty!\n");
				   		break;

			case 5:		qdisplay(&dq); 
				   		break;

			case 6:		return 0;
		}
	}
}

void init(dequeue_t *p)
{
	p->front = p->rear = NULL;
}

void qdisplay(dequeue_t* p)
{
	node_t *pres = p->front;

	//If the queue is already empty
	if (pres == NULL)
		printf("The queue is empty!\n");
	else {
		//Loop until we reach the end and print 
		//every value
		while(pres != p->rear) {
			printf("%d ", pres->key);
			pres = pres->next;
		}
		printf("%d\n", pres->key);
	}
}

void qinsert_head(dequeue_t *p, int key)
{
	//Initializing new node
	node_t *temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;
	
	//First element
	if (p->front == NULL)
		p->front = p->rear = temp;
	else {
		//All other cases
		temp->next = p->front;
		p->front->prev = temp;
		p->front = temp;
	}
}

int qdelete_head(dequeue_t *p)
{
	int key;
	node_t *pres = p->front;

	//Empty queue case
	if (pres == NULL) 
		return -1;

	key = pres->key;

	//Case with only one node
	if (p->front == p->rear)
		p->front = p->rear = NULL;
	else {
		//All other cases
		pres->next->prev=NULL;
		p->front=pres->next;
	}
	free(pres);
	return key;
}		


void qinsert_tail( dequeue_t *p, int key)
{
	node_t *temp;

	//Initializing new node
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = temp->prev = NULL;	

	//First element insertion
	if(p->front == NULL)
		p->front = p->rear = temp;	
	else {
		//All other cases
		p->rear->next = temp;
		temp->prev = p->rear;
		p->rear = temp;
	}
}

int qdelete_tail(dequeue_t *p)
{
	int key;
	node_t *pres = p->rear;

	//Empty queue case
	if (pres == NULL) 
		return -1;

	//Get the key
	key = pres->key;

	//Only one node case
	if (p->front == p->rear)
		p->front = p->rear = NULL;
	else {
		//All other cases
		pres->prev->next=NULL;
		p->rear=pres->prev;
	}
	free(pres);
	return key;
}

