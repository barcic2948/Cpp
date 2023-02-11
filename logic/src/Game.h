#include<vector>
#include<string>
#include<iostream>

class Gate
{
public:
    std::string id;
    std::string type;
    std::vector<std::string> inputs;
    bool state;

    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state) :
    id(id), type(type), inputs(inputs), state(state) {};
    
    std::string trace;
    bool traceEnable = false;

    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state, std::string traceEnable) :
    id(id), type(type), inputs(inputs), state(state), traceEnable(traceEnable == "trace" ? true : false) {};

    void traceUpdate() {this->trace += this->state ? '+' : '-';}
};

class Circuit
{
private:

    std::vector<Gate> components;

    const bool NOT(bool input_a) { return !input_a; };
    const bool AND(bool input_a, bool input_b) { return input_a & input_b; };
    const bool OR(bool input_a, bool input_b) { return input_a | input_b; };
    const bool NAND(bool input_a, bool input_b) { return !(input_a & input_b); };
    const bool NOR(bool input_a, bool input_b){ return !(input_a | input_b); };
    const bool XOR(bool input_a, bool input_b) { return input_a ^ input_b; };

    const Gate indexBy(std::string id) {
        for(auto &it : components) { if(it.id == id){return it;}}};

    void calculateState(int cycle);

    public:
        Circuit(std::vector<Gate> components) : components(components) {};
        
        void simulate(unsigned int cycles);

        void printTrace();
};

void Circuit::calculateState(int cycle) {
    for (size_t i = 0; i < 2; i++) {
        for (auto &component : this->components) {
            if (component.type == "controled") {}
            else if (component.type == "custom") {
                component.state = cycle <= component.inputs[0].length() - 1 ? short(component.inputs[0][cycle]) - 48 : 0;
            }
            else if (component.type == "clock") {
                if(i == 0) {
                    component.state = cycle ? ((cycle + stoi(component.inputs[0]) + 1) % (stoi(component.inputs[1]) + 1) ? component.state : !component.state) : component.state;
                }
            }
            else if (component.type == "not") {
                component.state = Circuit::NOT(Circuit::indexBy(component.inputs[0]).state);
            }
            else {
                bool input_1 = indexBy(component.inputs[0]).state;
                bool input_2 = indexBy(component.inputs[1]).state;

                if(component.type == "and") {component.state = AND(input_1, input_2);}
                else if(component.type == "nand") {component.state = NAND(input_1, input_2);}
                else if(component.type == "or") {component.state = OR(input_1, input_2);}
                else if(component.type == "nor") {component.state = NOR(input_1, input_2);}
                else if(component.type == "xor") {component.state = XOR(input_1, input_2);}
                else {}
            }
            if(i == 1 && component.traceEnable) {component.traceUpdate();}
        }
    }
}


void Circuit::printTrace() {
    int maxlen;
    for(auto component : this -> components) {
        if(component.traceEnable) {maxlen = component.id.length() > maxlen ? component.id.length() : maxlen;}
    }
    for(auto component : this -> components) {
        if(component.traceEnable) {
            std::cout << component.id << std::string(maxlen - component.id.length(), ' ') << " => " << component.trace << std::endl;
        }
    }
}


void Circuit::simulate(unsigned int cycles) {
    for (size_t i = 0; i < cycles; i++) {
        Circuit::calculateState(i);
    }
    Circuit::printTrace();
}
