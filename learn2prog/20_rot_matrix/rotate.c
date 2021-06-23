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
