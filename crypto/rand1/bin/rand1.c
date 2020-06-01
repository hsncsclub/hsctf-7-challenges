#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int a = 37;
unsigned char curr;
FILE* urandom;

void win(void) {
    FILE *fin = fopen("flag.txt", "r");
    char a;
    while (!feof(fin)) {
        a = fgetc(fin);
        if (a == -1) break;
        putchar(a);
    }
    fclose(fin);
}

void initRandom(void) {
    urandom = fopen("/dev/urandom", "r");
    curr = (unsigned char) fgetc(urandom);
    fclose(urandom);
}

int next(void) {
    return (int) (unsigned char) (curr = curr * a + 65);
}
int main(void) {
    initRandom();
    int guess, result;
    setvbuf(stdin, NULL, _IONBF, NULL);
    setvbuf(stdout, NULL, _IONBF, NULL);
    puts("I heard LCGs were cool so I made my own");
    printf("Since I'm so generous you get a free number: %d\n", next());
    for (int i = 0; i < 10; i++) {
        printf("Guess my number: ");
        scanf("%d", &guess);
        result = next();
        if (guess != result) {
            puts("Wrong!");
            return 1;
        }
    }
    win();
}
