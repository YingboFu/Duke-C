#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

kvarray_t * readlines (FILE * f) {
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->len = 0;
  ans->kvpairs = NULL;
  char * curr = NULL;
  size_t sz;
  while (getline(&curr, &sz, f) > 0) {
    ans->len ++;
    ans->kvpairs = realloc(ans->kvpairs, ans->len * sizeof(*(ans->kvpairs)));
    ans->kvpairs[ans->len-1] = malloc(sizeof(kvpair_t));
    char * separator = strchr(curr, '=');
    if (separator == NULL) {
      fprintf(stderr, "Invalid line: %s\n", curr);
      exit(EXIT_FAILURE);
    }

    char * currKey = malloc ((separator - curr + 1) * sizeof(char));
    strncpy(currKey, curr, separator - curr);
    currKey[separator - curr] = '\0';
    ans->kvpairs[ans->len-1]->key = currKey;

    char * temp = separator + 1;
    stripNewline(temp);
    char * currValue = malloc ((strlen(temp) + 1) * sizeof(char));
    strncpy(currValue, temp, strlen(temp));
    currValue[strlen(temp)] = '\0';
    ans->kvpairs[ans->len-1]->value = currValue;
    
  }
  free(curr);
  return ans;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Fails to open the file: %s\n", fname);
    exit(EXIT_FAILURE);
  }
  kvarray_t * ans = readlines(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fails to close the file: %s\n", fname);
    exit(EXIT_FAILURE);
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i ++) {
    free(pairs->kvpairs[i]->key);
    free(pairs->kvpairs[i]->value);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i ++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i]->key, pairs->kvpairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i ++) {
    if (strcmp(pairs->kvpairs[i]->key, key) == 0) {
      return pairs->kvpairs[i]->value;
    }
  }
  return NULL;
}

