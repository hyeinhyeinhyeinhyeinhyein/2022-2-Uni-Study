#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TOKEN " .-_:;*&^%"


void main() {
	char line[100]; // 정보를 입력받을 한 줄
	gets(line); // gets함수로 정보를 입력 받음

	char* token1; // 전화번호 토큰(1)
	char* token2; // 전화번호 토큰(2)
	char* token3; // 전화번호 토큰(3)
	char number_token[12]={NULL,}; // 11+1(NULL값)

	int i = 0; //전화번호를 전화번호 저장 문자배열인  number_token[11]에 넣을 때 필요한 인덱스

  	token1 = strtok(line, TOKEN);
		printf("%s", token1);

		for (i = 0; i < strlen(token1); i++) {
			number_token[i] = token1[i];
		}
		int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!


		token2 = strtok(NULL, TOKEN);
		printf("%s", token2);


		int ii = 0;
		for (i = j; i < j+strlen(token2); i++) {
			number_token[i] = token2[ii];
			ii++;
		}
		int k = j + strlen(token2);


		ii = 0;
		token3= strtok(NULL, TOKEN);
		printf("%s", token3);
		for (i = k; i < k+strlen(token3); i++) {
			number_token[i] = token3[ii];
			ii++;
		}

		puts("\n");

		printf("number_toekn에 저장된 전화번호: %s", number_token);

}
