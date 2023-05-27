#include "board.hxx"
#include <sstream>

using namespace ge211;

/*struct Test_access
{
    Board& board;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Board&);
    // Sets the player at `posn` to `player`.
    // Gives direct access to `model.next_moves_` so our tests can modify it:
    Move_map& ();
    Board & board ()
    {
        return board.board ;
    }
    std::set<int> get_duplicates(std::vector<int>& values)
    {
        return board.get_duplicates(values);
    }

    Position_set
    find_flips ( Model :: Position p ,
                 Model :: Dimensions d )
    {
        return model . find_flips_ (p , d );
    }
};

TEST_CASE ("get_duplicates") {

}*/
