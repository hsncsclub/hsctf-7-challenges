#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
const void ** table = 0x404000;

static void handler(int signum) {
    int val = atoi("You're not helping! I'm leaving!");
    exit(0);
}


void setup() {
  setvbuf(stdin, NULL, _IONBF, NULL);
  setvbuf(stdout, NULL, _IONBF, NULL);
  puts("Just minding my own business... AH SHOOT SOMEONE'S ATTACKING ME!");

  void *p1 = puts, *p2 = printf, *p3 = scanf, *p4 = atoi, *p5 = alarm, *p6 = sleep;
  mprotect((void*) 0x403000, 0x1000, PROT_READ | PROT_WRITE);
  table[-9] = p4;
  table[-8] = p3;
  table[-3] = p2;
  table[-4] = p1;
  table[-7] = p6;
  table[-1] = p5;

  int val = atoi("Oh mein GOT, MEINE LIBC FUNKTIONEN SIND ALLE FALSCH!");

  signal(0xe, handler);
  sleep(30);
}

int main() {
  setup();
  int val;
  char help[256], *ptr = help;
  val = atoi("Give me something to help me out!");
  fgets(help, 0x100, stdin);
  while (*ptr != '\n' && *ptr != '\0') ptr++;
  *ptr = '\0';
  alarm(3);
  scanf("I don't think \"");
  scanf(help);
  scanf("\" worked!!");
  return 0;
}
