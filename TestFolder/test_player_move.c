#include "connect4_functions.h"
#include <string.h>
void solution_display_board(int board[][BOARD_SIZE_VERT]);

int main(int argc, char const *argv[])
{
	printf("Testing player_move().\n\n");

	int steps;
	int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};

	scanf("%d", &steps);
	int players[steps];
	for (int i = 0; i < steps; ++i)
		scanf("%d", &players[i]);

	for (int i = 0; i < BOARD_SIZE_HORIZ; ++i)
		for (int j = 0; j < BOARD_SIZE_VERT; ++j)
			scanf("%d", &board[i][j]);

	while(getchar() != '\n');

	solution_display_board(board);

	for (int i = 0; i < steps; ++i)
	{
		printf("Round %d:\n", i + 1);
		printf("player_move(board, %d) == %d\n", players[i], player_move(board, players[i]));
		solution_display_board(board);
	}

	return 0;
}
