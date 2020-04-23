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

void addLinesToArray(FILE *file, char *** data, size_t * lenData){
  char *line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, file) >= 0){
    *data = realloc(*data, (*lenData+1)*sizeof(**data));
    (*data)[*lenData] = line;
    line = NULL;
    (*lenData)++;
  }
  free(line);
}

void printFreeReset(char *** data, size_t * lenData){
  for(int j = 0; j < *lenData; j++){
    printf("%s", (*data)[j]);
    free((*data)[j]);
  }
  free(*data);
  *data = NULL;
  *lenData = 0;
}

int main(int argc, char ** argv) {
  char ** data = NULL;
  size_t lenData = 0;
  
  if(argc == 1){
    addLinesToArray(stdin, &data, &lenData);
    sortData(data, lenData);
    printFreeReset(&data, &lenData);
  } else {
    for(int fileIdx = 1; fileIdx < argc; fileIdx++){
      FILE * file = fopen(argv[fileIdx], "r");
      if(file == NULL){
	perror("Could not open file");
	return EXIT_FAILURE;
      }
      addLinesToArray(file, &data, &lenData);

      if(fclose(file) != 0){
	perror("Could not close file");
	return EXIT_FAILURE;
      }
      sortData(data, lenData);
      printFreeReset(&data, &lenData);
    } 
  }
  
  return EXIT_SUCCESS;
}
