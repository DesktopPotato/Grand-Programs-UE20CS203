//Program to implement priority queue
//Uses Array Implementation
//This technique focuses on sorted insertion
//for easy deletion

#include <stdio.h>
#include <stdlib.h>


struct element
{
	int pty;
	int data;
};


typedef struct element element_t;
void pqinsert(element_t *, int, int , int*);
element_t pqdelete(element_t*, int*);
void qdisplay(element_t*, int);


int main(void)
{
	int k, ch, pty, x;

	//Initializing array of structures as our queue
	//Temp structure to access data in a dequeued element
	element_t pq[100], temp;

	//Count variable to keep track of number of items in queue
	int count = 0;


	for (;;) {
		qdisplay(pq,count);
		printf(" 1. Insert\n"
			" 2. Remove\n"
			" 3. Display\n"
			"-1. Exit\n\n");
		scanf(" %d", &ch);

		switch(ch) {
			case 1:		printf("Enter priority for the element:");
				   		scanf(" %d", &pty);
				   		printf("Enter the value:");
				   		scanf(" %d", &x);
				   		pqinsert(pq, x, pty, &count);
				   		break;

			case 2:		temp = pqdelete(pq, &count);

				   		if (temp.data == -1) {
							printf("The queue is empty!\n");
						} else 
				   		    printf("Dequeued Element:\n"
									"Priority:%d\n"
									"Data:%d\n", temp.data, temp.pty);
				   		break;

			case -1:	return 0; 
		}
	}
}


void pqinsert(element_t *pq, int data, int pty, int *count)
{
	//Sorted Insertion takes place.
	//Sorting occurs according to priority
	
	//Variable j for getting priority of existing
	//elements and to reorder elements 
	//according to priority
	int j;

	element_t temp;
	temp.data = data;
	temp.pty = pty;

	j = *count - 1;

	//While the element at index j has higher priority number
	//(less priority than the element to be inserted)
	//reorder the existing element to be at a higher index
	//
	while(j >= 0 && pq[j].pty > temp.pty) {
		//Moves j'th element to the j+1'th index
		pq[j+1] = pq[j];
		j--;
	}

	//Loop exits on finding an element with lower priority number
	//(higher priority)
	//Hence, we need to insert our temp element ahead of that index
	//or insert at j+1th index
	pq[j+1] = temp;

	//Increase count
	(*count)++;
}

void qdisplay(element_t *pq, int count)
{
	//If the queue is empty
	if (count == 0) {
		printf("The queue is empty\n");
		return;
	}
	//Looping through the queue
	for (int i = 0; i < count; i++)
		printf("Priority: %3d | Data: %5d\n", pq[i].pty, pq[i].data);

	printf("\n");
}

element_t pqdelete(element_t *pq, int *count)
{
	int i;
	element_t temp;

	//If the queue is empty
	if (*count == 0) {
		temp.data = -1;
		temp.pty = -1;
	} else {
		//Read the value at the first index
		temp = pq[0];
		
		//Reorder subsequent elements
		for (i = 1; i < *count; i++)
			pq[i-1] = pq[i];

		//Decrement count
		(*count)--;
	}


	return temp;
}




