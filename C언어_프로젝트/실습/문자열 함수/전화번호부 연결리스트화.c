// insert함수에서 오류가 남 -> 수정 필요
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN " .-+_:;*&^%" // 전화번호를 저장할 때 어디에서 토큰화할지 기준이 되는 기호 모음 
#define FTOKEN "\t" // 파일에서 입력받은 줄을 토큰화할 때 필요함

// 정보를 저장할 구조체
typedef struct Phonebook {
	char bookname[30];
	char bookphone[20];
	char bookaddress[100];
	struct Phonebook* link;
}Phonebook;

void tokenize(char* statement, Phonebook* head);
Phonebook* insert(Phonebook* head, char* name, char* phone, char* address);
Phonebook* search(Phonebook* head, char* key);
Phonebook* delete(Phonebook* head, char* key);

void main() {
	Phonebook* head = NULL;
	char line[100]; // 정보를 입력받을 한 줄

	FILE* fp; // 전화번호부 파일 포인터 
	char* path = "c:\\temp\\address.txt"; // 전화번호부가 저장될 위치
	char buffer[100]; // 파일 내용을 출력할 때 필요한 버퍼 

	// 파일에서 내용을 읽어올 때 이용하는 토큰들
	char* fname;	// 파일에서 fgets로 받아왔을 때 첫 토큰이 이름일텐데, 이름을 가리키는 문자열 포인터 
	char* fnumber;	// 파일에서 fgets로 받아왔을 때 두 번째 토큰이 전화번호일텐데, 전화번호를 가리키는 문자열 포인터 
	char* faddress;		// 파일에서 fgets로 받아왔을 때 세 번째 토큰이 주소일텐데, 주소를 가리키는 문자열 포인터 

	if (_access(path, 0) == 0)	// address.txt가 존재하면
	{
		fp = fopen("c:\\temp\\address.txt", "r");	// address.txt 파일을 연다

		while (!feof(fp)) { // 파일 포인터가 파일의 끝을 가리키기 전까지 아래의 동작을 반복
			fgets(buffer, 100, fp);	// 한 줄씩(최대 99byte) 문자열 버퍼에 저장 

			fname = strtok(buffer, FTOKEN);	// 버퍼에 저장된 문자열을 \t를 기준으로 토큰화한다. 첫 번째 토큰화된 문자열은 이름
			fnumber = strtok(NULL, FTOKEN); // 두 번째 토큰화된 문자열은 전화번호
			faddress = strtok(NULL, FTOKEN); // 세 번째 토큰화된 문자열은 주소 
			// 사실 메모리 덜 차지하게 하나의 char*로 써도 되긴하지만 가독성이 더 나은 것 같아 이렇게 함

			insert(head, fname, fnumber, faddress);
		}
		fclose(fp); // 파일에서 다 읽어왔으면 파일을 닫음
	}


	int menu = 0;
	while (menu != 5) {
		printf("메뉴를 입력하세요. 추가(1), 삭제(2), 탐색(3), 출력(4), 종료(5) >> ");
		scanf("%d", &menu);

		if (menu == 1) //연결리스트 항목 추가하기
		{
			gets(line);
			tokenize(line, head);
		}

		else if (menu == 2)
		{
			char search_name[10];
			printf("삭제할 키(이름)을 입력하세요. >> ");
			scanf("%s", search_name);
			delete(head, search_name);
		}
		else if (menu == 3)
		{
			char search_name[10];
			printf("탐색할 키(이름)을 입력하세요. >> ");
			scanf("%s", search_name);
			search(head, search_name);
		}
		else if (menu == 4)
		{
			fp = fopen("c:\\temp\\address.txt", "w");	
			Phonebook* next = head->link;
			while (next != NULL) {
				fprintf(fp, "%s\t", next->bookname);
				fprintf(fp, "%s\t", next->bookphone);
				fprintf(fp, "%s\t\n", next->bookaddress);
				next = next->link;
			}
			fclose(fp);
		}
	}
}

