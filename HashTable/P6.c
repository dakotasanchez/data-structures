/*
Dakota Sanchez
15 FEB 2014
This program utilizes an array as a hash table
for hash table functions. Display, searching, insertion, and deletion
are possible.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20 //default array size

struct wordEntry {
	char *word;
	int deleted;
};

//global
struct wordEntry table[SIZE];

int getInput(char *, char *);
void processInput(int, char, char *);
int hash(char *);
int search(char *);
void delete(char *);
int insert(char *);
void print();
void freeTable();
void help();

int main(void) {
	//initialize deleted flags
	int i;
	for(i = 0; i < SIZE; i++) {
		table[i].deleted = 0;
	}

	//user input variables
	char inputChar = 0;
	char inputWord[1024] = "";

	//greeting
	printf("\n-------------Hash Table example program------------\n");
	printf("-----------------(Enter #h for help)----------------\n");

	//main program loop
	while(1) {
		//result determines type of input
		int result = getInput(&inputChar, inputWord);

		processInput(result, inputChar, inputWord);
	}

	return 0;
}

//get user input, returns type of input
int getInput(char *inputChar, char *inputWord) {
	char buffer[100];
	int result;

	while(1){
		//intialize
		char octothorpe = 0;
		*inputChar = 0;
		
		printf(">");
		fgets(buffer, 120, stdin);
		//discard \n at end of string
		buffer[-1 + strlen(buffer)] = '\0';
		//get first value in buffer
		sscanf(buffer, "%c", inputChar);

		//starts with #
		if(*inputChar == '#') {
			result = sscanf(buffer, "%c%c %s", &octothorpe, inputChar, inputWord);

			if(result == 3) {
				//input = #command word
				return 3;
			} else {
				if(buffer[1] != ' ') {
					//input = #command
					return 2;
				} else {
					printf("Invalid input - Enter #h if you need help\n");
					continue;
				}
			}
		//string (could be spaces)
		} else {
			//make sure string isn't empty
			if(buffer[0] != '\0') {
				sscanf(buffer, "%s", inputWord);
				//input = word
				return 1;
			} else {
				printf("Invalid input - Enter #h if you need help\n");
				continue;
			}
		}
	}
}

void processInput(int result, char inputChar, char *inputWord) {
	//word
	if(result == 1) {
		if(search(inputWord)) {
			printf("Word is already in table\n");
		} else {
			if(insert(inputWord))
				printf("Table is full\n");
		}
	//#command
	} else if(result == 2) {
		switch(tolower(inputChar)) {
			case 'q':
				printf("Program terminating...\n");
				//free all memory
				freeTable();
				exit(0);
			case 'p':
				print();
				break;
			case 'h':
				help();
				break;
			default:
				printf("Invalid input - Enter #h if you need help\n");
		}
	//#command word
	} else {
		switch(tolower(inputChar)) {
			case 'd':
				if(search(inputWord))
					delete(inputWord);
				else
					printf("Word is not in the table\n");
				break;
			case 's':
				if(search(inputWord))
					printf("Word is in the table\n");
				else
					printf("Word is not in the table\n");
				break;
			default:
				printf("Invalid input - Enter #h if you need help\n");
		}
	}
}

//actual hashing function
//hash(k) = (word[0] + word[1] + ... word[n]) % 20
int hash(char *word) {
	int sum = 0;
	int i;
	for(i = 0; i < strlen(word); i++) {
		sum += word[i];
	}
	sum = sum % 20;
	return sum;
}

//returns 1 if word is found, 0 if not
int search(char *word) {
	int tries = 0;
	int entry = hash(word);
	while(table[entry].word != NULL && strcmp(table[entry].word, word) != 0) {
		if(table[entry].word != NULL) {
			entry = (entry + 7) % 20;
			tries++;
			//don't search over 20 times
			if(tries == SIZE)
				return 0;
		//if NULL, no reason to keep checking
		} else {
			return 0;
		}
	}
	//last checks to determine return value
	if(table[entry].word == NULL || table[entry].deleted)
		return 0;
	return 1;
}

//already searched, so word is in table
void delete(char *word) {
	int entry = hash(word);
	while(strcmp(table[entry].word, word) != 0) {
		entry = (entry + 7) % 20;
	}
	table[entry].deleted = 1;
}

//already searched, so word isn't in table
//returns 1 if table is full
int insert(char *word) {
	int tries = 0;
	int entry = hash(word);
	while(table[entry].word != NULL) {
		if(table[entry].deleted)
			break;
		entry = (entry + 7) % 20;
		tries++;
		//check if table is full
		if(tries == SIZE)
			return 1;
	}
	//insert word and set deleted flag
	free(table[entry].word);
	table[entry].word = malloc(sizeof(word) + 1);
	strcpy(table[entry].word, word);
	table[entry].deleted = 0;
	return 0;
}

//just go through table and print values
void print() {
	int i;
	for(i = 0; i < SIZE; i++) {
		if(table[i].word != NULL) {
			if(table[i].deleted == 0)
				printf("%.2i: %s\n", i, table[i].word);
			else
				printf("%.2i: <deleted>\n", i);
		} else {
			printf("%.2i: <null>\n", i);
		}
	}
}

//free all allocated memory
void freeTable() {
	int i;
	for(i = 0; i < SIZE; i++) {
		free(table[i].word);
	}
}

//help message
void help() {
	printf("\"#Q\"(without quotes) = quit\n");
	printf("\"#p\" = display entire hash table\n");
	printf("\"#h\" = help\n");
	printf("\"#s (word)\" = search for word in table\n");
	printf("\"#d (word)\" = delete word from table\n");
	printf("\"(anything else)\" = insert into table\n");
}
