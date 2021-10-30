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
void destroy(list_t *l);
void reverse(list_t *l);

int main(void)
{
	int key, code, key2;

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
			"-1. Exit\n"
			"Code: ");
		scanf(" %d", &code);

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

			case -1:			return 0;
								break;

			default:			printf("Invalid code\n");
								break;

		}
	}
}





void display(list_t *l)
{
	for (node_t *pres = l->head; pres != NULL; pres = pres->next)
		printf("%d -> ", pres->key);
	printf("NULL\n\n");
}


void init_list(list_t **l)
{	
	*l = malloc(sizeof(list_t));
	(*l)->head = NULL;
}


void insert_head(list_t *l, int key)
{
	node_t *temp = malloc(sizeof(node_t));

	temp->key = key;						
	temp->next = l->head;
	l->head = temp;

}


void insert_tail(list_t *l, int key)
{
	node_t *pres, *temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = NULL;


	if (l->head == NULL) {
		l->head = temp;
	} else {
		for (pres = l->head; pres->next != NULL; pres = pres->next)
			;
		pres->next = temp;
	}
}


int remove_head(list_t *l)
{
	node_t *pres;
	int key;

	if (l->head == NULL)
		printf("The list is empty!\n");
	else {
		pres = l->head;
		l->head = pres->next;
		key = pres->key;
		free(pres);
	}
	return key;
}

int remove_tail(list_t *l)
{
	int key;
	node_t *pres, *prev;

	if (l->head == NULL)								//Empty List
		printf("The list is empty!\n");				
	else if (l->head->next == NULL) {						//Only one node
		key = l->head->key;
		free(l->head);
		l->head = NULL;
	}
	else {
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
	node_t *prevx, *prevy, *presx, *presy, *temp;



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

	if (x == y)
		return;


	if (prevx != NULL)
		prevx->next = presy;
	else 
		l->head = presy;

	if (prevy != NULL)
		prevy->next = presx;
	else
		l->head = presx;

	temp = presy->next;
	presy->next = presx->next;
	presx->next = temp;

	}
}

void insert_at_position(list_t *l, int key, int pos)
{
	int count = 1;
	node_t *temp, *pres, *prev;
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = NULL;

	for (pres = l->head, prev = NULL;
		pres != NULL && count < pos;
		prev = pres, pres = pres->next, count++)
			;

	if (pres != NULL) {
		if (prev == NULL) {
			temp->next = l->head;
			l->head = temp;
		} else {
			temp->next = pres;
			prev->next = temp;
		}
	} else {

		if (count == pos)
			if (prev == NULL)
				l->head = temp;
			else 
				prev->next = temp;
		else 
			printf("Invalid position\n");
	}

}

void insert_order(list_t *l, int key)
{
	node_t *temp, *prev, *pres;
	temp = malloc(sizeof(node_t));
	temp->key = key;
	temp->next = NULL;

	for (prev = NULL, pres = l->head;
		pres != NULL && pres->key < key;
		prev = pres, pres = pres->next)
			;

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
