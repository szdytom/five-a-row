/**
 * board.h
 * 
 * This file defines the board & rules of 
 * the Gomoku game.
 * 
 * class Move is about each single move.
 * class Board is about the holo board of
 * the Gomoku game.
 * 
 * namespace: ltzero
 * 
 * class:
 *  - Move
 * 	  - Public Var:
 *      - x
 *      - y
 *    - Public Method:
 *      - Move(void)
 *      - Move(int, int)
 *  
 *  - Board
 *    - Public Method:
 *      - board(void)
 *      - void clear(void)
 *      - bool move(int, int)
 *      - bool is_end(void)
 *      - int check(void)
 *      - Color get_next_player(void)
 *      - void print_board(void)
 *      - std::vector<std::vector<Color> > get_board(void)
 *      - std::vector<Move> get_history(void)
 * 
 *   - Color (enum)
 *     - type: short
 *     - value:
 *       - Black = 1
 *       - White
 *       - Empty
 *  
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>

namespace ltzero {

/**
 * Color for a move
 * It has value of a short
 */
enum class Color : short {
	Black = 1,
	White,
	Empty
};

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
	static const size = 15;

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
	std::vector<Move> get_history();
};

} // namespace board

#endif // DOARD_H