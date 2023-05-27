//
// Created by Ravi Nuxoll on 5/24/23.
//


#include "board.hxx"

Board::Board(Dimensions dims)
    :dims_(dims)
{

}

Position_set
Board::find_contradictions() const{
    Position_set my_set {};
    return my_set;
}


Board::Rectangle
Board::all_positions() const
{
    Position the_origin = {0, 0};
    return Rectangle::from_top_left(the_origin, dims_);
}

// Citation: https://www.tutorialspoint.com/find-all-duplicates-in-an-array-in-cplusplus

std::set<int>
Board::get_duplicates(std::vector<int>& values)
const
{
    std::set<int> return_set = {};
    for (int i = 0; i < values.size(); ++i) {
        for (int j = 0; i < values.size(); ++j) {
            if (i == j) {
                continue;
            } else {
                if (values[i] == values[j]) {
                    return_set.insert(values[i]);
                }
            }
        }
    }
    return return_set;
}

Position_set
Board::find_contradicting_squares(Position cell_index) const
{
    return {};
    //int current_value = board[cell_index.x][cell_index.y];
}
