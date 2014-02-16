/*
Dakota Sanchez
26 Jan 2014
CSE 222, Prog Assgn. 3
This program utilizes a binary tree to show the process of
	traversing, deleting, inserting, and searching through a binary tree
*/

#include <stdio.h>
#include <stdlib.h>

//binary tree node
struct node {
	int data;
	struct node *left;
	struct node *right;
};

void getInput(char *, char *, int *);
int traverse(struct node *);
int search(struct node *, int);
struct node * insert(struct node *, int);
void help();

int main(void) {
	//tree initialization
	struct node *root = NULL;

	//user input variables
	char char1, char2;
	int num;

	//greeting
	printf("----------Binary tree example program----------\n");
	printf("--------------(Enter ? for help)---------------\n");

	int result;	//for returns from functions
	
	//main loop until termination
	while(1) {
		
		getInput(&char1, &char2, &num);

		//check what was entered
		switch(char2) {
			//case 'a' = single int
			case 'a':
				result = search(root, num);
				if(result == 1)
					printf("Integer is already in the tree\n");
				else
					root = insert(root, num);
				break;
			//case 'b' = single char
			case 'b':
				char1 = tolower(char1);
				switch(char1) {
					case 'q':
						printf("Program Terminating...\n");
						return 0;
					case 'p':
						printf("[ ");
						result = traverse(root);
						printf("]\nDepth = %i\n", result);
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
				char1 = tolower(char1);
				switch(char1) {
					case 's':
						result = search(root, num);
						if(result == 1)
							printf("Integer is in the tree\n");
						else
							printf("Integer is not in the tree\n");
						break;
					default:
						printf("Invalid input - Enter ? if you need help\n");
				}
				break;
			default:
				printf("default - error\n");
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

//traverse tree, print, and return depth
int traverse(struct node *root) {
	if(root == NULL) return 0;

	int left = traverse(root->left);
	printf("%i ", root->data);
	int right = traverse(root->right);

	//return depth of largest sub-tree + 1(current node)
	return (left > right) ? (left + 1) : right + 1;
}

//search tree for occurrence of integer num
int search(struct node *root, int num) {
	if(root == NULL) return 0;
	
	if(root->data == num) return 1;
	
	if(num > root->data)
		return search(root->right, num);

	if(num < root->data)
		return search(root->left, num);

	//never going to reach
	return 0;
}

//insert new node into tree
struct node * insert(struct node *root, int num) {
	if(root == NULL) {
		root = malloc(sizeof(struct node));
		root->data = num;
		root->left = root->right = NULL;
		return root;
	}
	if(num > root->data) {
		root->right = insert(root->right, num);
		return root;
	}
	if(num < root->data) {
		root->left = insert(root->left, num);
		return root;
	}

	//never going to reach, I already searched the tree
	return NULL;
}

//help message
void help() {
	printf("\"q\"(without quotes) = quit\n");
	printf("\"p\" = print tree in infix-order as well as depth of tree\n");
	printf("(single integer) = search tree for int, alert if it's there, insert if it's not\n");
	printf("\"s\" (single integer) = search tree for int, alert if it's there or not\n");
	printf("\"?\" = help\n");
}