void tokenize(char* statement, Phonebook* head) {

	// line에 실제로 저장된 byte 크기, 위치X(위치는 -1)
	int number_of_characters = 0;

	char number_token[12] = { NULL }; // 전화번호 저장 문자 배열, 11+1(NULL값)
	char address[70] = { NULL }; //주소 저장 문자 배열
	char name[7] = { NULL }; // 이름 저장 문자 배열, 배열 크기가 7인 이유는 (이름3글자*한글이 2byte)+NULL(1) = 7

	char* token1; // 전화번호 토큰(1)
	char* token2; // 전화번호 토큰(2)
	char* token3; // 전화번호 토큰(3)

	// 주소인지 확인할 때 사용할 정보 
	char* city1 = strstr(statement, "서울");
	char* city2 = strstr(statement, "경기");
	char* city3 = strstr(statement, "인천");
	char* city4 = strstr(statement, "강원");
	char* city5 = strstr(statement, "충청");
	char* city6 = strstr(statement, "경상");
	char* city7 = strstr(statement, "전라");
	char* city8 = strstr(statement, "제주");
	char* city9 = strstr(statement, "세종");
	char* city10 = strstr(statement, "대전");
	char* city11 = strstr(statement, "대구");
	char* city12 = strstr(statement, "부산");
	char* city13 = strstr(statement, "울산");
	char* city14 = strstr(statement, "광주");

	int number_of_address = 0; // address에 실제로 저장된 주소 길이

	int i = 0; // 전화번호를 전화번호 저장 문자배열인  number_token[12]에 넣을 때 필요한 인덱스
	int u = 0; // 이름을 이름 저장 문자배열인 name[7]에 넣을 때 필요한 인덱스 
	int m = 0; // 주소를 주소 저장 문자배열인 address[70]에 넣을 때 필요한 인덱스 

	// 총 바이트 구하기
	for (int number = 0; number < 100; number++) {
		if (statement[number] != NULL)
			number_of_characters++;
		else break;
	}

	/*-----------------------------------------------------------------------------------------------------*/
	// 전화번호로 시작하는지 확인(숫자로 시작하는지 확인하면 됨)
	if (statement[0] == '0' || statement[0] == '1' || statement[0] == '2' || statement[0] == '3' || statement[0] == '4' || statement[0] == '5' || statement[0] == '6' || statement[0] == '7' || statement[0] == '8' || statement[0] == '9') {

		// 숫자 다음에는 무조건 문자가 나올 것임
		// 그 문자가 주소의 첫 글자인지, 이름의 첫 글자인지 파악해야 함

		/*=============================전화번호-주소-이름=============================*/
		if ((city1 - statement) == 14 || (city2 - statement) == 14 || (city3 - statement) == 14 || (city4 - statement) == 14 || (city5 - statement) == 14 || (city6 - statement) == 14 || (city7 - statement) == 14 || (city8 - statement) == 14 || (city9 - statement) == 14 || (city10 - statement) == 14 || (city11 - statement) == 14 || (city12 - statement) == 14 || (city13 - statement) == 14 || (city14 - statement) == 14) {

			//이름 저장
			for (int number = number_of_characters - 6; number <= number_of_characters - 1; number++) {
				name[u] = statement[number];
				u++;
			}

			// 주소 저장
			for (int number = 14; number <= number_of_characters - 8; number++) { // null문자(1), 이름 (3*2=6), 띄어쓰기(1) 전까지 주소가 저장되어있음
				address[m] = statement[number]; // line에서 받은 주소를 주소 배열에 저장하기 
				m++;
				number_of_address++; // 주소 몇 바이트인지
			}
		}
		/*=============================전화번호-이름-주소=============================*/
		else {
			// 이름 저장하기
			for (int number = 14; number <= 19; number++) {
				name[u] = statement[number];
				u++;
			}

			// 주소 저장하기
			for (int number = 21; number <= number_of_characters; number++) {
				address[m] = statement[number];
				m++;
			}
		}

		// 전번 저장
		token1 = strtok(statement, TOKEN); // 010

		for (i = 0; i < strlen(token1); i++) { // 전화번호 배열에 번호 저장
			number_token[i] = token1[i];
		}

		int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!
		token2 = strtok(NULL, TOKEN);
		int ii = 0;
		for (i = j; i < j + strlen(token2); i++) {
			number_token[i] = token2[ii];
			ii++;
		}

		int k = j + strlen(token2);
		token3 = strtok(NULL, TOKEN);
		ii = 0;
		for (i = k; i < k + strlen(token3); i++) {
			number_token[i] = token3[ii];
			ii++;
		}
	}

	/*=============================문자로 시작=============================*/
	else {	// 주소로 시작하는지 확인
		/*=============================주소로 시작=============================*/
		if (city1 - statement == 0 || city2 - statement == 0 || city3 - statement == 0 || city4 - statement == 0 || city5 - statement == 0 || city6 - statement == 0 || city7 - statement == 0 || city8 - statement == 0 || city9 - statement == 0 || city10 - statement == 0 || city11 - statement == 14 || city12 - statement == 0 || city13 - statement == 0 || city14 - statement == 0) {

			// 가장 마지막에 써진 문자가 숫자면 주소-이름-전화번호 확정
			/*=============================주소-이름-전화번호=============================*/
			if (statement[number_of_characters - 1] == '0' || statement[number_of_characters - 1] == '1' || statement[number_of_characters - 1] == '2' || statement[number_of_characters - 1] == '3' || statement[number_of_characters - 1] == '4' || statement[number_of_characters - 1] == '5' || statement[number_of_characters - 1] == '6' || statement[number_of_characters - 1] == '7' || statement[number_of_characters - 1] == '8' || statement[number_of_characters - 1] == '9') {

				// 주소 저장하기 + 주소 크기(바이트) 계산
				//띄어쓰기(1) 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1) 
				for (int number = 0; number <= number_of_characters - 21; number++) {
					address[m] = statement[number];
					m++;
					number_of_address++;
				}

				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = number_of_characters - 20; number <= number_of_characters - 15; number++) {
					name[u] = statement[number];
					u++;
				}

				// 전화번호 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 13; number < number_of_characters; number++) {
					temp_phonenumber[r] = statement[number];
					r++;
				}

				temp_phonenumber[13] = NULL;

				token1 = strtok(temp_phonenumber, TOKEN);
				for (i = 0; i < strlen(token1); i++) {
					number_token[i] = token1[i];
				}

				int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!
				token2 = strtok(NULL, TOKEN);
				int ii = 0;
				for (i = j; i < j + strlen(token2); i++) {
					number_token[i] = token2[ii];
					ii++;
				}

				int k = j + strlen(token2);
				token3 = strtok(NULL, TOKEN);
				ii = 0;
				for (i = k; i < k + strlen(token3); i++) {
					number_token[i] = token3[ii];
					ii++;
				}
			}

			/*=============================주소-전화번호-이름=============================*/
			else {

				// 주소 저장하기 + 주소 길이 계산
				// 주소(?) 띄어쓰기(1) 전화번호(13) 띄어쓰기(1) 이름(6) 널문자(1)
				for (int number = 0; number <= number_of_characters - 22; number++) {
					address[m] = statement[number];
					m++;
					number_of_address++;
				}

				// 이름 저장하기
				// 이름(3*2=6) 널문자(1)
				for (int number = number_of_characters - 6; number <= number_of_characters - 1; number++) {
					name[u] = statement[number];
					u++;
				}

				// 전번 저장
				// 전화번호(13) 띄어쓰기(1) 이름(6) 널문자(1)
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 20; number <= number_of_characters - 8; number++) {
					temp_phonenumber[r] = statement[number];
					r++;
				}

				temp_phonenumber[13] = NULL;

				token1 = strtok(temp_phonenumber, TOKEN);

				for (i = 0; i < strlen(token1); i++) {
					number_token[i] = token1[i];
				}
				int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!


				token2 = strtok(NULL, TOKEN);

				int ii = 0;
				for (i = j; i < j + strlen(token2); i++) {
					number_token[i] = token2[ii];
					ii++;
				}
				int k = j + strlen(token2);

				ii = 0;
				token3 = strtok(NULL, TOKEN);

				for (i = k; i < k + strlen(token3); i++) {
					number_token[i] = token3[ii];
					ii++;
				}
			}
		}

		/*=============================이름으로 시작=============================*/
		else {

			/*=============================이름-전화번호-주소=============================*/
			if (statement[9] == '0' || statement[9] == '1' || statement[9] == '2' || statement[9] == '3' || statement[9] == '4' || statement[9] == '5' || statement[9] == '6' || statement[9] == '7' || statement[9] == '8' || statement[9] == '9') {

				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = 0; number <= 5; number++) {
					name[u] = statement[number];
					u++;
				}

				// 전번 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = 7; number <= 20; number++) {
					temp_phonenumber[r] = statement[number];
					r++;
				}
				temp_phonenumber[13] = NULL;

				// 주소 저장하기 + 주소 길이 계산
				for (int number = 21; number <= number_of_characters; number++) {
					address[m] = statement[number];
					m++;
					number_of_address++;
				}

				token1 = strtok(temp_phonenumber, TOKEN);

				for (i = 0; i < strlen(token1); i++) {
					number_token[i] = token1[i];
				}
				int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!

				token2 = strtok(NULL, TOKEN);

				int ii = 0;
				for (i = j; i < j + strlen(token2); i++) {
					number_token[i] = token2[ii];
					ii++;
				}
				int k = j + strlen(token2);

				ii = 0;
				token3 = strtok(NULL, TOKEN);

				for (i = k; i < k + strlen(token3); i++) {
					number_token[i] = token3[ii];
					ii++;
				}
			}
			/*=============================이름-주소-전화번호=============================*/
			else
			{
				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = 0; number <= 5; number++) {
					name[u] = statement[number];
					u++;
				}

				// 주소 저장하기 + 주소 길이 계산
				for (int number = 7; number <= number_of_characters - 14; number++) {
					address[m] = statement[number];
					m++;
					number_of_address++;
				}

				// 전번 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 13; number < number_of_characters; number++) {
					temp_phonenumber[r] = statement[number];
					r++;
				}
				temp_phonenumber[13] = NULL;

				token1 = strtok(temp_phonenumber, TOKEN);

				for (i = 0; i < strlen(token1); i++) {
					number_token[i] = token1[i];
				}
				int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!

				token2 = strtok(NULL, TOKEN);

				int ii = 0;
				for (i = j; i < j + strlen(token2); i++) {
					number_token[i] = token2[ii];
					ii++;
				}
				int k = j + strlen(token2);

				ii = 0;
				token3 = strtok(NULL, TOKEN);
				for (i = k; i < k + strlen(token3); i++) {
					number_token[i] = token3[ii];
					ii++;
				}
			}
		}
	}
	insert(head, name, number_token, address);
	printf("\n\n");
}

