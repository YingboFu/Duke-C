#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("check failed!");
    exit(EXIT_FAILURE);
  }
}

void main() {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(-1, 0, 1);
  run_check(1, 1, 1);
  run_check(0, 1, 0);
  run_check(-1, 1, -1);
  run_check(1, -1, 1);
  run_check(2, -1, 0.5);
  run_check(2, 16, 65536);
  exit(EXIT_SUCCESS);
}
