// 스택 두 개로 큐를 구현하기

#include <stdio.h>
#include <stdlib.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

// ===== 스택 코드의 끝 ===== 


int main(void)
{
	StackType s; // 첫 번째 스택
	StackType s2; // 두 번째 스택(원소를 출력할 스택임)

	init_stack(&s); // 스택 초기화
	init_stack(&s2);

	int value; // push할 값
	int whatareyougoing=0; // push할지 pop할지 고를 때 사용할 변수
	char reply[5] = "\0"; // exit할 때까지 push pop을 반복 


	while (whatareyougoing!=4) {

		printf("push는 1, pop은 2, 출력요청은 3, 종료는 4를 입력하세요.\n");
		scanf("%d", &whatareyougoing);

		// push
		if (whatareyougoing == 1) {
			printf("값을 입력하세요. >> ");
			scanf("%d", &value);
			push(&s,value); // 입력한 수를 s스택에 삽입
		}

		// pop
		else if (whatareyougoing == 2) {
			if (s.top == -1) {
				if (s2.top == -1) {
					printf("원소가 저장되어 있지 않습니다.\n");
				}
				if (s2.top != -1) {
					s2.top--;
					}
				}
		
			else if (s.top != -1) {
				for (int i = s.top; i > -1; i--) {
					push(&s2, pop(&s));
				}
				s2.top--;
			}
		}

		// 출력
		else if (whatareyougoing == 3) {
			if (s2.top == -1){	//s2에 아무런 스택이 없을 때 s에서 옮겨오는 과정을 거침 
				for (int i = s.top; i > -1; i--) {
					push(&s2, pop(&s));
				}
			}
		
			printf("저장된 스택: ");
			for (int i = s2.top; i > -1; i--) { // 저장된 스택 개수만큼
				printf("%d ", s2.data[i]);	// pop을 해도 되지만 스택을 보존하려고 top에서 부터 출력
			}
			break;
    }
	}
}
