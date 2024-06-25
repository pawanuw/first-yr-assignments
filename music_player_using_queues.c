#include <stdio.h>
#include <unistd.h>
#define MAX_SIZE 100

char queue[MAX_SIZE][1000];
int front=-1;
int rear=-1;

int isEmpty() {
	if (front == -1) {
        	return 1;
        }
        else {
                return 0;
        }
}

int isFull() {
        if (rear == MAX_SIZE - 1) {
                return 1;
        }
        else {
                return 0;
        }
}

void enqueue(char* song) {
        if (isFull()) {
        	printf("Queue is full. Cannot add songs.\n");
        }
        else {
        	if (isEmpty()) {
                	front=0;
		}
		int j=0;
		char letter;
                rear=rear+1;
		while((letter=getchar()) != '\n') {
			queue[rear][j]=letter;
			j++;
		}
		printf("New song added.\n");
        }
}

void dequeue() {
        if (isEmpty()) {
        	printf("Queue is empty. Cannot remove songs.\n");
        }
        else {
        	char* dequeuedSong = queue[front];
        	printf("Skipped playing %s.\n",dequeuedSong);
        	if (front >= rear) {
                	front = -1;
                	rear = -1;
              	}
              	else {
                    	front++;
              	}
        }
}

void displayQueue() {
        if (isEmpty()) {
              	printf("Queue is empty.\n");
	}
       	else {
		printf("Now playing: ");
		printf("%s",queue[front]);
		printf("\n\n");
	}
}

int main() {
	int n;
	char* song;
	printf("Enter the number of songs you want to add: ");
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		printf("Enter the name of the song: ");
		scanf("%s",song);
		enqueue(song);
	}
	printf("\n");

	for (int i=0; i<n;i++) {
		char op;
		displayQueue();
		printf("Do you want to skip?(Song duration 2 sec)[y/n]: ");
		scanf(" %c",&op);
		if (op=='y'||op=='Y') {
			dequeue();
		}
		else if (op=='n'||op=='N') {
			sleep(2);
		}
		else {
		        printf("ERROR:You entered an invalid input");
		}
	}
}

