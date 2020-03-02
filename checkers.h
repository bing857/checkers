#ifndef FILENAME_H
#define FILENAME_H

#define NUM_ROWS 8
#define NUM_COLS 8




/* print_board
 * prints out the checkerboard
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the board.
 */
void print_board( char board[NUM_ROWS][NUM_COLS] );

/* init_board
 * initializes the contents of the checkerboard.
 * The blue pieces occupy rows 0 to (NUM_ROWS/2 - 2), and
 * the white pieces occupy rows (NUM_ROWS / 2 + 1) to NUM_ROWS-1
 * An 8x8 board looks like this:
   * b * b * b * b
   b * b * b * b *
   * b * b * b * b
   * * * * * * * *
   * * * * * * * *
   w * w * w * w *
   * w * w * w * w
   w * w * w * w *
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void init_board(char board[NUM_ROWS][NUM_COLS]);

/* valid_move
 * checks if a move is valid, helper function for do_move
 * inputs:
 *    char player - piece to place
 *    int startrow - target start row #
 *    int startcol - target start col #
 *    int endrow - target end row #
 *    int endcol - target end col #
 * outputs:
 *    uint 1 if successful, 0 if otherwise.
 */
// returns 0 for invalid move, 1 for valid, 2 for jump move
int valid_move(char player,  int startrow,  int startcol, 
             int endrow,  int endcol, char board[8][8]);
/* place_piece
 * places a piece on the board if spot is empty
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 *    char player - piece to place
 *    uint row - target row #
 *    uint col - target col #
 * outputs:
 *    uint 1 if successful, 0 if otherwise.
 */
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS],
            char player, unsigned int row, unsigned int col);

void play_checkers();

/* player_won
 * checks if player has won the game
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - gameboard
 *    char player - piece to place
 * outputs:
 *    1 if player won, 0 otherwise
 */
int player_won(char board[NUM_ROWS][NUM_COLS], char player);
/* do move
 * checks if a move is valid, and does move
 * inputs:
 *    char player - piece to place
 *    int startrow - target start row #
 *    int startcol - target start col #
 *    int endrow - target end row #
 *    int endcol - target end col #
 * outputs:
 *    returns 0 for invalid move, 1 for valid, 2 for jump move
 */

unsigned int do_move(char player, unsigned int startrow, unsigned int startcol, 
                     unsigned int endrow, unsigned int endcol, 
                     char board[8][8]);
/* computer_move
 * computer makes a move
 * inputs:
 *    har board[NUM_ROWS][NUM_COLS] - input board
 *    char player - piece to place
 *    uint *row - end row #
 *    uint *col - end col #
 * outputs:
 *    returns 0 for invalid move, 1 for valid, 2 for jump move
 */
int computer_move(char board[NUM_ROWS][NUM_COLS], char player, 
                unsigned int *row, unsigned int *col);
/* test_checkers()
 * tests all functions
 * inputs:
 *    none.
 * outputs:
 *    none.
 */
void test_checkers();








#endif