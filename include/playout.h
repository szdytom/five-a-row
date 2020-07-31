/**
 * playout.h
 * 
 * This file is the fast rollout policy.
 */

#ifndef PLAYOUT_H
#define PLAYOUT_H
#include "board.h"

namespace ltzero {

enum class TupleState : short {
    Blank = 0, // This Tuple is blank
    F1, // This tuple contains 1 "our" chess
    F2, // This tuple contains 2 "our" chesses
    F3, // This tuple contains 3 "our" chesses
    F4, // This tuple contains 4 "our" chesses
    E1, // This tuple contains 1 "thier" chess
    E2, // This tuple contains 1 "thier" chesses
    E3, // This tuple contains 1 "thier" chesses
    E4, // This tuple contains 1 "thier" chesses
    Virtual, // This tuple does not exist
    Polluted, // This tuple have both "our" and "their" chesses
};

enum class TupleType : short {
    /**
     * like this kind:
     *  x
     *  x
     *  x
     *  x
     *  x
    */
    Virtcal = 1,

    /**
     * like this kind:
     * xxxxx
    */
    Horizontal,

    /**
     * like this kind:
     *     x
     *    x
     *   x
     *  x
     * x
    */
    LeftOblique,

    /**
     * like this kind:
     * x
     *  x
     *   x
     *    x
     *     x
    */
    RightOblique
};

class Playout {
private:
    void init_now_score();
    void drop_now_score();

protected:
    Board b;
    int *now_score = nullptr;
    int encode(int x, int y, int type);
    int decode(int &x, int &y, int &type);
    std::vector<ltzero::Move> get_best_moves();

public:
    static const int value_eval_table[11];
    static const int tuple_size;

    Playout();
    Playout(Board b);
    void init(Board b);

    ~Playout();

    Move make_fast_move();
    void play_to_end();
}

}

#endif // PLAYOUT_H