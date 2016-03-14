#ifndef GAMEBOARDMOVEMENT_H
#define GAMEBOARDMOVEMENT_H

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
class GameboardMovement;
}

class GameboardMovement : public QWidget
{
    Q_OBJECT

public:
    explicit GameboardMovement(QWidget *parent = 0);
    ~GameboardMovement();

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

    void increment_ship(std::vector<QPoint*>& ship, std::vector< std::vector<int> >& owner_type, int& direction);
    void set_direction(std::vector<QPoint*>& ship, int& direction);
    void update_board();
    void update_ship(std::vector<QPoint*>& ship, std::vector<bool>& ship_hit, std::vector< std::vector<QLabel*> >& owner, std::vector< std::vector<int> >& owner_type);
    void update_ship_opponent_board(std::vector<QPoint*>& ship, std::vector<bool>& ship_hit, std::vector< std::vector<QLabel*> >& owner, std::vector< std::vector<int> >& owner_type);

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
    Ui::GameboardMovement *ui;

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

    //0 if not hit 1 if hit
    std::vector<bool> aircraft_carrier_player_hit;
    std::vector<bool> aircraft_carrier_opponent_hit;
    std::vector<bool> battleship_player_hit;
    std::vector<bool> battleship_opponent_hit;
    std::vector<bool> submarine_player_hit;
    std::vector<bool> submarine_opponent_hit;
    std::vector<bool> cruiser_player_hit;
    std::vector<bool> cruiser_opponent_hit;
    std::vector<bool> destroyer_player_hit;
    std::vector<bool> destroyer_opponent_hit;

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

    //0 for left
    //1 for right
    //2 for down
    //3 for up
    int direction_movement_aircraft_carrier;
    int direction_movement_battleship;
    int direction_movement_submarine;
    int direction_movement_cruiser;
    int direction_movement_destroyer;

    int direction_movement_aircraft_carrier_opponent;
    int direction_movement_battleship_opponent;
    int direction_movement_submarine_opponent;
    int direction_movement_cruiser_opponent;
    int direction_movement_destroyer_opponent;


};

#endif // GAMEBOARDMOVEMENT_H
