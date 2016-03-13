/** @file mainwindow.cpp
  * @brief This file contains the definitions for the MainWindow class
  *
  * The functions defined in the MainWindow class overall create an interface for the player to navigate before he/she
  * starts the game. The song Plastic Pop is implemented as background music
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboardsingleplayer.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent is the parent widget
 * Default constructor for the MainWindow class has been expanded through the inclusion of QLabel and QPushButton objects
 * in a QVBoxLayout to create a starting menu. The start QPushButton switches the MainWindow central widget to the widget
 * created by GameboardSinglePlayer and the instructions QPushButton prompts a popup widget dictating how to play. A QMediaPlayer
 * object has been set to the song Plastic Pop and plays on a continuous loop through QMediaPlaylist
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    main = new QWidget;
    main_layout = new QVBoxLayout;

    //Sets home window title
    title = new QLabel("Let's Play Battleship!");
    title->setStyleSheet("font: bold 28pt");
    main_layout->addWidget(title);

    //Sets song to play throughout duration of app
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/new/media/PlasticPop.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    song = new QMediaPlayer;
    song->setPlaylist(playlist);
    song->play();

    //Sets home window start button
    classic_start_single_player = new QPushButton("Single Player");
    classic_start_single_player->setStyleSheet("font: 16pt");
    QObject::connect(classic_start_single_player, SIGNAL(clicked(bool)), this, SLOT(classic_game_single_player_begin()));
    main_layout->addWidget(classic_start_single_player);

    //Sets home window instructions button
    instructions = new QPushButton("How to play");
    instructions->setStyleSheet("font: 16pt");
    QObject::connect(instructions, SIGNAL(clicked(bool)), this, SLOT(show_instructions()));
    main_layout->addWidget(instructions);

    main->setLayout(main_layout);
    this->setCentralWidget(main);

    //Creates popup window of QLabel objects arranged in QVBoxLayout with rules
    instructions_line1 = new QLabel("Each player is given five ships to place on their respective boards.");
    instructions_line1->setStyleSheet("font: 14pt");
    instructions_line2 = new QLabel("The ships may only be placed in a horizontal or vertical orientation");
    instructions_line2->setStyleSheet("font: 14pt");
    instructions_line3 = new QLabel("and opposing players do not know their locations. Once the ships have");
    instructions_line3->setStyleSheet("font: 14pt");
    instructions_line4 = new QLabel("been placed in valid locations, each player takes turns guessing one");
    instructions_line4->setStyleSheet("font: 14pt");
    instructions_line5 = new QLabel("position on the opponent's grid at a time. If there is a ship, they register a");
    instructions_line5->setStyleSheet("font: 14pt");
    instructions_line6 = new QLabel("hit and if there is not, they register a miss. The players alternate");
    instructions_line6->setStyleSheet("font: 14pt");
    instructions_line7 = new QLabel("until all the positions occupied by the opponent ships have been hit thus");
    instructions_line7->setStyleSheet("font: 14pt");
    instructions_line8 = new QLabel("giving the first player to achieve this the victory");
    instructions_line8->setStyleSheet("font: 14pt");
    instructions_line9 = new QLabel();
    instructions_line10 = new QLabel("This version of battleship is played against a computer AI.");
    instructions_line10->setStyleSheet("font: 14pt");

    instructions_layout = new QVBoxLayout;
    instructions_layout->addWidget(instructions_line1);
    instructions_layout->addWidget(instructions_line2);
    instructions_layout->addWidget(instructions_line3);
    instructions_layout->addWidget(instructions_line4);
    instructions_layout->addWidget(instructions_line5);
    instructions_layout->addWidget(instructions_line6);
    instructions_layout->addWidget(instructions_line7);
    instructions_layout->addWidget(instructions_line8);
    instructions_layout->addWidget(instructions_line9);
    instructions_layout->addWidget(instructions_line10);

    instructions_popup = new QWidget;
    instructions_popup->setLayout(instructions_layout);
}

/**
 * @brief MainWindow::classic_game_single_player_begin
 * This public slots function creates a new GameboardSinglePlayer board and sets the widget as the MainWindow
 * central widget
 */
void MainWindow::classic_game_single_player_begin(){
    board_single_player = new GameboardSinglePlayer(this);
    this->setCentralWidget(board_single_player);
}

/**
 * @brief MainWindow::show_instructions
 * This public slots function calls show on the instructions popup widget created in the MainWindow constructor
 */
void MainWindow::show_instructions(){
    instructions_popup->show();
}

/**
 * @brief MainWindow::~MainWindow
 * Default destructor for the MainWindow class. Qt objects automatically deal with memory management
 */
MainWindow::~MainWindow(){
    delete ui;
}
