#include "connect4_functions.h"
#include <string.h>
void solution_display_board(int board[][BOARD_SIZE_VERT]);

int main(int argc, char const *argv[])
{
	printf("Testing random_move().\n\n");

	int player;
	int input_board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
	int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};

	scanf("%d", &player);
	for (int i = 0; i < BOARD_SIZE_HORIZ; ++i)
		for (int j = 0; j < BOARD_SIZE_VERT; ++j)
			scanf("%d", &input_board[i][j]);

	for (int i = 0; i < 10; ++i)
	{
		printf("Round %d:\n", i + 1);
		memcpy(board, input_board, BOARD_SIZE_HORIZ * BOARD_SIZE_VERT * sizeof(int));
		solution_display_board(board);
		printf("random_move(board, %d) == %d\n", player, random_move(board, player));
		solution_display_board(board);
	}
	return 0;
}
