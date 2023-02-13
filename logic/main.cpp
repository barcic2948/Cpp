#include <iostream>
#include <string>
#include <vector>
#include "src\game.h"
#include "src\CreateGate.h"


int main(int, char**) {
    std::cout << "START" << std::endl;

    CreateGate test;
    
    std::vector<Gate> components5 {
    Gate("Clock", "clock", {"0", "1"}, false),
    Gate("Custom", "custom", {"001111000000101000001000000011111111111000000000"}, false)
    };
    
    std::vector<Gate> tab2 = test.counter_ib(4, "test", "Clock");

    Circuit temp(components5);
    temp.addToCircuit(tab2);
    //temp.printComps();
    temp.simulate(250);
    //temp.printComps();
}
