/** @file gameboardsingleplayer.h
 *  @brief This file contains the declarations for the GameboardSinglePlayer class which creates a playable version of the
 *  boardgame Battleship in a QWidget object
 *
 *  The functions required to create the Battleship game are all included within the GameboardSinglePlayer class. Overall creates
 *  a playable single player version of Battleship with competent AI and checks that the game is being played correctly
*/

#ifndef GAMEBOARDSINGLEPLAYER_H
#define GAMEBOARDSINGLEPLAYER_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QPoint>
#include <QKeyEvent>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>
#include"pointcompare.h"

namespace Ui {
class GameboardSinglePlayer;
}

/**
 * @brief The GameboardSinglePlayer class
 *  The GameboardSinglePlayer class creates a QWidget with titles, instructions, start/quit buttons, ship settings and two 10x10 grids
 *  representing the player and opponent. The appearance of the main screen has been acheived by use of horizontal, vertical and grid
 *  box layouts. Vectors of vectors are utilized to store the QLabel/int types creating the grid which correspondingly
 *  allow the use of QPoint objects to store player and opponent coordinates. After board has been set, an AI operates which first
 *  guesses randomly then makes educated choices upon hits in order to provide the player a challenge. Moving through the board is done
 *  by the arrow keys and space through a pressKeyEvent function. A custom paintEvent function has been implemented allowing updates to
 *  the board to be shown. The GameboardSinglePlayer class inherits from QWidget
 */
class GameboardSinglePlayer: public QWidget
{
    Q_OBJECT

public:
    explicit GameboardSinglePlayer(QWidget* parent = 0);
    ~GameboardSinglePlayer();

    void updateLocation(int px, int py, int nx, int ny, std::vector<std::vector<QLabel*>>& grid, std::vector<std::vector<int>>& grid_type);
    void set_location();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

    bool isValid_aircraft_carrier();
    bool isValid_battleship();
    bool isValid_submarine();
    bool isValid_cruiser();
    bool isValid_destroyer();

    bool set_opponent_aircraft_carrier();
    bool set_opponent_battleship();
    bool set_opponent_submarine();
    bool set_opponent_cruiser();
    bool set_opponent_destroyer();

    void set_opponent_board();
    void clear_opponent_board();

    void guess_location();

    void opponent_turn();
    bool opponent_guess_up();
    bool opponent_guess_down();
    bool opponent_guess_left();
    bool opponent_guess_right();

    QLabel* create_gray_box();
    QLabel* create_white_box();

    void victor();

public slots:
    void set_aircraft_carrier();
    void set_battleship();
    void set_submarine();
    void set_cruiser();
    void set_destroyer();

    void start_game();
    void end_game();

private:
    Ui::GameboardSinglePlayer* ui;

    //labels to help user
    QLabel* title;
    QLabel* blank;
    QLabel* instructions;
    QLabel* instructions_line2;
    QLabel* player_label;
    QLabel* opponent_label;
    QLabel* error_message;
    QLabel* victory;

    //start and quit buttons
    QPushButton* begin;
    QPushButton* quit;

    //layouts to create the appearance of the GUI
    QVBoxLayout* main_layout;

    QHBoxLayout* top_row;
    QHBoxLayout* bottom_row;

    QHBoxLayout* aircraft_carrier;
    QHBoxLayout* battleship;
    QHBoxLayout* submarine;
    QHBoxLayout* cruiser;
    QHBoxLayout* destroyer;

    QCheckBox* aircraft_carrier_check;
    QCheckBox* battleship_check;
    QCheckBox* submarine_check;
    QCheckBox* cruiser_check;
    QCheckBox* destroyer_check;

    QVBoxLayout* bottom_left;
    QVBoxLayout* bottom_middle;
    QVBoxLayout* bottom_right;

    QGridLayout* player_grid;
    QGridLayout* opponent_grid;

    //vector of vectors store format of QLabel to be show in grid
    std::vector< std::vector<QLabel*> > player;
    std::vector< std::vector<QLabel*> > opponent;

    //vector of vectors denote what type of QLabel to set to
    std::vector< std::vector<int> > player_type;
    std::vector< std::vector<int> > opponent_type;

    QPoint* location;

    //vectors store locations of ships
    std::vector<QPoint*> aircraft_carrier_player_pos;
    std::vector<QPoint*> battleship_player_pos;
    std::vector<QPoint*> submarine_player_pos;
    std::vector<QPoint*> cruiser_player_pos;
    std::vector<QPoint*> destroyer_player_pos;

    std::vector<QPoint*> aircraft_carrier_opponent_pos;
    std::vector<QPoint*> battleship_opponent_pos;
    std::vector<QPoint*> submarine_opponent_pos;
    std::vector<QPoint*> cruiser_opponent_pos;
    std::vector<QPoint*> destroyer_opponent_pos;

    //tells if on player's or opponent's board
    int mode;

    //sets what type of Key_Space
    int space_type;

    //set number of registered hits
    int player_hits;
    int opponent_hits;

    //location of opponent and a backup container
    QPoint* opponent_location;
    QPoint* opponent_location_storage;

    //determines whether to reset opponent location storage
    bool reset;
};

#endif // GAMEBOARDSINGLEPLAYER_H
