#include "model.hxx"


// 2D-list of numbers represents board
// to store the candidate numbers that the user inputs, you can make a
// parallel 2D list of NumberSets, similar to PositionSets or MoveMaps
// where you can set, the square in row i and column j to have a candidate
// number of "X" by model_.board[i][i][X] = true;


using Position = ge211::Posn<int>;

Model::Model(std::string board_string, std::string solution_string)
    : board_(board_string, {9, 9}),
      solution_(solution_string, {9, 9}),
      selected_cell_index_(4, 4)
{
    std::cout << "Model constructor\n";
    board_.mark_duplicates();

}

bool
Model::is_in_bounds(Position cell_index) const {
    bool oob_horizontal = cell_index.x < 0 or cell_index.x + 1 > BOARD_SIZE;
    bool oob_vertical = cell_index.y < 0 or cell_index.y + 1 > BOARD_SIZE;
    if (oob_horizontal or oob_vertical){
        return false;
    }
    else{
        return true;
    }
}


// sets the selected cell only if the given cell index is in bounds
void
Model::set_selected_cell(Position cell_index){
    if (is_in_bounds(cell_index)){
        selected_cell_index_ = cell_index;
    }
}

void
Model::move_select_up()
{
    Position new_pos = selected_cell_index_.up_by(1);
    set_selected_cell(new_pos);
}

void Model::move_select_down()
{
    Position new_pos = selected_cell_index_.down_by(1);
    set_selected_cell(new_pos);
}

void Model::move_select_left()
{
    Position new_pos = selected_cell_index_.left_by(1);
    set_selected_cell(new_pos);
}

void Model::move_select_right()
{
    Position new_pos = selected_cell_index_.right_by(1);
    set_selected_cell(new_pos);
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

Board&
Model::get_board_reference()
{
    return board_;
}


Position
Model::get_selected_cell() const
{
    return selected_cell_index_;
}

void Model::print_board() const{
    Board board = get_board();
    std::cout << "Board\n----------------------------\n";
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            Cell curr = board.get_cell(j, i);
            std::cout << curr.get_value();
            if (curr.is_inconsistent()){
                std::cout << "x";
            }
            std::cout << "_";
        }
        std::cout << "\n";
    }
}

void Model::process_numerical_input(int n){
    Cell& curr_cell = board_.get_cell_reference(selected_cell_index_.x,
                                               selected_cell_index_.y);
    // if the current cell is fixed or a hint, then we can't write over this
    // cell
    if (curr_cell.is_fixed() or curr_cell.is_hint()){
        return;
    }
    // otherwise, set the value of this cell to the user input
    else{
        std::cout << "Setting value of " << curr_cell.get_index() << "to " <<
        n << "\n";
        curr_cell.set_value(n);
    }
}

void
Model::reveal_answer(){
    Cell& curr_cell = board_.get_cell_reference(selected_cell_index_.x,
                                                selected_cell_index_.y);
    Cell& soln_cell = solution_.get_cell_reference(selected_cell_index_.x,
                                                   selected_cell_index_.y);
    if (!curr_cell.is_fixed()) {
        curr_cell.set_hint(true);
        curr_cell.set_value(soln_cell.get_value());
    }

   /*if (curr_cell.is_hint()) {
    } else {
        return;
    }*/
}


void Model::attempt_clear_selected_cell()
{
    Cell& curr_cell = board_.get_cell_reference(selected_cell_index_.x,
                                                selected_cell_index_.y);

    if (curr_cell.is_fixed() or curr_cell.is_hint()){
        return;
    }
    else{
        std::cout << "Clearing cell: " << curr_cell.get_index() << "\n";
        curr_cell.set_value(0);
    }
}