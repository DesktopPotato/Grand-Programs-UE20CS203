#include <stdio.h>
#include <stdlib.h>
struct node {
	int key;
	struct node *next;

};

typedef struct node node_t;

struct list
{
	node_t *head;	
};

typedef struct list list_t;


void display(list_t *l);
void init_list(list_t **l);
void insert_head(list_t *l, int key);
void insert_tail(list_t *l, int key);
int remove_head(list_t *l);
int remove_tail(list_t *l);
void swap(list_t *l, int x, int y);
void insert_at_position(list_t *l, int key, int pos);
void insert_order(list_t *l, int key);
void reverse(list_t *l);
int delete_at_position(list_t *l, int pos);
int search(list_t *l, int key);
void merge(list_t *l1, list_t *l2, list_t *l3);
void print_recurse(node_t *n);
void destroy(list_t *l);
void reverse(list_t *l);
void delete_alternate(list_t *l);

int main(void)
{
	int CH, key, code, key2;

	list_t *l1, *l2, *l3;

	init_list(&l1);
	init_list(&l2);
	init_list(&l3);

	for (;;) 
	{
		printf("\nEnter code:\n"
			" 1. Display list 1.\n"
			" 2. Display list 2.\n"
			" 3. Insert sorted\n"
			" 4. Insert head\n"
			" 5. Insert tail\n"
			" 6. Remove head\n"
			" 7. Remove tail\n"
			" 8. Swap nodes\n"
			" 9. Search in list\n"
			"10. Merge both lists (REQUIRES BOTH LISTS TO BE SORTED!)\n"
			"11. Reverse list\n"
			"12. Reverse list using recursion\n"
			"13. Print reverse of a list using recursion\n"
			"14. Insert at position i\n"
			"15. Delete at position i\n"
			"16. Display merged list\n"
			"17. Destroy list\n"
			"18. Delete alternate nodes\n"
			"-1. Exit\n"
			"Code: ");
		scanf(" %d", &code);
		printf("\n");

		switch (code)
		{
			case 1: 			display(l1);
								break;

			case 2: 			display(l2);
								break;

			case 3: 			printf("Enter key: ");
								scanf(" %d", &key);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? insert_order(l1, key) : insert_order(l2, key);
								break;

			case 4: 			printf("Enter key: ");
								scanf(" %d", &key);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? insert_head(l1, key) : insert_head(l2, key);
								break;

			case 5: 			printf("Enter key: ");
								scanf(" %d", &key);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? insert_tail(l1, key) : insert_tail(l2, key);
								break;

			case 6: 			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								key = ((code == 1) ? remove_head(l1) : remove_head(l2));
								printf("The removed key was %d\n", key);
								break;

			case 7: 			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								key = ((code == 1) ? remove_tail(l1) : remove_tail(l2));
								printf("The removed key was %d\n", key);
								break;

			case 8: 			printf("Enter first key: ");
								scanf(" %d", &key);
								printf("Enter second key: ");
								scanf(" %d", &key2);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? swap(l1, key, key2) : swap(l2, key, key2);
								break;

			case 9:				printf("Enter key to search: ");
								scanf(" %d", &key);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								key = (code == 1) ? search(l1, key) : search(l2, key);
								key ? printf("The number does exist in the list\n") :printf("The number does not exist in the list\n"); 
								break;

			case 10: 			merge(l1, l2, l3);
								break;

			case 11:			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? reverse(l1): reverse(l2);
								break;

			case 13:			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? print_recurse(l1->head): print_recurse(l2->head);
								break;

			case 14:			printf("Enter key: ");
								scanf(" %d", &key);
								printf("Enter position: ");
								scanf(" %d", &key2);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);

								(code == 1) ? insert_at_position(l1, key, key2) : 
										insert_at_position(l2, key, key2);
								break;

			case 15:			printf("Enter position: ");
								scanf(" %d", &key2);
								printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								key = ((code == 1) ? delete_at_position(l1, key2) : delete_at_position(l2, key2));
								printf("The removed key was %d\n", key);
								break;

			case 16:			display(l3);
								break;

			case 17:			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? destroy(l1): destroy(l2);
								break;

			case 18:			printf("Enter list number (1/2): ");
								scanf(" %d", &code);
								(code == 1) ? delete_alternate(l1): delete_alternate(l2);
								break;

			case -1:			return 0;
								break;

			default:			printf("Invalid code\n");
								break;

		}
	}
}





void display(list_t *l)
{
	//First print the node's value, then move to next node
	for (node_t *pres = l->head; pres != NULL; pres = pres->next)
		printf("%d -> ", pres->key);
	printf("NULL\n\n");
}


void init_list(list_t **l)
{	
	//Allocate memory for the list, and then set the head to NULL
	*l = malloc(sizeof(list_t));
	(*l)->head = NULL;
}


