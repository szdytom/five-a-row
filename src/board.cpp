/**
 * board.cpp
 *
 * Define of functions and class in board.h
 */

#include "../include/board.h"
#include <algorithm>
#include <cstdio>

void ltzero::Board::clear_state() {
	this->status = 0;
	this->state.clear();
	this->state.resize(this->size);
	for (int i = 0; i < this->size; ++i) 
		state[i].resize(this->size);

	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			state[i][j] = ltzero::Board::Empty;
		}
	}
}

bool ltzero::Board::check_end_about(ltzero::Move last) {
	int cnt = 0;

	/**
	 * like this kind:
	 *  x
	 *  x
	 *  x
	 *  x
	 *  x
	*/
	for (int i = max(last.x - 4, 0); i < std::min(last.x + 5, this->size); ++i) {
		if (this->state[i][last.y] == last.c) {
			++cnt;
			if (cnt == 5 && (i + 1 >= this->size 
				 || state[i + 1][last.y] != last.c)) {
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
	for (int i = std::max(last.y - 4, 0); i < std::min(last.y + 5, this->size); ++i) {
		if (this->state[last.x][i] == last.c) {
			++cnt;
			if (cnt == 5 && (i + 1 >= this->size 
				 || this->state[last.x][i + 1] != last.c)) {
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
		int xx = last.x + i;
		int yy = last.y + i;
		if (xx < 0 || xx >= this->size || yy < 0 || yy >= this->size) continue;

		if (this->state[xx][yy] == last.c) {
			++cnt;
			if (cnt == 5 && (xx + 1 >= this->size || yy + 1 >= this->size
				 || this->state[xx + 1][yy + 1] != last.c)) {
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
		int xx = last.x + i;
		int yy = last.y - i;
		if (xx < 0 || xx >= this->size || yy < 0 || yy >= this->size) continue;

		if (this->state[xx][yy] == last.c) {
			++cnt;
			if (cnt == 5 && (xx + 1 >= this->size 
				 || yy - 1 < 0 || this->state[xx + 1][yy - 1] != last.c)) {
				return true;
			}
		}
	}

	return false;
}


void ltzero::Board::upd_status() {
	ltzero::Move last = this->moves[this->moves.size() - 1];

	if (this->check_end_about(last)) {
		this->status = (last.c == ltzero::Color::Black ? 1 : -1);
	}
}

bool ltzero::Board::make_move(ltzero::Move m) {
	if (this->isend()) {
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
	return this->make_move(ltzero::Move(x, y, this->next_player()));
}

bool ltzero::Board::undo() {
	if (this->isend()) return false;
	if (this->moves.size() == 0) return false;

	ltsero::Move last = this->moves[this->moves.size() - 1];
	this->moves.pop_back();

	this->state[last.x][last.y] = ltzero::Color::Empty;
	this->now_ts += 1;

	return true;
}

bool ltzero::Board::isend() {
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

ltzero::Color ltzero::Board::next_player() {
	if (this->moves.size() == 0) // Black moves the first
		return ltzero::Color::Black;

	if (this->moves[this->moves.size() - 1].c == ltzero::Color::White)
		return ltzero::Color::Black

	return ltzero::Color::White;
}

// Get available move list
void ltzero::Board::get_moves(std::vector<ltzero::Move> &m) {
	if (this->isend()) {
		m.clear();
		return;
	}

	if (this->ok_move_ts == this->now_ts) {
		m = this->ok_move;
		return;
	}

	ltzero::Color c = this->next_player();
	this->ok_move.clear();
	
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			if (state[i][j] == Empty) 
				this->ok_move.push_back(ltsero::Move(i, j, c));
		}
	}

	this->ok_move_ts = this->now_ts;
	m = this->ok_move;
}


void ltzero::Board::print_board() {
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
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
std::vector<std::vector<ltzero::Board::Color> > Board::get_board() {
	return this->state;
}

// Get move history
std::vector<ltzere::Move> Board::get_history() {
	return this->moves;
}