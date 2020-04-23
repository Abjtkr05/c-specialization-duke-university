#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int get_encryption_key(int * arr, int n){
  int max = 0, max_idx = 0;

  for(int i = 0; i < n; i++){
    if(arr[i] > max){
      max = arr[i];
      max_idx = i;
    }
  }
  if(max == 0){
    fprintf(stderr, "File is empty\n");
    return EXIT_FAILURE;
  }

  int key =  0;
  if (max_idx >= ('e' - 'a')){
    key = max_idx - ('e' - 'a');
  } else {
    key = (26 - ('e' - 'a')) + max_idx;
  }
  return key;
}

int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr, "File not supplied\n");
    return EXIT_FAILURE;
  }
  
  const char * file_name = argv[1];

  FILE * f = fopen(file_name, "r");
  if(f == NULL){
    fprintf(stderr, "File cannot be open\n");
    return EXIT_FAILURE;
  }

  int c;
  int arr[26] = {0};
  while((c=fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      c -= 'a';
      arr[c]++;
    }
  }

  if(fclose(f) != 0){
    fprintf(stderr, "Failed to close file\n");
    return EXIT_FAILURE;
  }
  
  int key = get_encryption_key(arr, 26);
  printf("%d\n", key);

  return EXIT_SUCCESS;
}
