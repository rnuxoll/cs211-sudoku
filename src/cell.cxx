//
// Created by Ravi Nuxoll on 5/24/23.
//

#include "cell.hxx"
#include <iostream>

Cell::Cell(Position ind)
    : value(0),
    fixed(false),
    index(ind)
{
    std::cout << "Cell constructor\n";
    /*for (int i = 1; i <= 9; i++){
        candidates[i] = false;
    }*/
}

void Cell::set_value(int newValue) {
    if(newValue >= 0 && newValue <= 9) {
        value = newValue;
    } else {
        throw std::out_of_range("Invalid value for cell. Value must be between 0 and 9.");
    }
}

void Cell::set_fixed(bool isFixed) {
    fixed = isFixed;
}

/*
void Cell::set_candidate(int candidate, bool isCandidate) {
    if(candidate >= 1 && candidate <= 9) {
        candidates[candidate] = isCandidate;
    } else {
        throw std::out_of_range("Invalid candidate for cell. Candidate must be between 1 and 9.");
    }
}*/