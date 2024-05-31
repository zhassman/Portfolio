#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum opt_command {NONE=0, LEFT=1, UP=2, RIGHT=3, DOWN=4, HELP=5, QUIT=6};

enum opt_command get_command(){
// read key from the user and passes the command to the main function
  int c = getchar();

  if (c == 'w'){
    return UP;
  }
  if (c == 'd'){
    return RIGHT;
  }
  if (c == 's'){
    return DOWN;
  }
  if (c == 'a'){
    return LEFT;
  }
  if (c == 'h'){
    return HELP;
  }
  if (c == 'q'){
    return QUIT;
  }
  return NONE;
}

char *board_new(){
// generate new board with characters in correct spots
  char chars[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 
                                 'A','B','C', 'D','E','F','_'};
  char* board = (char*)malloc(16 * sizeof(char));
  for (int i = 0; i < 16; i++){
    board[i] = chars[i];
  }
  return board;
}

int empty_cell(char *board){
// return the index of the empty cell '_' in the board array
  for (int i = 0; i < 15; i++){
    if (board[i] == '_'){
      return i;
    }
  }
  return 15;
}

int up_neighbor(int i){
// return the index of the "up neighbor" of the given index
// return -1 if there is no up neighbor
  if (i < 4){
    return -1;
  }
  return i - 4;
}

int down_neighbor(int i){
// return the index of the "down neighbor" of the given index
// return -1 if there is no down neighbor
  if (i > 11){
    return -1;
  }
  return i + 4;
}

int left_neighbor(int i){
// return the index of the "left neighbor" of the given index
// return -1 if there is no left neighbor
  if ((i % 4) == 0){
    return -1;
  }
  return i - 1;
}

int right_neighbor(int i){
// return the index of the "right neighbor" of the given index
// return -1 if there is no right neighbor
  if (((i + 1) % 4) == 0){
    return -1;
  }
    return i + 1;
}

void swap_with_empty(char *board, int empty_ind, int char_ind){
 //swaps the character at a given index with the empty character, '_'
  board[empty_ind] = board[char_ind];
  board[char_ind] = '_';
}

void slide_left(char *board){
// if it is possible to slide a tile left into the gap, slide it
// otherwise, perform no action
  int empty_ind = empty_cell(board);
  int right_ind = right_neighbor(empty_ind);
  if (right_ind != -1){
    swap_with_empty(board, empty_ind, right_ind);
  }
}

void slide_right(char *board){
// if it is possible to slide a tile right into the gap, slide it
// otherwise, perform no action
  int empty_ind = empty_cell(board);
  int left_ind = left_neighbor(empty_ind);
  if (left_ind != -1){
    swap_with_empty(board, empty_ind, left_ind);
  }
}
 

void slide_up(char *board){
// if it is possible to slide a tile up into the gap, slide it
// otherwise, perform no action
  int empty_ind = empty_cell(board);
  int down_ind = down_neighbor(empty_ind);
  if (down_ind != -1){
    swap_with_empty(board, empty_ind, down_ind);
  }
}

void slide_down(char *board){
// if it is possible to slide a tile down into the gap, slide it
// otherwise, perform no action
  int empty_ind = empty_cell(board);
  int up_ind = up_neighbor(empty_ind);
  if (up_ind != -1){
    swap_with_empty(board, empty_ind, up_ind);
  }
}

void perform_move(char *board, int command){
// executes the move instruction from the given command
  if (command == LEFT){
    slide_left(board);
  }
  else if (command == UP){
    slide_up(board);
  }
  else if (command == RIGHT){
    slide_right(board);
  }
  else if (command == DOWN){
    slide_down(board);
  }
}

void shuffle(char *board, unsigned int n){
// perform n moves at random to shuffle the board
  srand(time(NULL));
  for (int i = 0; i < n; i++){
    int random_int = (rand() % 4) + 1;
    perform_move(board, random_int);
  }
}


void show_board(char *board){
// given a char-array board, print a 2D representation to stdout
  for (int i = 0; i < 16; i++){
    putchar(board[i]);
    if (((i + 1) % 4) == 0){
      putchar('\n');
    }
    else{
      putchar(' ');
    }
  }
}

int solved(char *board){
// return 0 if the board is not in solved position
// return nonzero if the board is in solved position
  char chars[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 
                                 'A','B','C', 'D','E','F','_'};
  for (int i = 0; i < 16; i++){
    if (board[i] != chars[i]){
      return 0;
    }
  }
  return 1;
}

void display_help()
{
  printf("w: slide up (if possible)\n");
  printf("d: slide right (if possible)\n");
  printf("s: slide down (if possible)\n");
  printf("a: slide left (if possible)\n");
  printf("h: help\n");
  printf("q: quit\n");
  printf("\n");
}

int main(int argc, char *argv[])
{
  system("figlet SLIDE 15");
  char *board = board_new();
  int shuffles = 1000;
  if (argv[1]){
    shuffles = atoi(argv[1]);
  }
  shuffle(board, shuffles);
  show_board(board);
  while(1){
    if (solved(board)){
      system("figlet You Win!");
      break;
    }
    int command = get_command();
    if (command == 6){
      system("figlet Bye!");
      break;
    }
    else if (command == 5){
      putchar('\n');
      display_help();
      continue;
    }
    else if (command == 0){
      continue;
    }
    else{
      perform_move(board, command);
      putchar('\n');
      show_board(board);
      }
    }
  }
