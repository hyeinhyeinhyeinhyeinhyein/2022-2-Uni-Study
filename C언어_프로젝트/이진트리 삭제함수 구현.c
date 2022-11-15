#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char name[20];
	char id[8];
	struct student* parent;
	struct student* left;
	struct student* right;
}STUDENT;

STUDENT* btsearch(STUDENT* root, char* key);	//학생이름 위치를 나타내는 구조체 포인터, 루트는 어디고, 키(이름)을 받음
void print_node(STUDENT* node);	//노드를 모두 출력하는 함수, ?node부터 출력하는 거?, root 필요없음?
void insert_node(STUDENT** root, STUDENT* node);	// 노드를 삽입하는 함수, 뿌리를 알고, ? 몰라 node 왜 필요
void in_order(STUDENT* node); //전위탐색 함수, ?root 필요없음?
void delete(STUDENT* node);	//삭제 함수 


int main()
{
	char* filename = "student2023.txt";
	FILE* fp;
	STUDENT* root = NULL, * temp, * find,*temp_parent,*parent_print;
	char id[8];
	char name[10];

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		return 1;
	}	// 파일 존재 오류 처리 


	while (fscanf(fp, "%s", id) != EOF) {
		temp = (STUDENT*)malloc(sizeof(STUDENT));
		strcpy(temp->id,id);
		fscanf(fp, "%s", temp->name);
		temp->left = NULL;	
		temp->right = NULL;
		temp->parent = NULL;

		//printf("%s %s\n", temp->id, temp->name);

		// 이진트리 구현함 
		insert_node(&root, temp);	// 구조체에 학번이랑 이름은 채워지고, right랑 left는 아직 안 채운 상태의 노드를 삽입하기 
	}

	fclose(fp);


	int menu = 0; //메뉴 번호를 저장하는 변수
	while (menu != 8) {
		printf("1: 전체 노드 프린트(전위운행ver)\n");
		printf("2: 노드 삭제하기\n");
		printf("8: 프로그램 종료\n");
		printf("메뉴를 선택하세요! >> ");
		scanf("%d", &menu);

		if (menu == 1) {
			in_order(root);
		}

		else if (menu == 2) {
			printf("삭제할 부모 노드의 키(학번)을 입력하세요! >> ");
			scanf("%s", id);

			find = btsearch(root, id);

			if (find == NULL)
				printf("not found!\n");
			else
				delete(find);
		}

	else if (menu == 4) {
		printf("input id for search!!\n");
		scanf("%s", id);
		find = btsearch(root, id);
		if (find == NULL)
			printf("not found!\n");
		else
			print_node(find);
	}

	else if (menu == 5) {
		in_order(root);
	}

	else if (menu == 8) {
		exit(1);
	}

	else {
		printf("숫자를 다시 입력해주세요! >> ");
		break;
	}
	printf("\n");
}
}

void insert_node(STUDENT** root, STUDENT* node) { //왜 이중포인터 root씀?
	STUDENT* cur;	

	if (*root == NULL) {	// 처음 노드를 심을 때!
		*root = node;
		return;// 종료 
	}

	cur = *root; // 현재 노드를 *root라고 하고 

	if (strcmp(cur->id, node->id) < 0) {
		if (cur->right != NULL) {// 오른쪽 노드 자리에 이미 주인이 있으면 오른쪽 노드와 비교해서 트리를 뻗어내는 걸 반복하면 된다. 
			insert_node(&cur->right, node); //&cur->right임, 왜 &cur임? cur->right->id랑 비교해야 하는 거 아님? 아 순환이고, **이중포인터라 &쓴 거임  
		}
		else {
			cur->right = node;
			node->parent = cur;
		}

	}

	else{ //if (strcmp(cur->id, node->id) > 0)
		if (cur->left != NULL)
			insert_node(&cur->left, node);
		else {
			cur->left = node;
			node->parent = cur;
		}
	}
}


