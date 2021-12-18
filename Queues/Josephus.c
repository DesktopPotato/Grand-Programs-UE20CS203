//Josephus problem.
//Uses array implementation of circular queue


#include <stdio.h>
#include <stdlib.h>


struct queue
{
	int *cq;
	int f, r, size;
};

typedef struct queue queue_t;


void init(queue_t *);
int qinsert(queue_t *ptr_q, int key);
int qdelete(queue_t *);
void display(queue_t *);
int qisempty(queue_t *);			


int main()
{
	int ch, k, n, p[100], i, step;
	queue_t q;
	init(&q);
	printf("Enter the number of persons: ");
	scanf(" %d", &n);
	printf("Enter step size: ");
	scanf(" %d", &step);

	//Insert the numbers into the queue
	for (i = 1; i <= n; i++)
		qinsert(&q, i);


	//Until the queue is empty, delete step number of people
	//and insert them back into the queue
	//Then permanently delete one element from the queue
	//After the queue is empty, display the number which
	//survived
	while (!qisempty(&q)) {
		display(&q);

		
		for (int i = 0; i < step - 1; i++) {
			k = qdelete(&q);
			qinsert(&q, k);
		}

		k = qdelete(&q);
	}

	printf("The survivor is %d\n", k);
}



int qisempty(queue_t *ptr_q)
{
	//Returns 1 if empty
	return (ptr_q->f == -1);
}

int qinsert(queue_t *ptr_q, int key)
{
	//Case where queue is full
	if ((ptr_q->r + 1) % ptr_q->size == ptr_q->f) {
		printf("ERR: Queue size too small!\n");
		return -1;
	} 

	//Increment rear index
	ptr_q->r = (ptr_q->r+1) % ptr_q->size;
	//Assign number to rear index
	ptr_q->cq[ptr_q->r] = key;

	//If first insertion, increment front index
	if (ptr_q->f == -1)
		ptr_q->f = 0;

	//Successful insert
	return 1;
}

int qdelete(queue_t *ptr_q)
{
	int x, key;

	//Empty queue case:
	if (ptr_q->f == -1) {
		return -1;
	}

	//Get key
	key = ptr_q->cq[ptr_q->f];
	//Last element case:
	if (ptr_q->f == ptr_q->r)
		ptr_q->f = ptr_q->r = -1;
	else
		//All other cases
		ptr_q->f = (ptr_q->f + 1) % ptr_q->size;
	return key;

}



void init(queue_t *ptr_q)
{
	//Initializing
	printf("Enter size for the queue: ");
	scanf(" %d", &ptr_q->size);
	ptr_q->f = ptr_q->r = -1;
	//Contents of queue:
	ptr_q->cq = malloc(sizeof(int[ptr_q->size]));
}	

void display(queue_t *ptr_q)
{
	int f, r, size;
	
	//Empty queue case
	if (ptr_q->f == -1) {
		printf("ERR: The queue is empty!\n");
		return;
	}

	f = ptr_q->f;
	r = ptr_q->r;

	//Loop and print until front pointer reaches rear
	//pointer
	while (f != r) {
		printf("%d ", ptr_q->cq[f]);
		f = (f + 1) % ptr_q->size;
	}

	//Loop stops at last element. Print the last element
	//separately:
	printf("%d\n", ptr_q->cq[f]);
}		 
