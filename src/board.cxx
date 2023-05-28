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

    // for (int i = 0; i < dims.width; i++){
    //     for (int j = 0; j < dims.height; j++){
    //         board[i][j] = Cell(1, ge211::Posn<int>(i, j));
    //     }
    // }

    while (std::getline(ss, line, '\n') && row < BOARD_SIZE) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            char c = line[col * 2];  // Because every other char is an underscore '_'
            int value = (c == '_') ? 0 : c - '0';  // Convert char to int
            board[row][col] = Cell(value, {row, col});
        }
        ++row;
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
    Cell current_cell = board[cell_index.x][cell_index.y];
    int current_value = current_cell.get_value();
    //get_duplicates()
    return Position_set();
}

std::array<Cell, BOARD_SIZE>
Board::get_row_values(int row)
{
    if (row < 0 || row >= 9){
        throw std::out_of_range("Row index must be between 0 and 8");
    }

    std::array<Cell, 9> row_values;
    for (int c = 0; c < 9; c++){
        row_values[c] = board[row][c];
    }

    return row_values;
}

std::array<Cell, BOARD_SIZE>
Board::get_col_values(int col)
{
    if (col < 0 || col >= 9){
        throw std::out_of_range("Row index must be between 0 and 8");
    }

    std::array<Cell, 9> col_values;
    for (int r = 0; r < 9; r++){
        col_values[r] = board[r][col];
    }
    return col_values;
}

std::array<std::array<Cell, 3>, 3> Board::get_subgrid_values(int grid_index) {
    if (grid_index < 0 || grid_index >= 9) {
        throw std::out_of_range("Grid index must be between 0 and 8");
    }

    // Determine the starting row and column for the sub-grid
    int start_row = (grid_index / 3) * 3;
    int start_col = (grid_index % 3) * 3;

    std::array<std::array<Cell, 3>, 3> square_values;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            square_values[i][j] = board[start_row + i][start_col + j];
        }
    }

    return square_values;
}


// calling this function has the Board go through every row, column, and then
// every square and then update all of its constituent Cells to be inconsistent
// if they are duplicates
void Board::mark_duplicates(){
    // we will iterate through every row, column, and square in the same loop
    for (int i = 0; i < BOARD_SIZE; i++){

    }
}

Cell Board::get_cell(int row, int col) const{
    return board[row][col];
}

Cell& Board::get_cell_reference(int row, int col)
{
    return board[row][col];
}
