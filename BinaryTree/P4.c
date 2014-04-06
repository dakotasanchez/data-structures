/*
Dakota Sanchez
2 FEB 2014
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

//tree initialization
//global and only accessed by processInput()
struct node *_root = NULL;

void getInput(char *, char *, int *);
void processInput(char, char, int);
void traverse(struct node *);
int getDepth(struct node *);
int isBalanced(struct node *);
int search(struct node *, int);
struct node * insert(struct node *, int);
struct node * delete(struct node *, int);
void help();

int main(void) {

	//user input variables
	char char1, char2;
	int num;

	//greeting
	printf("----------Binary tree example program----------\n");
	printf("--------------(Enter ? for help)---------------\n");

	//main loop until termination
	while(1) {

		getInput(&char1, &char2, &num);

		processInput(char1, char2, num);
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

void processInput(char char1, char char2, int num) {
	int result;	//for returns from functions

	//check what was entered
	switch(char2) {
		//case 'a' = single int
		case 'a':
			result = search(_root, num);
			if(result == 1)
				printf("Integer is already in the tree\n");
			else
				_root = insert(_root, num);
			break;
		//case 'b' = single char
		case 'b':
			char1 = tolower(char1);
			switch(char1) {
				case 'q':
					printf("Program Terminating...\n");
					exit(0);
				case 'p':
					printf("[ ");
					traverse(_root);
					result = getDepth(_root);
					printf("]\nDepth = %i\n", result);
					if(isBalanced(_root))
						printf("Tree is balanced\n");
					else
						printf("Tree is not balanced\n");
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
					result = search(_root, num);
					if(result == 1)
						printf("Integer is in the tree\n");
					else
						printf("Integer is not in the tree\n");
					break;
				case 'd':
					result = search(_root, num);
					if(result == 1)
						_root = delete(_root, num);
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

//traverse tree, print, and return depth
void traverse(struct node *root) {
	if(root == NULL) return;

	traverse(root->left);
	printf("%i ", root->data);
	traverse(root->right);
}

int getDepth(struct node *root) {
	if(root == NULL) return 0;

	int left = getDepth(root->left);
	int right = getDepth(root->right);
	//return depth of largest sub-tree + 1(current node)
	return (left > right) ? (left + 1) : (right + 1);
}

//determine if distance from any two leaf nodes to root is <= 1
int isBalanced(struct node *root) {
	//for height of subtrees
	int left;
	int right;

	//empty tree is balanced
	if(root == NULL) return 1;

	left = getDepth(root->left);
	right = getDepth(root->right);

	if( abs(left-right) <= 1 && isBalanced(root->left) && isBalanced(root->right))
		return 1;

	//tree isn't balanced if we reach this
	return 0;
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

//delete node
struct node * delete(struct node *root, int num) {

	struct node *temp;
	//find node
	if(root == NULL) {
		return NULL;
	} else if(num < root->data) {
		root->left = delete(root->left, num);
	}else if(num > root->data) {
		root->right = delete(root->right, num);
	} else {

		//we're now at the "root" we want to delete

		//has 2 children
		if(root->left && root->right) {
			temp = root->right;
			while(temp->left != NULL) {
				temp = temp->left;
			}
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
		} else {
			temp = root;
			//has only right child
			if(root->left == NULL)
				root = root->right;
			//has only left child
			else if(root->right == NULL)
				root = root->left;
			free(temp);
		}
	}
	return root;
}

//help message
void help() {
	printf("\"q\"(without quotes) = quit\n");
	printf("\"p\" = print tree in infix-order as well as depth of tree\n");
	printf("(single integer) = search tree for int, alert if it's there, insert if it's not\n");
	printf("\"s\" (single integer) = search tree for int, alert if it's there or not\n");
	printf("\"d\" (single integer) = search tree for int, delete if it's there, alert if it's not\n");
	printf("\"?\" = help\n");
}
