/******************************************************************************
*
* File name: connect4_functions.c
*
* Author:  John Jane Doe
*          012345678
*          jjdoe@ucsd.edu
*
*
*     Lab #: 4
* Problem #: 1
*
******************************************************************************/


/*-----------------------------------------------------------------------------
   Include files
-----------------------------------------------------------------------------*/
#include "connect4_functions.h"
#include <time.h>
// If you would like to use standard library functions other than those
// declared in <stdio.h>, <stdlib.h>, <time.h>, <stdbool.h> (for which
// the #include directives are already given in connect4_functions.h), 
// you may #include the corresponding header files here.



/*=============================================================================
  Constants and definitions
=============================================================================*/

// If you would like to define constants other than BOARD_SIZE_HORIZ and 
// BOARD_SIZE_VERT, or if you would like to define new types, you may put 
// the corresponding #defines and typedefs here.



/*=============================================================================
  Global variables
=============================================================================*/

// If you would like to use global variables, declare them here.



/*=============================================================================
  Forward function declarations
=============================================================================*/

// If you would like to use functions other than those already declared in
// connect4_functions.h, put the forward declarations of these functions here.

int minimax(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int depth, int player_num, int lastMove, int bannedColumns[BOARD_SIZE_HORIZ]);
int heuristic(int board[][BOARD_SIZE_VERT], int player_num);
int runMinimax(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int depth, int player_num, int bannedColumns[BOARD_SIZE_HORIZ]);
int chooseColumn(int lastBoard[][BOARD_SIZE_VERT], int player_num, int opponent_num);
void bannedColumn(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int columnsthatareBanned[BOARD_SIZE_HORIZ], int player_num, int opponent_num);

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

                Function Definitions of Required Functions

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/******************************************************************************
*                                                                             *
*                       Function print_welcome()                              *
*                                                                             *
******************************************************************************/
int print_welcome(void)
{
	srand(time(NULL));
	int numInput;
	char option;
	printf("*** Welcome to the Connect Four game!!! ***\n");
	printf("Would you like to make the first move [y/n]: \n");
	scanf("%c", &option);
	if (option == 'n' || option == 'N')
	{
		while (((numInput = getchar()) != '\n') && ((numInput = getchar()) != EOF));
		return 2;
	}
	else
	{
		while (((numInput = getchar()) != '\n') && ((numInput = getchar()) != EOF));
		return 1;
	}
}

/******************************************************************************
*                                                                             *
*                      Function display_board()                               *
*                                                                             *
******************************************************************************/
void display_board(int board[][BOARD_SIZE_VERT])
{
	printf("\n");
	for (int i = 0; i < BOARD_SIZE_VERT; i++)
	{
		printf("+---+---+---+---+---+---+---+\n");
		printf("|");
		for (int j = 0; j < BOARD_SIZE_HORIZ; j++)
		{
			if (board[j][i] == 1)
				printf(" X |");
			else if (board[j][i] == 2)
				printf(" O |");
			else
				printf("   |");
		}
		printf("\n");
	}
	printf("+---+---+---+---+---+---+---+\n");
	for (int k = 1; k <= BOARD_SIZE_HORIZ; k++)
		printf("  %d ", k);
	printf(" \n\n");
}

/******************************************************************************
*                                                                             *
*                      Function random_move()                                 *
*                                                                             *
******************************************************************************/
int random_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
	int randomCol = rand() % BOARD_SIZE_HORIZ + 1;
	while(is_column_full(board, randomCol))
		randomCol = (rand() % BOARD_SIZE_HORIZ) + 1;
        update_board(board, randomCol, computer_num);
	return randomCol;
}

/******************************************************************************
*                                                                             *
*                      Function player_move()                                 *
*                                                                             *
******************************************************************************/
int player_move(int board[][BOARD_SIZE_VERT], int player_num)
{
	int numInput, tester;
	while (1)
	{	
		printf("Please enter your move: ");
		tester = scanf("%d", &numInput);
		if ((numInput < 1 || numInput > BOARD_SIZE_HORIZ) || tester != 1)
        	{
        	        printf("Not a valid move. Enter a column number!\n");
			while (getchar() != '\n');
        	}
		else
		{
			if(!is_column_full(board, numInput) && tester == 1)
			{
                		update_board(board, numInput, player_num);
				while (getchar() != '\n');
				break;
			}
			else
			{
				printf("This column is full. Try again!\n");
				while (getchar() != '\n');
			}
		}
	}
	return numInput;
}

