/** @mainpage PIC 10C Homework 4 Designing a Game/Creating its GUI
    @title PIC 10C Homework 4 Designing a Game/Creating its GUI
    @author Norris Khoo
    @date 01-29-2016

    This assignment is intended to have students create the core concepts and visual look of their game. I decided to
    create a single player Qt port of the board game Battleship. The GUI consists of two boards (created by 100 QLabel
    in a grid layout) that represent the player's and their opponent's field. An assortment of QLabel and QCheckBox to
    the left shows players which ships they must add to their board. There are additional QPushButton objects to
    start and quit the game. Further detail into the GUI and logic of my port can be found in the ProjectDescription pdf.

    Regarding the code, I intended to create a class gameboard that will create the two fields, track player movement
    and dictate logic. Unfortunately, I was unsure how to create a GUI through this method so app has currently been
    made through ui interface. I will update app once I learn how to create my class better
*/

/** @file main.cpp
  * @brief This file contains the default code for Qt projects

  * For creating the GUI, programming was done through the ui. Implementation of logic may require expansion of existing
  * main.cpp
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
