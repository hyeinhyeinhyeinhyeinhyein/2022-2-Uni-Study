// 한 번에 입력받은 문자열을 토큰화하기
#include <stdio.h>
#include <string.h>

#define TOKEN ", "

int main() {
	char strary[150]; //gets함수로 입력받을 문자 배열 
	char sstrary[150];

	char* token; // 토큰 포인터 생성
	char* name;

	int i = 0;	// 토큰을 돌면서 배열에 저장할 때 사용하는 인덱스 변수
	char* storage[100] = { NULL, };	// 잘린 토큰의 주소값을 저장하는 포인터 배열 

	printf("학번, 이름, 전화번호를 입력해주세요.\n");
	gets(strary);	// gets함수로 문자열을 입력받는다. 그 문자열은 strary에 저장된다. 

	token = strtok(strary, TOKEN);	// strary 문자배열이 TOKEN을 만났을 때 분리된다.
	printf("학번 ");
	printf("%s\n", token);	// token에 학번만 남음
	

	char *token2 = strtok(NULL, TOKEN);	// 학번 뒤의 구분자에서 잘린 곳부터 또 토큰화한다. 
	printf("이름 ");
	printf("%s\n", token2); // token2에 이름만 남음

	char* token3 = strtok(NULL, TOKEN);
	printf("전화번호 ");
	printf("%c%c%c-%c%c%c%c-%c%c%c%c", token3[0], token3[1], token3[2], token3[4], token3[5], token3[6], token3[7], token3[9], token3[10], token3[11], token3[12]);
	
}
