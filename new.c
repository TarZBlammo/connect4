#include <stdio.h>
/* player with AI of computer
* changing R and C from g4.c
* reverse printing the board from g5.c
 
* display      :           Print the board.
* possible     :           Check the move to be possible.
* playerTurn   :           Get the move(column) from user.
* computerTurn :           Creat the computer move.
* emptyBoard   :           Make a board with zero elements.
* put          :           Put the move in the board.
* rmv          :           Remove the latest move from "column".
* endgame      :           Check for ending the game return 1,2,3 or 0 
*                             for user, computer, stalement or board is full(no one) respectively. 
* heuristic    :           The hueristic is detemined by counting all potential spaces for making a row (ie
*                             all 4-size spaces that doesn't contain any enemy), and then subtracting the
*                             number of potential spaces for the enemy. Seems to work quite well even at low depth trees
*                             will not check diaginols (game's too clever already)
* ai           :           Returns the move with highest minimax value
* minimax      :           Return the minimax value of a board state,
*                             note that while the algorithm works, there's always only one board in memory,
*                             this is achieved by looping through each valid move and checks it by putting
*                             a piece in that row, recursively determine the value of the new board state,
*                             and then remove the piece putted to allow checking other valid moves.
*                             It is possible to use such low-memory-using algorithm because reversing the
*                             put operation (put() function) is very simple (rmv() function).  
*/
 
 
#define R 7 //row
#define C 6 //column
 
void display(int board[R][C]);                                 
int  possible(int board[R][C], int column);                    
int  playerTurn(void);                                         
int  computerTurn(int board[R][C],int depth);                  
void emptyBoard(int board[R][C]);                              
int  put(int board[R][C], int pos, int player);                
void rmv(int board[R][C], int column);                         
int  endgame(int board[R][C], int player);                                                               
int  heuristic(int board[R][C]);
int  minimax(int board[R][C], int depth, int turn /*1 or 2*/);
int  ai(int board[R][C], int depth);
 
 
int main(void) {
    int move,e;
    int turn = 1;
    int depth = 3;
    int board[R][C];
     
    emptyBoard(board);
    display(board);
    while(1) {
        turn = 1;
 
        while(!(e=endgame(board,turn))) {
            if(turn==1) {
                do {
                    move = playerTurn();                    
                }while(possible(board, move) == 0);
            } 
            else {
                do {
                    move = computerTurn(board,depth);
                    printf(" Computer move is %d \n ",move );
                }while(possible(board, move) == 0);                
            }
            put(board, move, turn);
            display(board);
            printf("\n");
            // changing the turn
            turn = 3 - turn;
        }
    }
 
    return 0;
}
 
void display(int board[R][C]){
 
    int i,j,k,m;
    char vert_line = '|';
    char horz_line_segment[4] = "---+";
    char horz_line_segment_prefix = '+';
         
    printf("\n");
    for(i = 0; i < C; i++)
        printf(" %d  ", i + 1);
    printf("\n");
 
    for ( i = C-1; i >= 0; i--) {
            printf("%c",vert_line);
            for ( j = 0; j < R; j++) {
                printf(" %d %c",board[j][i],vert_line);                
            }
            printf("\n");
            printf("%c", horz_line_segment_prefix);
            for ( k = 0; k < C; k++) 
                printf("%s",horz_line_segment);
 
            printf("\n");
        }
    for ( m = 1; m <= C; m++) {
        (m > 9) ? printf(" ") : printf("  ");        
    }
    printf("\n");
}
 
int possible(int board[R][C], int column)
{
    int i;
    int occupied = 0;
  
    if(column > C || column < 0 ) {
  
        printf("\n Invalid move \n");
        return 0;
    }
  
    for(i = 0; i < R; i++) {
        if(board[i][column] != 0)
            occupied++;
    }
  
    if(occupied == R) {
        printf("\n invalid move \n");
        return 0;
    }
  
    else
        return 1;
}
 
 
int playerTurn() {
    int pos;
    printf("It's player turn > ");
    scanf("%d", &pos);
 
    return pos-1;
}
 
 
int computerTurn(int board[R][C], int depth) {
 
    return ai(board, depth);
}
 
