/** @file mainwindow.h
 *  @brief This file contains the declarations for the MainWindow class which has been expanded to provide an interface from
 *  which the player can start the Battleship game
 *
 *  The MainWindow class has been updated to display prompts for starting the Battleship game or viewing its instructions. The
 *  song Plastic Pop has been implemented as background music for the entirety of the app (including during gameplay)
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboardsingleplayer.h"
#include "gameboardmovement.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * The MainWindow class utilizes QLabel and QPushButton objects organized in a QVBoxLayout to create prompts for the user to play
 * Battleship or read its instructions. Clicking on instructions prompts a window to pop up with a list of QLabel indicating the
 * game's rules. The song Plastic Pop has been included through a QMediaPlayer object and plays on a loop using QPlaylist
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void classic_game_single_player_begin();
    void show_instructions();

private:
    Ui::MainWindow *ui;

    GameboardSinglePlayer* board_single_player;
    GameboardMovement* board_movement;

    QWidget* main;
    QWidget* instructions_popup;

    QLabel* title;
    QLabel* player;
    QLabel* instructions_line1;
    QLabel* instructions_line2;
    QLabel* instructions_line3;
    QLabel* instructions_line4;
    QLabel* instructions_line5;
    QLabel* instructions_line6;
    QLabel* instructions_line7;
    QLabel* instructions_line8;
    QLabel* instructions_line9;
    QLabel* instructions_line10;

    QVBoxLayout* main_layout;
    QVBoxLayout* instructions_layout;

    QPushButton* classic_start_single_player;
    QPushButton* instructions;

    //utilized to play song
    QMediaPlayer* song;
    QMediaPlaylist* playlist;
};

#endif // MAINWINDOW_H
