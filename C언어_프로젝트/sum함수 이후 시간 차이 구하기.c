#include <stdio.h>
#include <time.h>
time_t now;
time_t future;

long long int sum(long long int n) {
	long long int sum = 0;
	for (long long int i = 1; i <= n; i++) {
		sum=sum+i;
	}
	return sum;
}

int main() {
	long long int n = 0;
	long long int fsum;

	printf("현재까지 초: %lld\n", now); // 현재 시간
	printf("1 ~ 2^63 범위 내의 정수를 입력하시오. >> ");
	scanf("%lld", &n);
	time(&now); // 함수를 실행하기 전의 시간을 구하기
	printf("현재초: %lld\n", now);

	fsum = sum(n); // 총합을 구하는 함수 실행

	time(&future); // 함수를 실행한 후의 시간을 구하기 
	printf("미래초: %lld\n", future);

	long long int differ = future - now;

	printf("시간 차이는 %lld입니다.", differ);

	printf("1부터 %lld까지 총합은 %lld이고 수행시간은 %lld시 %lld분 %lld초입니다.",n,fsum,differ/3600, differ/60, differ%60);


}
