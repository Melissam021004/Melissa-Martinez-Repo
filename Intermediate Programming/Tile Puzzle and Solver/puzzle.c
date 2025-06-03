#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ppm_io.h"
#include "puzzle.h"

int main(int argc, char **argv) {

    int temp;
    char direct;
    char moves[31] = {'\0'};
    int max_steps = 1;
    int cur_steps = 0;
    char steps[] = "lurd";
    int result; 
    int valid = 0;
    int t_used = 0;
    int c_used = 0;
    int temp_two = 0; 

  if (argc < 1 || argc > 2) {
    fprintf(stderr, "Usage: ./puzzle [<command file>]\n");
    return 1;
  }

  char com = '\0';
  Puzzle *p1 = NULL;

  FILE* fp = NULL;

  //A file is specified in the command line
  if (argc == 2){

    fp = fopen(argv[1], "r");

    //Checks if file openend successfully, ends program if not
    if(fp == NULL || ferror(fp)){
      fprintf(stderr, "Could not open input file %s\n", argv[1]);
      puzzle_destroy(p1);
      return 1;
    }

  }

  //Handles all of the commands
  while((fp != NULL && fscanf(fp, " %c", &com) == 1) || (fp == NULL && scanf(" %c", &com) == 1)){

    switch(com){

      //Creates a puzzle
      case('C'):
        if (c_used == 1) {
          if (p1 != NULL) {
            puzzle_destroy(p1);
          }
        }
        if((handle_C_command(fp, &p1)) == 0){
          if(fp != NULL) {
            fclose(fp);
            }
          if (p1 != NULL) {
            puzzle_destroy(p1);
          }
          return 1;
        }

        c_used = 1;
        break;

      //Initialize puzzle configuration with series of tile numbers
      case('T'):
        if(handle_T_command(fp, p1) == 0){
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        if(validate_tiles(p1) == 0){
          fprintf(stderr, "Invalid tile value\n");
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        t_used = 1;
        break;

      //Load the background image from specified PPM file
      case('I'):
        if(handle_I_command(fp, p1) == 0){
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        break;

      //Print sequence of tile numbers reflecting current puzzle configuration
      case('P'):
        if(handle_P_command(p1) == 0){
          fprintf(stderr, "No puzzle\n");
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        break;

      //Write puzzle image to first file and puzzle configuration to second file
      case('W'):
        if(handle_W_command(fp, p1) == 0){
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        break;

      //Slide a free tile in specified direction
      case('S'):
        if (t_used == 1) {
          if((fp == NULL && scanf(" %c", &direct) == 1) || 
            (fp != NULL && fscanf(fp, " %c", &direct) == 1)){
              temp_two = 1;

            temp = handle_S_command(p1, direct);
            
            // Checks the two errors possible
            if(temp == 0){
              fprintf(stderr, "Puzzle cannot be moved in specified direction\n");
              if(fp != NULL) {fclose(fp);}
              puzzle_destroy(p1);
              return 1;
            }
            else if (temp == 2) {
              fprintf(stderr, "Invalid input\n");
              if(fp != NULL) {fclose(fp);}
              puzzle_destroy(p1);
              return 1;
            }
          }
        }
        else if (t_used == 0) {
          fprintf(stderr, "Puzzle cannot be moved in specified direction\n");
          if(fp != NULL) {fclose(fp);}
            puzzle_destroy(p1);
          return 1;
        }
        if (temp_two == 0) {
          fprintf(stderr, "Invalid input\n");
          if(fp != NULL) {fclose(fp);}
            puzzle_destroy(p1);
            return 1;
          }
        temp_two = 0;
        break;

      //Check to see whether the puzzle is in the “winning” configuration
      case('K'):
        valid = handle_K_command(p1);
        if(valid == 0){
          if(fp != NULL) {fclose(fp);}
          puzzle_destroy(p1);
          return 1;
        }
        else if (valid == 1) {
          printf("Not solved\n");
        }
        else {
          printf("Solved\n");
        }
        break;

      //Compute a series of moves to solve the puzzle
      case('V'):
        if (t_used == 1) {
        for (max_steps = 1; max_steps <= 31; max_steps++) {
          result = handle_V_command(p1, steps, max_steps, cur_steps, moves, '\0');
          if (result != -1) {
            break;
          }
        }
        if (result != -1) {
          for (int i = 0; i < result; i++) {
            printf("S %c\n", moves[i]);
          }
        }
        else {
          printf("No solution found\n");
        }
        }
        else {
          printf("Solved\n");
        }

        break;

      //User quits the program
      case('Q'):
        if (p1 != NULL) {
        puzzle_destroy(p1);
        }
        if(fp != NULL) {fclose(fp);}
        return 0;
        break;

      default:
        fprintf(stderr, "Invalid command '%c'\n", com);
        if(fp != NULL) {fclose(fp);}
        return 1;
        break;
    }
  }

  puzzle_destroy(p1); 
  if(fp != NULL) {fclose(fp);}
  return 0;
}
