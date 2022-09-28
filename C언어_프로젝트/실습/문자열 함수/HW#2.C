#include <stdio.h>
#include <string.h>

#define TOKEN ", "
#define FIND_CHAR '-'

int main() {
	char strary[150]; //gets함수로 입력받을 문자 배열 
	char phonenumber[100];


	char* token; // 토큰 포인터 생성


	printf("이름, 주소, 전화번호를 입력해주세요.\n");
	gets(strary);	// gets함수로 문자열을 입력받는다. 그 문자열은 strary에 저장된다. 


	//전화번호를 먼저 입력했는지 확인할 때 필요한 것들
	char* numberSet = "0123456789";	// 숫자인지 확인하는 세트
	char* notNumberSet = "0123456789 ,.~!@#$%^&*()_+-={}[]:;'<>./?";	//문자임을 확인하고 싶을 때 사용하는 세트
	unsigned int position;	//숫자의 위치를 strcspn으로 반환받기 위해 할당한 변수 
	position = strcspn(strary, numberSet);

	unsigned int notPosition; // 숫자로 시작했으니(전화번호), 문자가 시작되는 위치를 반환받기 위한 할당한 변수 
	notPosition = strspn(strary, notNumberSet); 




	/********************숫자를 먼저 입력했을 경우***********************/

	if (position == 0) { //전화번호를 먼저 입력한 경우
		for (int i = 0; i < 13; i++) {
			phonenumber[i] = strary[i];
		}

		// 시/도 시/군/구 읍/면/동이 어디에 위치하는지 strstr로 파악할건데, 그때 필요한 변수들을 정의

		char* siret;	//'시'가 어디에 있는지 메모리 위치를 반환하는 포인터 변수 
		siret = strstr(strary, "시"); 
		int siretvalue = siret - strary; // 시가 있는 메모리 위치에서 strary의 시작위치를 빼면, strary 중 어디에 위치하는지 파악할 수 있다. 

		char* doret;
		doret = strstr(strary, "도");
		int doretvalue = doret - strary;

		char* gunret;
		gunret = strstr(strary, "군");
		int gunretvalue = gunret - strary;

		char* guret;
		guret = strstr(strary, "구");
		int guretvalue = guret - strary;

		char* epret;
		epret = strstr(strary, "읍");
		int epretvalue = epret - strary;

		char* myeonret;
		myeonret = strstr(strary, "면");
		int myeonretvalue = myeonret - strary;

		char* dongret;
		dongret = strstr(strary, "동");
		int dongretvalue = dongret - strary;

		// 전화번호 다음에 주소를 작성한 것인지 확인
		// 시도 다음에 구군인지 확인
		if ((siretvalue > 0 && siretvalue < 20) || (doretvalue > 0 && doretvalue < 20)) { // 줄에서 '시'나 '도'가 있으면 번호 다음이 주소일 것으로 추측, 이름일수도 있으니 재검토

			{if (gunretvalue > siretvalue || guretvalue > siretvalue || gunretvalue > doretvalue || guretvalue > doretvalue || siretvalue > 16) {

				if (epretvalue > siretvalue || epretvalue > gunretvalue || epretvalue > guretvalue) {//읍으로 끝나면 

					//모든 조건 만족하면 전화번호-주소-이름 확정


					// 이제 이름, 전화번호, 주소 출력 
					int controlnumber = 0;
					for (int i = 0; strary[i] != NULL; i++) {
						controlnumber = controlnumber + 1;
					}

					printf("이름: ");
					for (int i = 6; i > 0; i--) {	// 뒤에서 한글 3글자 이름 갖고 오기 
						printf("%c", strary[controlnumber - i]);
					}
					puts("");

					printf("주소: ");
					for (int i = notPosition; i < controlnumber - 6 + 1; i++) { // 문자로 시작하는 곳부터 뒤에 이름(6바이트) 전까지 주소로 보고 출력
						printf("%c", strary[i]);
					}
					puts("");

					printf("전화번호: ");	// 앞에서 부터 13자리가 전화번호
					for (int i = 0; i < 13; i++) {
						printf("%c", phonenumber[i]);
					}
					puts("");



				}

				else if (myeonretvalue > siretvalue || myeonretvalue > gunretvalue || myeonretvalue > guretvalue) { // 면으로 끝나면 

					//모든 조건 만족하면 전화번호-주소-이름 확정 (읍으로 끝날 때와 동일함) 
						
					// 이름, 전화번호, 주소 출력 
					int controlnumber = 0;
					for (int i = 0; strary[i] != NULL; i++) {
						controlnumber = controlnumber + 1;
					}

					printf("이름: ");

					for (int i = 6; i > 0; i--) {	// 뒤에서 한글 3글자 이름 갖고 오기 
						printf("%c", strary[controlnumber - i]);
					}
					puts("");

					printf("주소: ");
					for (int i = notPosition; i < controlnumber - 6 + 1; i++) {
						printf("%c", strary[i]);
					}
					puts("");

					printf("전화번호: ");
					for (int i = 0; i < 13; i++) {
						printf("%c", phonenumber[i]);
					}
					puts("");
				}

				else  if (dongretvalue > siretvalue || dongretvalue > gunretvalue || dongretvalue > guretvalue) { // 동으로 끝나면 

					//모든 조건 만족하면 전화번호-주소-이름 확정 (읍, 면으로 끝날 때와 동일함) 
					
					// 이름, 전화번호, 주소 출력 

					int controlnumber = 0;
					for (int i = 0; strary[i] != NULL; i++) {
						controlnumber = controlnumber + 1;
					}

					printf("이름: ");

					for (int i = 6; i > 0; i--) {	// 뒤에서 한글 3글자 이름 갖고 오기 
						printf("%c", strary[controlnumber - i]);
					}
					puts("");

					printf("주소: ");
					for (int i = notPosition; i < controlnumber - 6 + 1; i++) {
						printf("%c", strary[i]);
					}
					puts("");

					printf("전화번호: ");
					for (int i = 0; i < 13; i++) {
						printf("%c", phonenumber[i]);
					}
					puts("");
				}

			}


			}

		}


		else { // 주소 조건을 만족하지 않을 때, 결국 전화번호-이름-주소 확정


		// 이름, 주소, 전화번호 출력 
			int controlnumber = 0;
			for (int i = 0; strary[i] != NULL; i++) {	
				controlnumber = controlnumber + 1;
			}

			printf("\n이름: ");
			for (int i = notPosition; i < notPosition + 6; i++) {	// 전화번호 다음 문자인 것의 위치를 notPosition이라고 함, 그것은 이름의 시작 위치가 됨
				printf("%c", strary[i]);
			}
			puts("");

			printf("주소: ");
			for (i = notPosition + 6; i < controlnumber + 1; i++) {	//이름이 끝나고 문자열이 끝날 때까지는 주소로 판단
				printf("%c", strary[i]);
			}
			puts("");

			printf("전화번호: ");		
			for (int i = 0; i < 13; i++) { // 앞에 13자리 출력
 				printf("%c", phonenumber[i]);
			}
			puts("");

		}


	}

	/********************문자를 먼저 입력했을 경우***********************/
	else {  //if(position != 0) 숫자의 첫위치가 0이 아닐 때 = 문자로 시작할 때 
		char* siret;
		siret = strstr(strary, "시");
		int siretvalue = siret - strary;

		char* doret;
		doret = strstr(strary, "도");
		int doretvalue = doret - strary;

		char* gunret;
		gunret = strstr(strary, "군");
		int gunretvalue = gunret - strary;

		char* guret;
		guret = strstr(strary, "구");
		int guretvalue = guret - strary;

		char* epret;
		epret = strstr(strary, "읍");
		int epretvalue = epret - strary;

		char* myeonret;
		myeonret = strstr(strary, "면");
		int myeonretvalue = myeonret - strary;

		char* dongret;
		dongret = strstr(strary, "동");
		int dongretvalue = dongret - strary;



		// 문자 길이 확인
		int controlnumber = 0;
		for (int i = 0; strary[i] != NULL; i++) {
			controlnumber = controlnumber + 1;
		}

		// 시도 다음에 구군인지 확인

		if ((siretvalue > 0 && siretvalue < 7) || (doretvalue > 0 && doretvalue < 7)) { // 줄에서 '시'나 '도'가 있으면 번호 다음이 주소일 것으로 추측, 이름일수도 있으니 재검토

			{if (gunretvalue > siretvalue || guretvalue > siretvalue || gunretvalue > doretvalue || guretvalue > doretvalue || siretvalue > 16) {

				if (epretvalue > siretvalue || epretvalue > gunretvalue || epretvalue > guretvalue) {//읍으로 끝나면 

					// 그 다음이 이름인지 전화번호인지 (숫자인지 아닌지 확인)
					//전화번호가 끝에 있을 경우 
					
					// 맨 끝의 문자가 숫자일 경우 주소-이름-전화번호가 될 것임 
					// 아래의 조건을 만족하면 주소-이름-전화번호인지 확정
					if (strary[controlnumber] == 0 || strary[controlnumber] == 1 || strary[controlnumber] == 2 || strary[controlnumber] == 3 || strary[controlnumber] == 4 || strary[controlnumber] == 5 || strary[controlnumber] == 0 || strary[controlnumber] == 6 || strary[controlnumber] == 7 || strary[controlnumber] == 8 || strary[controlnumber] == 9)
					{

						//주소가 어디서 끝날지 모르니, 뒤에서 글자수를 세는 걸로 한다. 
						printf("이름: ");
						for (int i = controlnumber - 20; i < controlnumber - 14; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");	// 뒤에서부터 이름(6)이랑 전화번호(13)이랑 띄어쓰기(2) =21전이 주소가 끝나는 위치 
						for (i = 0; i < controlnumber - 21; i++) {
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");	// 뒤에서부터 13자리가 전화번호
						for (int i = controlnumber - 13; i < controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

					}

					else // 주소-전화번호-이름 확정
					{
						printf("이름: ");
						for (int i = controlnumber - 3; i <= controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");
						for (i = 0; i < controlnumber - 21; i++) { 	// 뒤에서부터 이름(6)이랑 전화번호(13)이랑 띄어쓰기(2) =21전이 주소가 끝나는 위치 
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");
						for (int i = controlnumber - 21; controlnumber - 6; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");
					}




				}

				else if (myeonretvalue > siretvalue || myeonretvalue > gunretvalue || myeonretvalue > guretvalue) { // 면으로 끝나면 -> 읍의 상황과 동일 

				// 그 다음이 이름인지 전화번호인지 (숫자인지 아닌지 확인)
					//전화번호가 끝에 있을 경우 
					// 주소-이름-전화번호
					if (strary[controlnumber] == 0 || strary[controlnumber] == 1 || strary[controlnumber] == 2 || strary[controlnumber] == 3 || strary[controlnumber] == 4 || strary[controlnumber] == 5 || strary[controlnumber] == 0 || strary[controlnumber] == 6 || strary[controlnumber] == 7 || strary[controlnumber] == 8 || strary[controlnumber] == 9)
					{
						//주소가 어디서 끝날지 모르니, 뒤에서 글자수를 세는 걸로 한다. 


						printf("이름: ");
						for (int i = controlnumber - 20; i < controlnumber - 14; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");
						for (i = 0; i < controlnumber - 21; i++) {
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");
						for (int i = controlnumber - 13; i < controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

					}

					else // 주소-전화번호-이름
					{
						printf("이름: ");
						for (int i = controlnumber - 3; i <= controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");
						for (i = 0; i < controlnumber - 21; i++) {
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");
						for (int i = controlnumber - 21; controlnumber - 6; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");
					}
				}

				else  if (dongretvalue > siretvalue || dongretvalue > gunretvalue || dongretvalue > guretvalue) { // 동으로 끝나면 -> 읍과 동의 상황과 동일 
							// 이름, 전화번호, 주소 출력 

					// 그 다음이 이름인지 전화번호인지 (숫자인지 아닌지 확인)
					//전화번호가 끝에 있을 경우 
					// 주소-이름-전화번호
					if (strary[controlnumber] == 0 || strary[controlnumber] == 1 || strary[controlnumber] == 2 || strary[controlnumber] == 3 || strary[controlnumber] == 4 || strary[controlnumber] == 5 || strary[controlnumber] == 0 || strary[controlnumber] == 6 || strary[controlnumber] == 7 || strary[controlnumber] == 8 || strary[controlnumber] == 9)
					{
						//주소가 어디서 끝날지 모르니, 뒤에서 글자수를 세는 걸로 한다. 


						printf("이름: ");
						for (int i = controlnumber - 20; i < controlnumber - 14; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");
						for (i = 0; i < controlnumber - 21; i++) {
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");
						for (int i = controlnumber - 13; i < controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

					}

					else // 주소-전화번호-이름 확정
					{
						printf("이름: ");
						for (int i = controlnumber - 3; i <= controlnumber; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");

						printf("주소: ");
						for (i = 0; i < controlnumber - 21; i++) {	// 뒤에서부터 이름(6)이랑 전화번호(13)이랑 띄어쓰기(2) =21전이 주소가 끝나는 위치 
							printf("%c", strary[i]);
						}
						puts("");

						printf("전화번호: ");
						for (int i = controlnumber - 21; controlnumber - 6; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
							printf("%c", strary[i]);
						}
						puts("");
					}
				}

			}


			}
		}
		else { // 이름으로 시작함
		printf("이름: ");
		for (int i =0; i <= 5; i++) {	// 뒤에서 한글 3글자 이름 갖고 오기 
			printf("%c", strary[i]);
		}
		puts("");

		// 이름(6)과 띄어쓰기(1) 후에 7번째 자리가 숫자인지 확인
		// 아래의 조건을 만족하면 이름 - 전화번호 - 주소 확정
		{if (strary[7] == 0 || strary[7] == 1 || strary[7] == 2 || strary[7] == 3 || strary[7] == 4 || strary[7] == 5 || strary[7] == 6 || strary[7] == 7 || strary[7] == 8 || strary[7] == 9) {
			printf("주소: ");
			for (i = 21; i < controlnumber; i++) {
				printf("%c", strary[i]);
			}
			puts("");
			printf("전화번호: ");
			for (int i = 7; i <= 19; i++) {
				printf("%c", strary[i]);
			}
		}

		else { // 이름 - 주소 - 전화번호 확정

			printf("주소: ");
			for (int i = 7; i < controlnumber - 13; i++)
				printf("%c", strary[i]);
			puts("");

			printf("전화번호: ");
			for (int i = controlnumber - 13; i <= controlnumber; i++) {
				printf("%c", strary[i]);
			}
		}

		}
			}
	}


}
