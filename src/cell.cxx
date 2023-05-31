//
// Created by Ravi Nuxoll on 5/24/23.
//

#include "cell.hxx"
#include <iostream>

using Position = ge211::Posn<int>;

Cell::Cell(int value, Position ind)
    : value(value),
      fixed(value != 0), // 0s indicate blank squares
    row_inconsistent(false),
      hint(false),
      index(ind)
{
    // std::cout << "Cell constructor\n";
    /*for (int i = 1; i <= 9; i++){
        candidates[i] = false;
    }*/
}

void Cell::set_value(int newValue) {
    if(newValue >= 0 && newValue <= 9) {
        value = newValue;
    } else {
        throw std::out_of_range("Invalid value for cell. Value must be"
                                " between 0 and 9.");
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
        throw std::out_of_range("Invalid candidate for cell. Candidate must
        be between 1 and 9.");
    }
}*/

int
Cell::get_value() const
{
    return value;
};


bool
Cell::is_fixed() const
{
    return fixed;
}

bool
Cell::is_inconsistent() const
{
    return row_inconsistent or col_inconsistent or square_inconsistent;
}

bool
Cell::is_hint() const
{
    return hint;
}

void
Cell::set_hint(bool value)
{
    hint = value;
}


void
Cell::set_inconsistent(bool value, char code)
{
    switch(code){
    case 'r':
        row_inconsistent = value;
        break;
    case 'c':
        col_inconsistent = value;
        break;
    case 's':
        square_inconsistent = value;
        break;
    }
}

Position
Cell::get_index()
{
    return index;
}

