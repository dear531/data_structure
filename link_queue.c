#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node *next;
	int data;
};

struct queue {
	struct node *front;
	struct node *rear;
};

static inline int init_queue(struct queue *queue, struct node *head)
{
	queue->front = queue->rear = head;
	head->data = 0;
	return 0;
}

static inline int is_queue_empty(struct queue *queue)
{
	return queue->front == queue->rear
		|| 0 == queue->front->data;
}

static inline int enqueue(struct queue *queue, int data)
{
	queue->rear->next = malloc(sizeof(*queue->rear->next));
	if (NULL == queue->rear->next)
		return -1;
	queue->rear->next->next = NULL;
	queue->rear->next->data = data;
	queue->rear = queue->rear->next;
	queue->front->data++;
	return 0;
}

static inline int dequeue(struct queue *queue, int *data)
{
	struct node *p = queue->front->next;
	queue->front->next = queue->front->next->next;
	if (NULL != data)
		*data = p->data;
	free(p);
	p = NULL;
	queue->front->data--;
	return 0;
}

static inline int destroy_queue(struct queue *queue)
{
	while (1 != is_queue_empty(queue))
		dequeue(queue, NULL);
	return 0;
}

static inline int print_queue(struct queue *queue)
{
	struct node *p = NULL;
	int i;
	fprintf(stdout, "queue number :%d\n",
			queue->front->data);
	for (p = queue->front->next; NULL != p; p = p->next) {
		fprintf(stdout, "queue [%d] :%d\n",
				i++, p->data);
	}
}

int main(void)
{
	struct queue queue;
	struct node head;
	int i;
	int data;
	init_queue(&queue, &head);
	for (i = 0; i < 10; i++) {
		enqueue(&queue, i);
	}
	print_queue(&queue);
	if (1 != is_queue_empty(&queue))
		dequeue(&queue, &data);
	fprintf(stdout, "data :%d\n", data);
	print_queue(&queue);
	enqueue(&queue, 11);
	print_queue(&queue);
	destroy_queue(&queue);
	print_queue(&queue);
	if (1 != is_queue_empty(&queue))
		dequeue(&queue, &data);
	return 0;
}
