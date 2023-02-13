class CreateGate
{
public:
    CreateGate();
    std::vector<Gate> connect(std::vector<Gate> a, std::vector<Gate> b);
    std::vector<Gate> clk_stab(std::string name, std::string clock_input);
    std::vector<Gate> sr_flipFlop(std::string name, std::string set_input, std::string reset_input);
    std::vector<Gate> d_flipFlop(std::string name, std::string D_input, std::string clock_input);
    std::vector<Gate> d_flipFlop_time(std::string name, std::string D_input, std::string clock_input);
    std::vector<Gate> counter_4b(std::string name, std::string clock_input);
    std::vector<Gate> counter_ib(int i, std::string name, std::string clock_input);
};

CreateGate::CreateGate() {}

std::vector<Gate> CreateGate::connect(std::vector<Gate> a, std::vector<Gate> b) {
    std::vector<Gate> rez;
    for(auto it : b) {
        a.push_back(it);
    }
    return a;
}

std::vector<Gate> CreateGate::sr_flipFlop(std::string name, std::string set_input, std::string reset_input) {
    std::vector<Gate> rez;
    rez.push_back(Gate(name+".Q", "nor", {reset_input, name+".~Q"}, false, "trace"));
    rez.push_back(Gate(name+".~Q", "nor", {set_input, name+".Q"}, true, "trace"));
    return rez;
}

std::vector<Gate> CreateGate::d_flipFlop(std::string name, std::string D_input, std::string clock_input) {
    std::vector<Gate> rez;
    rez.push_back(Gate(name+".~D", "not", {D_input}, false));
    rez.push_back(Gate(name+".DC_AND", "and", {D_input, clock_input}, false));
    rez.push_back(Gate(name+".~DC_AND", "and", {name+".~D", clock_input}, false));
    rez.push_back(Gate(name+".Q", "nor", {name+".~DC_AND", name+".~Q"}, false, "trace"));
    rez.push_back(Gate(name+".~Q", "nor", {name+".DC_AND", name+".Q"}, true));
    return rez;
}

std::vector<Gate> CreateGate::d_flipFlop_time(std::string name, std::string D_input, std::string clock_input) {
    std::vector<Gate> rez;
    rez = connect(rez, clk_stab(name+".timer", clock_input));
    rez = connect(rez, d_flipFlop(name, D_input, name+".timer.out"));
    return rez;
}


std::vector<Gate> CreateGate::clk_stab(std::string name, std::string clock_input) {
    std::vector<Gate> rez;
    rez.push_back(Gate(name+".out", "xor", {clock_input, name+".Q"}, false));
    rez.push_back(Gate(name+".~D", "not", {clock_input}, false));
    rez.push_back(Gate(name+".DC_AND", "and", {clock_input, name+".out"}, false));
    rez.push_back(Gate(name+".~DC_AND", "and", {name+".~D", name+".out"}, false));
    rez.push_back(Gate(name+".Q", "nor", {name+".~DC_AND", name+".~Q"}, false));
    rez.push_back(Gate(name+".~Q", "nor", {name+".DC_AND", name+".Q"}, true));
    return rez;
}
    
std::vector<Gate> CreateGate::counter_4b(std::string name, std::string clock_input) {
    std::vector<Gate> rez;
    rez.push_back(Gate(name+"0.xor", "xor", {name+"0.Q", name+"1.Q"}, false));
    rez.push_back(Gate(name+"0.and", "and", {name+"0.Q", name+"1.Q"}, false));
    rez.push_back(Gate(name+"1.xor", "xor", {name+"0.and", name+"2.Q"}, false));
    rez.push_back(Gate(name+"1.and", "and", {name+"0.and", name+"2.Q"}, false));
    rez.push_back(Gate(name+"2.xor", "xor", {name+"1.and", name+"3.Q"}, false));


    rez = connect(rez, d_flipFlop_time(name+"0", name+"0.~Q", clock_input));
    rez = connect(rez, d_flipFlop_time(name+"1", name+"0.xor", clock_input));
    rez = connect(rez, d_flipFlop_time(name+"2", name+"1.xor", clock_input));
    rez = connect(rez, d_flipFlop_time(name+"3", name+"2.xor", clock_input));
    return rez;
}

std::vector<Gate> CreateGate::counter_ib(int count, std::string name, std::string clock_input) {
    std::vector<Gate> rez;
    rez.push_back(Gate(name+"0.xor", "xor", {name+"0.Q", name+"1.Q"}, false));
    rez.push_back(Gate(name+"0.and", "and", {name+"0.Q", name+"1.Q"}, false));
    for(int i = 0; i < count-2; i++) {
        rez.push_back(Gate(name + std::to_string(i+1) + ".xor", "xor", {name + std::to_string(i) +".and", name + std::to_string(i+2) +".Q"}, false));
        rez.push_back(Gate(name + std::to_string(i+1) + ".and", "and", {name + std::to_string(i) +".and", name + std::to_string(i+2) +".Q"}, false));
    }
    rez = connect(rez, d_flipFlop_time(name+"0", name+"0.~Q", clock_input));
    for(int i = 0; i < count-1; i++) {
        rez = connect(rez, d_flipFlop_time(name+std::to_string(i+1), name+std::to_string(i)+".xor", clock_input));
    }
    return rez;
}