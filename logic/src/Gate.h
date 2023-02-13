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

    bool visited = false;
    bool repeat = true;

    std::string trace;
    bool traceEnable = false;

    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state) :
    id(id), type(type), inputs(inputs), state(state) {};
  
    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state, std::string traceEnable) :
    id(id), type(type), inputs(inputs), state(state), traceEnable(traceEnable == "trace" ? true : false) {};


    void traceUpdate() {this->trace += this->state ? '+' : '-';}
    void printGate() {
        std::cout << "ID: " << id << " Type: " << type << " Inputs: [" << inputs[0] << (inputs.size() > 1 ? ", " + inputs[1] : "") << "] State:" << state << " Visited: " << visited << " Repeat: " << repeat << std::endl;
    }
};