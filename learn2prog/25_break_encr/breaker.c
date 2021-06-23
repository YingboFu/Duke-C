#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void frequency_count (FILE * f, int counter[]) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      counter[c] += 1;
    }
  }
}

int find_key (int counter[]) {
  int max_index = 0;
  for (int i = 1; i < 26; i++) {
    if (counter[i] > counter[max_index]) {
      max_index = i;
    }
  }
  int e_a_gap = 'e' - 'a';
  if (max_index >= e_a_gap) {
    return max_index - e_a_gap;
  } else {
    return max_index - e_a_gap + 26;
  }
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: breaker encrypted_file\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  static int counter[26] = {0};
  frequency_count (f, counter);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  
  int key = find_key (counter);
  fprintf(stdout,"%d\n", key);

  return EXIT_SUCCESS;
}
