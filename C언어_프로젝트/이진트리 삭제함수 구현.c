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

void print_node(STUDENT* node);		//노드 정보를 출력하는 함수 (트리 순회할 때 사용한다.)
void insert_node(STUDENT** root, STUDENT* node);	// 이진트리의 노드를 추가하는 함수
void in_order(STUDENT* node);		//중위순회대로 노드를 출력하는 함수 
void pre_order(STUDENT* node);		//전위순회대로 노드를 출력하는 함수 
void post_order(STUDENT* node);		//후위순회대로 노드를 출력하는 함수 
void delete(STUDENT* node);		//키를 입력 받아 노드를 삭제하는 함수 
STUDENT* btsearch(STUDENT* root, char* key);	//키를 입력받아 해당키에 해당하는 노드의 정보를 출력하는 함수 

int main()
{

	// 파일을 열어서 학번과 이름을 temp에 잠시 저장한 후 이진트리노드에 추가하기 
	char* filename = "student2022.txt";
	FILE* fp;
	STUDENT* root = NULL, * temp, * find, * temp_parent, * parent_print;
	char id[8];
	char name[10];

	fp = fopen(filename, "r");
	if (fp == NULL) { // 파일 존재 오류 처리 
		perror(filename);
		return 1;
	}

	while (fscanf(fp, "%s", id) != EOF) {	//학번 id라는 버퍼에 저장 
		temp = (STUDENT*)malloc(sizeof(STUDENT));	// 노드 구조체
		strcpy(temp->id, id);	// 노드 구조체의 멤버변수 id에 저장
		fscanf(fp, "%s", temp->name);	//이름을 노드 구조체의 멤버변수 name에 저장
		temp->left = NULL;	// 자식, 부모노드는 아직 모르기에 NULL 저장 
		temp->right = NULL;
		temp->parent = NULL;

		//printf("%s %s\n", temp->id, temp->name); // 저장이 잘 되었는지 확인 
		insert_node(&root, temp);	//노드 구조체를 이진트리에 삽입 
	}
	fclose(fp);

	// 이진트리 활용 프로그램 시작 
	int menu = 0; //메뉴 번호를 저장하는 변수
	while (menu != 8) {
		printf("1: 전체 노드 프린트(중위운행)\n");
		printf("2: 전위운행\n");
		printf("3: 후위운행\n");
		printf("4: 학번으로 정보 검색하기\n");
		printf("5: 노드 삭제하기\n");
		printf("6: 프로그램 종료\n");
		printf("메뉴를 선택하세요! >> ");
		scanf("%d", &menu);

		if (menu == 1) {	// 중위순회
			in_order(root);
		}

		else if (menu == 2) {	// 전위순회
			pre_order(root);
		}

		else if (menu == 3) {	// 후위순회
			post_order(root);
		}

		else if (menu == 4) {	// 키 입력받아서 해당 학생의 정보 출력하기 
			printf("input id for search!!\n");
			scanf("%s", id);

			find = btsearch(root, id);	// 키가 어느 구조체에 있는지, 구조체 주소를 find에 반환
			if (find == NULL)
				printf("not found!\n");
			else
				print_node(find);
		}

		else if (menu == 5) {	// 키를 입력받아 노드 삭제하기 
			printf("삭제할 부모 노드의 키(학번)을 입력하세요! >> ");
			scanf("%s", id);

			find = btsearch(root, id);	// 키가 어느 구조체에 있는지, 구조체 주소를 find에 반환
			if (find == NULL)
				printf("not found!\n");
			else
				delete(find);
		}

		else if (menu == 6) {	// 프로그램 종료
			exit(1);
		}

		else {	//입력 오류
			printf("숫자를 다시 입력해주셔야 합니다. 아무 숫자를 누른 뒤 메뉴를 실행하세요!\n");
			scanf("%d", &menu);
		}
		printf("\n");
	}
}


/*------------------ 함수정의------------------*/
void insert_node(STUDENT** root, STUDENT* node) { //왜 이중포인터 root씀? -> strcopy를 5번이나 해야해서? 
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

	else if (strcmp(cur->id, node->id) > 0) { //if (strcmp(cur->id, node->id) > 0)
		if (cur->left != NULL)
			insert_node(&cur->left, node);
		else {
			cur->left = node;
			node->parent = cur;
		}
	}
}

void print_node(STUDENT* node) {
	printf("%s %s	부모노드: %s\n", node->id, node->name, node->parent);
}

void in_order(STUDENT* node) {
	if (node == NULL)	// 빈 이진트리
		return;
	in_order(node->left);
	print_node(node);	// root부터 출력해야겠네 -> 즉슨 매개변수 node는 거의 rootnode라고 해도 무방하겠네 
	in_order(node->right);
}

void pre_order(STUDENT* node) {
	if (node == NULL)
		return;
	print_node(node);	// root부터 출력해야 전체 노드가 출력되겠네 -> 매개변수 node는 거의 rootnode로 받아야한다고 해도 무방하겠네 
	pre_order(node->left);
	pre_order(node->right);
}

void post_order(STUDENT* node) {
	if (node == NULL)
		return;
	post_order(node->left);
	post_order(node->right);
	print_node(node);
}


