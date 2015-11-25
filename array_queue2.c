#include <stdio.h>

#define MAX_QUEUE_SIZE	10

struct queue {
	int front;
	int rear;
	int data[MAX_QUEUE_SIZE];
	/* lest enqueue 1, lest dequeue 0 */
	int flag;
};

#define CHECK_QUEUE_POINTER(queue)	do {			\
	if (NULL == queue) {					\
		fprintf(stderr, "queue pointer can not null\n");\
		return -2;					\
	}							\
} while (0)

static inline int is_queue_empty(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return queue->front == queue->rear && 0 == queue->flag;
}
static inline int is_queue_full(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return queue->front == queue->rear && 1 == queue->flag;
}
static inline int init_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	queue->front = 0;
	queue->rear = 0;
	queue->flag = 0;
	return 0;
}

static inline int queue_len(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	return queue->rear - queue->front
		? MAX_QUEUE_SIZE * queue->flag
		: (queue->rear - queue->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
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
	queue->flag = 1;
	return 0;
}

static inline int dequeue(struct queue *queue, int *data)
{
	CHECK_QUEUE_POINTER(queue);
	if (1 == is_queue_empty(queue)) {
		fprintf(stderr, "queue is empty\n");
		return 1;
	}
	if (NULL != data)
		*data = queue->data[queue->front];
	queue->front = (queue->front +1) % MAX_QUEUE_SIZE;
	queue->flag = 0;
	return 0;
}

static inline int print_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	int i, start;
	if (1 == is_queue_empty(queue)) {
		return 0;
	} else {
		if (1 == is_queue_full(queue)) {
			fprintf(stdout, "queue[%d]:%d\n",
					queue->front, queue->data[queue->front]);
			start = (queue->front + 1) % MAX_QUEUE_SIZE;
		} else {
			start = queue->front;
		}
		for (i = start; i != queue->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
			fprintf(stdout, "queue[%d]:%d\n",
					i, queue->data[i]);
		}
	}
}

static inline int destroy_queue(struct queue *queue)
{
	CHECK_QUEUE_POINTER(queue);
	while (0 == is_queue_empty(queue))
		dequeue(queue, NULL);
	return 0;
}

int main(void)
{
	struct queue queue;
	int i;
	init_queue(&queue);
	for (i = 0; i < MAX_QUEUE_SIZE; i++) {
		enqueue(&queue, i);
	}
	print_queue(&queue);
	if (1 != is_queue_full(&queue))
		enqueue(&queue, 10);
	print_queue(&queue);
	fprintf(stdout, "front :%d, rear :%d\n",
			queue.front, queue.rear);
	int data;
	fprintf(stdout, "dequeue\n");
	dequeue(&queue, &data);
	fprintf(stdout, "data :%d\n", data);
	enqueue(&queue, 11);
	fprintf(stdout, "front :%d, rear :%d\n",
			queue.front, queue.rear);
	print_queue(&queue);
	destroy_queue(&queue);
	
	return 0;
}
