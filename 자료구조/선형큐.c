// 선형큐
// 초기값 -1
// rear - front 값이 큐에 들어있는 원소 
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

void error(char message) { // 함수 안에서 오류 함수를 쓰는 게 됨 
	fprintf(stderr, "%s\n", message);
	exit(1); // 루프 종료
}

void init_queue(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}

void queue_print(QueueType* q) {
	for (int i = 0; i < MAX_QUEUE_SIZE; i++){ // 우선 5칸(max)을 모두 출력시킴, 
		if (i <= q->front || i > q->rear) // front=2, rear=3일 때, i가 2일 때까지( 3칸) 빈칸 _ i가 4부터 빈칸 -> data[3]만 출력 
			printf(" | ");
		else
			printf("%d | ", q->data[i]);
	}
}



int is_full(QueueType* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}

int is_empty(QueueType* q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(QueueType* q, int item) { // rear값이 늘어나
	if (is_full(q)) { // 큐에 6개 들어왔을 때도 오류라고 나오면 좋겠지만 그러지는 못하네 
		error("큐가 포화상태입니다."); // error라는 함수를 위에 정의했음, 이 함수에 따라 해당 문자열이 콘솔에 출력될 것
		return;
	}
	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q) { // front값이 늘어나 
	if (is_empty(q)) {
		error("큐가 비었습니다.");
		return -1;
	}
	else {
		int item = q->data[++(q->front)];
		return item; // 근데 반환을 왜 하냥
	}
}

int main(void) {
	int item = 0;
	QueueType q;

	init_queue(&q); // front=-1, rear=-1

	enqueue(&q, 1); // front=-1, rear=0
	enqueue(&q, 2); // front=-1, rear=1
	enqueue(&q, 3); // front=-1, rear=2
	enqueue(&q, 4); // front=-1, rear=3
	dequeue(&q); // front=0, rear=3
	enqueue(&q, 5); // front=0, rear=4

	queue_print(&q); // | 2 | 3 | 4 | 5 |
}

