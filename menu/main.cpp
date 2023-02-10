#include "menu.h"

int main(int, char**) {
    Menu menu(6);
    menu.break_line();
    menu.empty_line();
    menu.text_line_cnetered("---=== MAIN MENU ===---");
    menu.empty_line();
    menu.break_line();
    menu.text_line_cnetered("Chose option: ");
    menu.text_line_left("1. Start");
    menu.text_line_left("2. Quit");
    menu.break_line();
}
    