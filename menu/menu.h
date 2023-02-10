#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

class Menu
{
private:
    /**
     * @brief length (tabs) 
     * 
     */
    unsigned int length;
    /**
     * @brief Character used to build walls
     * 
     */
    char wallChar = '|';
    /**
     * @brief Character used to build continous lines dividing the lines
     * 
     */
    char breakChar = '=';

public:
    /**
     * @brief Construct a new Menu object
     * 
     * @param length 
     */
    Menu(unsigned int length);

    /**
     * @brief Construct a new Menu object
     * 
     * @param length new length
     * @param wallChar set wall character
     * @param breakChar set break character
     */
    Menu(unsigned int length, char wallChar, char breakChar);

    /**
     * @brief Line filled with breakChar
     * 
     */
    void break_line();

    /**
     * @brief Text placed to the left
     * 
     * @param sentance Text to be placed
     */
    void text_line_left(std::string sentance);

    /**
     * @brief Text centered
     * 
     * @param sentance Text to be placed
     */
    void text_line_cnetered(std::string sentance);

    /**
     * @brief Text placed from the right
     * 
     * @param sentance Text to be placed
     */
    void text_line_right(std::string sentance);
    
    /**
     * @brief "Empty line". Just two walls on either side
     * 
     */
    void empty_line();

    /**
     * @brief Set the Wall Char object
     * 
     * @param wallChar 
     */
    void setWallChar(char wallChar);

    /**
     * @brief Set the Length object
     * 
     * @param newLength 
     */
    void setLength(unsigned int newLength);

    /**
     * @brief Set the Break Char object
     * 
     * @param breakChar 
     */
    void setBreakChar(char breakChar);
};

#endif