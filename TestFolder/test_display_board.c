#include "connect4_functions.h"

int main(int argc, char const *argv[])
{
	printf("Testing display_board().\n\n");

	int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
	for (int i = 0; i < BOARD_SIZE_HORIZ; ++i)
		for (int j = 0; j < BOARD_SIZE_VERT; ++j)
			scanf("%d", &board[i][j]);

	display_board(board);
	return 0;
}
