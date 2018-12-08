#include "connect4_functions.h"

int main(int argc, char const *argv[])
{
	printf("Testing print_welcome().\n\n");
	for (int i = 0; i < 5; i++) {
		int player_num = print_welcome();
		printf("Round %d, player_num = %d\n\n", i + 1, player_num);
	}
	return 0;
}
