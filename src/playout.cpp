/**
 * playout.cpp
 * 
 * Define of functions and classes in playout.h
 * 
 */

#include "../include/board.h"
#include "../include/playout.h"
#include "../include/tools/random.h"

#include <cstring>

const int ltzero::Playout::tuple_size = 2 * (ltzero::Board::size - 4) * ltzero::Board::size
                                        + (ltzero::Board::size - 4) * (2 * ltzero::Board::size - 8) / 2;

const int ltzero::Playout::value_eval_table[11];

ltzero::Playout() {}

ltzero::Playout(ltzero::Board b) {
    this->init(b);
}

ltzero::~Playout() {
    this->drop_now_score();
}

void ltzero::Playout::init(ltzero::Board b) {
    this->b = b;
    this->init_now_score();
}

void ltzero::Playout::drop_now_score() {
    if (this->now_score != nullptr)
        delete[] this->now_score;
}

void ltzero::Playout::init_now_score() {
    this->drop_now_score();
    this->now_score = new int[ltzero::Playout::tuple_size];
}

ltzero::Move ltzero::Playout::make_move() {
    return ltzero::tools::random_choice(this->get_best_moves());
}

std::vector<ltzero::Move> ltzero::Playout::get_best_move() {

}