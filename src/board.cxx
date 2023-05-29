//
// Created by Ravi Nuxoll on 5/24/23.
//


#include "board.hxx"

Board::Board(std::string board_string, Dimensions dims)
    :dims_(dims)
{
    std::stringstream ss(board_string);
    std::string line;

    // TODO modify this
    std::cout << "Board constructor\n";

    std::cout << board_string;

    // for (int i = 0; i < dims.width; i++){
    //     for (int j = 0; j < dims.height; j++){
    //         board[i][j] = Cell(1, ge211::Posn<int>(i, j));
    //     }
    // }
    // int row = 0;
    // while (std::getline(ss, line, '\n') && row < BOARD_SIZE) {
    //     for (int col = 0; col < BOARD_SIZE; ++col) {
    //         char c = line[col * 2];  // Because every other char is an underscore '_'
    //         int value = (c == '_') ? 0 : c - '0';  // Convert char to int
    //         board[row][col] = Cell(value, {row, col});
    //     }
    //     ++row;
    // }

    int row = 0;
    while (std::getline(ss, line, '\n') && row < BOARD_SIZE) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            char c = line[col * 2];  // Because every other char is an underscore '_'
            int value = (c == '_') ? 0 : c - '0';  // Convert char to int
            board[col][row] = Cell(value, {col, row});
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
                // if the duplicate value is 0, then it's a blank square and
                // not really a duplicate
                if (values[i].get_value() != 0 and values[i].get_value() ==
                values[j].get_value
                ()) {

                    // modification: return indexes of duplicates
                    // return_set.insert(values[i].get_value());
                    return_set.insert(i);
                    return_set.insert(j);
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
        row_values[c] = board[c][row];
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
        col_values[r] = board[col][r];
    }
    return col_values;
}

std::array<std::array<Cell, 3>, 3>
Board::get_subgrid_values(int grid_index) {
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


void
Board::mark_duplicates_in_row(int row){
    std::array<Cell, BOARD_SIZE> row_cells = get_row_values(row);
    for(const Cell& cell : row_cells) {
        std::cout << cell.get_value() << " ";
    }
    std::set<int> duplicate_indices = get_duplicates(row_cells);
    //
    //
    std::cout << "row: " << row << "\n";
    std::cout << "get duplicates told us that the duplicate indices are: ";
    for (const auto &index : duplicate_indices) {
        std::cout << index << " ";
    }
    std::cout << "\n";

    // now, iterate through each cell whose column is duplicate_indices and
    // mark it is a duplicate

    // how to find an element in a set:
    // https://stackoverflow.com/questions/1701067/how-to-check-that-an-element-is-in-a-stdset
    for (int col = 0; col < BOARD_SIZE; col++){
        Cell& cell_to_mark = get_cell_reference(col, row);
        if (duplicate_indices.find(col) != duplicate_indices.end()){
            // if this cell's index is in the set of duplicate indices
            if (row == 0){
                std::cout << "Marking cell: " << cell_to_mark.get_index() <<
                "as row_inconsistent\n";
            }
            // it is marking the positions in
            cell_to_mark.set_inconsistent(true, 'r');

            Cell cell_to_mark_final = get_cell_reference(col, row);
            std::cout << "Final value of row_inconsistent: " <<
            cell_to_mark_final.is_inconsistent() << "\n";
        }
        else{
            // std::cout << "Marking cell: " << cell_to_mark.get_index() << "
            // as ""consistent\n";
            if (row == 0){
                std::cout << "Marking cell: " << cell_to_mark.get_index() <<
                          "as consistent\n";
            }
            cell_to_mark.set_inconsistent(false, 'r');
        }
    }
}
void
Board::mark_duplicates_in_col(int col){
    std::array<Cell, BOARD_SIZE> col_cells = get_col_values(col);

    for(const Cell& cell : col_cells) {
        std::cout << cell.get_value() << " ";
    }
    std::set<int> duplicate_indices = get_duplicates(col_cells);

    // std::cout << "col: " << col << "\n";
    // std::cout << "get duplicates told us that the " << duplicate_indices.size
    // () << " duplicate indices are: ";
    // for (const auto &index : duplicate_indices) {
    //     std::cout << index << " ";
    // }
    // std::cout << "\n";

    // now, iterate through each cell whose column is duplicate_indices and
    // mark it is a duplicate

    // how to find an element in a set:
    // https://stackoverflow.com/questions/1701067/how-to-check-that-an-element-is-in-a-stdset
    for (int row = 0; row < BOARD_SIZE; row++){
        Cell& cell_to_mark = get_cell_reference(col, row);
        if (duplicate_indices.find(row) != duplicate_indices.end()){
            // if this cell's index is in the set of duplicate indices
            // std::cout << "Marking cell: " << cell_to_mark.get_index() <<
            //           "as row_inconsistent\n";
            // it is marking the positions in
            cell_to_mark.set_inconsistent(true, 'c');

            Cell cell_to_mark_check = get_cell_reference(col, row);
            // std::cout << "Final value of row_inconsistent bool: " <<
            // cell_to_mark_check.is_inconsistent() << "\n";
        }
        // todo, I think the error is here
        // cells that are marked row_inconsistent because of some property in the
        // row
        // are marked as consistent in the column if the column is consistent
        // one way around this is to create separate bools for
        // row_inconsistent, col_inconsistent, and square_inconsistent
        else{
            std::cout << "Marking cell: " << cell_to_mark.get_index() << "as "
            "consistent\n";
            cell_to_mark.set_inconsistent(false, 'c');
        }

        // std::cout << "checked if we need to mark something in row: " << row
        // << "\n";
    }
}


// calling this function has the Board go through every row, column, and then
// every square and then update all of its constituent Cells to be row_inconsistent
// if they are duplicates
void Board::mark_duplicates(){
    // we will iterate through every row, column, and square in the same loop
    for (int i = 0; i < BOARD_SIZE; i++){
        std::cout << "marking duplicates in row and col: " << i << "\n";
        mark_duplicates_in_row(i);
        mark_duplicates_in_col(i);
        // mark_duplicates_in_square(i);
    }

    std::cout << "finished marking duplicates!\n";
}

Cell Board::get_cell(int row, int col) const{
    return board[row][col];
}

Cell& Board::get_cell_reference(int row, int col)
{
    return board[row][col];
}
