#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  
  if (n <= 0) {
    return 0;
  }
  
  size_t count_max = 1;
  size_t count_current = 1;

  for(size_t i=1;i<n;i++) {
    if (array[i] > array[i-1]) {
      count_current ++;
      if (count_current > count_max) {
	count_max = count_current;
      }
    }
    else {
      if (count_current > count_max) {
	count_max = count_current;
      }
      count_current = 1;
    }
  }
  return count_max;
}
