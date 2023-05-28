#include "model.hxx"


// 2D-list of numbers represents board
// to store the candidate numbers that the user inputs, you can make a
// parallel 2D list of NumberSets, similar to PositionSets or MoveMaps
// where you can set, the square in row i and column j to have a candidate
// number of "X" by model_.board[i][i][X] = true;


using Position = ge211::Posn<int>;

Model::Model(std::string board_string)
    : board_(board_string, {9, 9}),
      selected_square_(4, 4)
{
    std::cout << "Model constructor\n";

}

void
Model::set_selected_cell(Position cell_index){
    selected_square_ = cell_index;
}


Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}

Board
Model::get_board() const
{
    return board_;
}


Position
Model::get_selected_cell() const
{
    return selected_square_;
}