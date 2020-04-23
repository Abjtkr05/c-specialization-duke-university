#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t *createCounts(void) {
  counts_t *counts = malloc(sizeof(*counts));
  counts->arr = NULL;
  counts->size = 0;
  counts->unknowns = 0;
  return counts;
}

void addCount(counts_t *c, const char *name) {
  if (name == NULL){
    c->unknowns++;
  } else {
    one_count_t *count = NULL;
    int found = 0;
    for(size_t i = 0 ; i < c->size; i++){
      count = c->arr[i];
      if (strcmp(count->name, name) == 0) {
	count->count++;
	found = 1;
      }
    }
    if(found == 0){
      one_count_t *newCount = NULL;
      newCount = malloc(sizeof(*newCount));
      newCount->name = malloc(strlen(name) + 8);
      strcpy(newCount->name, name);
      newCount->count = 1;
      c->arr = realloc(c->arr, (c->size + 1)*sizeof(*c->arr));
      c->arr[c->size] = newCount;
      c->size++;
    }
  }
}
void printCounts(counts_t *c, FILE *outFile) {
  one_count_t *count = NULL;
  for (size_t i = 0; i < c->size; i++){
    count = c->arr[i];
    fprintf(outFile, "%s: %zd\n", count->name, count->count);
  }
  if (c->unknowns != 0){
    fprintf(outFile, "<unknown> : %zd\n", c->unknowns);
  }
}

void freeCounts(counts_t *c) {
  for (size_t i = 0; i < c->size; i++){
    free(c->arr[i]->name);
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}
