#include <stdio.h>
#include <malloc.h>
#define SIZE 100

void print_ary(int* ary, int height, int width);

int main() {
	FILE* drawfp;	//이진수로 되어있는 그림 파일 포인터 
	FILE* convertfp;//이진수그림을 □or■로 바꿔 저장하는 그림 파일 포인터 
	char buff[SIZE]; //fgets할 때 저장하는 버퍼 
	int width = 0;	//그림파일의 가로길이
	int height = 0;	//그림파일의 세로길이 
	char ch;
	drawfp = fopen("c:\\temp\\draw.txt", "r+");
	convertfp = fopen("c:\\temp\\convert.txt", "w+");

	if (drawfp == NULL)
	{
		perror("파일 읽기 개방 에러");
		return;
	}

	// 그림파일의 가로 계산하기 
	while (fgetc(drawfp) != '\n') {
		width++;
	}
	rewind(drawfp); //파일포인터 처음으로 

	// 그림파일의 세로 계산하기 
	while (!feof(drawfp)) {
		fgets(buff, SIZE, drawfp);
		height++;
	}
	rewind(drawfp);

	printf("가로개수: %d, 세로갯수: %d\n", width, height);


	// 숫자를 그림화하기 > 배열에 정보 저장하기 
	int** ary;	//이차원 배열 메모리 할당하기 
	ary = (int**)malloc(sizeof(int*) * width);
	for (int i= 0; i < width; i++)
	{
		ary[i] = (int*)malloc(sizeof(int) * height);
	}

	// 배열에 숫자 집어넣기 
	for (int i = 0; i < height; i++)
	{
		fgets(buff, SIZE, drawfp);
		for (int j = 0; j < width; j++)
		{
			ary[i][j] = fgetc(drawfp);
		}
	}

	
	print_ary(ary,height,width); // 배열 출력


	fclose(drawfp);
	fclose(convertfp);

	for (int i = 0; i < width; i++) {
		free(ary[i]);
	}
	free(ary);
}


//배열 전체 출력
void print_ary(int** ary, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (ary[i][j] == '1') printf("■");
			else printf("□");
			//printf("%c", ary[i][j]);
		}
		printf("\n");
	}
}
