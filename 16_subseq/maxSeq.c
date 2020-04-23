#include <stddef.h>

size_t maxSeq(int * array, size_t n){
  if(n == 0){
    return 0;
  }
  int current_streak = 1;
  int max_streak = 1;
  for(int i = 0; i < n-1; i++){
    if(array[i+1] > array[i]){
      current_streak++;
      if(current_streak > max_streak){
	max_streak = current_streak;
      }
    } else {
      current_streak = 1;
    }
  }
  return max_streak;
}
