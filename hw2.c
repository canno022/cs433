#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* structure for passing data to threads */
typedef struct
{
   int row;
   int column;
   int (* puzzle)[9];
  //The entire puzzle as an array pointer//
} parameters;

void * check_rows(void * params);
void * check_columns(void * params);
void * check_squares(void * params);
//functions passed as void pointers that will pass the parameters to and from the threads//
int main(void)
{

  int puzzle[9][9] = {
    {6,2,4,5,3,9,1,8,7},
    {5,1,9,7,2,8,6,3,4},
    {8,3,7,6,1,4,2,9,5},
    {1,4,3,8,6,5,7,2,9},
    {9,5,8,2,4,7,3,6,1},
    {7,6,2,3,9,1,4,5,8},
    {3,7,1,9,5,6,8,4,2},
    {4,9,6,1,8,2,5,7,3},
    {2,8,5,4,7,3,9,1,6}
  };
  //for the columns and rows
  parameters * data0 = (parameters *) malloc(sizeof(parameters));
  data0->row = 0;
  data0->column = 0;
  data0->puzzle = puzzle;
  
    
  // next 9 are for the squares
  parameters * data1 = (parameters *) malloc(sizeof(parameters));
  data1->row = 0;
  data1->column = 0;
  data1->puzzle = puzzle;
  
    parameters * data2 = (parameters *) malloc(sizeof(parameters));
  data2->row = 0;
  data2->column = 3;
  data2->puzzle = puzzle;

  
    parameters * data3 = (parameters *) malloc(sizeof(parameters));
  data3->row = 0;
  data3->column = 6;
  data3->puzzle = puzzle;

  
    parameters * data4 = (parameters *) malloc(sizeof(parameters));
  data4->row = 3;
  data4->column = 0;
  data4->puzzle = puzzle;

  
    parameters * data5 = (parameters *) malloc(sizeof(parameters));
  data5->row = 3;
  data5->column = 3;
  data5->puzzle = puzzle;

  
    parameters * data6 = (parameters *) malloc(sizeof(parameters));
  data6->row = 3;
  data6->column = 6;
  data6->puzzle = puzzle;

  
    parameters * data7 = (parameters *) malloc(sizeof(parameters));
  data7->row = 6;
  data7->column = 0;
  data7->puzzle = puzzle;

  
    parameters * data8 = (parameters *) malloc(sizeof(parameters));
  data8->row = 6;
  data8->column = 3;
  data8->puzzle = puzzle;

  
    parameters * data9 = (parameters *) malloc(sizeof(parameters));
  data9->row = 6;
  data9->column = 6;
  data9->puzzle = puzzle;

  //threads to check all of the lines and squares of the puzzle
  pthread_t rowsthread, columnsthread, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
  
   //how the threads results will be returned
  void * rows;
  void * columns;
  void * square1;
  void * square2;
  void * square3;
  void * square4;
  void * square5;
  void * square6;
  void * square7;
  void * square8;
  void * square9;
  
  //Threads are initialized here and given necessary pointers
  pthread_create(&rowsthread, NULL, check_rows, (void *) data0);
  pthread_create(&columnsthread, NULL, check_columns, (void *) data0);
  pthread_create(&thread1, NULL, check_squares, (void *) data1);
  pthread_create(&thread2, NULL, check_squares, (void *) data2);
  pthread_create(&thread3, NULL, check_squares, (void *) data3);
  pthread_create(&thread4, NULL, check_squares, (void *) data4);
  pthread_create(&thread5, NULL, check_squares, (void *) data5);
  pthread_create(&thread6, NULL, check_squares, (void *) data6);
  pthread_create(&thread7, NULL, check_squares, (void *) data7);
  pthread_create(&thread8, NULL, check_squares, (void *) data8);
  pthread_create(&thread9, NULL, check_squares, (void *) data9);
  

  pthread_join(rowsthread, &rows);
  pthread_join(columnsthread, &columns);
  pthread_join(thread1, &square1);
  pthread_join(thread2, &square2);
  pthread_join(thread3, &square3);
  pthread_join(thread4, &square4);
  pthread_join(thread5, &square5);
  pthread_join(thread6, &square6);
  pthread_join(thread7, &square7);
  pthread_join(thread8, &square8);
  pthread_join(thread9, &square9);
  
if ((long) rows == 1 && (long) columns == 1 && (long) square1 == 1 && (long) square2 == 1 && (long) square3 == 1 && (long) square4 == 1 && (long) square5 == 1 && (long) square6 == 1 && (long) square7 == 1 && (long) square8 == 1 && (long) square9 == 1 ) 
  {
    printf("The puzzle is solved!\n");
  }
  else {
    printf("One or more of the entries are incorrect.\n");
  }
  
  return 0;
}

void * check_rows(void * params) 
{
  parameters * data = (parameters *) params;
  int startRow = data->row;
  int startColumn = data->column;
  for (int i = startRow; i < 9; ++i) {
    int row[10] = {0};
    for (int j = startColumn; j < 9; ++j) {
      int check = data->puzzle[i][j];
      if (row[check] != 0) {
	return (void *) 0;
      }
      else{
	row[check] = 1;
      }
    }
  }
  return (void *) 1;
}

void * check_columns(void * params) 
{
  parameters * data = (parameters *) params;
  int startRow = data->row;
  int startColumn = data->column;
  for (int i = startColumn; i < 9; ++i) {
    int column[10] = {0};
    for (int j = startRow; j < 9; ++j) {
      int check = data->puzzle[j][i];
      if (column[check] != 0) {
	return (void *) 0;
      }
      else{
	column[check] = 1;
      }
    }
  }
  return (void *) 1;
}

void * check_squares(void * params) 
{
  parameters * data = (parameters *) params;
  int startRow = data->row;
  int startColumn = data->column;
  int square[10] = {0};
  for (int i = startRow; i < startRow + 3; ++i) {
    for (int j = startColumn; j < startColumn + 3; ++j) {
      int check = data->puzzle[i][j];
      if (square[check] != 0) {
	return (void *) 0;
      }
      else{
	square[check] = 1;
      }
    }
  }
  return (void *) 1;
}
