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
    while (std::getline(ss, line, '\n') && row < BOARD_SIZE) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Because every other char is an underscore '_'
            char c = line[col * 2];
            int value = (c == '_') ? 0 : c - '0';  // Convert char to int
            board_[col][row] = Cell(value, {col, row});
        }
        row++;
    }
    mark_duplicates();
}



std::set<int>
Board::get_duplicates(const std::array<Cell, BOARD_SIZE> values)
const
{
    std::set<int> return_set = {};
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = i+1; j < BOARD_SIZE; ++j) {
            if (i == j) {
                // without this clause, everything would be a duplicate
                continue;
            } else {
                // if the duplicate value_ is 0, then it's a blank square and
                // not really a duplicate
                if (values[i].get_value() != 0 and values[i].get_value() ==
                values[j].get_value
                ()) {
                    return_set.insert(i);
                    return_set.insert(j);
                }
            }
        }
    }
    return return_set;
}


std::array<Cell, BOARD_SIZE>
Board::get_row_cell_values(int row)
{
    if (row < 0 || row >= 9){
        throw std::out_of_range("Row index_ must be between 0 and 8");
    }

    std::array<Cell, 9> row_values;
    for (int c = 0; c < 9; c++){
        row_values[c] = board_[c][row];
    }

    return row_values;
}

std::array<Cell, BOARD_SIZE>
Board::get_col_cell_values(int col)
{
    if (col < 0 || col >= BOARD_SIZE){
        throw std::out_of_range("Row index_ must be between 0 and 8");
    }

    std::array<Cell, BOARD_SIZE> col_values;
    for (int r = 0; r < BOARD_SIZE; r++){
        col_values[r] = board_[col][r];
    }
    return col_values;
}

std::array<Cell, BOARD_SIZE>
Board::get_square_cell_values(int square_index) {
    if (square_index < 0 || square_index >= 9) {
        throw std::out_of_range("Grid index_ must be between 0 and 8");
    }

    std::array<Cell, 9> square_values;

    int start_row = (square_index / 3) * 3;
    int start_col = (square_index % 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            square_values[3*i + j] = board_[start_col + j][start_row + i];
        }
    }

    return square_values;
}


void
Board::mark_duplicates_in_row(int row){
    std::array<Cell, BOARD_SIZE> row_cells = get_row_cell_values(row);

    std::set<int> duplicate_indices = get_duplicates(row_cells);

    // now, iterate through each cell whose column is duplicate_indices and
    // mark it is a duplicate

    // how to find an element in a set:
    // https://stackoverflow.com/questions/1701067/how-to-check-that-an-element-is-in-a-stdset
    for (int col = 0; col < BOARD_SIZE; col++){
        Cell& cell_to_mark = get_cell_reference(col, row);
        if (duplicate_indices.find(col) != duplicate_indices.end()){
            // if this cell's index_ is in the set of duplicate indices
            // it is marking the positions in
            cell_to_mark.set_inconsistent(true, 'r');
        }
        else{
            cell_to_mark.set_inconsistent(false, 'r');
        }
    }
}
void
Board::mark_duplicates_in_col(int col){
    std::array<Cell, BOARD_SIZE> col_cells = get_col_cell_values(col);

    std::set<int> duplicate_indices = get_duplicates(col_cells);

    // now, iterate through each cell whose column is duplicate_indices and
    // mark it is a duplicate

    // how to find an element in a set:
    // https://stackoverflow.com/questions/1701067/how-to-check-that-an-element-is-in-a-stdset
    for (int row = 0; row < BOARD_SIZE; row++){
        Cell& cell_to_mark = get_cell_reference(col, row);
        if (duplicate_indices.find(row) != duplicate_indices.end()){
            cell_to_mark.set_inconsistent(true, 'c');
        }
        else{
            cell_to_mark.set_inconsistent(false, 'c');
        }
    }
}

void Board::mark_duplicates_in_square(int square_index)
{
    std::array<Cell, 9> square_cells = get_square_cell_values
            (square_index);

    std::set<int> duplicate_indices = get_duplicates(square_cells);

    int start_row = (square_index / 3) * 3;
    int start_col = (square_index % 3) * 3;

    // iterate through all the cells in the square given by
    // square_index. It converts the indices in 1D form
    // to the corresponding board position.
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            int i = c + 3 * r; // the corresponding index_ in 1d form
            // now check if i is in the list of duplicate indices
            // if i is indeed in the list of duplicate indices, then
            // mark that cell in the board as inconsistent
            Cell& cell_to_mark = get_cell_reference(start_col + c,
                                                   start_row + r);

            // if the index_ in 1d form is in the list of duplicate indices
            if (duplicate_indices.find(i) != duplicate_indices.end()){
                // this if statement is hitting on the correct cells
                cell_to_mark.set_inconsistent(true, 's');
            }
            else{
                cell_to_mark.set_inconsistent(false, 's');
            }
        }
    }

    // since grid indexes are defined as follows
    // 0 1 2
    // 3 4 5
    // 6 7 8

    // the start column of the square_index is square_index modulo 3
    // the starts row of the square_index is square_index integer division by 3
}


// calling this function has the Board go through every row, column, and then
// every square and then update all of its constituent Cells to be
// row_inconsistent_ if they are duplicates
void Board::mark_duplicates(){
    // we will iterate through every row, column, and square in the same loop
    for (int i = 0; i < BOARD_SIZE; i++){
        // std::cout << "marking duplicates in row and col: " << i << "\n";
        mark_duplicates_in_row(i);
        mark_duplicates_in_col(i);
        // wrong because all of the squares are starting off with red dots
        mark_duplicates_in_square(i);
    }
}

Cell Board::get_cell(int col, int row) const{
    return board_[col][row];
}

Cell& Board::get_cell_reference(int col, int row)
{
    return board_[col][row];
}
