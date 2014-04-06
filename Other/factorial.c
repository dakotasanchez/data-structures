/* Dakota Sanchez
 * Factorial Calculator (up to 100 input digits, up to 10000 output digits)
*/

#include <stdio.h>
#define NUMELEM(x) (sizeof(x) / sizeof(x[0]))

int enter_num(int *, int *, int, int);
void factorial(int *, int *, int *, int, int, int);
void multiply(int *, int *, int *, int, int);
void add(int *, int *, int);
void decrement_num(int *, int);

int main (void) {

	int num1[100], result[10000], result_copy[10000];

	//Flush result arrays with zeros	
	int i;
	for(i = 0; i < NUMELEM(result); i++) {
		result[i] = 0;
		result_copy[i] = 0;
	}

	//Get factorial to be calculated,
	//copy that integer into result_copy for first multiplication,
	//and return number of multiplication iterations to be performed
	int iterations = enter_num(num1, result_copy, NUMELEM(num1), NUMELEM(result_copy)) - 2;
	
	//Calculate factorial
	factorial(num1, result_copy, result, NUMELEM(num1), NUMELEM(result), iterations);

	printf("\n%i! equals: \n", iterations + 2);

	//Check if entered integer is 2, 1, or 0
	//If not, remove leading zeros from result and print result
	if(iterations + 2 == 2)

		printf("2");

	else if((iterations + 2 == 1) || (iterations + 2 == 0))

		printf("1");

	else {
		int j = 0;
		while(result[j] == 0)
			j++;
		for(j; j < NUMELEM(result); j++) 
			printf("%i", result[j]);
	}
	
	printf("\n\n");	

	return 0;
}

int enter_num(int * num, int * result_copy, int size, int copy_size) {

	int entered_int;
	printf("\nCalculate factorial for integer: ");
	scanf("%i", &entered_int);
	
	int copy = entered_int;

	//Copy integer into array num and array result_copy
	int i;
	int j = copy_size - 1;
	for(i = size - 1;  i >= 0; i--) {
		num[i] = entered_int % 10;
		result_copy[j] = num[i];
		entered_int /= 10;
		j--;
	}

	//Result_copy--
	decrement_num(result_copy, copy_size);

	return copy;
}

void factorial(int * num, int * result_copy, int * result, int num_size, int result_size, int iterations) {

	//For first iteration
	int first = 1;
	
	//For copying result into result_copy
	int k;
	
	while(iterations > 0){

		//Long multiplication
		multiply(num, result_copy, result, num_size, result_size);
		
		//Copy result into result_copy
		for(k = result_size - 1; k >= 0; k--) {
			result_copy[k] = result[k];
		
			//Set result to zero during calculations because result_copy holds result intermediately
			//If wasn't set, leftover integers in result would be added to answer
			if(iterations > 1)
				result[k] = 0;
		}

		//Extra decrement for num on first iteration
		//e.g. for 5!, 5x4 already happened, result holds 20, num gets decremented here and 6 lines below, num holds 3, 3x20, 2x60, etc.
		if(first == 1) {
			decrement_num(num, num_size);
			first--;
		}

		//Decrement factorial
		decrement_num(num, num_size);

		iterations--;
	}
}

void multiply(int * num, int * result_copy, int * result, int num_size, int result_size) {

	//Temp array for adding to result array
	int temp[result_size];

	int carry = 0;	

	// i for num array, j for result_copy array, 
	// num_of_zeros for placing trailing zeros in long multiplication,
	// temp_placer for holding temp array index
	int i, j, num_of_zeros, temp_placer;

	for(i = num_size - 1; i >= 0; i--) {
		
		j = result_size - 1;
		temp_placer = j;
		num_of_zeros = (num_size - 1) - i;
		
		//Multiply until temp array is full
		while(temp_placer >= 0) {
		
			if(num_of_zeros > 0) {
				temp[temp_placer] = 0;
				num_of_zeros--;
				temp_placer--;			
			} else {
		
				//Multiply
				if((num[i] * result_copy[j]) + carry > 9) {
					temp[temp_placer] = ((num[i] * result_copy[j]) % 10) + carry;
					carry = (num[i] * result_copy[j]) / 10;
				} else {
					temp[temp_placer] = (num[i] * result_copy[j]) + carry;
					carry = 0;
				}
		
				j--;
				temp_placer--;
			}
		}
		
		//Add intermediate answer to result
		add(temp, result, result_size);
	}
}


//Add num1 to num2
void add(int * num1, int * num2, int size) {

	int carry = 0;
	int i;
	int j = size - 1;
	for(i = size - 1; i >= 0; i--) {
		if(num2[j] + num1[i] + carry > 9) {
			num2[j] = ((num1[i] + num2[j]) - 10) + carry;
			carry = 1;
		} else {
			num2[j] = num1[i] + num2[j] + carry;
			carry = 0;
		}
		j--;
	}
}

//Decrement number by 1
void decrement_num(int * num, int size) {

	int i = 1;
	while(num[size - i] == 0)
		i++;

	if(i > 1){
		int j;
		for(j = 1; j < i; j++)
			num[size - j] = 9;
		num[size - i]--;
	}else{
		num[size - 1]--;
	}
}
