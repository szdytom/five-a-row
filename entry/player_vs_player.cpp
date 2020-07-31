#include <cstdio>
#include "../include/board.h"
using namespace std;
using namespace ltzero;

void player_vs_player(Board &b) {
	while (true) {
		int x, y;
		while (true) {
			scanf("%d %d", &x, &y);
			if (b.move(x, y)) break;
			else printf("Not correct! input again: ");
		}

		b.print_board();
		if (b.is_end()) {
			printf("%s wins!\n", b.check() == -1 ? "white" : "black");
			break;
		}
		
		printf("Next is %s\n", b.get_next_player() == Color::White ? "white" : "black");
	}
}

int main() {
	Board b;
	player_vs_player(b);
	return 0;
}