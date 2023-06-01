#include "model.hxx"
#include <random>


// 2D-list of numbers represents board
// to store the candidate numbers that the user inputs, you can make a
// parallel 2D list of NumberSets, similar to PositionSets or MoveMaps
// where you can set, the square in row i and column j to have a candidate
// number of "X" by model_.board[i][i][X] = true;


using Position = ge211::Posn<int>;
using str = std::string;


Model::Model(const std::pair<Board, Board>& board_solution)
    : board_(board_solution.first),
    solution_(board_solution.second),
    selected_cell_index_(4, 4),
    new_game_(true),
    game_over_(false)
{
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


// sets the selected cell only if the given cell index_ is in bounds
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
    // if the current cell is fixed_ or a hint_, then we can't write over this
    // cell
    if (curr_cell.is_fixed() or curr_cell.is_hint()){
        return;
    }
    // otherwise, set the value_ of this cell to the user input
    else{
        // std::cout << "Setting value_ of " << curr_cell.get_index() << "to "
        // << n << "\n";
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

}


void Model::attempt_clear_selected_cell()
{
    Cell& curr_cell = board_.get_cell_reference(selected_cell_index_.x,
                                                selected_cell_index_.y);

    if (curr_cell.is_fixed() or curr_cell.is_hint()){
        return;
    }
    else{
        // std::cout << "Clearing cell: " << curr_cell.get_index() << "\n";
        curr_cell.set_value(0);
    }
}


void Model::check_game_over(){
    for (int r = 0; r < BOARD_SIZE; r++){
        for (int c = 0; c < BOARD_SIZE; c++){
            Cell curr_cell = board_.get_cell(c, r);
            if (curr_cell.get_value() == 0 or curr_cell.is_inconsistent()){
                game_over_ = false;
                return;
            }
        }
    }
    game_over_ = true;
}

bool Model::is_game_over() const{
    return game_over_;
}

bool Model::is_new_game() const
{
    return new_game_;
}

std::pair<Board, Board> Model::get_random_board(){

        str board_1 =
            "5_3_0_0_7_0_0_0_0_\n"
            "6_0_0_1_9_5_0_0_0_\n"
            "0_9_8_0_0_0_0_6_0_\n"
            "8_0_0_0_6_0_0_0_3_\n"
            "4_0_0_8_0_3_0_0_1_\n"
            "7_0_0_0_2_0_0_0_6_\n"
            "0_6_0_0_0_0_2_8_0_\n"
            "0_0_0_4_1_9_0_0_5_\n"
            "0_0_0_0_8_0_0_7_9_\n";

        str solution_1 =
            "5_3_4_6_7_8_9_1_2_\n"
            "6_7_2_1_9_5_3_4_8_\n"
            "1_9_8_3_4_2_5_6_7_\n"
            "8_5_9_7_6_1_4_2_3_\n"
            "4_2_6_8_5_3_7_9_1_\n"
            "7_1_3_9_2_4_8_5_6_\n"
            "9_6_1_5_3_7_2_8_4_\n"
            "2_8_7_4_1_9_6_3_5_\n"
            "3_4_5_2_8_6_1_7_9_\n";

        str board_2 =
            "8_2_7_0_0_0_0_6_1_\n"
            "0_1_5_9_0_7_0_0_0_\n"
            "0_0_0_0_6_0_0_8_5_\n"
            "4_0_8_3_1_0_0_5_0_\n"
            "1_0_0_7_4_0_0_0_2_\n"
            "2_0_9_0_0_0_1_0_7_\n"
            "0_4_0_0_9_6_3_0_0_\n"
            "0_6_1_0_2_0_5_0_0_\n"
            "9_8_0_0_0_4_2_0_6_\n";

        str solution_2 =
            "8_2_7_4_3_5_9_6_1_\n"
            "6_1_5_9_8_7_4_2_3_\n"
            "3_9_4_2_6_1_7_8_5_\n"
            "4_7_8_3_1_2_6_5_9_\n"
            "1_5_6_7_4_9_8_3_2_\n"
            "2_3_9_6_5_8_1_4_7_\n"
            "5_4_2_1_9_6_3_7_8_\n"
            "7_6_1_8_2_3_5_9_4_\n"
            "9_8_3_5_7_4_2_1_6_\n";

        // define two arrays of strings
        str board_array[] = {board_1, board_2};
        str solution_array[] = {solution_1, solution_2};

        // get the board_array_size of arrays
        size_t board_array_size = sizeof(board_array) / sizeof(board_array[0]);

        // create random engine
        std::default_random_engine generator;
        generator.seed(std::random_device()()); // to get different outcomes each time you run the code
        std::uniform_int_distribution<size_t> distribution(0, board_array_size - 1); // define the distribution

        // generate a random index_
        size_t randomIndex = distribution(generator);

        // return pair of strings at the randomly selected index_
        Board chosen_board = Board(board_array[randomIndex], {BOARD_SIZE, BOARD_SIZE});
        Board chosen_board_solution = Board(solution_array[randomIndex],
                                            {BOARD_SIZE, BOARD_SIZE});

        return std::make_pair(chosen_board, chosen_board_solution);
}


std::pair<Board, Board> Model::get_random_beginner_game(){
    str board_1 =
            "8_2_7_0_0_0_0_6_1_\n"
            "0_1_5_9_0_7_0_0_0_\n"
            "0_0_0_0_6_0_0_8_5_\n"
            "4_0_8_3_1_0_0_5_0_\n"
            "1_0_0_7_4_0_0_0_2_\n"
            "2_0_9_0_0_0_1_0_7_\n"
            "0_4_0_0_9_6_3_0_0_\n"
            "0_6_1_0_2_0_5_0_0_\n"
            "9_8_0_0_0_4_2_0_6_\n";

    str solution_1 =
            "8_2_7_4_3_5_9_6_1_\n"
            "6_1_5_9_8_7_4_2_3_\n"
            "3_9_4_2_6_1_7_8_5_\n"
            "4_7_8_3_1_2_6_5_9_\n"
            "1_5_6_7_4_9_8_3_2_\n"
            "2_3_9_6_5_8_1_4_7_\n"
            "5_4_2_1_9_6_3_7_8_\n"
            "7_6_1_8_2_3_5_9_4_\n"
            "9_8_3_5_7_4_2_1_6_\n";

    // define two arrays of strings
    str board_array[] = {board_1};
    str solution_array[] = {solution_1, };

    // get the board_array_size of arrays
    size_t board_array_size = sizeof(board_array) / sizeof(board_array[0]);

    // create random engine
    std::default_random_engine generator;
    generator.seed(std::random_device()()); // to get different outcomes each time you run the code
    std::uniform_int_distribution<size_t> distribution(0, board_array_size - 1); // define the distribution

    // generate a random index_
    size_t randomIndex = distribution(generator);

    // return pair of strings at the randomly selected index_
    Board chosen_board = Board(board_array[randomIndex], {BOARD_SIZE, BOARD_SIZE});
    Board chosen_board_solution = Board(solution_array[randomIndex],
                                        {BOARD_SIZE, BOARD_SIZE});

    return std::make_pair(chosen_board, chosen_board_solution);
}

std::pair<Board, Board> Model::get_random_normal_game(){

    str board_1 =
            "5_3_0_0_7_0_0_0_0_\n"
            "6_0_0_1_9_5_0_0_0_\n"
            "0_9_8_0_0_0_0_6_0_\n"
            "8_0_0_0_6_0_0_0_3_\n"
            "4_0_0_8_0_3_0_0_1_\n"
            "7_0_0_0_2_0_0_0_6_\n"
            "0_6_0_0_0_0_2_8_0_\n"
            "0_0_0_4_1_9_0_0_5_\n"
            "0_0_0_0_8_0_0_7_9_\n";

    str solution_1 =
            "5_3_4_6_7_8_9_1_2_\n"
            "6_7_2_1_9_5_3_4_8_\n"
            "1_9_8_3_4_2_5_6_7_\n"
            "8_5_9_7_6_1_4_2_3_\n"
            "4_2_6_8_5_3_7_9_1_\n"
            "7_1_3_9_2_4_8_5_6_\n"
            "9_6_1_5_3_7_2_8_4_\n"
            "2_8_7_4_1_9_6_3_5_\n"
            "3_4_5_2_8_6_1_7_9_\n";


    // define two arrays of strings
    str board_array[] = {board_1};
    str solution_array[] = {solution_1};

    // get the board_array_size of arrays
    size_t board_array_size = sizeof(board_array) / sizeof(board_array[0]);

    // create random engine
    std::default_random_engine generator;
    generator.seed(std::random_device()()); // to get different outcomes each time you run the code
    std::uniform_int_distribution<size_t> distribution(0, board_array_size - 1); // define the distribution

    // generate a random index_
    size_t randomIndex = distribution(generator);

    // return pair of strings at the randomly selected index_
    Board chosen_board = Board(board_array[randomIndex], {BOARD_SIZE, BOARD_SIZE});
    Board chosen_board_solution = Board(solution_array[randomIndex],
                                        {BOARD_SIZE, BOARD_SIZE});

    return std::make_pair(chosen_board, chosen_board_solution);
}

std::pair<Board, Board> Model::get_random_expert_game(){

    str board_1 =
            "0_0_0_6_0_0_0_0_0_\n"
            "0_4_6_0_5_0_0_2_0_\n"
            "0_7_0_4_0_0_0_5_8_\n"
            "6_0_0_9_0_0_3_0_0_\n"
            "4_0_0_0_0_0_0_0_0_\n"
            "0_0_1_7_0_2_0_0_0_\n"
            "8_5_0_0_9_0_0_3_0_\n"
            "0_0_0_5_0_0_0_0_0_\n"
            "0_0_0_0_0_3_0_7_0_\n";

    str solution_1 =
            "2_8_5_6_7_9_1_4_3_\n"
            "1_4_6_3_5_8_7_2_9_\n"
            "3_7_9_4_2_1_6_5_8_\n"
            "6_2_8_9_4_5_3_1_7_\n"
            "4_3_7_8_1_6_2_9_5_\n"
            "5_9_1_7_3_2_8_6_4_\n"
            "8_5_2_1_9_7_4_3_6_\n"
            "7_1_3_5_6_4_9_8_2_\n"
            "9_6_4_2_8_3_5_7_1_\n";


    // define two arrays of strings
    str board_array[] = {board_1};
    str solution_array[] = {solution_1};

    // get the board_array_size of arrays
    size_t board_array_size = sizeof(board_array) / sizeof(board_array[0]);

    // create random engine
    std::default_random_engine generator;
    generator.seed(std::random_device()()); // to get different outcomes each time you run the code
    std::uniform_int_distribution<size_t> distribution(0, board_array_size - 1); // define the distribution

    // generate a random index_
    size_t randomIndex = distribution(generator);

    // return pair of strings at the randomly selected index_
    Board chosen_board = Board(board_array[randomIndex], {BOARD_SIZE, BOARD_SIZE});
    Board chosen_board_solution = Board(solution_array[randomIndex],
                                        {BOARD_SIZE, BOARD_SIZE});

    return std::make_pair(chosen_board, chosen_board_solution);
}



void Model::start_new_game(char difficulty)
{
    // this is just done because C++ insists we initialize it with a value_
    std::pair<Board, Board> board_solution = get_random_normal_game();
    new_game_ = false;
    // as the current one and returns false

    // delay initialization of variable:
    // https://stackoverflow.com/questions/38603409/what-is-the-most-idiomatic-way-to-delay-the-construction-of-a-c-object
    switch(difficulty) {
    case ('b'):
        board_solution = get_random_beginner_game();
        break;
    case ('n'):
        board_solution = get_random_normal_game();
        break;
    case ('e'):
        board_solution = get_random_expert_game();
        break;
    default:
        break;
    }

    board_ = board_solution.first;
    solution_ = board_solution.second;
}