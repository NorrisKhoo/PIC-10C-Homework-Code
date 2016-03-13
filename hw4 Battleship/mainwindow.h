/** @file mainwindow.h
 *  @brief This file contains the default declarations for the MainWindow class
 *
 *  Default behavior declares functionality for app definitions stored in mainwindow.cpp
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/** @class MainWindow
 *  @brief The MainWindow class creates and manages the app's GUI
 *
 *  The MainWindow class serves as the parent for all additional GUI material. Derived class
 *  content (widgets such as QPushButton) are automatically deleted at end of program. In this app,
 *  Mainwindow functionality has been expanded to create a GUI representation for a Battleship port.
 *  Class will be further expanded to tentatively call constructors for the gameboard class, take
 *  user input and run paintEvent functions
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
