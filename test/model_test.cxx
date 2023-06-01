#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{

}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//

/*struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `player`.

    Board& board ()
    {
        return model.board_;
    }
    Position_set
    find_flips ( Model :: Position p ,
                 Model :: Dimensions d )
    {
        return model . find_flips_ (p , d );
    }
};*/
// Test 1: Input a board with a row inconsistency and check that the cells
// are marked inconsistent

TEST_CASE("Mark Duplicates Row")
{
    std::string board_string = "5_3_0_0_7_0_6_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_2_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    Board board = model.get_board();
    CHECK(board.get_cell(4, 5).is_inconsistent());
    CHECK(board.get_cell(5, 5).is_inconsistent());


}

// Test 2: Input a board with a column inconsistency and check that the cells
// are marked inconsistent
TEST_CASE("Mark Duplicates Column")
{
    std::string board_string = "5_3_0_0_7_0_0_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_1_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);    Board board = model.get_board();
    CHECK(board.get_cell(8, 2).is_inconsistent());
    CHECK(board.get_cell(8, 4).is_inconsistent());


}

// Test 3: Input a board with a square inconsistency and check that the cells
// are marked inconsistent

TEST_CASE("Mark Duplicates Square")
{
    std::string board_string = "5_3_0_0_7_0_6_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    Board board = model.get_board();
    CHECK(board.get_cell(6, 0).is_inconsistent());
    CHECK(board.get_cell(7, 2).is_inconsistent());


}

//Test 4: General duplicates with row and column inconsistencies

TEST_CASE("Mark Duplicates 1")
{
    std::string board_string = "5_3_0_0_7_0_0_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_1_1_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    Board board = model.get_board();
    CHECK(board.get_cell(2, 3).is_inconsistent());
    CHECK(board.get_cell(3, 3).is_inconsistent());
    CHECK(board.get_cell(3, 1).is_inconsistent());
}

// Test 5: General duplicates, with square, column, and row inconsistency

TEST_CASE("Mark Duplicates 2")
{
    std::string board_string = "5_3_5_0_7_0_0_0_0_\n"
                               "6_0_5_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);    Board board = model.get_board();
    CHECK(board.get_cell(0, 0).is_inconsistent());
    CHECK(board.get_cell(2, 0).is_inconsistent());
    CHECK(board.get_cell(2, 1).is_inconsistent());
    CHECK(board.get_cell(5, 1).is_inconsistent());

}

// Test 6: Game Over
TEST_CASE("Game over")
{
    std::string board_string = "5_3_4_6_7_8_9_1_2_\n"
                               "6_7_2_1_9_5_3_4_8_\n"
                               "1_9_8_3_4_2_5_6_7_\n"
                               "8_5_9_7_6_1_4_2_3_\n"
                               "4_2_6_8_5_3_7_9_1_\n"
                               "7_1_3_9_2_4_8_5_6_\n"
                               "9_6_1_5_3_7_2_8_4_\n"
                               "2_8_7_4_1_9_6_3_5_\n"
                               "3_4_5_2_8_6_1_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    Board board = model.get_board();
    model.check_game_over();
    CHECK(model.is_game_over());
}

// Test 7: Check that the fixed_ values load properly
TEST_CASE("Fixed values")
{
    std::string board_string ="5_3_0_0_7_0_0_0_0_\n"
                              "6_0_0_1_9_5_0_0_0_\n"
                              "0_9_8_0_0_0_0_6_0_\n"
                              "8_0_0_0_6_0_0_0_3_\n"
                              "4_0_0_8_0_3_0_0_1_\n"
                              "7_0_0_0_2_0_0_0_6_\n"
                              "0_6_0_0_0_0_2_8_0_\n"
                              "0_0_0_4_1_9_0_0_5_\n"
                              "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    Board board = model.get_board();
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.get_cell(col, row).get_value() != 0) {
                CHECK(board.get_cell(col,row). is_fixed());
            }

        }
    }
    CHECK(board.get_cell(0,0).is_fixed());
    CHECK(board.get_cell(0,0).is_fixed());

}

// Test 8: Check that the model can correctly process input, i.e test
// set_selected_cell and process_numerical_input, with corners and out of
// bounds and trying to modify fixed_ cell
TEST_CASE("Enter values")
{
    std::string board_string = "0_3_0_0_7_0_0_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_0_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    model.set_selected_cell({1,3});
    model.process_numerical_input(5);
    Board board = model.get_board();
    CHECK(board.get_cell(1, 3).get_value() == 5); // Random check
    // Top Left Corner
    model.set_selected_cell({0,0});
    model.process_numerical_input(6);
    Board board_1 = model.get_board();
    CHECK(board_1.get_cell(0, 0).get_value() == 6);

    // Top Right Corner
    model.set_selected_cell({0,8});
    model.process_numerical_input(7);
    Board board_2 = model.get_board();
    CHECK(board_2.get_cell(0, 8).get_value() == 7);

    // Bottom Left Corner
    model.set_selected_cell({0,8});
    model.process_numerical_input(1);
    Board board_3 = model.get_board();
    CHECK(board_3.get_cell(0, 8).get_value() == 1);


    // Bottom Right Corner
    model.set_selected_cell({8,8});
    model.process_numerical_input(9);
    Board board_4 = model.get_board();
    CHECK(board_4.get_cell(8, 8).get_value() == 9);

    // Out of bounds selected cell does nothing to board
    model.set_selected_cell({9,9});
    model.process_numerical_input(9);
    Board board_5 = model.get_board();
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.get_cell(col, row).get_value() != 0) {
                CHECK(board_5.get_cell(col,row).get_value() == board_4
                .get_cell(col,row).get_value());
            }

        }
    }

    // Attempting to change a fixed_ cell does nothing
    model.set_selected_cell({0,1});
    model.process_numerical_input(8);
    Board board_6 = model.get_board();
    CHECK(board_6.get_cell(0, 1).get_value() == 6);

}

