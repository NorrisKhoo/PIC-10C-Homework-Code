/** @file gameboard.h
 *  @brief This file contains broad plans for my future gameboard class
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QWidget>
#include <vector>
#include <QLabel>

namespace Ui{
class gameboard;
}


/** @class gameboard
 *  @brief The gameboard class will create and manage the gameboards for Battleship
 *
 *  For my Battleship game, I plan to use the gameboard class to create the game's GUI and dictate its logic.
 *  Currently, the class is empty because I was unable to figure out how to create the grids of QLabel necessary
 *  for my GUI (hence programming done through the ui). I overall plan to hold the QLabel in a vector storing
 *  them in row major format. To implement the GUI and logic, this class will be expanded greatly
 */
class gameboard
{
public:
    gameboard();
    ~gameboard();
private:
    Ui::gameboard* ui;
    QWidget* board;
    std::vector<QLabel*> labels;
};

#endif // GAMEBOARD_H
