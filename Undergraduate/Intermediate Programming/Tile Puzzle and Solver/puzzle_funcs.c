#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "puzzle.h"

void puzzle_destroy(Puzzle *p){
    
    //Doesn't do anything if the puzzle doesn't exist
    if (p == NULL) {
        return;
    }
    
    //Frees tiles if initialized
    if (p->tiles != NULL) {
        free(p->tiles);
    }

    //Frees the image and its data if initialized
    if (p->im != NULL) {
        if (p->im->data != NULL) {
            free(p->im->data);
        }
        free(p->im);
    }

    free(p);
}

void puzzle_set_tile(Puzzle *p, int col, int row, int value){
    p->tiles[(p->size)*col + row] = value;
}

int puzzle_get_tile(const Puzzle *p, int col, int row){

    return p->tiles[4*col + row];
}

int validate_tiles(Puzzle *p){

    //Initializing counter array
    int a[(p->size) * (p->size) + 1];

    //Setting counter array to 0
    for(int i = 0; i < ((p->size) * (p->size) + 1); i++){
        a[i] = 0;
    }

    //Making sure there is 1 of every number
    for(int i = 0; i < ((p->size) * (p->size)); i++){
        int val = p->tiles[i];
        a[val] += 1;

        //Checking if duplicates exist
        if(a[val] >1){
            return 0;
        }
    }

    return 1;
}

int handle_V_command(Puzzle *p, char* steps, int max_steps, int cur_steps, char moves[], char prev_move) {

    // checks to see if there is puzzle
    if (p->size <= 0) {
        fprintf(stderr, "No puzzle\n");
        return -1;
    }

    // If there is a correct configuration return a non -1 number
    if (handle_K_command(p) == 2) {
        return cur_steps; 
    }

    // if the current steps reach past the max steps return -1
    if (cur_steps >= max_steps) {
        return -1;
    }

    // Tries through all the 4 moves before failing
    for (int i = 0; i < 4; i++) {

        //Checks to see that the previous move is not the opposite of current move
        if (steps[i] != opposite_direction(prev_move)) {

            // Makes copy and performs the move
            Puzzle *copy = make_copy(p);
            if (handle_S_command(copy, steps[i])) {

                //puts the move in the array
                moves[cur_steps] = steps[i];

                // Tries the next move to see if wins
                int result = handle_V_command(copy, steps, max_steps, cur_steps + 1, moves, steps[i]);

                // If it is win config
                if (result != -1) {
                    free(p->tiles);
                    p -> tiles = copy->tiles;
                    free(copy); 
                    return result;
                }

                // Not win config
                else {
                    free(copy->tiles);
                    free(copy);
                }
            }

            // Not win config
            else {
                free(copy->tiles);
                free(copy);
            }
        }
    }

    return -1;
       
}

char opposite_direction(char dir) {

    // Returns the opposite of what character gives you based on the slide logic
    switch (dir) {
        case 'u':
            return 'd';
        case 'd':
            return 'u';
        case 'l':
            return 'r';
        case 'r':
            return 'l';
        default:
            return '\0';
    }
}

int handle_S_command(Puzzle *p, char direct) {

    
    int where = 0;

    // Finds where the "0" tile is located
    for (int i = 0; i < (p->size) * (p->size); i++) {
        if (p->tiles[i] == 0) {
            where = i;
        }
    }
    
    int temp = 0;       

    switch (direct) {

        case 'd' :

            // If the black tile is on the top row: error
            if (where < p->size) {
                return 0;
            }

            // Moves the tile up 
            else {
                temp = p->tiles[where - p->size];
                p->tiles[where - p->size] = 0;
                p->tiles[where] = temp;
            }
            break;

        case 'r' : 

            // If the black tile is on the leftmost row: error
            if (where % p->size == 0) {
                return 0;
            }

            // Moves the black tile left 
            else {
                temp = p->tiles[where - 1];
                p->tiles[where - 1] = 0;
                p->tiles[where] = temp;
            }
            break;

        case 'l' : 

            // If the black tile is on the rightmost row: error
            if (where % (p->size) == (p -> size -1)) {
                return 0;
            }

            // Moves the black tile right 
            else {
                temp = p->tiles[where + 1];
                p->tiles[where + 1] = 0;
                p->tiles[where] = temp;
            }
            break;

        case 'u' :

            // If the black tile is on the bottom row: error
            if (where / p->size == p -> size -1) {
                return 0;
            }

            // Moves the black tile down
            else {
                temp = p->tiles[where + p->size];
                p->tiles[where + p->size] = 0;
                p->tiles[where] = temp;
            }
            break;

        default :

            //invalid input
            return 2;
        }
    
    // returns success 
    return 1; 
}

