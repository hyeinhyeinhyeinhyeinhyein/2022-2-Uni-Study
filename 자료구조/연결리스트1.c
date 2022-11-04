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
	p->link = head;	//p의 링크가 먼저 head가 가리키는 애를 선점해야 head에 p를  넣을 수 있음 
	head = p;
	return head; // ?포인터를 반환하면 뭐가 어떻게 되나??

}

ListNode* insert_first(ListNode* head, ListNode* pre,element value) {

	ListNode* p;

}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}




int main() {

}
