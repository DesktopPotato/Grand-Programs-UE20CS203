//program to implement Linear probling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct element will have 3 variables:
//A key (for the identification)
//A string associated with the key
//And a mark boolean (for marking as 
//available or unavailable)
struct element
{
	int key;
	char name[100];
	int mark;
};

typedef struct element element_t;

void display(element_t *, int);
void insert_to_hash(element_t *, int, int, char *, int *);
void delete_from_hash(element_t *, int, int, int *);
void search_in_hash(element_t *, int, int, int);

int main(void)
{
	element_t *hashtable;
	int i, n, ch, key, count;
	char name[100];

	int tablesize;
	printf("Enter the size for the hash table: ");
	scanf(" %d", &tablesize);

	//create hash table
	hashtable = malloc(sizeof(element_t[tablesize]));
	//Initializing hash table
	for (i = 0; i < tablesize; i++)
		hashtable[i].mark = 0;

	count = 0;

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
						printf("Enter name for this key: ");
						scanf(" %s",name);
						insert_to_hash(hashtable, tablesize, key, name, &count);
						break;

			case 2: 	printf("Enter key for deletion:");
						scanf(" %d", &key);
						delete_from_hash(hashtable, tablesize, key, &count);
						break;

			case 3: 	printf("Enter the key to search in the table:");
						scanf(" %d", &key);
						search_in_hash(hashtable, tablesize, key, count);
						break;

			case 4: 	display(hashtable, tablesize);
						break;

			case -1:	return 0;

		}
	}

}

void display(element_t *ht, int size)
{
	//Display all non empty keys:
	for (int i = 0; i < size; i++) {
		printf("Index %d:", i);
		if (ht[i].mark != 0)
			printf("\nKey: %d\nName: %s\n", ht[i].key, ht[i].name);
		printf("\n");
	}
}

void search_in_hash(element_t *ht, int size, int key, int count)
{
	int index, i = 0;

	//Empty table case
	if (count == 0) {
		printf("The table is empty!\n");
		return;
	}

	index = key % size;			//hash function

	while (i < count) {
		if (ht[index].mark == 1) {						//If a key is assigned to this index
			if (ht[index].key == key) {                  //Checking if the key in the index matches
				printf("Key found\n"
					"Key: %d\nName: %s\n\n",
					ht[index].key, ht[index].name);
				return;
			}
			i++;							//Key wasn't found, increment count
		}			
		index = (index+1) % size;			//Check at the next index
	}
	printf("The key that you searched does not exist\n");
}


void delete_from_hash(element_t* ht, int size, int key,int *count)
{
	//i is a counting variable
	int index, i = 0;
	//If there are no elements
	if (*count == 0) {
		printf("The table is already empty!\n");
		return;
	}

	index = key % size;			//hash function

	//Deletion part:
	//If the key exists in it's respective index,
	//delete it. Otherwise, increment your counting
	//and index variable and check again
	//This is similar to searching
	
	while (i < *count) {
		if (ht[index].mark == 1) {			//If a key is assigned to this index
			if(ht[index].key == key) {		//Checking if the key in the index matches
				ht[index].mark=0;			//Assign the index to be available 
				*count--;					//Decrement count
				return;
			}
			i++;							//Key wasn't found, increment count
		}			
		index = (index+1) % size;			//check at the next index
	}

	//Breaking out of the loop means key wasn't found
	printf("The key that you wish to delete was not found\n");
};


void insert_to_hash(element_t* ht, int size, int key, char *name, int *count)
{

	int index;

	//Checking full table condition
	if (size == *count) {
		printf("The table is already full!\n");
		return;
	}

	index = key % size;			//hash function

	//If the index that we want to assign
	//is already occupied, insert the key
	//into the next available index
	while (ht[index].mark != 0)
		index = (index+1) % size;

	//This part is why the method is called 
	//"Linear Probing"

	//Assiging the key to the hash table
	ht[index].key = key;
	strcpy(ht[index].name, name);
	//Mark the index as occupied
	ht[index].mark = 1;

	//Increment the count number
	(*count)++;

	return;
}

