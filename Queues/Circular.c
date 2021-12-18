//Array implementation of a circular queue

#include <stdlib.h>
#include <stdio.h>

struct queue
{
	int *cq;
	int f, r, size;
};

typedef struct queue queue_t;

void init(queue_t *);
int qinsert(queue_t *, int);
int qdelete(queue_t *);
void display(queue_t *);



int main(void)
{
	int ch, k, x;
	queue_t q;
	init(&q);

	for (;;) {
		display(&q);

		printf("Enter code:\n"
			" 1. Insert\n"
			" 2. Delete\n"
			" 3. Display\n"
			"-1. EXIT\n");
		scanf(" %d", &ch);

		switch (ch) {
			case 1:		printf("Enter the value: ");
				   		scanf(" %d", &x);
				   		k = qinsert(&q, x);
				   		if (k == -1)
							printf("The queue is full!\n");
						else 
							printf("Element inserted successfully\n");
				   		break;

			case 2:		k = qdelete(&q);
				   		if (k >= 0)
				   		    printf("element deleted = %d\n", k);
				   		break;

			case 3:		display(&q);
				   		break;

			case -1:	return (0); 
		}
	}
}


void init(queue_t *ptr_q)
{
	//Initializing the queue
	//First get size of array from the user
	printf("Enter size for the queue: ");
	scanf(" %d", &ptr_q->size);
	//Front and rear indices are initialized to -1
	ptr_q->f = ptr_q->r = -1;
	//Array for the queue
	ptr_q->cq = malloc(sizeof(int[ptr_q->size]));
}	

int qinsert(queue_t *ptr_q, int key)
{
	//Returns integer based on if successful
	//Returns -1 on unsuccessful insert
	//Otherwise returns 1
	
	
	//If the queue is already full
	if ((ptr_q->r + 1) % ptr_q->size == ptr_q->f) {
		return -1;
	}

	//increment rear in a cyclical fashion
	ptr_q->r = (ptr_q->r + 1) % ptr_q->size; 
	ptr_q->cq[ptr_q->r] = key;			//Insert the element

	//if the element being inserted is the first element
	if (ptr_q->f == -1) 
		ptr_q->f = 0;

	//Successful insert: return 0
	return 0;
}

int qdelete(queue_t *ptr_q)
{
	int key;
	
	//Check if the queue is already empty:
	if (ptr_q->f == -1) 
		return -1;
	
	//Getting the element at the front
	key = ptr_q->cq[ptr_q->f];

	//only one element
	if (ptr_q->f == ptr_q->r)
		ptr_q->f = ptr_q->r = -1;
	else
		//Increment front in a cyclical fashion
		ptr_q->f = (ptr_q->f + 1) % ptr_q->size;

	//Return the key
	return key;
}

void display(queue_t* ptr_q)
{
	int f = ptr_q->f;
	if (ptr_q->f == -1) {
		printf("The queue is empty\n");
		return ;
	}

	//Print all elements except last element
	
	while (f != ptr_q->r){
		printf("%d ", ptr_q->cq[f]);
		f = (f + 1) % ptr_q->size;
	}
	
	//Print the last element
	printf("%d\n", ptr_q->cq[f]);
}		 
