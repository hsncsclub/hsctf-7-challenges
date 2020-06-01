#include <stdio.h>
#include <stdlib.h>

const unsigned long long a = 25214903917;
const unsigned long long b = 11;
unsigned long long curr;
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
    long long base = 0;
    for (int i = 0; i < 8; i++) {
        base *= 256;
        base += fgetc(urandom);
    }
    curr = base;
    fclose(urandom);
}

unsigned long long next(void) {
    return (unsigned long long) (curr = curr * a + b);
}
int main(void) {
    initRandom();
    setvbuf(stdin, NULL, _IONBF, NULL);
    setvbuf(stdout, NULL, _IONBF, NULL);
    long long guess = 0, result;
    puts("I had a bit too much coffee so this is in Java not C");
    puts("(Actually it's still in C because Java is a pain)");
    puts("Since I'm so generous you get 2 free numbers");
    printf("%llu\n", next());
    printf("%llu\n", next());
    for (int i = 0; i < 10; i++) {
        printf("Guess my number: ");
        scanf("%llu", &guess);
        if (guess != next()) {
            puts("WRONG!");
            exit(0);
        }

    }
    puts("You win!");
    printf("Have a flag: ");
    win();
    puts("");
}
