#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName = malloc( (strlen(inputName) + 8) * sizeof(*outputName) );
  strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}
