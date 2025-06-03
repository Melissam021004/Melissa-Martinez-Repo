#ifndef PUZZLE_H
#define PUZZLE_H

#include "ppm_io.h" // for Image data type

typedef struct {
  int size;
  int *tiles;
  Image *im;
} Puzzle;

/* puzzle_create
 * Creates a puzzle struct with the given dimensions
 * and sets all tiles to 0 after dynamically allocating
 * the memory needed for those tiles
 * Returns a pointer to the newly made puzzle
 */
Puzzle *puzzle_create(int size);

/* puzzle_destroy
 * frees all dynamically allocated memory 
 * associated with the passed puzzle
 */
void puzzle_destroy(Puzzle *p);

/* puzzle_set_tile
 * Sets the tile at the given row,column location 
 * with the given value
 */
void puzzle_set_tile(Puzzle *p, int col, int row, int value);

/* puzzle_get_tile
 * Gets the number of the tile at the specified row and column
 * Returns the afromentioned tile number
 */
int puzzle_get_tile(const Puzzle *p, int col, int row);

/* validate_tiles
 * Validates that there are no tile duplicates in the puzzle
 * Returns 1 if no duplicates of tiles, 0 if there are
 */
int validate_tiles(Puzzle *p);

/* handle_C_command
 * Will create a new puzzle based on the size indicated by the file
 * Returns 1 if successful and 0 otherwise
 */
int handle_C_command(FILE *in, Puzzle **p);

/* handle_T_command
 * Will scan in file or the command line for the tile contents
 * and validates if each tile is within [0, N^2), then stores
 * the tile values in the order they were given in row-major order
 * into the puzzle's tiles
 * Returns 1 if all tile values are valid and if 
 * the correct number of values were provided, 0 otherwise
 */
int handle_T_command(FILE *in, Puzzle *p);

/* handle_I_command
 * Opens up the image for the puzzle
 * and validates that it was read properly
 * Returns 1 if read and opened without errors, 0 otherwise
 */
int handle_I_command(FILE *in, Puzzle *p);

/* handle_W_command
 * Scans input for two file names, the first which will be
 * written with the PPM image contents of the current puzzle.
 * The second which will be written with the puzzle's
 * current configuration in row-major order
 * Returns 1 if successful, 0 otherwise
 */
int handle_W_command(FILE *in, Puzzle *p);

/* handle_P_command
 * Prints out to the command line the order of
 * the puzzle's configuration in row-major order
 * Returns 1 if successful, 0 if no puzzle exists
 */
int handle_P_command(Puzzle *p);

/* handle_K_command
 * Checks to see if the current configuration is correct
 * Prints "solved" or "not solved" depending on above
 * Returns 1 if not solved, 2 if solved, 0 if no puzzle has been created
 */
int handle_K_command(Puzzle *p);

/* handle_V_command
 * Tries to solve the current configuration by brute force
 * Attempts until 31 moves, and stores/rewrites the move into the array; takes into account previous move
 * Returns -1 if failed and positive number if it succeeds
 */
int handle_V_command(Puzzle *p, char* steps, int max_steps, int cur_steps, char moves[], char prev_move);

/* handle_S_command
 * Moves the black tile to the opposite direction of the command or the tile located in that direction to the spot of the black tile
 * Returns 1 if success, 0 if the move is not legal, or 2 if the direction in not one of the 4 logic moves given.
 */
int handle_S_command(Puzzle *p, char direct);

/* make_copy
 * Makes a exact replica of the puzzle that is inputted into the function
 * Copies the size, im, and tiles
 */
Puzzle *make_copy(Puzzle *p);

/* opposite_direction
 * Returns the opposite direction of the one given
 * If the letter is not one of the puzzle logic returns \0
 */
char opposite_direction(char dir);

#endif // PUZZLE_H