void print_node(STUDENT* node) {
	printf("%s %s 부모노드: %s\n", node->id, node->name, node->parent);
}

STUDENT* btsearch(STUDENT* root, char* key) {
	if (root == NULL)	// 도대체 root가 NULL인 것은 무엇을 의미하는 것인지 모르겠음. 	
		return NULL;
	/*-------------------------*/
	if (!strcmp(root->id, key)) // 한 번에 id랑 key랑 일치하면, 더 이상 더 찾을 필요없쥐~ 찾은 키가 있는 주소를 반환해 
		return root;
	else if (strcmp(root->id, key) > 0) { // root가 더 크면! 그 왼쪽만 탐색하면 돼 
		btsearch(root->left, key);
	}
	else { //(strcmp(root->id, key) < 0) // root가 더 작으면! 그 오른쪽만 탐색하면 돼 
		btsearch(root->right, key);
	}
}



void in_order(STUDENT* node) { // 전위탐색이라 작은 것 부터 출력하는 거임 -> left에서 right 로 출력하면 됨
	if (node == NULL)	//? node가 NULL이라는 말은, 그 안에 아무것도 저장되어 있지 않다는 것? 그럴 수가 있나? 애초에 insert할 때 꽉 채워진 node를 삽입하자나 ...
		return;
	in_order(node->left);
	print_node(node);	// root부터 출력해야겠네 -> 즉슨 매개변수 node는 거의 rootnode라고 해도 무방하겠네 
	in_order(node->right);
}

void delete(STUDENT* node) {	//부모노드에서 어느 방향 자식 노드를 삭제할지 (direction 1: 왼쪽, 2: 오른쪽)
	STUDENT* delete_parent;
	delete_parent = node->parent;

	// 자식노드가 없을 때 
	if (node->left == NULL && node->right == NULL) {
		printf("자식의 양쪽 노드가 존재하지 않습니다. %s %s노드를 삭제하겠습니다.\n", node->id, node->name);

		if (delete_parent->left == node) {
			delete_parent->left = NULL;
		}
		else if (delete_parent->right == node) {
			delete_parent->right = NULL;
		}

		free(node);
	}

	// 자식노드가 있을 때
	else {
		// 자식 노드가 왼쪽에만 있을 때(자식노드 하나)
		if (node->right == NULL) {
			STUDENT* ltemp = node->left;
			strcpy(node->id, ltemp->id);
			strcpy(node->name, ltemp->name);
			node->left = NULL;
			free(ltemp);
		}

		// 자식 노드가 오른쪽에만 있을 때(자식노드 하나)
		else if (node->left == NULL) {
			STUDENT* rtemp = node->right;
			strcpy(node->id, rtemp->id);
			strcpy(node->name, rtemp->name);
			node->right = NULL;
			free(rtemp);
		}

		//자식 노드가 둘다 있을 때 (자식노드 두개)
		//루트노드에서 가장 가까운 오른쪽을 올리기로 했다! (원래는 가장 가까운 왼쪽을 올려도 됨)
		else {
			STUDENT* ltemp = node->left;
			STUDENT* rtemp = node->right;
			STUDENT* parent_endtemp;	//가장 왼쪽의 노드의 부모노드  
			STUDENT* endtemp=NULL;	//가장 왼쪽노드
			if (rtemp->left == NULL) {	// right의 왼쪽 노드가 없다면 오른쪽 노드가 바로 올라가고,
				strcpy(node->id, rtemp->id);
				strcpy(node->name, rtemp->name);
				node->right = rtemp->right;
				free(rtemp);
			}
			else { // right의 왼쪽 노드가 있다면 가장 왼쪽 노드로 가서 걔가 올라감 
				parent_endtemp = rtemp;
				while (endtemp->left != NULL) {
					endtemp = parent_endtemp->left;
				}
				strcpy(node->id, endtemp->id);
				strcpy(node->name, endtemp->name);
				parent_endtemp->left = NULL;
				free(endtemp);			
			}
		}
	}
}