void emptyBoard(int s[R][C]) {
    int i,j;
    for(i=0; i<6; i++)
        for(j=0; j<7; j++)
            s[i][j] = 0;
}
 
int put(int board[R][C], int column, int player) {
 
    int i;
  
    for(i = 0; i < R; i++) {
        if(board[i][column] == 0) {
            board[i][column] = player;
            return i+1;
        }
    }
}
 
void rmv(int board[R][C], int column) { 
    int i;
    for (i=R-1; i>=0; i--){
        if (board[i][column] != 0) {
            board[i][column] = 0;
	    break;
        }
    }
}
 
/* void rmv(int s[6][7], int column) {
    int i = 6-1;
 
    while(s[i][column]==0) i--;
    s[i][column] = 0;
} */
 
//0=no, 1=player, 2=computer, 3=stalemate
int endgame(int s[R][C],int player) {
    int i, j;
     
    //check horizontals
    for(i=0; i<6; i++)
        for(j=0; j<=7-4; j++){
            if(s[i][j]== player && s[i][j+1]== player && s[i][j+2]== player && s[i][j+3]== player)
                return player;
        }
 
    //check verticals
    for(i=0; i<=6-4; i++)
        for(j=0; j<7; j++){
            if(s[i][j]== player && s[i+1][j]== player && s[i+2][j]== player && s[i+3][j]== player )
                return player;
        }
 
    //check main diagonals (\)
    for(i=6-1; i>=4-1; i--)
        for(j=0; j<=7-4; j++){
            if(s[i][j]== player && s[i-1][j+1]== player && s[i-2][j+2]== player && s[i-3][j+3]== player)
                return player;
        }
 
    //check other diagonals (/)
    for(i=0; i<=6-4; i++)
        for(j=0; j<=7-4; j++){        
            if(s[i][j]== player && s[i+1][j+1]== player && s[i+2][j+2]== player && s[i+3][j+3]== player)
                return player;
        }
 
 
    //check if stalement
    for(i=0; i<7; i++)
        if(s[6-1][i]==0)
            return 0; //game haven't finished yet - there's at least one empty cell in a top of a row
 
    return 3; //stalemate - board is full
}
 
 
int heuristic(int s[R][C]) {
    int result = 0;
    int i, j;
 
    //check horizontals
    for(i=0; i<6; i++)
        for(j=0; j<=7-4; j++){
            if(s[i][j]!= 2 && s[i][j+1]!= 2 && s[i][j+2]!= 2 && s[i][j+3]!= 2)
                result++;
            if(s[i][j]!= 1 && s[i][j+1]!= 1 && s[i][j+2]!= 1 && s[i][j+3]!= 1)
                result--;
        }
 
    //check verticals
    for(i=0; i<=6-4; i++)
        for(j=0; j<7; j++){
            if(s[i][j]!= 2 && s[i+1][j]!= 2 && s[i+2][j]!= 2 && s[i+3][j]!= 2 )
                result++;
            if(s[i][j]!= 1 && s[i+1][j]!= 1 && s[i+2][j]!= 1 && s[i+3][j]!= 1 )
                result--;
        }
 
    return result;
}
 
int minimax(int board[R][C], int depth, int turn /*1 or 2*/) {
    int e;
    int col, best;
    int n;
    int player;
    if((e=endgame(board, turn))) {
        if(e==3)
            return 0;
        if(e==turn)
            return 10000;
        else
            return -10000;
    }
 
    if(depth==0)
        return ((turn==1) ? heuristic(board) : -heuristic(board));
 
    best = -10000;
     
    for(col=0; col < 7; col++)     //check every move
        if(board[6-1][col]==0) {   //make sure column isn't empty
            put(board, col, turn);
            n = minimax(board, depth-1, 3-turn);
            if(turn==1) {
                if ( -n > best ) best = -n;
            } else { //turn==2
                if ( -n > best ) best = -n;
            }
            rmv(board, col);
        }
 
    return best;
}
 
int ai(int board[R][C], int depth) {
    int col, move;
    int n, val = -10000-1;
 
    for(col=0; col < 7; col++)
        if(board[6-1][col]==0) {
            put(board, col, 2);
            n = minimax(board, depth, 1);
            if ( -n > val ) {
                val = -n;
                move = col;
            }
            rmv(board, col);
        }
 
    return move;
}
