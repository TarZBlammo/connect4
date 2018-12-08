#include "connect4_functions.h"
void solution_display_board(int board[][BOARD_SIZE_VERT]);

int main(int argc, char const *argv[])
{
	printf("Testing check_win_or_tie().\n\n");

	int last_move;
	int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};

	scanf("%d", &last_move);
	for (int i = 0; i < BOARD_SIZE_HORIZ; ++i)
		for (int j = 0; j < BOARD_SIZE_VERT; ++j)
			scanf("%d", &board[i][j]);

	solution_display_board(board);
	printf("check_win_or_tie(board, %d) == %d\n", last_move, check_win_or_tie(board, last_move));
	solution_display_board(board);
	return 0;
}
