#include <stdlib.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned ans){
  //printf("Testing %d^%d = %d - ", x, y, ans);
  unsigned check_this = power(x, y);
  if (check_this != ans){
    //printf("WRONG: %d\n", check_this);
    exit(EXIT_FAILURE);
  } else {
    //printf("CORRECT\n");
    return;
  }
}

int main(){
  run_check(0, 0, 1);
  run_check(1, 1, 1);
  run_check(1, 2, 1);
  run_check(2, 2, 4);
  run_check(2, 0, 1);
  run_check(3, 3, 27);
  run_check(0, 5, 0);
  run_check(5, 0, 1);
  run_check(5, 2, 25);
  run_check(5, 1, 5);
  run_check(6, 2, 36);
  run_check(2, 10, 1024);
  run_check(10, 2, 100);
  run_check(10, 5, 100000);

  return EXIT_SUCCESS;
}
