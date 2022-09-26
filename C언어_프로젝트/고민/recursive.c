#include <stdio.h> 

int asterisk(int i) {
    if (i > 1) {
        asterisk(i / 2);
        asterisk(i / 2);
    }
    printf("*");
}

int main() {
    asterisk(5);
}
