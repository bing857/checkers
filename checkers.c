#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "checkers.h"
#define getName(var)  #var 


/* print_board
 * prints out the checkerboard
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the board.
 */
void print_board( char board[NUM_ROWS][NUM_COLS] )
{
        unsigned int i, j; 
        printf("   ");
        for(j=0;j<NUM_COLS;j++)
        {
                printf("%u ",j);
        }
        printf("\n");
        for(i=0;i<NUM_ROWS;i++)
        {
                printf("%u: ",i);
                for(j=0;j<NUM_COLS;j++)
                {
                        printf("%c ",board[i][j]);
                }
                printf("\n");
        }
}

/* line_helper
 * helper function for init board, edits line
 * inputs:
 *    char line[]  - array to edit
 *    char x - character to put into place
 *    int columns - # of columns in checkerboard
 *    int startpos - startpos of first checker in row
 * outputs:
 *    none. edits the line array.
 */
void line_helper(char line[] , char x, int columns, int startpos)
{
	int i = startpos;
	for(i; i<columns; i=i+2)
	{
		line[i]=x;
	}
		
}



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
void init_board(char board[NUM_ROWS][NUM_COLS])
{
	int i;
	int j;
	for(i=0;i<NUM_ROWS;i++)
	{
		for(j=0;j<NUM_COLS;j++)
		{
			board[i][j]='*';
		}
	}
	
	line_helper(board[0], 'b', NUM_COLS, 1);
	line_helper(board[1], 'b', NUM_COLS, 0);
	line_helper(board[2], 'b', NUM_COLS, 1);
	line_helper(board[5], 'w', NUM_COLS, 0);
	line_helper(board[6], 'w', NUM_COLS, 1);
	line_helper(board[7], 'w', NUM_COLS, 0);
	

}

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
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS], char player, 
						unsigned int row, unsigned int col)
{
	if(board[row][col]=='*')
	{
		board[row][col]=player; 
		return 1;
	}
	else
	{
		return 0;
	}
	
}

/* valid_move
 * checks if a move is valid, helper function for do_move
 * inputs:
 *    char player - piece to place
 *    int startrow - target start row #
 *    int startcol - target start col #
 *    int endrow - target end row #
 *    int endcol - target end col #
 * outputs:
 *    returns 0 for invalid move, 1 for valid, 2 for jump move
 */

