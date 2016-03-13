/** @mainpage PIC 10C Homework 5 Implementing Game Logic
    @title PIC 10C Homework 5 Implementing Game Logic
    @author Norris Khoo 004-420-262
    @date 02-05-2016

    The goal of this assignment is to implement logic for my game (Battleship) so that it is playable. The current code provides a fully
    working version of the game that creates a board, allows setting of player/opponent ships and runs player/opponent turns with a
    competent AI. Checks are made at each step of the game process to ensure that operations are valid. Movement is tracked with a black
    border controlled by the arrow keys and space (functionality provided with custom paintEvent, update location and keyPressEvent functions).
    Overall, the board consisting of titles, instructions, start/quit buttons, ship settings and two 10x10 grids is created on the
    MainWindow as the default class has been expanded. Have fun playing!
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
