/*
Dakota Sanchez
20 Jan 2014
CSE 222, Prog Assgn. 2
This program utilizes a linked list to show the process of
	traversing, deleting, inserting, and searching through a linked list
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void getInput(char *, char *, int *);
int search(struct node *, int);
void insert(struct node *, int);
void delete(struct node *, int);
void traverse(struct node *);
void help();

int main(void) {
	//list initialization
	struct node *list;
	struct node *head = malloc(sizeof(struct node));
	list = head;
	head->next = NULL;

	//user input variables
	char *char1, *char2;
	int *num;
	char1 = malloc(sizeof(char));
	char2 = malloc(sizeof(char));
	num = malloc(sizeof(int));

	//greeting
	printf("----------Linked list example program----------\n");
	printf("--------------(Enter ? for help)---------------\n");

	int result; //for search function
	
	//main loop until termination
	while(1) {
		
		getInput(char1, char2, num);

		//check what was entered
		switch(*char2) {
			//case 'a' = single int
			case 'a':
				result = search(list, *num);
				if(result == 1)
					printf("Integer is already in the list\n");
				else
					insert(list, *num);
				break;
			//case 'b' = single char
			case 'b':
				*char1 = tolower(*char1);
				switch(*char1) {
					case 'q':
						printf("Program Terminating...\n");
						return 0;
					case 'p':
						traverse(list);
						break;
					case '?':
						help();
						break;
					default:
						printf("Invalid input - Enter ? if you need help\n");
				}
				break;
			//case 'c' = char (space) int
			case 'c':
				*char1 = tolower(*char1);
				switch(*char1) {
					case 's':
						result = search(list, *num);
						if(result == 1)
							printf("Integer is in the list\n");
						else
							printf("Integer is not in the list\n");
						break;
					case 'd':
						result = search(list, *num);
						if(result == 1)
							delete(list, *num);
						else
							printf("Integer is not in the list\n");
						break;
					default:
						printf("Invalid input - Enter ? if you need help\n");
				}
				break;
			default:
				printf("default\n");
		}
	}		
	
	return 0;
}

//get user input
void getInput(char *char1, char *char2, int *num) {
	char buffer[100];
	int result;
	while(1){
		//clear values
		//char 2 is a "return status" for a switch statement later 
		*char1 = 0;
		*char2 = 0;
		*num = 0;
		printf(">");
		
		fgets(buffer, 100, stdin);
		//get first value in buffer
		sscanf(buffer, "%c", char1);

		//starts with a number
		if(isdigit(*char1)) {
			result = sscanf(buffer, "%i %c", num, char1);
			if(result == 1) {
				//'a' means single int was entered
				*char2 = 'a';
				break;
			} else {
				printf("Invalid input - Enter ? if you need help\n");
				continue;
			}
		//does not start with number
		} else {
			result = sscanf(buffer, "%c %c", char1, char2);
			if(result == 1) {
				//'b' means single char was entered
				*char2 = 'b';
				break;
			} else {
				if(isdigit(*char2)) {
					sscanf(buffer, "%c %i", char1, num);
					//'c' means char followed by an int was entered
					*char2 = 'c';
					break;
				} else {
					printf("Invalid input - Enter ? if you need help\n");
					continue;
				}
			}	
		}
	}
}

//search list for occurrence of integer num
int search(struct node *list, int num) {
	struct node *currentPtr = list->next;
	while(currentPtr != NULL) {
		if(currentPtr->data == num)
			return 1;
		currentPtr = currentPtr->next;
	}
	return 0;
}

//insert new node at beginning of list
void insert(struct node *list, int num) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = num;
	newNode->next = list->next;
	list->next = newNode;
}

//delete node
void delete(struct node *list, int num) {
	struct node *currentPtr = list->next;
	struct node *prevPtr = list;
	while(currentPtr != NULL) {
		if(currentPtr->data == num) {
			prevPtr->next = currentPtr->next;
			free(currentPtr);
			return;
		}
		prevPtr = currentPtr;
		currentPtr = currentPtr->next;
	}
}

//traverse list and print
void traverse(struct node *list) {
	struct node *currentPtr = list->next;
	while(currentPtr != NULL) {
		printf("%i ", currentPtr->data);
		currentPtr = currentPtr->next;
	}
	printf("\n");
}

//help message
void help() {
	printf("\"q\"(without quotes) = quit\n");
	printf("\"p\" = print list\n");
	printf("(single integer) = search list for int, alert if it's there, insert if it's not\n");
	printf("\"s\" (single integer) = search list for int, alert if it's there or not\n");
	printf("\"d\" (single integer) = search list for int, delete if it's there, alert if it's not\n");
	printf("\"?\" = help\n");
}