void insert_head(list_t *l, int key)
{
	//Allocate memory for a node
	node_t *temp = malloc(sizeof(node_t));

	//Set node's data to key
	temp->key = key;						
	temp->next = l->head;			//Make temp point to the node being pointed by list's head
	l->head = temp;					//Make list point to the node

}


void insert_tail(list_t *l, int key)
{
	//Allocate memory for the node
	node_t *pres, *temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = NULL;				//The tail is the last node, so set n->next to NULL

	if (l->head == NULL) {			//Empty list condition
		l->head = temp;
	} else {
		//Iterate through the list until the last position is found
		for (pres = l->head; pres->next != NULL; pres = pres->next)
			;
		pres->next = temp;
	}
}


int remove_head(list_t *l)
{
	node_t *pres;
	int key;							//For getting value of the first node

	if (l->head == NULL){				//Case where list is already empty
		printf("The list is empty!\n");
		key = -1;
	}
	else {								//Copy value of head into the key
		pres = l->head;					//Then remove head
		l->head = pres->next;
		key = pres->key;
		free(pres);
	}
	return key;
}

int remove_tail(list_t *l)
{
	int key;
	//Trailing pointer technique: Iterating through the list 
	//using two pointers. The trailing pointer will set the value
	//of the second last node to null
	//The pointer that stays ahead will be freed
	node_t *pres, *prev;

	if (l->head == NULL)								//Empty List condition
		printf("The list is empty!\n");				
	else if (l->head->next == NULL) {					//Only one node
		key = l->head->key;
		free(l->head);
		l->head = NULL;
	}
	else {												//Multiple nodes
		for (pres = l->head; 
			pres->next != NULL; 
			prev = pres, pres = pres->next) 
					;
		prev->next = NULL;
		key = pres->key;
		free(pres);
	}
	return key;
}

void swap(list_t *l, int x, int y)
{
	//Swapping two nodes through their addresses
	node_t *prevx, *prevy, *presx, *presy, *temp;


	//First, make sure that the values that we're looking for
	//exist in the list. If any of them don't, then return from 
	//the function
	for (prevx = NULL, presx = l->head; 
		presx != NULL && presx->key != x; 
		prevx = presx, presx = presx->next)
		;

	if (presx == NULL) {
		printf("Number %d not found!\n", x);
		return;
	
	for (prevy = NULL, presy = l->head; 
		presy != NULL && presy->key != y; 
		prevy = presy, presy = presy->next)
		;

	if (presy == NULL) {
		printf("Number %d not found!\n", y);
		return;
	}

	//First, change the next-nodes being pointed by the pointer 
	//which is at the back. Then change the next-nodes pointed 
	//by the pointers at the front
	if (prevx != NULL)
		prevx->next = presy;
	else 
		l->head = presy;

	if (prevy != NULL)
		prevy->next = presx;
	else
		l->head = presx;

	//Swap the two nodes
	temp = presy->next;
	presy->next = presx->next;
	presx->next = temp;

	}
}

void insert_at_position(list_t *l, int key, int pos)
{
	//Initializing count, and then allocating memory
	//The node's next pointer is initially initialized to NULL
	//It can be changed later, in the case it gets inserted
	//in the middle of the list
	//
	//This method also uses trailing pointers
	//
	int count = 1;
	node_t *temp, *pres, *prev;
	temp = malloc(sizeof(node_t));	//Temp is the node to be added
	temp->key = key;
	temp->next = NULL;

	for (pres = l->head, prev = NULL;				//Counting till we reach the
		pres != NULL && count < pos;				//desired position
		prev = pres, pres = pres->next, count++)
			;

	if (pres != NULL) {				//Position reached
		if (prev == NULL) {
			temp->next = l->head;
			l->head = temp;
		} else {
			temp->next = pres;
			prev->next = temp;
		}
	} else {							
		//Case where the list is either NULL
		if (count == pos)
			if (prev == NULL)			//or has just one node
				l->head = temp;
			else 
				prev->next = temp;
		else								//Position unreachable 
			printf("Invalid position\n");
	}

}

void insert_order(list_t *l, int key)
{
	//Trailing pointer method
	//Assumes that the list is also ordered initially
	//Traverse through the list until you find the key
	//which is greater than the given key
	node_t *temp, *prev, *pres;
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = NULL;

	for (prev = NULL, pres = l->head;
		pres != NULL && pres->key < key;
		prev = pres, pres = pres->next)
			;

	//If you don't find the node (pres reaches NULL),
	//then insert the node right away
	//Otherwise, insert behind pres
	//
	if (prev == NULL) {
		temp->next = l->head;
		l->head = temp;
	} else {
		temp->next = pres;
		prev->next = temp;
	}

}

