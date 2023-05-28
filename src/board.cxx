//
// Created by Ravi Nuxoll on 5/24/23.
//


#include "board.hxx"

Board::Board(std::string board_string, Dimensions dims)
    :dims_(dims)
{
    std::stringstream ss(board_string);
    std::string line;
    int row = 0;

    // TODO modify this
    std::cout << "Board constructor\n";

    std::cout << board_string;

    for (int i = 0; i < dims.width; i++){
        for (int j = 0; j < dims.height; j++){
            board[i][j] = Cell(1, ge211::Posn<int>(i, j));
        }
    }
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

std::set<int>
Board::get_duplicates(const std::array<Cell, BOARD_SIZE>& values)
const
{
    std::set<int> return_set = {};
    for (int i = 0; i < sizeof(values); ++i) {
        for (int j = 0; j < sizeof (values); ++j) {
            if (i == j) {
                continue;
            } else {
                if (values[i].get_value() == values[j].get_value()) {
                    return_set.insert(values[i].get_value());
                    //values[i].set_inconsistent();
                }
            }
        }
    }
    return return_set;
}

Position_set
Board::find_contradicting_squares(Position cell_index) const
{
    Cell current_cell = get_cell(cell_index.x, cell_index.y);
    int current_value = current_cell.get_value();
    //get_duplicates()
    std::array<Cell, BOARD_SIZE> row;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        row[i] = get_cell(cell_index.x + i, cell_index.y);
    }
    std::set<int> set_of_duplicates = get_duplicates(row);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (set_of_duplicates.find(board[cell_index.x + i][cell_index.y]
                                               .get_value()) !=
                                               set_of_duplicates.end()) {
            //board[cell_index.x + i][cell_index.y].set_inconsistent();
        }
    }


    return Position_set();
}

Cell
Board::get_cell(int row, int col) const
{
    return board[row][col];
}
