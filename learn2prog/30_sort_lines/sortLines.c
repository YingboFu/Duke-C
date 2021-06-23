#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printAndFree (char ** data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

void processData (FILE * f) {
  char ** lines = NULL;
  size_t sz = 0;
  char * curr = NULL;
  size_t count = 0;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (count + 1) * sizeof (*lines));
    lines[count] = curr;
    count++;
    curr = NULL;
  }
  free(curr);
  sortData(lines, count);
  printAndFree(lines, count);
}

void processFile (char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    fprintf(stderr, "Fails to open the file!\n");
    exit(EXIT_FAILURE);
  }
  processData(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fails to close the file!\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    processData(stdin);
  } else {
    for (size_t i = 1; i < argc; i++) {
      processFile(argv[i]);
    }
  }
  
  return EXIT_SUCCESS;
}