Phonebook* insert(Phonebook* head, char* name, char* phone, char* address) {

	if (head == NULL) //아무것도 없는 연결리스트일 때
	{
		Phonebook* p = (Phonebook*)malloc(sizeof(Phonebook));
		head = p;
		strcpy(p->bookname, name);
		strcpy(p->bookphone, phone);
		strcpy(p->bookaddress, address);
		p->link = NULL;
	}

	else {
		Phonebook* next = head->link;
		Phonebook* pre = head;
		while (strcmp(name, head->bookname) > 0) { //삽입하려는 이름을 첫 리스트부터 비교하는데, 삽입 이름이 더 크면 뒤로 가야쥐
			pre = head;
			head = head->link;
		}

		Phonebook* p = (Phonebook*)malloc(sizeof(Phonebook));
		strcpy(p->bookname, name);
		strcpy(p->bookphone, phone);
		strcpy(p->bookaddress, address);

		p->link = head;
		pre->link = p;
	}

	return head;
}

Phonebook* search(Phonebook* head, char* key) {
	Phonebook* current = head;
	while (head->bookphone != key)
		current = current->link;
	return current;
}

Phonebook* delete(Phonebook* head, char* key) {
	Phonebook* current = head;
	Phonebook* pre = head;
	while (head->bookphone != key)
	{
		pre = current;
		current = current->link;
	}
	free(current);
	return pre;
}