/******************************************************************************
*                                                                             *
*                      Function check_win_or_tie()                            *
*                                                                             *
******************************************************************************/
bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move)
{
	//printf("The last move passed: %d", last_move);
	int result = check_winner(board, last_move);
	if (result == 1)
	{
		printf("*****************************\n");
		printf("* Player X won!!! Game over *\n");
		printf("*****************************\n");
		return true;
	}
	else if (result == 2)
	{
		printf("*****************************\n");
		printf("* Player O won!!! Game over *\n");
		printf("*****************************\n");
                return true;
	}
	else
	{
		for (int i = 0; i < BOARD_SIZE_HORIZ; i++)
			for (int j = 0; j < BOARD_SIZE_VERT; j++)
				if (board[i][j] == 0)
					return false;
		printf("*****************************\n");
		printf("* Game is a tie!! No winner *\n");
		printf("*****************************\n");
		return true;
	}
}

/******************************************************************************
*                                                                             *
*                     Function is_column_full()                               *
*                                                                             *
******************************************************************************/
bool is_column_full(int board[][BOARD_SIZE_VERT], int m)
{
	int counter = 0;
	for (int i = 0; i < BOARD_SIZE_VERT; i++)
	{
		if (board[m-1][i] != 0)
			counter++;
		else
			break;
	}
	if (counter != BOARD_SIZE_VERT)
		return false;
	else
		return true;
}

/******************************************************************************
*                                                                             *
*                      Function update_board()                                *
*                                                                             *
******************************************************************************/
void update_board(int board[][BOARD_SIZE_VERT], int m, int player_num)
{
	for (int i = BOARD_SIZE_VERT - 1; i > -1; i--)
	{
		if (board[m-1][i] == 0)
		{
			board[m-1][i] = player_num;
			break;
		}
	}

}

/******************************************************************************
*                                                                             *
*                      Function check_winner()                                *
*                                                                             *
******************************************************************************/
int check_winner(int board[][BOARD_SIZE_VERT], int last_move)
{
	int counter = 0, positioninCol = 0, playerNum, indexisValid = 1, posColDia, posRowDia;
	last_move--;
	for (int i = 0; i < BOARD_SIZE_VERT; i++)
	{
		if (board[last_move][i] != 0)
                {
			//printf("The last move made: %d\n", last_move);
			//printf("This is the value of player: %d\n", board[last_move][i]);
			playerNum = board[last_move][i];
                        positioninCol = i;
			//printf("Position in array: %d\n", positioninCol);
			break;                      
                }
        }
	
	//Horizontal matching block
	for (int j = last_move; j >= 0; j--)
	{
		if (board[j][positioninCol] == playerNum)
			counter++;
		else
			break;
	}
	for (int j = last_move; j < BOARD_SIZE_HORIZ; j++)
	{
		if (board[j][positioninCol] == playerNum)
                        counter++;
                else
                        break;
	}
	if (counter >= 5) //Greater than or equal to 5 since last_move is counted twice
		return playerNum;
	else
		counter = 0;

	//Vertical matching block
	for (int k = positioninCol; k < BOARD_SIZE_VERT; k++) //Only need to go down in position for the column
	{
		if (board[last_move][k] == playerNum)
			counter++;
		else
			break;
	}
	if (counter >= 4)
		return playerNum;
	else 
		counter = 0;

	//Right Diagonal matching block
	posColDia = positioninCol;
	posRowDia = last_move;
	while(indexisValid)
	{
		if (posColDia < BOARD_SIZE_VERT)
			if (posRowDia < BOARD_SIZE_HORIZ)
			{
				if (board[posRowDia][posColDia] == playerNum)
					counter++;
				else
					indexisValid = 0;
				posColDia++;
                                posRowDia++;
			}
			else
				indexisValid = 0;
		else
			indexisValid = 0;
	}
	indexisValid = 1;
	posColDia = positioninCol;
        posRowDia = last_move;
	while(indexisValid)
        {
                if (posColDia >= 0)
                        if (posRowDia >= 0)
                        {
                                if (board[posRowDia][posColDia] == playerNum)
                                        counter++;
                                else
                                        indexisValid = 0;
                                posColDia--;
                                posRowDia--;
                        }
                        else
                                indexisValid = 0;
                else
                        indexisValid = 0;
        }
	//printf("This is counter for diagonal: %d\n", counter);
	if (counter >= 5) //first entry counted twice again
		return playerNum;

	//Left Diagonal matching block
	counter = 0;
	indexisValid = 1;
        posColDia = positioninCol;
        posRowDia = last_move;
	while(indexisValid)
        {
                if (posColDia >= 0)
                        if (posRowDia < BOARD_SIZE_HORIZ)
                        {
                                if (board[posRowDia][posColDia] == playerNum)
                                        counter++;
                                else
                                        indexisValid = 0;
                                posColDia--;
                                posRowDia++;
                        }
                        else
                                indexisValid = 0;
                else
                        indexisValid = 0;
        }
	indexisValid = 1;
        posColDia = positioninCol;
        posRowDia = last_move;
	while(indexisValid)
        {
                if (posColDia < BOARD_SIZE_VERT)
                        if (posRowDia >= 0)
                        {
                                if (board[posRowDia][posColDia] == playerNum)
                                        counter++;
                                else
                                        indexisValid = 0;
                                posColDia++;
                                posRowDia--;
                        }
                        else
                                indexisValid = 0;
                else
                        indexisValid = 0;
        }
	if (counter >= 5) //first entry counted twice again
                return playerNum;
	else 
		return 0;		
}