int valid_move(char player, int startrow, int startcol, 
            int endrow, int endcol, char board[8][8])
{
    if ((endrow < 0 || endrow > 8)|| 
        (endcol < 0 || endcol > 8)|| 
        (startrow < 0 || startrow > 8)|| 
        (startcol < 0 || startcol > 8))
    {
        return 0;
    }

    // if (( player=='B' || player=='b') &&
    //     (board[startrow][startcol]!='b' ||
    //      board[startrow][startcol]!='B'))
    // {
    //     return 0;
    // } 

    // if (( player=='W' || player=='w') &&
    //     (board[startrow][startcol]!='w' ||
    //      board[startrow][startcol]!='W'))
    // {
    //     return 0;
    // } 
    if (player=='b')
    {
        if ((int)(endrow-startrow)==1 &&
            ((int)(endcol-startcol)==1 ||
            (int)(endcol-startcol)== -1))
        {
            if (board[endrow][endcol]=='*')
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if ((int)(endrow-startrow)==2 &&
                ((int)(endcol-startcol)==2 ||
                (int)(endcol-startcol)== -2))
        {
            if (((board[(startrow+endrow)/2][(startcol+endcol)/2]=='w') ||
               (board[(startrow+endrow)/2][(startcol+endcol)/2]=='W')) &&
               (board[endrow][endcol]=='*'))
            {
                return 2;
            } 
            else
            {
                return 0;
            }
            
        }
        else
        {
            return 0;
        }
    }

    else if (player=='w')
    {
        if ((int)(endrow-startrow) == -1 &&
            ((int)(endcol-startcol) == 1 ||
            (int)(endcol-startcol) == -1))
        {
            if (board[endrow][endcol]=='*')
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if ((int)(endrow-startrow)==-2 &&
                ((int)(endcol-startcol)==2 ||
                (int)(endcol-startcol)== -2 ))
        {
            if (((board[(startrow+endrow)/2][(startcol+endcol)/2]=='b') ||
               (board[(startrow+endrow)/2][(startcol+endcol)/2]=='B')) &&
               (board[endrow][endcol]=='*'))
            {
                return 2;
            } 
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    else if (player=='B')
    {
        if  (((int)(endrow-startrow) == -1 &&
            ((int)(endcol-startcol) == 1 ||
            (int)(endcol-startcol) == -1)) ||
            ((int)(endrow-startrow)==1 &&
            ((int)(endcol-startcol)==1 ||
            (int)(endcol-startcol)== -1)))

        {
            if (board[endrow][endcol]=='*')
            {
                return 1;
            }
            else
            {
                return 0;
            }   
        }
        else if (((int)(endrow-startrow)==-2 ||
                (int)(endrow-startrow)==2 ) &&
                ((int)(endcol-startcol)==2 ||
                (int)(endcol-startcol)== -2 ))
        {
            if (((board[(startrow+endrow)/2][(startcol+endcol)/2]=='w') ||
               (board[(startrow+endrow)/2][(startcol+endcol)/2]=='W')) &&
               (board[endrow][endcol]=='*'))
            {
                return 2;
            } 
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }

    }

    else if (player=='W')
    {
        if  (((int)(endrow-startrow) == -1 ||
            (int)(endrow-startrow==1)) &&
            ((int)(endcol-startcol) == 1 ||
            (int)(endcol-startcol) == -1 ))
        {
            if (board[endrow][endcol]=='*')
            {
                return 1;
            }
            else
            {
                return 0;
            }   
        }
        else if (((int)(endrow-startrow)==-2 ||
                (int)(endrow-startrow)==2 ) &&
                ((int)(endcol-startcol)==2 ||
                (int)(endcol-startcol)== -2 ))
        {
            if ((board[(startrow+endrow)/2][(startcol+endcol)/2]=='b' ||
               board[(startrow+endrow)/2][(startcol+endcol)/2]=='B') &&
               board[endrow][endcol]=='*')
            {
                return 2;
            } 
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
        

    }



    else
    {
        return 0;
    }
    


}

/* player_won
 * checks if player has won the game
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - gameboard
 *    char player - piece to place
 * outputs:
 *    1 if player won, 0 otherwise
 */
int player_won(char board[NUM_ROWS][NUM_COLS], char player)
{
    //no more opponent pieces
    int i;
    int j;
    int k;
    int l;
    char opponent;
    char opponent_king;

    if ((player=='b') || (player=='B'))
    {
        opponent='w';
        opponent_king='W';
    }
    else
    {
        opponent='b';
        opponent_king='B';
    }


    for(i=0;i<NUM_ROWS-1;i++)
    {
        for(j=0;j<NUM_COLS-1;j++)
        {
            // printf("%c", board[i][j]);
            if (board[i][j]==opponent)
            { 
                if (valid_move(opponent, i, j, i+1, j+1, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i-1, j-1, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i-1, j+1, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i+1, j-1, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i-2, j-2, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i+2, j+2, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i-2, j+2, board)>0)
                        {
                            return 0;
                        }
                if (valid_move(opponent, i, j, i+2, j-2, board)>0)
                        {
                            return 0;
                        }
            }
            else if (board[i][j]=='W')
            {
                for(k=-2;k<3;k++)
                  {
                      for(l=-2;l<3;l++)
                      {
                          if (valid_move('W', 
                          i, j, i+k, j+l, board)==1)
                          {
                              return 0;
                          }
                      }
                  }
            }
            
        }
    }

    return 1;

}

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

unsigned int do_move(char player, unsigned int startrow, 
unsigned int startcol,
unsigned int endrow, unsigned int endcol, char board[8][8])
{
    int a = valid_move(player, startrow, startcol, endrow, endcol, board);
    if (a==0)
    {
        return 0;
    }
    else if (a==1)
    {
        board[endrow][endcol]=board[startrow][startcol];
        board[startrow][startcol]='*';
        return 1;
    }
    else if (a==2)
    {
        board[endrow][endcol]=board[startrow][startcol];
        board[startrow][startcol]='*';
        board[(startrow+endrow)/2][(startcol+endcol)/2]='*';
        return 2;
    }
}

/* plays_checkers
 * starts game of checkers
 * inputs:
 *    none
 * outputs:
 *    none
 */
void play_checkers()
{
    char again;
	char board[8][8] = {    {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'},
                            {'*','*','*','*','*','*','*','*'}  };
        init_board(board);
	int winner = 0;
	char player_turn = 'B';
	while (winner == 0)
	{
		unsigned int sr, sc, er, ec;
		unsigned int response;
		
		// obtain the player's move
		do {
			printf("Player %c, in what row (0-7) is" 
            "the piece you are moving located? ",player_turn);
			scanf("%u",&sr);
			if (sr >= NUM_ROWS)
				printf("That is not a valid row. Try again.\n");
		} while (sr >= NUM_ROWS);
		do {
			printf("Player %c, in what column (0-7) is the piece" 
            "you are moving located? ",player_turn);
			scanf("%u",&sc);
			if (sc >= NUM_COLS)
				printf("That is not a valid column. Try again.\n");
		} while (sc >= NUM_COLS);
		do {
			printf("Player %c, to what row (0-7) do you want to" 
            "move it? ",player_turn);
			scanf("%u",&er);
			if (er >= NUM_ROWS)
				printf("That is not a valid row. Try again.\n");
		} while (er >= NUM_ROWS);
		do {
			printf("Player %c, to what column (0-7) do you want" 
            "to move it? ",player_turn);
			scanf("%u",&ec);
			if (ec >= NUM_COLS)
				printf("That is not a valid column. Try again.\n");
		} while (ec >= NUM_COLS);

		// attempt to do the move
		response = do_move(player_turn, sr, sc, er, ec, board);

                // invalid move
                if (response == 0)
                {
                        printf("That is not a valid move. Try again.\n");
                }       
                // valid move, switch to other player
                else if (response == 1)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
                                printf("Valid move. Next player's turn\n");
                                player_turn = (player_turn == 'B'?'W':'B');
                        }       
                        else
                                printf("Congratulations! Player"
                                "%c won!\n",player_turn);
                }               
                // captured opponent's piece - gets another turn
                else // if (response == 2)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
                                printf("You jumped your opponent!\n");
                                do { 
                                        printf("Would you like"
                                        " to move again?\n");
                                        printf("Enter y for yes"
                                        " or n for no: \n");
                                        scanf("%c",&again);
                                        if (again == 'n')
                                        {                
                                                player_turn = 
                                                (player_turn == 'B'?'W':'B');
                                        }       
                                        else if (again != 'y')
                                        {
                                                printf("Invalid response.\n");
                                        }       
                                } while ((again == 'n') || (again == 'y'));
                        }       
                        else
                                printf("Congratulations! Player"
                                " %c won!\n",player_turn);
                }   

	} // end of while no winner
}

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
unsigned int *row, unsigned int *col)
{
    int i;
    int j;
    int k;
    int l;
        
    char player_normal;
    char player_king;
    if ((player=='b') || (player=='B'))
    {
        player_normal='b';
        player_king='B';
    }
    else
    {
        player_normal='w';
        player_king='W';
    }
    for(i=0;i<NUM_ROWS-1;i++)
    {
        for(j=0;j<NUM_COLS-1;j++)
        {
            if (board[i][j]==player_normal)
            { 
                for(k=-2;k<3;k++)
                {
                    for(l=-2;l<3;l++)
                    {
                        if (valid_move(player_normal, 
                        i, j, i+k, j+l, board)>0)
                        {
                            printf("move from %d %d to %d %d", i, j, i+k, j+l);
                            do_move(player_normal, i, j, i+k, j+l, board);
                            *row=i+k;
                            *col=j+l;
                            return 1;
                        }
                    }
                }
            }
            else if (board[i][j]==player_king)
            {
                for(k=-2;k<3;k++)
                  {
                      for(l=-2;l<3;l++)
                      {
                          if (valid_move(player_king, i, j, i+k, j+l, board)>0)
                          {
                              do_move(player_king, i, j, i+k, j+l, board);
                              *row=i+k;
                              *col=j+l;  
                              return 1;
                          }
                      }
                  }
            }
        }
    }
    return 0;
}


/***********************************************************
********** PLACE OTHER TEST FUNCTIONS HERE *****************
***********************************************************/
/* test_place_piece
 * This tests the extract_digit function
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - input board
 *    char player - player piece to place
 *    unsigned int row - row to place piece
 *    unsigned int col - column to place piece
 *    int expected - expected result
 * outputs:
 *    uint success - 0 for failure, 1 for success
 */
unsigned int test_place_piece(char board[NUM_ROWS][NUM_COLS],
    char player, unsigned int row, unsigned int col, int expected)
{
	int result = place_piece(board, player, row, col);
	if (result == expected)
	{
		printf("place_piece(%s, %c, %u, %u) = %u. Success\n",
			getName(board), player, row, col, result);
		return 1;
	}
	else
	{
		printf("place_piece(%s, %c, %u, %u) = %u. Expected %u. FAILURE\n",
			getName(board), player, row, col, result, expected);
		return 0;
	}
}






unsigned int test_player_won(char board[NUM_ROWS][NUM_COLS], 
char player, int expected)
{
	int result = player_won(board, player);
	if (result == expected)
	{
		printf("player_won(board, %c) = %d. Success\n",
			player, result);
		return 1;
	}
	else
	{
		printf("player_won(board, %c) = %d. Expected %u. FAILURE\n",
			player, result, expected);
		return 0;
    }

}
unsigned int test_do_move(char player, unsigned int startrow, 
unsigned int startcol, unsigned int endrow, unsigned int endcol, 
char board[8][8], unsigned int expected)
{
	unsigned int result = do_move(player, startrow, startcol, 
    endrow, endcol, board);
	if (result == expected)
	{
		printf("test_do_move(player, startrow, startcol," 
    "endrow, endcol, board, expected) = %u. Success\n",
			result);
		return 1;
	}
	else
	{
		printf("test_do_move(player, startrow, startcol, " 
    "endrow, endcol, board, expected) = %u. Expected %u. FAILURE\n",
			result, expected);
		return 0;
    }

}

// int computer_move(char board[NUM_ROWS][NUM_COLS], char player, unsigned int *row, unsigned int *col)



/* test_checkers()
 * tests all functions
 * inputs:
 *    none.
 * outputs:
 *    none.
 */
void test_checkers()
{
 	char startboard[8][8];
    char board1a[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','b','*'},
                          {'*','*','*','*','*','b','*','b'},
                          {'*','*','b','*','b','*','*','*'},
                          {'*','*','*','W','*','*','*','*'},
                          {'*','*','*','*','b','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };

    char board2a[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','b','*'},
                          {'*','*','*','*','*','b','*','b'},
                          {'*','*','b','*','b','*','*','*'},
                          {'*','*','*','W','*','*','*','*'},
                          {'*','*','*','*','b','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };
    
    char board3a[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','b','*','*','*','b','*'},
                          {'*','b','*','*','*','b','*','b'},
                          {'W','*','b','*','b','*','*','*'},
                          {'*','b','*','W','*','*','*','*'},
                          {'*','*','b','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };
    char board1[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','b','*'},
                          {'*','*','*','*','*','b','*','b'},
                          {'*','*','b','*','b','*','*','*'},
                          {'*','*','*','W','*','*','*','*'},
                          {'*','*','*','*','b','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };

    char board2[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','b','*'},
                          {'*','*','*','*','*','b','*','b'},
                          {'*','*','b','*','b','*','*','*'},
                          {'*','*','*','W','*','*','*','*'},
                          {'*','*','*','*','b','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };
    
    char board3[8][8] = { {'*','*','*','*','*','*','*','*'},
                          {'*','*','b','*','*','*','b','*'},
                          {'*','b','*','*','*','b','*','b'},
                          {'W','*','b','*','b','*','*','*'},
                          {'*','b','*','W','*','*','*','*'},
                          {'*','*','b','*','b','*','*','*'},
                          {'*','*','*','*','*','*','*','*'},
                          {'*','*','*','*','*','*','*','*'}  };

    print_board(board1a);
    print_board(board2a);
    print_board(board3a);
    test_place_piece(board1a, 'w', 1, 1, 1);
	print_board(board1a);
	test_place_piece(board2a, 'w', 2, 2, 1);
	print_board(board2a);
	test_place_piece(board3a, 'w', 3, 3, 1);
	print_board(board3a);
    init_board(startboard);
    print_board(startboard);
    test_player_won(board3, 'b', 1);
    test_player_won(board1, 'b', 0);
    test_player_won(board2, 'w', 0);
    test_player_won(board2, 'b', 0);
    test_do_move('W', 4, 3, 
            5, 4, board3, 0);
    test_do_move('b', 5, 4, 
            6, 5, board3, 1);
    test_do_move('b', 6, 5, 
            7, 6, board3, 1);
    test_do_move('W', 4, 3, 
            6, 5, board2, 2);
    print_board(startboard);
    printf("%d\n", valid_move('b', 2, 1, 
            3, 0, board3));
    unsigned int roww;
    unsigned int *row;
    row=&roww;
    unsigned int coll;
    unsigned int *col;
    col=&coll;
    computer_move(startboard, 'b', row, col);
    printf("computer_move: move 1\n");
    print_board(startboard);
    computer_move(startboard, 'w', row, col);
    printf("computer_move: move 2\n");
    print_board(startboard);
    computer_move(startboard, 'b', row, col);
    printf("computer_move: move 3\n");
    print_board(startboard);

}