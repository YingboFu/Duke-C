#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 12

void rotate(char matrix[10][10]) {
  char rotate[10][10];
  
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      rotate[j][9-i] = matrix[i][j];
    }
  }
  
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      matrix[i][j] = rotate[i][j];
    }
  }
  
}


int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf( stderr, "Usage: ./rotateMatrix input_file_name \n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf( stderr, "Fails to open the input file \n");
    exit(EXIT_FAILURE);
  }
  char matrix[10][10];
  char line[LINE_SIZE];
  int row_idx = 0;
  while(fgets(line, LINE_SIZE, f) != NULL) {
    if (strchr(line, '\n') == NULL) {
      fprintf( stderr, "Line too long \n");
      exit(EXIT_FAILURE);
    }
    if ((strchr(line, '\n') - line) != 10) {
      fprintf( stderr, "Line too short \n");
      exit(EXIT_FAILURE);
    }
    if (row_idx > 9) {
      fprintf( stderr, "Too many lines \n");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++) {
      matrix[row_idx][i] = line[i];
    }
    row_idx++;
  }
  if (row_idx < 10) {
    fprintf( stderr, "Too few lines \n");
    exit(EXIT_FAILURE);
  }

  if (fclose(f) != 0) {
    fprintf( stderr, "Fails to close the file \n");
    exit(EXIT_FAILURE);
  }
  
  rotate(matrix);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf( stdout, "%c", matrix[i][j]);
    }
    fprintf( stdout, "\n");
  }
  exit(EXIT_SUCCESS);
}
