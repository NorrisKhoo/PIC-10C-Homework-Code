/** @file mainwindow.cpp
  * @brief This file contains code for implementing the MainWindow class

  * For now, code consists of default material. Creating the GUI was done through the ui interface. Implementation
  * of game logic will require expansion of the mainwindow class and gameboard class
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Constructor for MainWindow class that creates the GUI. For now, constructor consists of default material as GUI was
 * created entirely through ui interface. GUI consists of two grids of QLabel (representing boards), QCheckBox to
 * ensure ships are placed correctly and QPushButton for start/quit functions
 * @param parent is the parent widget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * @brief MainWindow::~MainWindow
 * Default destructor. No calls to new made in my code
 */
MainWindow::~MainWindow()
{
    delete ui;
}
