#include "Gate.h" 

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
    void calculateState1(int cycle);

    public:
        Circuit(std::vector<Gate> components) : components(components) {};
        
        void addToCircuit(std::vector<Gate> circ);

        void simulate(unsigned int cycles);
        
        void printTrace();

        void printComps();
};

void Circuit::addToCircuit(std::vector<Gate> circ) {
    for(auto component : circ) {
        this->components.push_back(component);
    }
}

void Circuit::calculateState(int cycle) {
    bool condition = true;
    while(condition) {
        for(auto &component : this-> components) {
            if(component.repeat) {
                if (component.type == "controled") { component.visited = true; component.repeat = false; }
                else if (component.type == "custom") {
                    component.visited = true; component.repeat = false;
                    component.state = cycle <= component.inputs[0].length() - 1 ? int(component.inputs[0][cycle]) - 48 : false;
                }
                else if (component.type == "clock") {
                    component.visited = true; component.repeat = false;
                    component.state = cycle ? ((cycle + stoi(component.inputs[0])) % (stoi(component.inputs[1])) ? component.state : !component.state) : component.state;
                }
                else if (component.type == "not") {
                    component.visited = true;
                    component.repeat = !Circuit::indexBy(component.inputs[0]).visited;
                    component.state = Circuit::NOT(Circuit::indexBy(component.inputs[0]).state);
                }
                else {
                    component.visited = true;
                    component.repeat = !Circuit::indexBy(component.inputs[0]).visited;
                    component.repeat = !Circuit::indexBy(component.inputs[1]).visited;
                    
                    bool input_1 = indexBy(component.inputs[0]).state;
                    bool input_2 = indexBy(component.inputs[1]).state;
                    
                    if(component.type == "and") {component.state = AND(input_1, input_2);}
                    else if(component.type == "nand") {component.state = NAND(input_1, input_2);}
                    else if(component.type == "or") {component.state = OR(input_1, input_2);}
                    else if(component.type == "nor") {component.state = NOR(input_1, input_2);}
                    else if(component.type == "xor") {component.state = XOR(input_1, input_2);}
                    else {}
                }
            }
        }
        for(auto component : this-> components) {condition = false; if(component.repeat) {condition = true; break;}}
    }
    for(auto &component : this-> components) {
        if(component.traceEnable) {component.traceUpdate();}
        component.visited = false; component.repeat = true;
    }
}

void Circuit::simulate(unsigned int cycles) {
    for (size_t i = 0; i < cycles; i++) {
        Circuit::calculateState(i);
    }
    Circuit::printTrace();
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

void Circuit::printComps() {
    for (auto it : components) {
        it.printGate();
    }
}
