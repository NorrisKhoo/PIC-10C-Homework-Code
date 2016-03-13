/** @mainpage PIC 10C Homework 3 Particles on a Board
    @title PIC 10C Homework 3 Particles on a Board
    @author Norris Khoo
    @date 01-22-2016

    This assignment is intended to provide students with the opportunity to begin creating GUIs using Qt. Expanding
    upon the base requirements, I created a WWE themed program that will display pictures of wrestling superstars
    and their names. Further changes include the use of pictures through QPixmap, the increase in number of particles
    to 30 (inspired by the 30 entrants to the Royal Rumble) and cosmetic differences. The program utilizes connect to
    link two slider widgets together. The bulk of the programming was done with the ui designer and images are stored
    in a resource folder specific to this project
*/

/** @file main.cpp
    @brief This file contains the default main for Qt projects. Programming was done primarily through the ui
*/

#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
