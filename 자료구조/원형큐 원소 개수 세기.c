#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// 이 부분을 구현하는 게 핵심이었음!
// 원형큐의 원소 개수를 반환하는 함수 
element get_count(QueueType* q)
{
	int count = 0; // 큐의 원소 개수를 나타냄
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			count++;
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	return count;
}

// ===== 원형큐 코드 끝 ======

int main(void)
{
	QueueType queue;
	int whatareyougoing = 0; // push, pop, 전체 출력 중 고를 때 필요한 변수
	int element;

	init_queue(&queue);

	while (whatareyougoing != 4) {

		printf("push는 1, pop은 2, 원소 전체 출력은 3, 종료는 4를 입력하세요. >> ");
		scanf("%d", &whatareyougoing);

		if (whatareyougoing == 1) { //push
			printf("정수를 입력하시오: ");
			scanf("%d", &element);
			enqueue(&queue, element);
			printf("현재 원형큐에 저장된 원소의 개수는 %d개 입니다.\n", get_count(&queue));
		}

		if (whatareyougoing == 2) { //pop
			dequeue(&queue);
			printf("현재 원형큐에 저장된 원소의 개수는 %d개 입니다.\n", get_count(&queue));
		}

		if (whatareyougoing == 3) { //print
			queue_print(&queue);
			printf("현재 원형큐에 저장된 원소의 개수는 %d개 입니다.\n", get_count(&queue));
		}
		
	}
}
