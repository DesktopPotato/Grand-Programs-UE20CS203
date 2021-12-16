#include <stdlib.h>
#include <stdio.h>

struct queue
{
	int *item;
	int f;					//Front index
	int r;					//Rear index
	int size;
};


typedef struct queue queue_t;

void init(queue_t *);
int qinsert(queue_t *,int);
int qdelete(queue_t *);
void display(queue_t *);


int main(void)
{
	queue_t *q = malloc(sizeof(queue_t));
	int ch, k, x;
	init(q);
	for (;;) {
		display(q);
		printf("1. Insert\n"
			"2. Delete\n"
			"3. Display\n"
			"4. Exit\n\n");
		scanf(" %d",&ch);

		switch(ch) {
			case 1:		printf("Enter key:");
				   		scanf(" %d", &x);
				   		k = qinsert(q, x);
				   		if (k >= 0)
				   		    printf("Element inserted successfully\n");
				   		break;

			case 2:		k = qdelete(q);
				   		if (k >= 0)
				   		    printf("Element deleted = %d\n",k);
				   		break;

			case 3:		display(q);
				   		break;

			case 4:		return 0; 
		}
	}
}


void init(queue_t *ptr_q)
{
	printf("Enter the max size of the queue:");
	scanf("%d", &ptr_q->size);

	ptr_q->item = malloc(sizeof(int[ptr_q->size]));

	//The indices are initialized to -1.
	ptr_q->f = -1;					
	ptr_q->r = -1;
}

int qinsert(queue_t *ptr_q, int key)
{
	//Check for queue overflow
	//Return -1 if insert fails

	if(ptr_q->r == ptr_q->size - 1) {
		printf("The queue is full!\n");
		return -1;
	}

	ptr_q->r++;						//increment rear
	ptr_q->item[ptr_q->r]=key;

	if(ptr_q->f==-1)				//if first element
		ptr_q->f=0;					//Increment front
}

int qdelete(queue_t *ptr_q)
{
	int key;		
	//The next element in the queue is pointed to by 
	//f pointer

	//If the queue is empty, return -1
	//
	if(ptr_q->f == -1) {
		printf("The queue is emptty!\n");
		return -1;
	}
	key = ptr_q->item[ptr_q->f];

	//If there's only one element remaining in the queue
	//Reset the two pointers
	//Otherwise, increment front
	if(ptr_q->f == ptr_q->r) 
		ptr_q->f=ptr_q->r=-1;
	else
		ptr_q->f++; //increment front
	return key;
}

void display(queue_t *ptr_q)
{
	int i;
	if(ptr_q->f == -1){
		printf("The queue is empty\n");
		return;
	}
	//Print contents from front to rear indices
	for (i = ptr_q->f; i <= ptr_q->r; i++)
		printf("%d  ",ptr_q->item[i]);
	printf("\n");
	
}

