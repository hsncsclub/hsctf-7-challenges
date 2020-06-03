#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>
#define __uint128 unsigned __int128
char pad1 = 0;
__uint128 state = (__uint128) 0;
char pad2 = 0;
unsigned char* msg;
unsigned char* keystream;
char* extra;


void update() {
  // Who made this shuffling algorithm???
  // Who hurt you for you to make this???
  int i, ip1, newind, newind2;
  __uint128 tmp;
  for (i = 0; i < 128 - 7; i++) {
    newind = (state & ((__uint128) 0b11111110 << i)) >> (i+1);
    newind2 = (newind + 1) & 0b1111111;
    ip1 = (i + 1) & 0b1111111;
    state ^= (__uint128) ((state & ((__uint128) 1 << newind)) > (__uint128) 0) << i;
    state ^= (__uint128) ((state & ((__uint128) 1 << newind2)) > (__uint128) 0) << ip1;
  }
  for (i = 128-7; i < 127; i++) {
    newind = ((state & ((((__uint128) 1 << (128-i)) - 1) << (i+1))) >> (i+1)) | ((state & (((__uint128) 1 << (i-120)) - 1)) << (127-i));
    newind2 = (newind + 1) & 0b1111111;
    ip1 = (i + 1) & 0b1111111;
    state ^= (__uint128) ((state & ((__uint128) 1 << newind)) > (__uint128) 0) << i;
    state ^= (__uint128) ((state & ((__uint128) 1 << newind2)) > (__uint128) 0) << ip1;
  }
  newind = (state & ((__uint128) 0b1111111));
  newind2 = (newind + 1) & 0b1111111;
  ip1 = (i + 1) & 0b1111111;
  state ^= (__uint128) ((state & ((__uint128) 1 << newind)) > (__uint128) 0) << i;
  state ^= (__uint128) ((state & ((__uint128) 1 << newind2)) > (__uint128) 0) << ip1;
}

unsigned char get_key_byte() {
  unsigned char ret = 0;
  for (int i = 0; i < 16; i++) {
    ret *= 2;
    ret += (*((char*) &state + i) & 0b10000000) >> 7;
  }
  return ret;
}

void seed() {
  FILE* f = fopen("/dev/random", "r");
  fread(&state, 1, 3, f);
  // What if we exhaust /dev/random?? Gotta use bytes sparingly
  // Why are we not using /dev/urandom?
  // The Mayor's orders
  srand((unsigned int) state);
  for (int i = 4; i < 16; i++) {
    ((char*) &state)[i] = (char) rand();
  }
  fclose(f);
}

static void handler(int signum) {
    puts("*The Mayor has returned. Your time is up. Your s**t is wrecked.*");
    exit(0);
}

void setup() {
  seed();
  setvbuf(stdin, NULL, _IONBF, NULL);
  setvbuf(stdout, NULL, _IONBF, NULL);
  signal(0xe, handler);
  alarm(30);
}

void print_state(__uint128 val) {
  for (int i = 0; i < 128; i++) {
    printf("%d", (val & ((__uint128) 1 << i)) > 0);
  }
  puts("");
}

int main() {
  char password[32], input[24], a;
  unsigned long length;
  setup();
  printf("Please enter your password: ");
  read(0, password, 31);
  if (strcmp(password, "no_one_will_guess_the_protocol\n")) {
    puts("Wrong password.");
    exit(0);
  }
  puts("Welcome, The Mayor.");
  puts("This is the debug encryption service for the custom stream cipher implemented on your servers.");
  puts("It is as secure as ever.");
  puts("To allay your paranoia, I will allow you to encrypt anything you would like.");
  puts("Just enter your (hex) byte values.");
  puts("Please enter the length (in bytes) of the text to be encoded.");
  fgets(input, 23, stdin);
  length = strtoul(input, NULL, 10);
  if (length > 1000) {
    puts("That's a tad much, don't you think?");
    exit(0);
  }
  msg = calloc(length+1, 1);
  keystream = calloc(length+1, 1);
  int i = 0;
  puts("Now enter the hex of the bytes to be encoded.");
  while (i < length && read(0, input, 2) > 0) {
    msg[i] = (unsigned char) strtoul(input, &extra, 16);
    if (extra[0] != '\0') {
      printf("Unrecognised char, breaking");
      msg[i] = '\0';
      break;
    }
    i++;
  }
  for (int c = 0; c < i; c++) {
    update();
    printf("%02x", msg[i] ^ get_key_byte());
  }
  puts("");
  puts("There's your ciphertext. Now leave me alone.");
  FILE* f = fopen("flag.txt", "r");
  puts("Oh no, I dropped my encoded flag!");
  while (fread(&a, 1, 1, f) == 1) {
    update();
    printf("%02x", a ^ get_key_byte());
  }
  puts("");
  puts("Aaaah! No, no, no, The Mayor is gonna kill me, I gotta go.");
  exit(0);
}
