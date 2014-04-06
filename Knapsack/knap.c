/*
Dakota Sanchez
3 MARCH 2014
This program solves the 0/1 knapsack problem. It computes 
the maximum possible value for a knapsack given weight-value 
pairs from knapsack.data and a maximum weight capacity.
*/

#include <stdio.h>
#include <stdlib.h>

struct item {
	int weight;
	int value;
	char name[32];
};

// number of items
int ITEMS_SIZE;
// items from file
struct item ITEMS[128];
// saved for dynamic computing
int SAVED[1024];
int LARGEST;

int getFileItems();
int maximum(int);

int main(int argc, char *argv[]) {
	// knapsack weight capacity
	int capacity;
	// check for > 1 arguments or non-integer
	if(argc != 2 || (sscanf(argv[1], "%i", &capacity) != 1)) {
		printf("Error: knap expects one integer argument\n");
		exit(1);
	}

	// initialize array for saving maximums
	int i;
	for(i = 0; i < 1024; i++) {
		SAVED[i] = -1;
	}

	// get file items
	ITEMS_SIZE = getFileItems();

	LARGEST = 0;
	// get maximum value
	int max = maximum(capacity);
	printf("\nMaximum value for capacity of %i = %i\n", capacity, max);

	return 0;
}

int getFileItems() {
	FILE *fp;
	fp = fopen("knapsack.data", "r");

	// throw error if fail to open file
	if(fp == NULL) {
		printf("Error: failure to open file\n");
		exit(1);
	}

	int i = 0;
	while(1) {
		fscanf(fp, "%i %i %s", &ITEMS[i].weight, &ITEMS[i].value, ITEMS[i].name);
		// check for end of file
		char c = fgetc(fp);
		if(c == EOF)
			break;
		// echo file for user
		printf("%i %i %s\n", ITEMS[i].weight, ITEMS[i].value, ITEMS[i].name);
		i++;
	}

	fclose(fp);
	// return number of items in array
	return i;
}

// returns maximum value for knapsack with given capacity and items
int maximum(int weight) {
	if(weight <= 0)
		return 0;

	int i, value;
	for (i = 0; i < ITEMS_SIZE; i++) {
		// for re-use
		int diff = weight - ITEMS[i].weight;
		if(diff >= 0) {
			// save maximum() result if not already saved, then use it below
			if(SAVED[diff] == -1)
				SAVED[diff] = maximum(diff);
			value = ITEMS[i].value + SAVED[diff];
		}
		if(value > LARGEST)
			LARGEST = value;
	}
	return LARGEST;
}
