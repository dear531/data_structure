#include <stdio.h>

#define MAX_QUEUE_SIZE	10
struct queue {
	int data[MAX_QUEUE_SIZE];
	int front;
	int rear;
};

#define CHECK_QUEUE_POINTER(queue)	do {			\
	if (NULL == queue) {					\
		fprintf(stderr, "queue pointer can not null\n");\
		return -2;					\
	}							\
}while (0)

static inline int is_queue_empty(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return queue->front == queue->rear;
}

static inline int is_queue_full(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE;
}

static inline int queue_len(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return (queue->rear - queue->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

static inline int init_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	queue->front = 0;
	queue->rear = 0;
	return 0;
}

static inline int enqueue(struct queue *queue, int data)
{
	CHECK_QUEUE_POINTER(queue);
	if (1 == is_queue_full(queue)) {
		fprintf(stderr, "queue is full\n");
		return -1;
	}
	queue->data[queue->rear] = data;
	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	return 0;
}

static inline int dequeue(struct queue *queue, int *data)
{
	CHECK_QUEUE_POINTER(queue);
	if (is_queue_empty(queue))
		return -1;
	if (NULL != data)
		*data = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	return 0;
}

static inline int destroy_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	while (0 == dequeue(queue, NULL))
		dequeue(queue, NULL);
	return 0;
}

static inline int print_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	int i;
	for (i = queue->front; i != queue->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
		fprintf(stdout, "queue[%d]:%d\n", i, queue->data[i]);
	}
	return 0;
}


int main(void)
{
	struct queue queue;
	int i;
	fprintf(stdout, "init_queue\n");
	init_queue(&queue);
	print_queue(&queue);
	fprintf(stdout, "enqueue 1\n");
	enqueue(&queue, 1);
	print_queue(&queue);
	fprintf(stdout, "for max_queue_size enqueue\n");
	for (i = 0; i < MAX_QUEUE_SIZE; i++) {
		enqueue(&queue, i);
	}
	fprintf(stdout, "front :%d, rear :%d\n", queue.front, queue.rear);
	print_queue(&queue);
	fprintf(stdout, "dequeue twice and enqueue 11, 12\n");
	dequeue(&queue, NULL);
	dequeue(&queue, NULL);
	enqueue(&queue, 11);
	enqueue(&queue, 12);
	print_queue(&queue);
	int data;
	for (i = 0; i < MAX_QUEUE_SIZE && 0 == dequeue(&queue, &data); i++) {
		fprintf(stdout, "i %d, data %d\n",
				i, data);
	}
	fprintf(stdout, "front :%d, rear :%d\n", queue.front, queue.rear);
	destroy_queue(&queue);
	return 0;
}
