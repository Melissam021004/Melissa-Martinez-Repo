#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "puzzle.h"

// also tests puzzle_destroy
void test_puzzle_create(void) {
  Puzzle *p3 = puzzle_create(3);
  Puzzle *p5 = puzzle_create(5);

  assert(p3->size == 3);
  for (int i = 0; i < 9; ++i) {
    assert(p3->tiles[i] == 0);
  }

  assert(p5->size == 5);
  for (int i = 0; i < 25; ++i) {
    assert(p5->tiles[i] == 0);
  }

  puzzle_destroy(p3);

  puzzle_destroy(p5);
}

// also tests puzzle_get_tile
void test_puzzle_set_tile(void) {
  int init[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };

  Puzzle *p4 = puzzle_create(4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j){
      puzzle_set_tile(p4, j, i, init[i][j]);
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      assert(puzzle_get_tile(p4, j, i) == init[i][j]);
    }
  }

  puzzle_destroy(p4);
}

void test_puzzle_validate_tile(void) {
  int init[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 7, 12 },
  };

  int poop[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };

  Puzzle *p5 = puzzle_create(4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      puzzle_set_tile(p5, j, i, poop[i][j]);
    }
  }

  Puzzle *p4 = puzzle_create(4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      puzzle_set_tile(p4, j, i, init[i][j]);
    }
  }

  assert(validate_tiles(p4)== 0);
  assert(validate_tiles(p5)== 1);
  puzzle_destroy(p4);
  puzzle_destroy(p5);
}

void test_V_command(void) {
  char moves[31] = {'\0'};
  char steps[] = "lurd";
  int result; 

  int test1[3][3] = {
    { 1, 2, 3},
    { 4, 5, 0},
    { 7, 8, 6},
  };

  int test2[3][3] = {
    { 0, 1, 2},
    { 4, 5, 3},
    { 7, 8, 6},
  };

  Puzzle *p3 = puzzle_create(3);
  Puzzle *p33 = puzzle_create(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      puzzle_set_tile(p3, j, i, test1[i][j]);
      puzzle_set_tile(p33, j, i, test2[i][j]);
    }
  }
    result = handle_V_command(p3, steps, 1, 0, moves, '\0');
  assert(result != 1);
  result = handle_V_command(p33, steps, 4, 0, moves, '\0');
  assert(result != 1);
  puzzle_destroy(p3);
  puzzle_destroy(p33);
}

void test_opposite(void){
  assert(opposite_direction('u')=='d');
  assert(opposite_direction('d')=='u');
  assert(opposite_direction('r')=='l');
  assert(opposite_direction('l')=='r');
  assert(opposite_direction('p')=='\0');
}

void test_S_command(void){
  int test[2][2] = {{0 , 1} , { 2, 3}};
  Puzzle *p2 = puzzle_create(2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      puzzle_set_tile(p2, j, i, test[i][j]);
    }
  }
  int result = handle_S_command(p2, 'd');
  assert(result == 0);
  result = handle_S_command(p2, 'r');
  assert(result == 0);
  result = handle_S_command(p2, 'u');
  assert(result == 1);
  result = handle_S_command(p2, 'u');
  assert(result == 0);
  result = handle_S_command(p2, 'l');
  assert(result == 1);
  result = handle_S_command(p2, 'l');
  assert(result == 0);

  puzzle_destroy(p2);
}

void test_W_command(void) {

  FILE* testw = fopen("test_file_1.txt", "w");
  fprintf(testw, "test1.ppm test1Puzzle.txt"); 
  fclose(testw);

  FILE* testr = fopen("test_file_1.txt", "r");

  int test[2][2] = {{1 , 2} , { 3, 0}};
  Puzzle *p2 = puzzle_create(2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      puzzle_set_tile(p2, j, i, test[i][j]);
    }
  }

  fclose(testr);

  puzzle_destroy(p2);
}

void test_K_command(void) {

  int testg[2][2] = {{1 , 2} , { 3, 0}};
  Puzzle *pg = puzzle_create(2);

  int testb[2][2] = {{1 , 0} , { 3, 2}};
  Puzzle *pb = puzzle_create(2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      puzzle_set_tile(pg, i, j, testg[i][j]);
      puzzle_set_tile(pb, i, j, testb[i][j]);
    }
  }

  assert(handle_K_command(pg) == 2);
  assert(handle_K_command(pb) == 1);
  puzzle_destroy(pg);
  puzzle_destroy(pb);

}

void test_P_command(void) {
  Puzzle *p = puzzle_create(0);
  assert(handle_P_command(p)== 0);
  puzzle_destroy(p);
}

void test_I_command(void){

  FILE* testw = fopen("test_file_2.txt", "w");
  fprintf(testw, "0 1 2 3"); 
  fclose(testw);

  FILE* testr = fopen("test_file_2.txt", "r");
  Puzzle *p = puzzle_create(2);

  assert(handle_T_command(testr, p) == 1);
  fclose(testr);
  puzzle_destroy(p);
}

void test_C_command(void) {

  FILE* testw1 = fopen("test_file_4.txt", "w");
  fprintf(testw1, "3"); 
  fclose(testw1);

  FILE* test2 = fopen("test_file_4.txt", "r");

  Puzzle *testg;

  assert(handle_C_command(test2, &testg) == 1);

  puzzle_destroy(testg);

  fclose(test2);
}


int main(void) {

  printf("Starting Tests...\n");
  
  test_puzzle_create();
  test_puzzle_set_tile();
  test_puzzle_validate_tile();
  test_V_command();
  test_opposite();
  test_S_command();
  test_W_command();
  test_K_command();
  test_P_command();
  test_I_command();
  test_C_command();
  
  printf("All tests passed!\n");
  return 0;
}