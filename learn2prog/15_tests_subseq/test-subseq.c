#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {

  int test1[6] = {1, 8, 10, 6, 7, 5};
  int test2[0] = {};
  int test3[7] = {1, 10, 2, 8, 5, 9, 78};
  int test4[10] = {1, 1, 3, 6, 9, 8, 5, 5, 7, 10};
  int test5[4] = {1, 2, 3, 2};
  int test6[4] = {9, 1, 2, 3};
  int test7[7] = {1, 2, 5, 4, 6, 10, 16};
  int test8[3] = {-1, 0, 1};
  int test9[6] = {-999, -99, -9, -7, -5, 0};
  
  if (maxSeq(test1, 6) != 3) {
    return EXIT_FAILURE;
  }
  
  if (maxSeq(test2, 0) != 0) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test3, 7) != 3) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test4, 10) != 4) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test5, 4) != 3) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test6, 4) != 3) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test7, 7) != 4) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test8, 3) != 3) {
    return EXIT_FAILURE;
  }

  if (maxSeq(test9, 6) != 6) {
    return EXIT_FAILURE;
  }
  
  
  
  
  
  return EXIT_SUCCESS;
}