int handle_W_command(FILE *in, Puzzle *p){

    //Validating that a puzzle exists
    if(p->size <= 0){
        fprintf(stderr, "No puzzle\n");
        return 0;
    }

    //Background image hasn’t been read
    if(p-> im == NULL){
        fprintf(stderr, "No image\n");
        return 0;
    }

    //Declaring arrays for names as well as files for image and configurations
    char im_file_name[255];
    char config_name[255];
    FILE* im_file;
    FILE* config_file;

    //Scanning and validating file names
    if((in == NULL && scanf(" %s %s", im_file_name, config_name) == 2) || 
        (in != NULL && fscanf(in, " %s %s", im_file_name, config_name) == 2)){

        im_file = fopen(im_file_name, "w");
        config_file = fopen(config_name, "w");

        //Output image file can’t be opened
        if(im_file == NULL){
            fprintf(stderr, "Could not open output image file '%s'\n", im_file_name);
            return 0;
        }

        //Output puzzle configuration file can’t be opened
        if(config_file == NULL){
            fprintf(stderr, "Could not open output puzzle file %s\n", config_name);
            return 0;
        }

    }

    //Didn't provide two file names
    else{
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    //Writing puzzle configuration to file
    for(int i = 0; i < (p->size) * (p->size); i++){
        fprintf(config_file, "%d ", p->tiles[i]);
    }

    //Checking if configuration file is in an error state
    if(ferror(config_file) != 0){
        fprintf(stderr, "Could not write puzzle data %s\n", config_name);
        return 0;
    }

    //Background image rows or columns not evenly divisible by puzzle rows/columns
    if(((p->im->cols) % (p->size) != 0) || ((p->im->rows) % (p->size) != 0)){
        fprintf(stderr, "Invalid image dimensions\n");
        return 0;
    }

    //Initializing image data
    Image *img;
    img = malloc(sizeof(Image));
    img->data = malloc(sizeof(Pixel) * (p->im->cols) * (p->im->rows));
    img->rows = p->im->rows;
    img->cols = p->im->cols;

    //How many pixels the row/column of each tile
    int tile_rows = (p->im->rows) / (p->size);
    int tile_cols = (p->im->cols) / (p->size);
    int pixel_counter = 0;

    //Number of tile being written
    int tile_num;

    //Row and column of tile if in correct spot
    int tile_r;
    int tile_c;

    //Current row and column being written
    int row_loc;
    int col_loc;

    //Pixel to be printed for 0 tile
    Pixel black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    //Putting image data based on current puzzle into img
    
    //One loop for each row of tiles
    for(int i = 0; i < p->size; i++){

        //One loop for each row of pixels in a row of tiles
        for(int j = 0; j < tile_rows; j++){

            //One loop for each tile in a column
            for(int k = 0; k < p->size; k++){
                tile_num = p->tiles[(p->size)*i + k];

                //What the row and column would be in a solved puzzle
                tile_r = (tile_num - 1) / (p->size);
                tile_c = (tile_num - 1) % (p->size);

                row_loc = (tile_r * (img->cols) * tile_rows + (img->cols) * j);
                col_loc = (tile_c * tile_cols);

                //One loop for each pixel in a column of a tile
                for(int m = 0; m < tile_cols; m++){
                    
                    //Prints black pixel when tile is 0
                    if (tile_num == 0) {
                        img->data[pixel_counter] = black;
                        pixel_counter += 1;
                    }
                    //Prints actual pixel if tile isn't 0
                    else{
                        img->data[pixel_counter] = p->im->data[row_loc + col_loc + m];
                        pixel_counter += 1;
                    }
                }

            }
        }

    }
    //Writing and validating the image in the image file
    if(WritePPM(im_file, img) != ((p->im->cols)*(p->im->rows))){
        return 0;
    }

    //Freeing and closing all mallocs and used files
    free(img->data);
    free(img);
    fclose(im_file);
    fclose(config_file);
    return 1;
}

int handle_K_command(Puzzle *p){

    //Validating that a puzzle exists
    if(p->size <= 0){
        fprintf(stderr, "No puzzle\n");
        return 0;
    }

    //Making sure they're all in the correct configuration
    for(int i = 1; i <= (p->size)*(p->size); i++){
        if(p->tiles[i-1] != i){
            if(p->tiles[i-1] != 0){
                return 1;
            }
        }
    }

    return 2;
}

int handle_P_command(Puzzle *p){

    //Validating that a puzzle exists
    if(p->size <= 0){
        return 0;
    }

    //Printing out the order of the tiles
    for(int i = 0; i < (p->size)*(p->size); i++){
        fprintf(stdout,"%d ", p->tiles[i]);
    }

    //Final new line
    printf("\n");
    return 1;

}

int handle_I_command(FILE *in, Puzzle *p){

    //Char array to hold the image file name
    char name[255];

    if((in == NULL && scanf(" %s", name) == 1) || 
        (in != NULL && fscanf(in, " %s", name))){

        //Opening up image and reading it
        FILE* imagefile = fopen(name, "r");

        //Validating that the image was read
        if(imagefile == NULL || ferror(imagefile)){
            fprintf(stderr, "Could not open image file '%s'\n", name);
            return 0;
        }

        //Reading and assigning the image to the puzzle
        Image *ima = ReadPPM(imagefile);
        p->im = ima;

        fclose(imagefile);
        return 1;

    }

    fprintf(stderr, "Invalid input\n");
    return 0;
    
}

int handle_T_command(FILE *in, Puzzle *p){

    //Checking if puzzle has been initialized
    if(p->size <= 0){
        fprintf(stderr, "No puzzle\n");
        return 0;
    }

    int count = 0;
    int val;

   //Getting and validating values
    while((in == NULL && scanf(" %d", &val) == 1) ||
        (in != NULL && (fscanf(in, " %d", &val) == 1))){
        
        //Checking if tile value is within range
        if(val < 0 || val > ((p->size)*(p->size))){
            fprintf(stderr, "Invalid tile value\n");
            return 0;
        }
        //Putting the value into the array of tiles
        else{
            p->tiles[count] = val;
            count++;
        }

    }

    //Not enough values were provided
    if(count < (p->size)*(p->size)){
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    return 1;

}

int handle_C_command(FILE *in, Puzzle **p){

    int size;

    //Getting and validating size
    if((in == NULL && scanf(" %d", &size) == 1) || 
        (in != NULL && fscanf(in, "%d", &size) == 1)){
        
        //Checking if puzzle size is within range
        if(size < 2 || size > 20) {
            fprintf(stderr, "Invalid puzzle size\n");
            return 0;
        }

        //Create puzzle if size is within range
        else {
            *p = puzzle_create(size);
            return 1;
        }

    }

    //The argument after C was not a number
    fprintf(stderr, "Invalid input\n");
    return 0;

}

Puzzle *puzzle_create(int size){

    //Allocating memory and assigning size
    Puzzle *p = malloc(sizeof(Puzzle));
    p->size = size;
    p->tiles = malloc(size * size * sizeof(int));

    //Initializing tiles to 0
    for(int i = 0; i < size * size; i++){
        p->tiles[i] = 0;
    }

    return p;
}

Puzzle *make_copy(Puzzle *p){

    // copies information from the puzzle
    Puzzle *copy = malloc(sizeof(Puzzle));
    copy->size = p->size;
    copy->tiles = malloc(p->size * p->size * sizeof(int));
    copy->im = p->im;

    //Initializing tiles to the value of the original puzzle
    for(int i = 0; i < p->size * p->size; i++){
        copy->tiles[i] = p->tiles[i];
    }

    return copy;

}