#ifndef BOARD_H
#define BOARD_H

namespace board {

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

};

}

#endif