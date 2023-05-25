//
// Created by Ravi Nuxoll on 5/24/23.
//


#include "board.hxx"

Board::Board() {
    // this default constructor just initializes the board to an
    // empty board with all zeroes
    for(auto &row : board) {
        for(auto &cell : row) {
            cell.set_value(0);
            cell.set_fixed(false);
            for(int candidate = 1; candidate <= 9; ++candidate) {
                cell.set_candidate(candidate, false);
            }
        }
    }
}

