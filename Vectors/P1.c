/*Dakota Sanchez
*10 Jan 2014
*Simple structs representing vectors example
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector {
	double x;
	double y;
	double z;
} vector;

int getNumVectors();
void setVectorValues(vector *, int);
void print(vector *, int);
void flushArray(char *, int);
double length(vector);
void clearstdin();

int main(void) {
	//pointer to a block of memory holding vectors
	vector *vectorArray;
	//number of vectors in that block
	int numVectors;	

	numVectors = getNumVectors();

	vectorArray = malloc(numVectors*sizeof(vector));
	
	setVectorValues(vectorArray, numVectors);

	print(vectorArray, numVectors);	

	return 0;
}

//get number of vectors to be entered
int getNumVectors() {

	printf("Please enter the number of vectors you want to enter(>=1) : ");

	int numVectors;
	while((scanf("%i", &numVectors)) != 1) {
		printf("Must be a number, try again: ");
		clearstdin();
	}
	//flush stdin
	clearstdin();

	return numVectors;
}

//get x y and z components of each vector
void setVectorValues(vector *vectorArray, int numVectors) {

	//hold user input
	char inputBuffer[100];

	int i = 0;
	while(i < numVectors) {
		printf("For vector %i input x y and z (separated by spaces): ", i + 1);
		fgets(inputBuffer, 100, stdin);
		int result = sscanf(inputBuffer, "%lf %lf %lf", &vectorArray[i].x, &vectorArray[i].y, &vectorArray[i].z);
		//redo loop if user doesn't enter 3 valid numbers
		if(result != 3) {
			printf("Must be 3 numbers, try again...\n");
			continue;
		} 
		i++;
	}
}

void print(vector *vectorArray, int numVectors) {

	//access each vector in the "array" and print its contents as well as computed length
	printf("\nVectors entered:\n");
	int i;
	for(i = 0; i < numVectors; i++) {
		printf("\nVector %i: x = %.1lf, y = %.1lf, z = %.1lf\n", i + 1, vectorArray[i].x, vectorArray[i].y, vectorArray[i].z);
		printf("\tVector %i length = %lf\n", i + 1, length(vectorArray[i]));
	}
}

//compute length
double length(vector vec) {
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

//flush stdin
void clearstdin() {
	int ch;
	while((ch = getchar()) != EOF && ch != '\n') {}
}

