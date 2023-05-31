#include "controller.hxx"

#include "stdio.h"
#include <string>

int
main()
{
    // std::string example_board = "[ "
    // "[ 5, 3, 0, 0, 7, 0, 0, 0, 0 ],"
    // "[ 6, 0, 0, 1, 9, 5, 0, 0, 0 ],"
    // "[ 0, 9, 8, 0, 0, 0, 0, 6, 0 ],"
    // "[ 8, 0, 0, 0, 6, 0, 0, 0, 3 ],"
    // "[ 4, 0, 0, 8, 0, 3, 0, 0, 1 ],"
    // "[ 7, 0, 0, 0, 2, 0, 0, 0, 6 ],"
    // "[ 0, 6, 0, 0, 0, 0, 2, 8, 0 ],"
    // "[ 0, 0, 0, 4, 1, 9, 0, 0, 5 ],"
    // "[ 0, 0, 0, 0, 8, 0, 0, 7, 9 ]"
    // "]";

    std::string example_board =
            "5_3_0_0_7_0_0_0_0_\n"
            "6_0_0_1_9_5_0_0_0_\n"
            "0_9_8_0_0_0_0_6_0_\n"
            "8_0_0_0_6_0_0_0_3_\n"
            "4_0_0_8_0_3_0_0_1_\n"
            "7_0_0_0_2_0_0_0_6_\n"
            "0_6_0_0_0_0_2_8_0_\n"
            "0_0_0_4_1_9_0_0_5_\n"
            "0_0_0_0_8_0_0_7_9_\n";

    // todo replace this solution string with a solved board
    std::string example_solution =
            "5_3_4_6_7_8_9_1_2_\n"
            "6_7_2_1_9_5_3_4_8_\n"
            "1_9_8_3_4_2_5_6_7_\n"
            "8_5_9_7_6_1_4_2_3_\n"
            "4_2_6_8_5_3_7_9_1_\n"
            "7_1_3_9_2_4_8_5_6_\n"
            "9_6_1_5_3_7_2_8_4_\n"
            "2_8_7_4_1_9_6_3_5_\n"
            "3_4_5_2_8_6_1_7_9_\n";

    Controller(example_board, example_solution).run();


    return 0;
}
