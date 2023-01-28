#include "menu.h"

Menu::Menu(unsigned int length){
    this->length = length;
}

Menu::Menu(unsigned int length, char wallChar, char breakChar) {
    this->length = length;
    this->wallChar = wallChar;
    this->breakChar = breakChar;
}


void Menu::break_line() {
    std::cout << "\t|";
    for(int i = 0; i < this->length*8 - 1; i++) {
        std::cout  << this->breakChar;
    }
    std::cout << "|\t\n";
}

void Menu::empty_line() {
    std::cout << "\t|";
    for(int i = 0; i < this->length; i++) {
        std::cout  << "\t";
    }
    std::cout << "|\t\n";
}

void Menu::text_line_left(std::string sentance) {
    std::cout << "\t|\t" << sentance;
    for(int i = 0; i < this->length - 2 - sentance.length()/8; i++) { std::cout << '\t'; }
    std::cout << "\t|\t" << std::endl;
}

void Menu::text_line_cnetered(std::string sentance) {
    std::cout << "\t|\t";
        for(int i = 0; i < (this->length*3 - sentance.length()/2); i++) { std::cout << ' '; }
        std::cout << sentance;
        for(int i = 0; i < (this->length*3 - sentance.length()/2); i++) { std::cout << ' '; }
    std::cout << "\t|\t" << std::endl;
}

void Menu::text_line_right(std::string sentance) {
    std::string temp = "\t|\t";
    std::cout << "\t|\t";
    for(int i = 0; i < (this->length - 2 - sentance.length()/8)*8; i++) { temp += ' '; }
    temp += sentance;
    std::cout << "\t|\t" << std::endl;
}

void Menu::setLength(unsigned int length) {
    this->length = length;
}

void Menu::setBreakChar(char breakChar) {
    this->breakChar = breakChar;
}

void Menu::setWallChar(char wallChar) {
    this->wallChar = wallChar;
}