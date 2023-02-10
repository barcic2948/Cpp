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
private:
    /* data */
public:
    std::string id;
    std::string type;
    std::vector<std::string> inputs;
    bool state;

    Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state);
    ~Gate();
};

Gate::Gate(std::string id, std::string type, std::vector<std::string> inputs, bool state) :
    id(id), type(type), inputs(inputs), state(state) {};

Gate::~Gate()
{
}

const auto indexBy = [](std::vector<Gate> components, std::string id) -> Gate {
    for(auto it : components) {
        if(it.id == id) {
            return it;
        }
    }
};

std::vector<Gate> components {
    Gate("Huj", "huj", {"ww", "ww"}, false),
    Gate("Huj2", "huj", {"ww", "ww"}, false),
    Gate("Huj3", "huj", {"ww", "ww"}, false)
};

const auto componentLookup = indexBy(components , "id");