/******************************************************************************
*                                                                             *
*                       Function best_move()                                  *
*                                                                             *
*******************************************************************************
*                                                                             *
*  This is the EXTRA-CREDIT function to be used for the student competition.  *
*                                                                             *
******************************************************************************/
int best_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
	//Diagonals won't really be a tactic, too hard to use and even harder to carry count unless purposely trying for it
	//Most people will try for columns and a few might try rows.
	//My winning strategy: Place token in column 4, then 5 and then 3 or 6, doesn't matter
	//If not blocked, auto-win (this is if I am going first)
	//Going second, column stack in column 1 (if something placed in column 4).
	//If nothing placed in column 4, place token there
	
	int lastMoveCol = -1, lastMoveRow = BOARD_SIZE_HORIZ;
	int columntoMoveto, doMove = 1;
	int opponent_num = (computer_num == 1 ? 2 : 1);
	static int firstMove = 1, madeotherMoves = 0;
	static int lastBoard[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
	int bannedColumns[BOARD_SIZE_HORIZ] = {0};

	//This block checks what move the opponent made in the previous move and records it into the static array stored
	for (int i = BOARD_SIZE_VERT - 1; i >= 0; i--)
                for (int j = 0; j < BOARD_SIZE_HORIZ; j++)
		{
			if (lastBoard[j][i] != board[j][i])
			{
				if (board[j][i] == computer_num)
					lastBoard[j][i] = board[j][i];
				else
				{
					if (j != 3)
						madeotherMoves = 1;
					firstMove = 0;
					lastMoveCol = j;
					lastMoveRow = i;
					lastBoard[j][i] = board[j][i];
					i = -1;
					j = BOARD_SIZE_HORIZ;
				}
			}
		}
/*	if ((lastMoveCol == 3 && lastMoveRow > 1 && !madeotherMoves) || firstMove == 1)
	{
		update_board(board, 4, computer_num);
		update_board(lastBoard, 4, computer_num);
		firstMove++;
		return 4;
	}

	int value = chooseColumn(lastBoard, computer_num, computer_num);
        if (value != -1)
        {
                update_board(board, value, computer_num);
                return value;
        }
        value = chooseColumn(lastBoard, computer_num, opponent_num);
        if (value != -1)
        {
                update_board(board, value, computer_num);
                return value;
        }
*/
	bannedColumn(lastBoard, board, bannedColumns, computer_num, opponent_num);
	columntoMoveto = runMinimax(lastBoard, board, 1, computer_num, bannedColumns);	
	if (columntoMoveto == -10)
	{
		while (is_column_full(lastBoard, doMove))
		{
			doMove++;
			if (doMove == BOARD_SIZE_HORIZ)
				doMove = 1;
		}		
		columntoMoveto = doMove;
	}
	//printf("THIS IS WHAT IS OUTPUTTED: %d\n", columntoMoveto);
	update_board(board, columntoMoveto, computer_num);
        update_board(lastBoard, columntoMoveto, computer_num);
	return columntoMoveto;
}
//ALL FUNCTIONS BELOW WERE INSPIRED BY THIS LINK AND WERE ALTERED FOR THE PURPOSES OF THE BEST MOVE PROGRAM EXCEPT FOR CHOOSECOLUMN AND BANNEDCOLUMN FUNCTIONS
//https://www.dropbox.com/s/010pspnw975zyor/g6.c?dl=0#
//https://stackoverflow.com/questions/29461184/minimax-code-of-connect-4-to-make-best-move


