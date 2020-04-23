struct index_tag {
  int row;
  int col;
};
typedef struct index_tag index_t;


index_t rotateIndex(index_t index){
  index_t newIndex;
  newIndex.col = 9 - index.row;
  newIndex.row = index.col;
  return newIndex;
}

void rotate(char matrix[10][10]){
  char tmp[10][10];
  for(int row = 0; row < 10; row++){
    for (int col = 0; col < 10; col++){
      index_t index = {row, col};
      index_t newIndex = rotateIndex(index);
      tmp[newIndex.row][newIndex.col] = matrix[row][col];
    }
  }
  
  for(int row = 0; row < 10; row++){
    for(int col = 0; col < 10; col++){
      matrix[row][col] = tmp[row][col];
    }
  }
}
