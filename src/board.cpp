/**
 * board.cpp
 *
 * Define of functions and class in board.h
 */

#include "../include/board.h"
#include <algorithm>
#include <cstdio>

const int ltzero::Board::size = 15;

void ltzero::Board::clear_state() {
	this->status = 0;
	this->state.clear();
	this->state.resize(ltzero::Board::size);
	for (int i = 0; i < ltzero::Board::size; ++i) 
		state[i].resize(ltzero::Board::size);

	for (int i = 0; i < ltzero::Board::size; ++i) {
		for (int j = 0; j < ltzero::Board::size; ++j) {
			state[i][j] = ltzero::Color::Empty;
		}
	}
}

bool ltzero::Board::check_end_about(ltzero::Move lst) {
	int cnt = 0;

	/**
	 * like this kind:
	 *  x
	 *  x
	 *  x
	 *  x
	 *  x
	*/
	for (int i = std::max(lst.x - 4, 0); i < std::min(lst.x + 5, ltzero::Board::size); ++i) {
		if (this->state[i][lst.y] == lst.c) {
			++cnt;
			if (cnt == 5 && (i + 1 >= ltzero::Board::size 
				 || state[i + 1][lst.y] != lst.c)) {
				return true;
			}
		} else {
			cnt = 0;
			continue;
		}
	}

	/**
	 * like this kind:
	 * xxxxx
	*/
	cnt = 0;
	for (int i = std::max(lst.y - 4, 0); i < std::min(lst.y + 5, ltzero::Board::size); ++i) {
		if (this->state[lst.x][i] == lst.c) {
			++cnt;
			if (cnt == 5 && (i + 1 >= ltzero::Board::size 
				 || this->state[lst.x][i + 1] != lst.c)) {
				return true;
			}
		} else {
			cnt = 0;
			continue;
		}
	}

	/**
	 * like this kind
	 * x
	 *  x
	 *   x
	 *    x
	 *     x
	*/
	cnt = 0;
	for (int i = -4; i <= 4; ++i) {
		int xx = lst.x + i;
		int yy = lst.y + i;
		if (xx < 0 || xx >= ltzero::Board::size || yy < 0 || yy >= ltzero::Board::size) continue;

		if (this->state[xx][yy] == lst.c) {
			++cnt;
			if (cnt == 5 && (xx + 1 >= ltzero::Board::size || yy + 1 >= ltzero::Board::size
				 || this->state[xx + 1][yy + 1] != lst.c)) {
				return true;
			}
		}
	}

	/**
	 * like this kind:
	 *     x
	 *    x
	 *   x
	 *  x
	 * x
	*/
	cnt = 0;
	for (int i = -4; i <= 4; ++i) {
		int xx = lst.x + i;
		int yy = lst.y - i;
		if (xx < 0 || xx >= ltzero::Board::size || yy < 0 || yy >= ltzero::Board::size) continue;

		if (this->state[xx][yy] == lst.c) {
			++cnt;
			if (cnt == 5 && (xx + 1 >= ltzero::Board::size 
				 || yy - 1 < 0 || this->state[xx + 1][yy - 1] != lst.c)) {
				return true;
			}
		}
	}

	return false;
}


void ltzero::Board::upd_status() {
	ltzero::Move lst = this->moves[this->moves.size() - 1];

	if (this->check_end_about(lst)) {
		this->status = (lst.c == ltzero::Color::Black ? 1 : -1);
	}
}

bool ltzero::Board::make_move(ltzero::Move m) {
	if (this->is_end()) {
		return false;
	}

	if (this->state[m.x][m.y] != ltzero::Color::Empty) {
		return false;
	}

	this->moves.push_back(m);
	this->state[m.x][m.y] = m.c;
	this->upd_status();
	now_ts += 1;

	return true;
}

ltzero::Board::Board() {
	this->clear();
}

bool ltzero::Board::move(int x, int y) {
	return this->make_move(ltzero::Move(x, y, this->get_next_player()));
}

bool ltzero::Board::undo() {
	if (this->is_end()) return false;
	if (this->moves.size() == 0) return false;

	ltzero::Move lst = this->moves[this->moves.size() - 1];
	this->moves.pop_back();

	this->state[lst.x][lst.y] = ltzero::Color::Empty;
	this->now_ts += 1;

	return true;
}

bool ltzero::Board::is_end() {
	return this->status != 0;
}

/**
 * Check the state.
 * -1 for white wins.
 * 0 for still running.
 * 1 for black wins.
*/
int ltzero::Board::check() {
	return this->status;
}

void ltzero::Board::clear() {
	this->clear_state();
	this->moves.clear();
	this->now_ts = 0;

	this->ok_move_ts = -1;
}

ltzero::Color ltzero::Board::get_next_player() {
	if (this->moves.size() == 0) // Black moves the first
		return ltzero::Color::Black;

	if (this->moves[this->moves.size() - 1].c == ltzero::Color::White)
		return ltzero::Color::Black;

	return ltzero::Color::White;
}

// Get available move list
void ltzero::Board::get_moves(std::vector<ltzero::Move> &m) {
	if (this->is_end()) {
		m.clear();
		return;
	}

	if (this->ok_move_ts == this->now_ts) {
		m = this->ok_move;
		return;
	}

	ltzero::Color c = this->get_next_player();
	this->ok_move.clear();
	
	for (int i = 0; i < ltzero::Board::size; ++i) {
		for (int j = 0; j < ltzero::Board::size; ++j) {
			if (state[i][j] == ltzero::Color::Empty) 
				this->ok_move.push_back(ltzero::Move(i, j, c));
		}
	}

	this->ok_move_ts = this->now_ts;
	m = this->ok_move;
}


void ltzero::Board::print_board() {
	for (int i = 0; i < ltzero::Board::size; ++i) {
		for (int j = 0; j < ltzero::Board::size; ++j) {
			switch (this->state[i][j]) {
				case ltzero::Color::Empty:
					std::printf(".");
					break;
				case ltzero::Color::Black:
					std::printf("X");
					break;
				case ltzero::Color::White:
					std::printf("O");
					break;
				default:
					break;
			}
		}
		std::printf("\n");
	}
}

// Get the board
std::vector<std::vector<ltzero::Color> > ltzero::Board::get_board() {
	return this->state;
}

// Get move history
std::vector<ltzero::Move> ltzero::Board::get_history() {
	return this->moves;
}

ltzero::Move::Move() {
	this->x = -1;
	this->y = -21;
	this->c = ltzero::Color::Empty;
}

ltzero::Move::Move(int x, int y) {
	this->x = x;
	this->y = y;
	this->c = ltzero::Color::Empty;
}

ltzero::Move::Move(int x, int y, ltzero::Color c) {
	this->x = x;
	this->y = y;
	this->c = c;
}