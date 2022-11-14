//이중연결리스트 구현(이중연결리스트도 원형연결리스트임) -> init(header)하면 llink와 rlink에 자기 자신을 넣음 -> insert할 때 newnode->rlink=befor->llink 를 하는데, before가 header면 header의 llink(자기자신)과 같아질 수 밖에 없음 
//header노드, insert, delete를 이해해야 함

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	// 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* header)
{
	header->llink = header;
	header->rlink = header;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* header)
{
	DListNode* p;
	for (p = header->rlink; p != header; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");
	
		// 헤드 노드의 오른쪽에 삽입
		dinsert(head, 100);
		dinsert(head, 200);
		dinsert(head, 300);
		dinsert(head, 400);
		dinsert(head, 500);
		dinsert(head, 600);
		dinsert(head, 700);
		dinsert(head, 800);
		print_dlist(head);

	printf("\n삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
}
