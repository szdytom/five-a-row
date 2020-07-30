#ifndef BOARD_H
#define BOARD_H

#include <vector>

namespace ltzero {

/**
 * Define a move
 * 
 * public vars:
 * * x -> the row number of this move
 * * y -> the col number of this move
 * 
 * Init function:
 * Move() {}
 * Move(x: int, y: int) {}
*/
class Move {
public:
	int x;
	int y;
	Move();
	Move(int x, int y);
};

/**
 * Define a board
*/
class Board {
protected:
	std::vector<std::vector<Color> > state;
	std::vector<Move> moves;
	int status;
	int now_ts;

	std::vector<Move> ok_move;
	int ok_move_ts;

	void clear_state();
	bool check_end_about(Move lst);
	void upd_status();
	bool make_move();

public:
	Board();
	void clear();

	bool move(int x, int y);
	bool undo();

	bool is_end();
	int check();

	Color get_next_player();
	void get_moves(std::vector<Move> &m);
	void print_board();
	std::vector<std::vector<Color> > get_board();
	std::vector<Move> get_moves();
};

} // namespace board

#endif // DOARD_H