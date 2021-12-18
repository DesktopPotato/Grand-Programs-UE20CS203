//Hashing using Separate Chaining
//Hash Function Used: Division Method 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node_t is the same as your 
//linked list node
struct node
{
	int key;
	char name[100];
	struct node *next;
};

typedef struct node node_t;

//hash struct is your linked list container
//structure
struct hash
{
	node_t *head;
	int count;
};

typedef struct hash hash_t;

void display(hash_t *, int);
void insert_to_hash(hash_t *, int, int, char *);
void delete_from_hash(hash_t *, int, int);
void search_in_hash(hash_t *ht, int size, int key);

int main(void)
{
	hash_t *hashtable;
	int i, n, ch, key;
	char name[100];
	int tablesize;
	printf("Enter the table size: ");
	scanf("%d", &tablesize);
	//create hash table
	hashtable = malloc(sizeof(hash_t[tablesize]));

	//Initializing hash table
	for (i = 0; i < tablesize; i++) {
		hashtable[i].head = NULL;
		hashtable[i].count = 0;
	}

	//Main loop
	for (;;) {
		printf(" 1. Insert\n"
			" 2. Delete\n"
			" 3. Search\n"
			" 4. Display\n"
			"-1. Exit\n\n");

		scanf("%d",&ch);
		switch(ch) {
			case 1:		printf("Enter key: ");
						scanf(" %d",&key);
						printf("Enter name (no spaces): ");
						scanf(" %s",name);
						insert_to_hash(hashtable, tablesize, key, name);
						break;

			case 2: 	printf("Enter key for deletion: ");
						scanf(" %d",&key);
						delete_from_hash(hashtable, tablesize, key);
						break;

			case 3: 	printf("Enter key for seaching: ");
						scanf(" %d",&key);
						search_in_hash(hashtable, tablesize, key);
						break;

			case 4: 	display(hashtable, tablesize);
						break;

			case -1:	return 0;

			default:	printf("Invalid Code\n");
						break;
		}
	}
}


void insert_to_hash(hash_t *ht, int size, int key, char*name)
{
	int index;

	//Creating and initializing a new node 
	node_t *temp = malloc(sizeof(node_t));
	temp->key = key;
	strcpy(temp->name, name);
	temp->next = NULL;

	//hash function
	index = key % size;

	//Standard front insertion
	temp->next = ht[index].head;
	ht[index].head=temp;

	//Increment count for the node's index
	ht[index].count++;
}

void delete_from_hash(hash_t *ht, int size, int key)
{

	//Deletion of a node in a linked list
	//using trailing pointer
	node_t *prev, *temp;

	//hash function
	int index = key % size; 

	//Intialize prev to NULL
	prev = NULL;

	//Initialize temp to the first node
	temp = ht[index].head;

	//Traverse through the list until temp is NULL
	//or until key is found
	while (temp != NULL && temp->key != key) {
		prev=temp;
		temp=temp->next;
	}

	//key found 
	if (temp != NULL){
		if(prev==NULL)
			ht[index].head=temp->next;		//first node
		else
			prev->next=temp->next;			//All other cases
		free(temp);
	} else									//Key not found
		printf("The key was not found in the table\n");
}




void display(hash_t* ht, int size)
{
	int i;
	node_t *temp;
	printf("\n");
	//Traverse through the array of struct hashs
	//And also print lists associated with
	//each index
	for (i = 0; i < size; i++) {
		printf("Index %d: ", i);
		if (ht[i].head != NULL) {
			temp = ht[i].head;
			while (temp != NULL) {
				printf("(%d, %s) -> ", temp->key, temp->name);
				temp = temp->next;
			}
		}
		printf("NULL\n");
	}
}


void search_in_hash(hash_t *ht, int sz, int key)
{

	int index = key % sz;
	node_t *temp = ht[index].head;

	//Traverse through the list to find if 
	//a node exists for the given key
	while (temp != NULL && temp->key != key)
		temp = temp->next;

	//Key found
	if (temp != NULL) {
		printf("The given key exists in the table\n"
				"Details:\n"
				"Key: %d\n"
				"Name: %s\n", temp->key, temp->name);     
	} 
	else			//Key not found
		printf("The given key was not found in the table\n");
}













