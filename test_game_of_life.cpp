#define CATCH_CONFIG_MAIN

#include <array>
#include "../catch.hpp"
#include "game_of_life.hpp"

using namespace std;
using Matrix = array<array<int, 8>, 8>;;

TEST_CASE("Get live neighbours") {
    Matrix matrix { {
        { {0, 1, 0, 0, 0, 0, 1, 1} },
        { {1, 1, 0, 0, 0, 0, 1, 0} },
        { {1, 1, 1, 0, 0, 1, 0, 0} },
        { {1, 0, 1, 1, 0, 0, 0, 0} },
        { {1, 1, 1, 0, 0, 1, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 1, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 0, 0, 0, 0, 0, 1} }
    } };

    int actual = get_live_neighbours(0, 0, matrix);
    int actual_2 = get_live_neighbours(0, 7, matrix);
    int actual_3 = get_live_neighbours(3, 1, matrix);
    int actual_4 = get_live_neighbours(3, 4, matrix);
    int actual_5 = get_live_neighbours(7, 0, matrix);
    int actual_6 = get_live_neighbours(7, 7, matrix);

    REQUIRE(actual == 6);
    REQUIRE(actual_2 == 5);
    REQUIRE(actual_3 == 8);
    REQUIRE(actual_4 == 3);
    REQUIRE(actual_5 == 4);
    REQUIRE(actual_6 == 3);
}

TEST_CASE("Cyclical world") {
    Matrix matrix { {
        { {0, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 1} },
        { {1, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 0, 0, 0, 0, 0, 1} }
    } };

    Matrix expected { {
        { {1, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 0, 0, 0, 0, 0, 1} },
        { {1, 0, 0, 0, 0, 0, 1, 1} },
        { {1, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 0, 0, 0, 0, 0, 1} }
    } };

    next_generation(matrix);

    REQUIRE(matrix == expected);
}

TEST_CASE("Next generation") {
    Matrix matrix { {
        { {1, 1, 0, 0, 0, 0, 1, 1} },
        { {0, 0, 0, 0, 0, 0, 1, 0} },
        { {0, 0, 1, 1, 0, 0, 0, 0} },
        { {0, 0, 1, 1, 0, 0, 0, 0} },
        { {0, 0, 1, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 1, 1, 1, 0, 0, 1} }
    } };

    Matrix expected { {
        { {0, 1, 1, 1, 0, 1, 1, 0} },
        { {1, 1, 1, 0, 0, 0, 1, 0} },
        { {0, 0, 1, 1, 0, 0, 0, 0} },
        { {0, 1, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 1, 1, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 1, 0, 0, 0, 0} },
        { {0, 0, 1, 1, 0, 0, 1, 0} }
    } };

    next_generation(matrix);

    REQUIRE(matrix == expected);
}

TEST_CASE("Result after some generations") {
    Matrix matrix { {
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 1, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 1, 1, 1} }
    } };

    Matrix expected { {
        { {1, 1, 0, 0, 0, 0, 0, 0} },
        { {1, 0, 0, 0, 0, 0, 0, 1} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 0} },
        { {0, 0, 0, 0, 0, 0, 0, 1} }
    } };

    for (int i=0; i<7; i++) {
        next_generation(matrix);
    }

    REQUIRE(matrix == expected);
}