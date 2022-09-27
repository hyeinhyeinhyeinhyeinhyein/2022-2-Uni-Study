#include <stdio.h>
#include <string.h>

#define TOKEN ", "
#define FIND_CHAR '-'

int main() {
	char strary[150]; //gets함수로 입력받을 문자 배열 


	char* token; // 토큰 포인터 생성
	int i = 0;	// 토큰을 돌면서 배열에 저장할 때 사용하는 인덱스 변수


	printf("학번, 이름, 전화번호를 입력해주세요.\n");
	gets(strary);	// gets함수로 문자열을 입력받는다. 그 문자열은 strary에 저장된다. 

	token = strtok(strary, TOKEN);	// strary 문자배열이 TOKEN을 만났을 때 분리된다.
	printf("학번 ");
	printf("%s\n", token);	// token에 학번만 남음


	char* token2 = strtok(NULL, TOKEN);	// 학번 뒤의 구분자에서 잘린 곳부터 또 토큰화한다. 
	printf("이름 ");
	printf("%s\n", token2); // token2에 이름만 남음

	char* token3 = strtok(NULL, TOKEN); // 
	printf("전화번호 ");
	//	printf("%s", token3);

	char numberbox[20];
	for (int i = 0; i < 20; i++){
		if (*(token3 + i) == 0 || *(token3 + i) == 1 || *(token3 + i) == 2 || *(token3 + i) == 3 || *(token3 + i) == 4 || *(token3 + i) == 5 || *(token3 + i) == 6 || *(token3 + i) == 7 || *(token3 + i) == 8 || *(token3 + i) == 9)
		{
			numberbox[i] = *(token3 + i);
			printf("%c", numberbox[i]);
		}
	}

	
}
