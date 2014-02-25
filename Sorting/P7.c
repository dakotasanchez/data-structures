/*
Dakota Sanchez
2-23-14
Program 7
Demonstrates the use of insertion sort and 
merge sort on an array of 32 random integers
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 32

int myRand(int *);
void insertionSort(int *);
void mergeSort(int *, int);
void merge(int *, int, int *, int *);
void print(int *);

int main() {
	//initialize and randomize
	int nums[SIZE];
	myRand(nums);

	//insertion sort
	printf("Before insertion sort:\n");
	print(nums);
	insertionSort(nums);
	printf("After insertion sort:\n");
	print(nums);
	printf("\n");

	//merge sort
	myRand(nums);	//randomize again
	printf("Before merge sort:\n");
	print(nums);
	mergeSort(nums, SIZE);
	printf("After merge sort:\n");
	print(nums);
	printf("\n");

	return 0;
}

//randomize an array
int myRand(int *numbers) {
	int i, tmp, i1, i2;
	for(i = 0; i < SIZE; i++) {
		numbers[i] = i + 1;		//numbers = 1,2,3....SIZE
	}

	//shuffle
	for(i = 0; i < 1000; i++) {
		i1 = rand() % SIZE;
		i2 = rand() % SIZE;
		tmp = numbers[i1];
		numbers[i1]=numbers[i2];
		numbers[i2] = tmp;
	}
}

//insert numbers into progressively larger sorted partition of nums[]
void insertionSort(int *nums) {
	int i, j, tmp;
	for(i = 0; i < SIZE; i++) {
		tmp = nums[i];
		j = i - 1;
		while(j >= 0 && nums[j] > tmp) {
			nums[j + 1] = nums[j];
			j--;
		}
		nums[j + 1] = tmp;
	}
}

//split nums[] in half, merge them in order
void mergeSort(int * nums, int length) {
	if(length >= 2) {
		int middle = length/2;
		int left[middle];
		int right[length - middle];
		int i;
		for(i = 0; i < middle; i++) {
			left[i] = nums[i];
		}
		for(i = 0; i < (length - middle); i++) {
			right[i] = nums[i + middle];
		}
		mergeSort(left, middle);
		mergeSort(right, length - middle);
		merge(nums, length, left, right);
	}
}

//sort sub arrays into target array by comparing one at a time
//if one sub array is empty, obviously grab integers from the other
void merge(int *result, int length, int *left, int *right) {
	int i1 = 0;
	int i2 = 0;
	int i;
	for(i = 0; i < length; i++) {
		if(i2 >= (length - length/2) || (i1 < (length/2) && left[i1] <= right[i2])) {
			result[i] = left[i1];
			i1++;
		} else {
			result[i] = right[i2];
			i2++;
		}
	}
}

void print(int *nums) {
	int i;
	for(i = 0; i < SIZE; i++) {
		printf("%i ", nums[i]);
	}
	printf("\n");
}