// Test 9: Test that the move functions in model work properly
TEST_CASE("Model move") {
    std::string board_string = "5_3_0_0_7_0_0_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string =  "5_3_4_6_7_8_9_1_2_\n"
                                   "6_7_2_1_9_5_3_4_8_\n"
                                   "1_9_8_3_4_2_5_6_7_\n"
                                   "8_5_9_7_6_1_4_2_3_\n"
                                   "4_2_6_8_5_3_7_9_1_\n"
                                   "7_1_3_9_2_4_8_5_6_\n"
                                   "9_6_1_5_3_7_2_8_4_\n"
                                   "2_8_7_4_1_9_6_3_5_\n"
                                   "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    model.set_selected_cell({1,3});
    model.move_select_down();
    ge211::Posn<int> expect_pos = {1,4};
    CHECK(model.get_selected_cell() == expect_pos);
    model.move_select_right();
    ge211::Posn<int> expect_pos_1 = {2,4};
    CHECK(model.get_selected_cell() == expect_pos_1);
    model.move_select_left();
    ge211::Posn<int> expect_pos_2 = {1,4};
    CHECK(model.get_selected_cell() == expect_pos_2);
    model.move_select_down();
    ge211::Posn<int> expect_pos_3 = {1,5};
    CHECK(model.get_selected_cell() == expect_pos_3);

    // Set selected cell to bottom right and try to move down, expect no change
    model.set_selected_cell({8,8});
    model.move_select_down();
    ge211::Posn<int> expect_pos_4 = {8,8};
    CHECK(model.get_selected_cell() == expect_pos_4);


}

// Test 10: Clearing cells and working with hints
TEST_CASE("Clear cells and hints")
{
    std::string board_string = "5_3_0_0_7_0_0_0_0_\n"
                               "6_0_0_1_9_5_0_0_0_\n"
                               "0_9_8_0_0_0_0_6_0_\n"
                               "8_0_0_0_6_0_0_0_3_\n"
                               "4_0_0_8_0_3_0_0_1_\n"
                               "7_0_0_0_2_0_0_0_6_\n"
                               "0_6_0_0_0_0_2_8_0_\n"
                               "0_0_0_4_1_9_0_0_5_\n"
                               "0_0_0_0_8_0_0_7_9_\n";
    std::string solution_string = "5_3_4_6_7_8_9_1_2_\n"
                                  "6_7_2_1_9_5_3_4_8_\n"
                                  "1_9_8_3_4_2_5_6_7_\n"
                                  "8_5_9_7_6_1_4_2_3_\n"
                                  "4_2_6_8_5_3_7_9_1_\n"
                                  "7_1_3_9_2_4_8_5_6_\n"
                                  "9_6_1_5_3_7_2_8_4_\n"
                                  "2_8_7_4_1_9_6_3_5_\n"
                                  "3_4_5_2_8_6_1_7_9_\n";
    const std::pair<Board, Board>& board_pair = std::make_pair(Board(board_string, {BOARD_SIZE,BOARD_SIZE}),
                                                               Board(solution_string,{BOARD_SIZE,BOARD_SIZE}));
    Model model = Model(board_pair);
    model.set_selected_cell({1, 2});
    model.attempt_clear_selected_cell();
    Board board = model.get_board();
    CHECK(board.get_cell(1, 2).get_value() == 9); // Attempt to clear fixed_ cell

    model.set_selected_cell({1, 3}); // select cell not fixed_
    model.process_numerical_input(1); // enter value_ 1
    model.set_selected_cell({1, 4}); // move selected cell
    model.set_selected_cell({1, 3}); // move back
    model.attempt_clear_selected_cell(); // clear
    Board board1 = model.get_board();
    CHECK(board1.get_cell(1, 3).get_value() == 0); // check that value_ is 0

    // Try to clear hint_ cell, also a test of reveal_answer()
    model.set_selected_cell({1, 4}); // select cell not fixed_
    model.reveal_answer();
    Board board2 = model.get_board();
    CHECK(board2.get_cell(1,4).is_hint());
    CHECK(board2.get_cell(1,4).get_value() == 2);
    model.attempt_clear_selected_cell();
    CHECK(board2.get_cell(1,4).get_value() == 2);

}


/*Test_access::Test_access(Model& model)
        : model(model)
{ }*/
