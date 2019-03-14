#include <stdio.h>
#include <unistd.h>

int main () {
  
  char *argv[3] = {"killall", "soal5.out", NULL};
  
  execv("/usr/bin/killall", argv);


  return 0;
}
