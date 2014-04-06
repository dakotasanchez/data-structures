/*
Dakota Sanchez
9 Mar 2014
This program takes data from adj.data to construct an unweighted
directed graph. The program takes two nodes as arguments and finds 
the shortest path from the source to the destination, if it exists.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 129

struct node {
	int num; // integer asscociated with node
	int hops; // hops associated with node
};

void readAdjFile();
int path(struct node *, struct node *);
void push(struct node *);
struct node * pop();

int adjMatrix[MAX][MAX]; // adjacency matrix for connected nodes
struct node *queue[MAX]; // holds nodes connected to current node
int visited[MAX]; // holds already visited nodes so we don't loop
int HEAD; // head of queue
int TAIL; // tail of queue
int SIZE; // current size of queue

int main(int argc, char **argv) {
	struct node *src = malloc(sizeof(struct node)); // source node from **argv
	struct node *dest = malloc(sizeof(struct node)); // destination node from **argv

	if(argc != 3 || (sscanf(argv[1], "%i", &(src->num)) + 
		sscanf(argv[2], "%i", &(dest->num)) != 2)) {
		printf("Error: program expects two integer arguments\n");
		return 1;
	}

	// read data from adj.data and set 'connected' flags in adjMatrix
	readAdjFile();

	// get # of hops from src to dest if it exists
	int ret = path(src, dest);

	// print results
	if(ret == -1)
		printf("Sorry dude: No path from your source to your destination");
	else
		printf("Shortest path from %i to %i is: %i hop", src->num, dest->num, ret);
	
	// grammar time!
	if(ret > 1 || ret == 0)
		printf("s\n");
	else
		printf("\n");

	return 0;
}

void readAdjFile() {
	FILE *fp;
	fp = fopen("adj.data", "r");

	// throw error if failure to open file
	if(fp == NULL) {
		printf("Error: failure to open file\n");
		exit(1);
	}

	int a, b; // for each pair of connected nodes
	while(1) {
		// get each pair of connected nodes in file
		fscanf(fp, "%i %i", &a, &b);
		// check for end of file
		char c = fgetc(fp);
		if(c == EOF)
			break;
		adjMatrix[a][b] = 1; // set flag in adjMatrix
	}

	fclose(fp);
}

int path(struct node *src, struct node *dest) {
	push(src); // add src node to queue

	struct node *s; // temp node variable
	int hops = 0; // total hops
	while(SIZE > 0) {
		s = pop();
		visited[s->num] = 1; // mark that we've visited this node
		hops = s->hops;	// adjust hops
		if(s->num == dest->num) {
			return hops; // return hops
		} else {
			int i;
			hops++;	// hops + 1 for all connected nodes
			for(i = 0; i < MAX; i++) {
				if(adjMatrix[s->num][i] == 1) {
					if(visited[i] != 1) {	//  check if already visited
						struct node *temp = malloc(sizeof(struct node));
						temp->num = i;
						temp->hops = hops;
						push(temp); // add connected node and hops + 1 to queue
					}
				}
			}
		}
	}
	return -1;	// failure
}

void push(struct node *node) {
	//if tail + 1 == head then the queue is full
	if(((TAIL + 1) % MAX) == (HEAD % MAX))
		printf("Error: QUEUE OVERFLOW\n");
	else {
		SIZE++; // increment size of queue
		queue[TAIL++ % MAX] = node;
	}
}

struct node * pop() {
	//if they're already equal, queue is empty
	if(HEAD == TAIL) {
		printf("Error: QUEUE UNDERFLOW\n");
		return NULL;
	} else {
		SIZE--; // decrement size of queue
		return queue[HEAD++ % MAX];
	}
}