void delete(STUDENT* node) {
/*
	노드를 삭제할 때는 기본적으로 세 가지를 고려해야 한다.
1.	삭제노드의 자식노드 parent를 바꾸었는지 
2.	삭제노드의 부모노드 right or left를 바꾸었는지
3.	free로 삭제노드 메모리 해제시키기
*/
	STUDENT* delete_parent;	// 삭제할 노드의 부모노드 포인터
	delete_parent = node->parent;


	// 자식노드가 없을 때 
	if (node->left == NULL && node->right == NULL) {
		printf("자식의 양쪽 노드가 존재하지 않습니다. %s %s노드를 삭제하겠습니다.\n", node->id, node->name);

		if (delete_parent->left == node) {
			delete_parent->left = NULL; //부모노드의 left NULL처리
		}
		else if (delete_parent->right == node) {
			delete_parent->right = NULL;
		}
		free(node);
	}

	// 자식노드가 있을 때
	else {
		/*-------------------자식노드가 한 개일 때-------------------*/
		// 자식 노드가 왼쪽에만 있을 때(자식노드 하나)
		if (node->right == NULL) {
			printf("자식 노드가 하나뿐입니다.\n");
			STUDENT* ltemp = node->left;

				if (delete_parent->left == node) {
					delete_parent->left = node->left; //부모노드의 left NULL처리
					ltemp->parent = delete_parent;
					free(node);
				}
				else if (delete_parent->right == node) {
					delete_parent->right = node->left; //부모노드의 left NULL처리
					ltemp->parent = delete_parent;
					free(node);
				}
			}		

		// 자식 노드가 오른쪽에만 있을 때(자식노드 하나)
		else if (node->left == NULL) {
			printf("자식 노드가 하나뿐입니다.\n");
			STUDENT* rtemp = node->right;
				if (delete_parent->left == node) {
					delete_parent->left = node->right; //부모노드의 left NULL처리
					rtemp->parent = delete_parent;	//자식노드의 parent를 노드의 부모노드로
					free(node);	//메모리 해제
				}
				else if (delete_parent->right == node) {
					delete_parent->right = node->right; //부모노드의 left NULL처리
					rtemp->parent = delete_parent;
					free(node);
			}
		}


		/*-------------------자식노드가 두 개일 때-------------------*/
		// 노드를 삭제할 때는 기본적으로 세 가지를 고려하되, 
		// 다른 케이스들과 다르게 삭제노드는 삭제할 값이 들어있는 노드가 아닌, 
		// 삭제값보다 큰값 중 가장 작은 값이 있는 노드이다.
		// 삭제값이 있는 노드를 지워버리게 되면 트리가 무너지기 때문이다. 
		
		//자식 노드가 둘다 있을 때 (자식노드 두개)
		//루트노드에서 가장 가까운 오른쪽을 올리기로 했다! (원래는 가장 가까운 왼쪽을 올려도 됨)
		else {
			STUDENT* ltemp = node->left;
			STUDENT* rtemp = node->right;
			STUDENT* parent_endtemp;	//가장 왼쪽노드의 부모노드  
			STUDENT* endtemp;	//가장 왼쪽노드

			if (rtemp->left == NULL) {	// right의 왼쪽 노드가 없다면 오른쪽 노드가 바로 올라감
				strcpy(node->id, rtemp->id);	//내용을 삭제할 노드에 삭제값과 가장 근접한 오른쪽 값을 복사해준다.
				strcpy(node->name, rtemp->name);
				if (rtemp->right == NULL) {	// 복사된 노드에 오른쪽 노드가 없으면 부모노드는 바꿀 게 없고, node의 자식노드만 NULL로 처리해주면 된다.  
					node->right = NULL;
				}
				else {	//복사된 노드에 오른쪽 노드가 있으면 부모노드와 자식노드를 알맞게 바꾼다. 
					node->right = rtemp->right;
					STUDENT* rtemp_right;
					rtemp_right = rtemp->right;
					rtemp_right->parent = node;
				}
				free(rtemp);	//복사된 노드가 메모리 해제됨
			}
			else { // right의 왼쪽 노드가 있다면 가장 왼쪽 노드(삭제값보다 크지만 가장 작은 값)로 가서 걔가 올라감
				endtemp = rtemp;
				while (endtemp->left != NULL) {	// 가장 왼쪽 노드 찾기
					endtemp = endtemp->left;
				}
				strcpy(node->id, endtemp->id);	// 삭제값이 있는 노드가 메모리해제되는게 아니라 맨 왼쪽의 노드가 메모리해제되는 거라 복사하는 거임
				strcpy(node->name, endtemp->name);
				parent_endtemp = endtemp->parent;
				parent_endtemp->left = NULL;
				free(endtemp);
			}
		}
	}
}

STUDENT* btsearch(STUDENT* root, char* key) {
	if (root == NULL)
		return NULL;

	if (!strcmp(root->id, key)) // 한 번에 id랑 key랑 일치하면, 더 이상 더 찾을 필요없쥐~ 찾은 키가 있는 주소를 반환해 
		return root;
	else if (strcmp(root->id, key) > 0) { // root가 더 크면! root기준 왼쪽만 탐색하면 돼 
		btsearch(root->left, key);	// !strcmp(root->id, key)일 때까지 반복!
	}
	else { //(strcmp(root->id, key) < 0) // root가 더 작으면! root 오른쪽만 탐색하면 돼 
		btsearch(root->right, key);
	}
}

