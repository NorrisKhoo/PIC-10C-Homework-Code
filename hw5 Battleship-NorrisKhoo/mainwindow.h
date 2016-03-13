/** @file mainwindow.h
 *  @brief This file contains the declarations for the MainWindow class with expanded functionality to create a playable version
 *  of the game Battleship
 *
 *  The functions required to create the Battleship game are all included within the MainWindow class. Overall creates a playable
 *  single player version of Battleship with competent AI and checks that the game is being played correctly
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <vector>
#include <QPoint>
#include <QKeyEvent>
#include <algorithm>
#include <random>
#include <time.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 *  The default MainWindow class has been expanded to create a window with titles, instructions, start/quit buttons, ship settings
 *  and two 10x10 grids representing the player and opponent. The appearance of the main screen has been acheived by use of horizontal,
 *  vertical and grid box layouts.Vectors of vectors are utilized to store the QLabel/int types creating the grid which correspondingly
 *  allow the use of QPoint objects to store player and opponent coordinates. After board has been set, an AI operates which first
 *  guesses randomly then makes educated choices upon hits in order to provide the player a challenge. Moving through the board is done
 *  by the arrow keys and space through a pressKeyEvent function. A custom paintEvent function has been implemented allowing updates to
 *  the board to be shown. The MainWindow class inherits from QMainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;

    QWidget* main;

    //labels to help user
    QLabel* title;
    QLabel* blank;
    QLabel* instructions;
    QLabel* instructions_line2;
    QLabel* player_label;
    QLabel* opponent_label;
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

    //running int value that is incremented so seed values are different
    int seed_change;
};

#endif // MAINWINDOW_H