void reverse(list_t *l)
{
	//Trailing pointers method
	//Uses 3 pointers in total.
	//Set the present node's next pointer to previous, 
	//and then keep incrementing the present to the
	//next pointer
	//After reaching the end (present = NULL), set
	//prev as the head of the list
	node_t *prev, *pres, *next;

	pres = l->head;
	prev = next = NULL;
	while (pres != NULL) {
		next = pres->next;
		pres->next = prev;
		prev = pres;
		pres = next;
	}

	l->head = prev;
}

//WIP
//void recursive_reverse(node_t *n, node_t *tobeassigned)
//{
//}

void print_recurse(node_t *n)
{
	//If n is null (list is empty), then just print NULL
	//Else if n is the last node, then print n pointing towards NULL
	//For all other cases, recursively call the function and then print
	//the value of the current node
	if (n == NULL) 
		printf("NULL\n");
	else if (n->next == NULL)
		printf("NULL <- %d", n->key);
	else {
		print_recurse(n->next);
		printf(" <- %d", n->key);
	}
}

int delete_at_position(list_t *l, int pos)
{
	int count = 1;
	node_t *prev, *pres;
	
	for (prev = NULL, pres = l->head;
		pres != NULL && count < pos;
		prev = pres, pres = pres->next, count++)
			;

	if (pres == NULL) {
		printf("Invalid position\n");
		return -1;
	} else {
		if (prev == NULL) 
			l->head = pres->next;
		else 
			prev->next = pres->next;

	}

	count = pres->key;
	free(pres);
	return count;

}

int search(list_t *l, int key)
{
	//Iterative search.
	//Keep searching through the list unless 
	//1. temp is NULL (key wasn't found in the list)
	//2. Key is found.
	//Then return value accordingly
	//
	node_t *temp;
	for (temp = l->head; temp != NULL && temp->key != key; temp = temp->next)
		;
	return (temp? 1: 0);
}

void merge(list_t *l1, list_t *l2, list_t *l3)
{
	//Merging two sorted lists
	//Take two pointers and assign them each as the heads of l1 and l2
	//While iterating, if the data of the node in first list is smaller than 
	//the data of the node in the second list, then insert the node in the first 
	//list into the third list. Otherwise, insert the node in the second list.
	//Then iterate the pointer accordingly.
	//After either of them get assigned to NULL, insert all the nodes in the list
	//which wasn't finished.
	node_t *first, *second, *third;
	first = l1->head;
	second = l2->head;

	while (first != NULL && second != NULL) {
		if (first->key < second->key) {
			insert_tail(l3, first->key);
			first = first->next;
		} else {
			insert_tail(l3, second->key);
			second = second->next;
		}
	}

	while (first != NULL) {
		insert_tail(l3, first->key);
		first = first->next;
	}
	while (second != NULL) {
		insert_tail(l3, second->key);
		second = second->next;
	}

}

void destroy(list_t *l)
{
	//Trailing pointer technique
	//Use one pointer (named as 'death' here) to free each node. 
	//After freeing, the pointer will become a dangling pointer.
	//So we use another pointer that will remain ahead of the node to be freed. The freeing pointer
	//will be reassigned to this pointer, every iteration
	for (node_t *death = l->head, *ahead; death != NULL; death = ahead){	
		ahead = death->next;
		free(death);
	}
	l->head = NULL;
}



void delete_alternate(list_t *l)
{
	node_t *tempone, *temptwo, *freethis;
	
	//Looking at the non-general cases:
	//If list is empty
	if (l->head == NULL) {
		printf("The list is empty\n");
		return;
	} 
	
	//or if list has only one member
	if (l->head->next == NULL) {
		printf("Your list has only one member\n");
		return;
	}

	//Take two pointers, tempone and temptwo
	//We shall be deleting every second node, to which
	//tempone shall be assigned and then freed
	//First initialize temptwo to be the first node
	//and then tempone to be the next node
	//free the node in every iteration
	for (temptwo = l->head, tempone = temptwo->next; 
		tempone != NULL; 
		free(freethis)) 
	{
		//freethis is the pointer used for freeing
		freethis = tempone;
		//Increment tempone to go to the next node
		tempone = tempone->next;


		//Now, if we've reached the end of the list
		if (tempone == NULL) {
			//Make temptwo's next pointer NULL,
			//since that node will get freed.
			temptwo->next = NULL;
			free(freethis);
			//Return from the function to break
			//the loop
			return;
		}

		//If we haven't reached the end of the list
		//make temptwo's next point to tempone's current 
		//node
		temptwo->next = tempone;
		//Now, assign tempone to temptwo
		temptwo = tempone;
		//Now make tempone the node next to temptwo
		tempone = tempone->next;
		//Let the loop repeat
	}

}
