#include <iostream>
#include <string>
#include <vector>
#include "src\game.h"


int main(int, char**) {
    std::cout << "START" << std::endl;


    std::vector<Gate> components {
    Gate("Set", "custom", {"0000000000001111"}, false, "trace"),
    Gate("Reset", "custom", {"00001111"}, false, "trace"),
    Gate("Q", "nor", {"Reset", "~Q"}, false, "trace"),
    Gate("~Q", "nor", {"Set", "Q"}, false, "trace"),
    };


    Circuit temp(components);
    temp.simulate(52);

}