int heuristic(int board[][BOARD_SIZE_VERT], int player_num) {
	
    	int result = 0;
    	int i, j;
 	int opponent_num = (player_num == 1) ? 2 : 1;
    	//check horizontals
    	for(i = BOARD_SIZE_VERT-1; i >= 0; i--)
        	for(j = 0; j <= BOARD_SIZE_HORIZ - 4; j++)
		{
            		if(board[j][i] == player_num && board[j+1][i] == player_num && board[j+2][i] == player_num && board[j+3][i] == player_num)
                		result++;
            		if(board[j][i] == opponent_num && board[j+1][i] == opponent_num && board[j+2][i] == opponent_num && board[j+3][i] == opponent_num)
                		result--;
        	}
	for(i = BOARD_SIZE_VERT-1; i >= 0; i--)
                for(j = 0; j <= BOARD_SIZE_HORIZ - 4; j++)
                {
                        if(board[j][i] == player_num && board[j+1][i] == player_num && board[j+2][i] == player_num && board[j+3][i] == 0)
                                result++;
                        if(board[j][i] == opponent_num && board[j+1][i] == opponent_num && board[j+2][i] == opponent_num && board[j+3][i] == opponent_num)
                                result--;
                }


    	//check verticals FIX THIS
    	for(i = BOARD_SIZE_VERT - 1; i >= BOARD_SIZE_VERT - 3; i--)
        	for(j = 0; j < BOARD_SIZE_HORIZ; j++)
		{
            		if(board[j][i] == player_num && board[j][i-1] == player_num && board[j][i-2] == player_num && board[j][i-3] == player_num)
                		result++;
            		if(board[j][i] == opponent_num && board[j][i-1] == opponent_num && board[j][i-2] == opponent_num && board[j][i-3] == opponent_num)
                		result--;
        	}


	//check diagonals
	for(j = 0; j < BOARD_SIZE_HORIZ - 3; j++)
		for (i = BOARD_SIZE_VERT - 1; i >= BOARD_SIZE_VERT - 3; i--)
		{
			if(board[j][i] == player_num && board[j+1][i-1] == player_num && board[j+2][i-2] == player_num && board[j+3][i-3] == player_num)
				result++;
			if(board[j][i] == opponent_num && board[j+1][i-1] == opponent_num && board[j+2][i-2] == opponent_num && board[j+3][i-3] == opponent_num)
                                result--;
		}


	for(j = BOARD_SIZE_HORIZ - 1; j >= BOARD_SIZE_HORIZ - 4; j--)
		for (i = BOARD_SIZE_VERT - 1; i >= BOARD_SIZE_VERT - 3; i--)
                {
                        if(board[j][i] == player_num && board[j-1][i-1] == player_num && board[j-2][i-2] == player_num && board[j-3][i-3] == player_num)
                                result++;
                        if(board[j][i] == opponent_num && board[j-1][i-1] == opponent_num && board[j-2][i-2] == opponent_num && board[j-3][i-3] == opponent_num)
                                result--;
                } 
	printf("Value Returned: %d\n", result); 
    return result;
}

