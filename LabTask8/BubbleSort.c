//----------------------------------------------------------------------------------
// Zishi Wu
// November 06, 2015
// BubbleSort.c
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_SIZE 5  

//------------------------------------------------------------------------------------
/* initialize two arrays, one that stores random numbers and 
 * another array that points to these random numbers
 */
typedef int *IntPointer;
typedef int IntArray[ARRAY_SIZE];
typedef IntPointer IntPointerArray[ARRAY_SIZE];

void intialize ( IntArray array, IntPointerArray pointerArray ) {

  // initialize array of integers
	srand(getpid());
	int index;
	for ( index = 0; index < ARRAY_SIZE; index++ ) {
		array[index] = rand();
		// printf("%d\n", array[index]);
	}
	
	// initialize array of int pointers
	for ( index = 0; index < ARRAY_SIZE; index++ ) {
	  pointerArray[index] = &(array[index]);
	}
}
//------------------------------------------------------------------------------------
/* print random numbers from an int array 
 */
void printArray( IntArray array ) {
	int index;
	for ( index = 0; index < ARRAY_SIZE; index++ ) {
		printf("%d: %d\n", index, array[index]);
	}
}
//------------------------------------------------------------------------------------
/* print random numbers from an array of int pointers to said random numbers
 */
void printPointerArray( IntPointerArray pointerArray ) {
	int index;
	for ( index = 0; index < ARRAY_SIZE; index++ ) {
		printf("%d: %d\n", index, *(pointerArray[index]) );
	}
}
//------------------------------------------------------------------------------------
/* use bubble sort to make pointers in an int array point to integer values
 * in order. For example, if an int[] a = {3, 5, 2} then bubbleSort would
 * make pointerArray[0] point to 2 = a[2], pointerArray[1] point to 3 = int[0],
 * and pointerArray[2] point to 5 = int[1]
 */
void bubbleSortPointerArray( IntPointerArray pointerArray ) {
	int i, numSwaps;
	bool keepSwapping = 1;
	IntPointer temp;

	while (keepSwapping) {
		numSwaps = 0;
		for ( i = 0; i < (ARRAY_SIZE-1); i++ ) {
			if ( *(*(pointerArray + i)) > *(*(pointerArray + i + 1)) ) {
				temp = *(pointerArray + i);
				*(pointerArray + i) = *(pointerArray + i + 1);
				*(pointerArray + i + 1) = temp;
				numSwaps++;
			}
		}
		if (numSwaps == 0) {
			keepSwapping = 0;
		}
	}
}
//------------------------------------------------------------------------------------
/* use bubble sort to sort values in an int array. For example, if 
 * int[] a = {3, 5, 2} then bubbleSort would rearrange 
 * int[] a = {2, 3, 5} after many inefficient steps though...
 */
void bubbleSortArray( IntArray array ) {
	int i, numSwaps;
	bool keepSwapping = 1;
	int temp;

	while (keepSwapping) {
		numSwaps = 0;
		for ( i = 0; i < (ARRAY_SIZE-1); i++ ) {
			if ( *(array + i) > *(array + i + 1) ) {
				temp = *(array + i);
				*(array + i) = *(array + i + 1);
				*(array + i + 1) = temp;
				numSwaps++;
			}
		}
		if (numSwaps == 0) {
			keepSwapping = 0;
		}
	}
}
//------------------------------------------------------------------------------------
int main(void) {
	
	IntArray array;
	IntPointerArray pointerArray;
		
	intialize(array, pointerArray);

	printf("Initialized Array of Integers:\n");
	printArray(array);
	
	printf("Sorted Array of Pointers:\n");
	bubbleSortPointerArray(pointerArray);
	printPointerArray(pointerArray);
	
	printf("Sorted Array of Integers:\n");
	bubbleSortArray(array);
	printArray(array);
	
	printf("Array of Pointers:\n");	
	printPointerArray(pointerArray);
		
  return(EXIT_SUCCESS);
}
//------------------------------------------------------------------------------------
