
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();

	// Write a benchmark test to demonstrate the difference between
	// ArrayQueue and CircularArrayQueue
	// Times will not be much different for enqueue but very different for dequeue

    for (int i = 1; i < 10000; i++) { QueueEnqueue(q, i); }
    for (int j = 1; j < 10000; j++) { QueueDequeue(q); }

	QueueFree(q);
}

