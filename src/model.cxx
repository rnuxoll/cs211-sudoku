#include "model.hxx"


// 2D-list of numbers represents board
// to store the candidate numbers that the user inputs, you can make a
// parallel 2D list of NumberSets, similar to PositionSets or MoveMaps
// where you can set, the square in row i and column j to have a candidate
// number of "X" by model_.board[i][i][X] = true;

Model::Model()
    : selected_square_(Position(5, 5))
{

}
