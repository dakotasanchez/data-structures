/*
Dakota Sanchez
7 FEB 2014
CSE 222, Prog Assgn. 5
This program has an array to represent a stack, and one to represent a queue.
To interact with the structures you can switch between them, pop integers off,
and push integers onto them.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10 //default array size

int getInput(char *, int *);
void processInput(int, char, int);
void push(int);
int pop();
void print();
void help();

//globals
char state;
int stack[MAX];
int TOS;	//Top of Stack
int queue[MAX];
int HEAD;	//Head of Queue
int TAIL;	//Tail of Queue

int main(void) {
	//default value = stack
	state = 's';
	//default array 'pointers'
	TOS = 0;
	HEAD = 0;
	TAIL = 0;

	//initialize arrays 
	int i;
	for(i = 0; i < MAX; i++) {
		stack[i] = -1;
		queue[i] = -1;
	}

	//user input variables
	char inputChar = 0;
	int inputNum = 0;

	//greeting
	printf("\n----------Stack and Queue example program----------\n");
	printf("-----------------(Enter ? for help)----------------\n");

	//main program loop
	while(1) {
		int result = getInput(&inputChar, &inputNum);

		processInput(result, inputChar, inputNum);
	}

	return 0;
}

//get user input
int getInput(char *inputChar, int *inputNum) {
	char buffer[100];
	int result;

	while(1){
		//clear values
		*inputChar = 0;
		*inputNum = 0;
		//see if user inputs extra data
		char extraChar;
		
		printf(">");
		fgets(buffer, 100, stdin);
		//get first value in buffer
		sscanf(buffer, "%c", inputChar);

		//starts with a number
		if(isdigit(*inputChar)) {
			result = sscanf(buffer, "%i %c", inputNum, &extraChar);
			if(result != 1) {
				printf("Invalid input - Enter ? if you need help\n");
				continue;
			} else {
				//user entered a number
				return 1;
			}
		//starts with char
		} else {
			result = sscanf(buffer, "%c %c", inputChar, &extraChar);
			if(result != 1) {
				printf("Invalid input - Enter ? if you need help\n");
				continue;
			} else {
				//user entered a letter
				return 0;
			}
		}
	}
}

void processInput(int result, char inputChar, int inputNum) {
	if(result == 1) {
		push(inputNum);
	} else {
		int popped;

		switch(inputChar) {
			case 'Q':
				printf("Program terminating\n");
				exit(0);
			case 'q':
				//queue mode
				state = inputChar;
				print();
				break;
			case 's':
				//stack mode
				state = inputChar;
				print();
				break;
			case 'p':
				popped = pop();
				if(popped != -1)
					printf("%i\n", popped);
				break;
			case '?':
				help();
				break;
			default:
				printf("Invalid input - Enter ? if you need help\n");
		}
	}
}

void push(int num) {
	//if stack mode
	if(state == 's') {
		//if TOS == MAX, stack is full
		if(TOS != MAX)
			stack[TOS++] = num;
		else
			printf("STACK OVERFLOW\n");
	} else {
		//if tail + 1 == head then the queue is full
		if(((TAIL + 1) % MAX) == (HEAD % MAX))
			printf("QUEUE OVERFLOW\n");
		else {
			queue[TAIL++ % MAX] = num;
		}
	}
}

int pop() {
	//if stack mode
	if(state == 's') {
		//if TOS is 0, stack is empty
		if(TOS != 0) {
			return stack[--TOS];
		} else {
			printf("STACK UNDERFLOW\n");
			return -1;
		}
	} else {
		//if they're already equal, queue is empty
		if(HEAD == TAIL) {
			printf("QUEUE UNDERFLOW\n");
			return -1;
		} else {
			return queue[HEAD++ % MAX];
		}
	}
}

void print() {
	int i;
	if(state == 's') {
		printf("Stack mode\n");
		for(i = 0; i < TOS; i++) {
			printf("%i ", stack[i]);
		}
		printf("<--TOS");
	} else {
		printf("Queue mode\nHEAD--> ");
		//check to see if it's wrapped around
		if((TAIL % MAX) < (HEAD % MAX)) {
			for(i = (HEAD % MAX); i < MAX; i++) {
				printf("%i ", queue[i]);
			}
			for(i = 0; i < (TAIL % MAX); i++) {
				printf("%i ", queue[i]);
			}
		//else print normally
		} else {
			for(i = (HEAD % MAX); i < (TAIL % MAX); i++) {
				printf("%i ", queue[i]);
			}
		}
		printf("<--TAIL");
	}
	printf("\n");
}

//help message
void help() {
	printf("\"Q\"(without quotes) = quit\n");
	printf("\"q\" = switch to queue mode and display contents\n");
	printf("\"s\" = switch to stack mode and display contents\n");
	printf("(single integer) = push integer into queue or stack (depends on mode)\n");
	printf("\"p\"  = pop integer off stack or queue\n");
	printf("\"?\" = help\n");
}
