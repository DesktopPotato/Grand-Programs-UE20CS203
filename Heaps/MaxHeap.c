#include <stdio.h>
#include <stdlib.h>

//Heaps are 1) Complete binary trees (only rightmost children could be
//missing) and 2) Increasing or decreasing order from parent to children
//
//
//If in an array, x is the last index, then floor of (x-1)/2
//will give the the index of it's parent node 
//For finding left child of a given element at location j
//is 2j + 1
//Right child: 2j+2
//
//
//Converting a complete tree into a heap:
//1) Bottom up algo:
//	Take the last parent node and convert the subtree formed by it 
//	and it's children into a heap.
//	Similarly convert the other subtrees by moving left and moving up
//	Continue until the entire tree is a heap
//	- Converting a subtree into a heap: 
//		Check which node is greater among the children
//		Compare the value with the parent
//		Switch the parent if the value of the child is greater


void bot_heap(int *h, int n);			//n is the index of the last element
int max_delete(int *h, int *n);
void heapify(int *h, int n);

int main(void) 
{
	int h[100];						//heap
	int i, n;

	printf("Enter the no of elements: ");
	scanf(" %d", &n);

	//Putting elements into the array
	printf("Enter numbers: ");
	for (int i = 0; i < n; i++)
		scanf(" %d", &h[i]);		

	bot_heap(h, n-1);
	

	//Displaying the heap
	for (int i = 0; i < n; i++)
		printf(" %d", h[i]);

	printf("\n\n");

	i = max_delete(h, &n);

	printf("The element at the top is: %d\n", i);

	//Displaying the heap
	for (int i = 0; i < n; i++)
		printf(" %d", h[i]);

}


void bot_heap(int *h, int n)			//n is the index of the last element
{
	//Variable i for child nod
	//j k and j for parent node
	//key for the value in the
	//parent node
	int i, j, key, k;

	//For loop traverses through all 
	//parent nodes, starting from
	//the last parent node
	for (k = (n-1)/2; k >= 0; k--) {
		j = k;
		key = h[j];

		i = 2*j + 1;					//Get the left child
		while (i <= n) {				//Until the left child exists
			if (i + 1 <= n) 			//Checking if the right child exists
				if (h[i+1] > h[i])		//Finding the largest child
					i++;
			
			if (key < h[i]){			//Compare the key with the largest child
				h[j] = h[i];			//Move child up						    
				j = i;
				i = 2*j + 1;
			} else 
				break;
		}
		h[j] = key;
	}
}


int max_delete(int *h, int *n)
{
	//Deleting the top element of the heap
	//and returning it:
	//After deletion, we'll have to bring the next-largest
	//element up and reform the heap
	int key;
	key = h[0];
	h[0] = h[*n-1];
	--(*n);
	heapify(h, *n-1);
	return key;
}


void heapify(int *h, int n)
{
	//Variable i for child, j for parent,
	//k for parent, and key for the data 
	//in the parent node
	

	int j = 0, key = h[j], i = 2*j+1;

	//Until the left child exists
	while (i <= n) {
		if (i + 1 <= n)					//Checking if the right child exists
			if (h[i+1] > h[i])          //Finding the largest child
				i++;                                                            
                                                                                
		if (key < h[i]) {               //Compare the key with the largest child
			h[j] = h[i];                //Move child up						    
			j = i;
			i = 2*j + 1;
		} else
			break;
	}
	h[j] = key;						//Inserting the initial parent's
									//key in it's place


}
