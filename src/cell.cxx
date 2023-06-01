//
// Created by Ravi Nuxoll on 5/24/23.
//

#include "cell.hxx"
#include <iostream>

using Position = ge211::Posn<int>;

Cell::Cell(int value, Position ind)
    : value_(value),
      fixed_(value != 0), // 0s indicate blank squares
    row_inconsistent_(false),
      hint_(false),
      index_(ind)
{
}

void Cell::set_value(int newValue) {
    if(newValue >= 0 && newValue <= 9) {
        value_ = newValue;
    } else {
        throw std::out_of_range("Invalid value_ for cell. Value must be"
                                " between 0 and 9.");
    }
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
    return value_;
}


bool
Cell::is_fixed() const
{
    return fixed_;
}

bool
Cell::is_inconsistent() const
{
    return row_inconsistent_ or col_inconsistent_ or square_inconsistent_;
}

bool
Cell::is_hint() const
{
    return hint_;
}

void
Cell::set_hint(bool value)
{
    hint_ = value;
}


void
Cell::set_inconsistent(bool value, char code)
{
    switch(code){
    case 'r':
        row_inconsistent_ = value;
        break;
    case 'c':
        col_inconsistent_ = value;
        break;
    case 's':
        square_inconsistent_ = value;
        break;
    }
}

Position
Cell::get_index()
{
    return index_;
}

