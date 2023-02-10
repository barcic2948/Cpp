#include <iostream>
#include <string>
#include <vector>

const auto NOT = [](bool input_a) -> bool {return !input_a;};
const auto AND = [](bool input_a, bool input_b) -> bool {return input_a & input_b;};
const auto OR = [](bool input_a, bool input_b) -> bool {return input_a | input_b;};
const auto NAND = [](bool input_a, bool input_b) -> bool {return !(input_a & input_b);};
const auto NOR = [](bool input_a, bool input_b) -> bool {return !(input_a | input_b);};
const auto XOR = [](bool input_a, bool input_b) -> bool {return input_a ^ input_b;};

class Gate
{
public:
    std::string id;
    std::string type;
    std::vector<std::string> inputs;
    bool state;
    std::string cycle;

    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state);
    ~Gate();

    void update();
};

Gate::Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state) :
    id(id), type(type), inputs(inputs), state(state) {};

Gate::~Gate()
{
}

void Gate::update() {
    if(this->state) {
        this->cycle+= '+';
    }
    else {
        this->cycle+= '-';
    }
}

std::vector<Gate> components {
    Gate("CLOCK", "clock", {"4"}, false),
    Gate("SET_1", "custom", {"0000001111111000000000000000000000000000000000000000000000000000000000000"}, false),
    Gate("AND_1", "and", {"CLOCK", "SET_1"}, true),
    Gate("SET_2", "custom", {"000000000000000000000111111000000000000000000000000000000000000000000000000"}, false),
    Gate("AND_2", "and", {"CLOCK", "SET_2"}, true),
    Gate("NOR_1", "nor", {"AND_1", "NOR_2"}, false),
    Gate("NOR_2", "nor", {"AND_2", "NOR_1"}, false)
    
};

std::vector<Gate> SR {
    Gate("SET_3", "custom", {"0000111100000000000000000000000000000000000000"}, false),
    Gate("SET_4", "custom", {"0000000000000000001111000000000000000000000000"}, false),
    Gate("NOR_1", "nor", {"SET_3", "NOR_2"}, false),
    Gate("NOR_2", "nor", {"SET_4", "NOR_1"}, false)
};


const auto indexBy = [](std::vector<Gate> components, std::string id) -> Gate {
    for(auto it : components) {
        if(it.id == id) {
            return it;
        }
    }
};


void solveBin() {
    for(int i = 0; i < 2; i++) {
        for(auto &component : components) {
            if(component.type == "controled") {}
            else if (component.type == "custom") {
                component.state = int(component.inputs[0][component.cycle.length()])-48;
            }
            else if (component.type == "clock"){
                if(i == 0){
                    component.state = component.cycle.length() % stoi(component.inputs[0]) ? component.state : !component.state;
                }
            }
            else if (component.type == "not"){
                bool Input = indexBy(components, component.inputs[0]).state;
                component.state = NOT(Input);
            }
            else {
                bool Input_1 = indexBy(components, component.inputs[0]).state;
                bool Input_2 = indexBy(components, component.inputs[1]).state;
                if(component.type == "and") {component.state = AND(Input_1, Input_2);}
                else if(component.type == "nand") {component.state = NAND(Input_1, Input_2);}
                else if(component.type == "or") {component.state = OR(Input_1, Input_2);}
                else if(component.type == "nor") {component.state = NOR(Input_1, Input_2);}
                else if(component.type == "xor") {component.state = XOR(Input_1, Input_2);}
            }
            if(i == 1){
                component.update();
            }
        }
    }
}

void print_state() {
    for(auto component : components) {
        std::cout << component.id << " -> " << component.cycle << std::endl;
    }
}

void simulate() {
    int CLOCK_CYCLES = 20;
    int CLOCK_LENGTH = 2;
    for(int i = 0; i < CLOCK_CYCLES*CLOCK_LENGTH; i++) {
        solveBin();
    }
}

int main(int, char**) {
    std::cout << "START" << std::endl;
    simulate();
    print_state();
}
