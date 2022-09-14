// 미완성
// 60. 문자열을 비교하는 함수 만들기 (strcmp함수를 사용자 정의 함수로 작성)

#include <stdio.h>

#define MY "my"

int My_strcmp(const char* strin1, const char* strin2); 

int main() {
	char string[100];
	int ret;

	printf("영단어를 입력한 후 Enter키를 치세요!\n");
	printf("my를 입력하면 프로그램이 종료됩니다.\n");

	do {
		gets(string);

		ret = strcmp(string, MY);
		
		if (ret == 0) 
		{
			printf("%s == %s, ret = %d\n", string, MY, ret);
			break;
		}
		else if(ret < 0) 
			printf("%s < %s, ret = %d\n", string, MY, ret);
		else 
			printf("%s > %s, ret = %d\n", string, MY, ret); 
	} while (1);
}

int My_strcmp(const char* string1, const char* string2) {
// string1이 가리키는 참조값과 string2이 가리키는 참조값이 같은지 판단 
	if (*string1 == (int)NULL && *string2 == (int)NULL) 
		return 0;

// string1이 가리키는 참조값이  NULL값이 될 때까지
	while (*string1 != (int)NULL) {

// string2이 가리키는 참조값이 NULL일 때 1을 반환 
		if (*string2 == (int)NULL)
			return 1;

// string1이 가리키는 참조값과 string2이 가리키는 참조값이 같을 때는 
		if (*string1 == *string2) {
			string1++;
			string2++;
			continue;
		}

		if (*string1 < *string2)
			return -1;
		else return 1;
	}

	if (*string2 != (int)NULL)
		return -1;

	return 0;
}
