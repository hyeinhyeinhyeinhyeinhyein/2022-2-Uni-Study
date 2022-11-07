#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;


void error(char* message) {
	fprintf(stderr, "%s\n", message); //stderr는 printf가 버퍼문제(버퍼링)로 출력 지연이 생길 수 있어서 사용한대
}

ListNode* insert_first(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //p에 ListNode만큼 메모리를 할당해둔 주소를 저장한다.
	p->data = value;
	p->link = head;	//원래 head가 가리키던 곳을 옮겨야지! p의 링크가 먼저 head가 가리키는 애를 선점해야 head에 p를  넣을 수 있음 
	head = p;
	return head; // ?포인터를 반환하면 뭐가 어떻게 되나??

}

ListNode* insert(ListNode* head, ListNode* pre, element value) { //head는 어느 리스트에 삽입할지 구분하는 것임! (아마) 
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; // 이거 확인하기
	free(removed);
	return head;
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%d->", p->data);
	}
	printf("NULL \n");
}


int main() {
	ListNode* head=NULL;

	head=insert_first(head, 100);//head= 는 왜 써야하는 것?

	//insert(head, head, 200);

	//insert_first(head, 500);

	insert_first(head, 800);

	print_list(head);
	
	// 800 500 100 200
}
