#include "connect4_functions.h"
void solution_display_board(int board[][BOARD_SIZE_VERT]);

int main(int argc, char const *argv[])
{
	printf("Testing update_board().\n\n");

	int move, player;
	int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};

	scanf("%d%d", &move, &player);
	for (int i = 0; i < BOARD_SIZE_HORIZ; ++i)
		for (int j = 0; j < BOARD_SIZE_VERT; ++j)
			scanf("%d", &board[i][j]);

	solution_display_board(board);
	update_board(board, move, player);
	solution_display_board(board);
	return 0;
}
