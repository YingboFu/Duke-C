#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc (sizeof(*ans));
  ans->counts = NULL;
  ans->len = 0;
  ans->count_unknown = 0;
  return ans;
}

int findName (counts_t * c, const char * name) {
  for (size_t i = 0; i < c->len; i++) {
    if (strcmp(c->counts[i]->str, name) == 0) {
      return i;
    }
  }
  return -1;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //int nameIndex = findName(c, name);
  if (name == NULL) {
    c->count_unknown ++;
  } else if (findName(c, name) == -1){
    c->len++;
    c->counts = realloc(c->counts, c->len * sizeof(*(c->counts)));
    c->counts[c->len-1] = malloc(sizeof(one_count_t));
    c->counts[c->len-1]->str = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(c->counts[c->len-1]->str, name);
    c->counts[c->len-1]->count = 1;
  } else {
    int nameIndex = findName(c, name);
    c->counts[nameIndex]->count ++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %zu\n", c->counts[i]->str, c->counts[i]->count);
  }
  if (c->count_unknown != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->count_unknown);
  }
  /*
  if (fclose(f) != 0) {
    fprintf("Fails to close the file %s", outFile);
    exit(EXIT_FAILURE);
  }
  */
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i = 0; i < c->len; i++){
    free(c->counts[i]->str);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
