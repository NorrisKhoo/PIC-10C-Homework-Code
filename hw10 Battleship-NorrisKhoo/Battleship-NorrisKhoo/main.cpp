/** @mainpage PIC 10C Homework 10 Complete game
    @title PIC 10C Homework 10 Complete game
    @author Norris Khoo
    @date 03-11-2016

    The goal of this assignment is to submit the final playable version of my game (Battleship). The current code provides a fully
    working version of the game that creates a board, allows setting of player/opponent ships and runs player/opponent turns with a
    competent AI. Checks are made at each step of the game process to ensure that operations are valid. Movement is tracked with a black
    border controlled by the arrow keys and space (functionality provided with custom paintEvent, update location and keyPressEvent functions).
    Overall, the board consisting of titles, instructions, start/quit buttons, ship settings and two 10x10 grids is created on the
    GameboardSinglePlayer class. The MainWindow class has been expanded to create a starting menu prompting the user to start the game
    (which then sets central widget as the board) or read its instructions. The song Plastic Pop has been implemented as background music.
    Have fun playing!
*/

/** @file main.cpp
  * @brief This file contains the default code for Qt projects
  *
  * Prints the MainWindow to the screen
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
