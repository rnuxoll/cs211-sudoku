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

/*std::set<int>
Board::get_duplicates(const std::array<int, BOARD_SIZE>& values)
const
{
    std::set<int> return_set = {};
    for (int i = 0; i < sizeof(values); ++i) {
        int x = abs(values[i]);
        x--;
        if (nums[x] < 0) {
            return_set.insert(x+1);
        } else {
            nums[x] *= -1;
        }
    }
    return return_set;
}*/