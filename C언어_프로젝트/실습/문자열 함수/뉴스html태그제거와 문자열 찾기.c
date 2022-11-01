// 뉴스의 제목과 내용만 추출
// 특정 단어가 들어가는 문장을 모두 출력 

#include <stdio.h>
#include <string.h>

#define START "google_ad_section_start(name=gad1)"
#define END "<dl>"
#define openTOKEN "<"
#define closeTOKEN ">"
#define findnum "1"


void main() {
	FILE* fp;
	FILE* wp;
	char news[5000] = { "\0" };
	char buffer[1300];


	fp = fopen("c:\\temp\\article1.html", "r");
	wp = fopen("c:\\temp\\news1.txt", "w");
	char* token;

	while (!feof(fp)) {

		// 기사의 시작태그<google_ad_section_start(name=gad1)>가 버퍼에 있을 때까지 html에서 한 줄씩 버퍼에 저장한다.
		fgets(buffer, 500, fp);

		if (strstr(buffer, START) != NULL) {
			for (int i = 1; i <= 6; i++) {
				fgets(buffer, 1300, fp);
			}

			// 시작태그 다음에는 5번의 줄바꿈이 있다. 6번째 fgets부터 기사제목이 써진다. 


			// 제목 
			token = strtok(buffer, "<"); // 제목 뒤에는 태그가 붙어있으므로 뒤에있는 <전까지 토큰화한다.
			strcat(token, "\n");
			fputs(buffer, wp); // 제목을 파일에 입력한다.

			//printf("%s", buffer);

			// <dl>태그는 기사의 끝을 나타내므로, 버퍼에 <dl>가 들어갈 때까지 fgets로 한 줄씩 가져온다.
			while (strstr(buffer, "<dl>") == NULL) {

				fgets(buffer, 500, fp); // 한 줄을 buffer에 저장한다.

				// 기사 한 줄마다 앞과 뒤에 <p> </p>태그가 붙어있다. 


				// <p>태그가 없을 때는 
				if (strstr(buffer, "<p>") == NULL) {
					if (strstr(buffer, "<dl>") != NULL) break;
					if (strstr(buffer, "img") != NULL) fgets(buffer, 500, fp);
					fputs(buffer, wp);
					fprintf(wp, "\n");
					fgets(buffer, 500, fp);

				}

				else {
					if (strstr(buffer, "<dl>") != NULL) break;
					if (strstr(buffer, "img") != NULL) fgets(buffer, 500, fp);
					token = strtok(buffer, closeTOKEN);
					token = strtok(NULL, openTOKEN);
					fputs(token, wp);
					fprintf(wp, "\n");
				}
				//puts(token);

			}
			break;

		}
	}
	fclose(fp);
	fclose(wp);


	char findword[10];
	int ret;

	printf("찾을 문자열을 입력하세요 >> ");
	gets(findword);
	
	// 문자열을 읽어오기
	fp = fopen("c:\\temp\\news1.txt", "r");

	while (!feof(fp)) {
		fgets(buffer, 500, fp);
		ret = strstr(buffer, findword);
		if (ret != NULL) puts(buffer);
	}

	fclose(fp);
}