int minimax(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int depth, int player_num, int lastMove, int bannedColumns[BOARD_SIZE_HORIZ]) {
    	int e;
    	int col, best;
    	int n;
	int opponent_num = (player_num == 1) ? 2 : 1;
    	e = check_winner(board, lastMove);
        if(e == opponent_num)
	{
		//printf("DOES THIS RUN AT SOME POINT");
        	return -10;
	}
       	if(e == player_num)
       		return 10;
    if(depth == 0)
        return ((player_num == 1) ? heuristic(board, player_num) : -heuristic(board, player_num));
    best = -10000;
     
    for(col=0; col < 7; col++)     //check every move
        if(board[col][0] == 0 && bannedColumns[col] != 1) //make sure column isn't full 
	{   
            	update_board(board, col+1, player_num);
            	n = minimax(board, origBoard, depth-1, 3 - player_num, col, bannedColumns);
		if (depth == 1)
		{
			printf("Depth: %d \n", depth);
			printf("Score for column %d: %d\n", col+1, n);
		}
		if ( -n > best ) best = -n;
		if (depth == 1){
		printf("Best value %d \n", best);
		printf("-----------------------\n");}
		for (int j = 0; j < BOARD_SIZE_VERT; j++)
                	if (board[col][j] != origBoard[col][j])
			{
                        	board[col][j] = origBoard[col][j];
				break;
			}
        }
    return best;
}

int runMinimax(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int depth, int player_num, int bannedColumns[BOARD_SIZE_HORIZ]) {
    	int col, move = -10;
    	int n, val = -10000-1;
 
    	for(col = 0; col < BOARD_SIZE_HORIZ; col++)
        	if(board[col][0] == 0 && bannedColumns[col] != 1) {
            	update_board(board, col + 1, player_num);
            	n = minimax(board, origBoard, depth, 3 - player_num, col, bannedColumns);
		printf("This is the value for n at column %d: %d \n", col+1, n);
            	if ( -n > val ) {
                	val = -n;
                	move = col + 1;
		}
		//display_board(board);
		for (int j = 0; j < BOARD_SIZE_VERT; j++)
                        if (board[col][j] != origBoard[col][j])
                                board[col][j] = origBoard[col][j];
        }
	//display_board(board);
 
    return move;
}

int chooseColumn(int board[][BOARD_SIZE_VERT], int player_num, int opponent_num)
{
        int column = -1;
        for (int i = 1; i <= BOARD_SIZE_HORIZ; i++)
        {
                if(!is_column_full(board, i))
                {
                        update_board(board, i, opponent_num);
                        if(check_winner(board, i))
                        {
                                //printf("MORE FAILURE: %d", i);
                                for (int j = 0; j < BOARD_SIZE_VERT; j++)
                                        if (board[i-1][j] != 0)
                                        {
                                                //printf("THIS SUCKS\n");
                                                board[i-1][j] = player_num;
                                                break;
                                        }
                                column = i;
                                break;
                        }
                        else
                                for (int j = 0; j < BOARD_SIZE_VERT; j++)
                                        if (board[i-1][j] != 0)
                                        {
                                                board[i-1][j] = 0;
                                                break;
                                        }
                }
                //printf("The second board\n");
                //display_board(board);
        }
        return column;
}

void bannedColumn(int board[][BOARD_SIZE_VERT], int origBoard[][BOARD_SIZE_VERT], int columnsthatareBanned[BOARD_SIZE_HORIZ], int player_num, int opponent_num)
{
	for (int i = 0; i < BOARD_SIZE_HORIZ; i++)
	{
		if (board[i][0] == 0)
		{
			update_board(board, i+1, player_num);
			if (board[i][0] == 0)
			{
				update_board(board, i+1, opponent_num);
				if (check_winner(board, i+1) == opponent_num)
					columnsthatareBanned[i] = 1;
			}
			for (int j = 0; j < BOARD_SIZE_VERT; j++)
				if (board[i][j] != origBoard[i][j])
					board[i][j] = origBoard[i][j];
		}
	}
}

//int cycleColumnX3(int board[][BOARD_SIZE_VERT], int player_num, int opponent_num)
//{
//}

/*=============================================================================
  Function definitions of other functions
=============================================================================*/

// If you would like to use functions other than those declared in
// connect4_functions.h and implemented above, put the definitions
// of
