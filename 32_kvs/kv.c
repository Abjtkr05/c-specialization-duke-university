#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t* splitPairs(char* str){

  char* value1 = strchr(str,'=');
  *value1 = '\0';
  value1++;
  char* n = strchr(value1,'\n');
  if(n != NULL){
    *n='\0';
  };

  kvpair_t* pair = malloc((size_t)sizeof(*pair));
  pair->key = str;
  pair->value = value1;
  return pair;
}


kvarray_t * readKVs(const char * fname) {
  FILE *f = fopen(fname, "r");
  if(f == NULL){
    perror("Cannot open file");
    exit(EXIT_FAILURE);
  }
  
  kvpair_t* curr_pair = NULL;
  kvarray_t *kvarray = malloc(sizeof(*kvarray));
  kvarray->pairs = NULL;
  kvarray->numPairs = 0;
  char *line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f) >= 0){
    curr_pair = splitPairs(line);
    kvarray->pairs = realloc(kvarray->pairs,(kvarray->numPairs + 1) * sizeof(*kvarray->pairs));
    kvarray->pairs[kvarray->numPairs] = curr_pair;
    kvarray->numPairs++;
    line=NULL;
  }

  free(line);

  if(fclose(f) != 0){
    perror("Cant close file");
    return NULL;
  }

  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->numPairs; i++){
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
  return;
}

void printKVs(kvarray_t * pairs) {
  kvpair_t * currPair;
  for(int i = 0; i < pairs->numPairs; i++){
    currPair = pairs->pairs[i];
    printf("key = '%s' value = '%s'\n", currPair->key, currPair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for(int i = 0; i < pairs->numPairs; i++){
    if(strcmp(key, pairs->pairs[i]->key) == 0){
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
