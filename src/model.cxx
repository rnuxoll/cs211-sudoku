#include "model.hxx"


// 2D-list of numbers represents board
// to store the candidate numbers that the user inputs, you can make a
// parallel 2D list of NumberSets, similar to PositionSets or MoveMaps
// where you can set, the square in row i and column j to have a candidate
// number of "X" by model_.board[i][i][X] = true;

Model::Model()
    : board_({9, 9}),
      selected_square_(4, 4)
{
    std::cout << "Model constructor\n";

}

Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}