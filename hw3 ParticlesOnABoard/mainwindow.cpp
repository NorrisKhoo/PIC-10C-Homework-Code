/** @file mainwindow.cpp
    @brief This file contains code for implementing the MainWindow class

    In addition to default material, this code links QPixmap objects to labels within the ui. The objects open images
    stored in resources and then set labels to scaled versions of the pictures.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>

/**
 * @brief MainWindow::MainWindow
 * Constructor for MainWindow class that creates the GUI. QPixmap objects are initialized with location in resources.
 * QLabel objects are then set to point to QPixmap objects allowing them to be displayed on GUI
 * @param parent is the parent widget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialize QPixmap object
    QPixmap Batista(":/new/images/Wrestlers/Batista.jpg");
    //formats QPixmap object to fit within QLabel
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //assigns QPixmap object to QLabel
    ui->label->setPixmap(Batista);

    QPixmap BigE(":/new/images/Wrestlers/BigE.jpg");
    ui->label_2->setScaledContents( true );
    ui->label_2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_2->setPixmap(BigE);

    QPixmap BrayWyatt(":/new/images/Wrestlers/BrayWyatt.jpg");
    ui->label_3->setScaledContents( true );
    ui->label_3->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_3->setPixmap(BrayWyatt);

    QPixmap BretHart(":/new/images/Wrestlers/BretHart.jpg");
    ui->label_4->setScaledContents( true );
    ui->label_4->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_4->setPixmap(BretHart);

    QPixmap BrockLesnar(":/new/images/Wrestlers/BrockLesnar.jpg");
    ui->label_5->setScaledContents( true );
    ui->label_5->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_5->setPixmap(BrockLesnar);

    QPixmap Cesaro(":/new/images/Wrestlers/Cesaro.jpg");
    ui->label_6->setScaledContents( true );
    ui->label_6->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_6->setPixmap(Cesaro);

    QPixmap ChrisJericho(":/new/images/Wrestlers/ChrisJericho.jpg");
    ui->label_7->setScaledContents( true );
    ui->label_7->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_7->setPixmap(ChrisJericho);

    QPixmap Christian(":/new/images/Wrestlers/Christian.jpg");
    ui->label_8->setScaledContents( true );
    ui->label_8->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_8->setPixmap(Christian);

    QPixmap CMPunk(":/new/images/Wrestlers/CMPunk.jpg");
    ui->label_9->setScaledContents( true );
    ui->label_9->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_9->setPixmap(CMPunk);

    QPixmap DanielBryan(":/new/images/Wrestlers/DanielBryan.jpg");
    ui->label_10->setScaledContents( true );
    ui->label_10->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_10->setPixmap(DanielBryan);

    QPixmap DeanAmbrose(":/new/images/Wrestlers/DeanAmbrose.jpg");
    ui->label_11->setScaledContents( true );
    ui->label_11->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_11->setPixmap(DeanAmbrose);

    QPixmap DolphZiggler(":/new/images/Wrestlers/DolphZiggler.jpg");
    ui->label_12->setScaledContents( true );
    ui->label_12->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_12->setPixmap(DolphZiggler);

    QPixmap Edge(":/new/images/Wrestlers/Edge.jpg");
    ui->label_13->setScaledContents( true );
    ui->label_13->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_13->setPixmap(Edge);

    QPixmap Goldust(":/new/images/Wrestlers/Goldust.jpg");
    ui->label_14->setScaledContents( true );
    ui->label_14->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_14->setPixmap(Goldust);

    QPixmap JeffHardy(":/new/images/Wrestlers/JeffHardy.jpg");
    ui->label_15->setScaledContents( true );
    ui->label_15->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_15->setPixmap(JeffHardy);

    QPixmap JohnCena(":/new/images/Wrestlers/JohnCena.jpg");
    ui->label_16->setScaledContents( true );
    ui->label_16->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_16->setPixmap(JohnCena);

    QPixmap Kane(":/new/images/Wrestlers/Kane.jpg");
    ui->label_17->setScaledContents( true );
    ui->label_17->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_17->setPixmap(Kane);

    QPixmap KurtAngle(":/new/images/Wrestlers/KurtAngle.jpg");
    ui->label_18->setScaledContents( true );
    ui->label_18->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_18->setPixmap(KurtAngle);

    QPixmap RandyOrton(":/new/images/Wrestlers/RandyOrton.jpg");
    ui->label_19->setScaledContents( true );
    ui->label_19->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_19->setPixmap(RandyOrton);

    QPixmap ReyMysterio(":/new/images/Wrestlers/ReyMysterio.jpg");
    ui->label_20->setScaledContents( true );
    ui->label_20->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_20->setPixmap(ReyMysterio);

    QPixmap Rusev(":/new/images/Wrestlers/Rusev.jpg");
    ui->label_21->setScaledContents( true );
    ui->label_21->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_21->setPixmap(Rusev);

    QPixmap RVD(":/new/images/Wrestlers/RVD.jpg");
    ui->label_22->setScaledContents( true );
    ui->label_22->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_22->setPixmap(RVD);

    QPixmap SethRollins(":/new/images/Wrestlers/SethRollins.jpg");
    ui->label_23->setScaledContents( true );
    ui->label_23->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_23->setPixmap(SethRollins);

    QPixmap ShawnMichaels(":/new/images/Wrestlers/ShawnMichaels.jpg");
    ui->label_24->setScaledContents( true );
    ui->label_24->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_24->setPixmap(ShawnMichaels);

    QPixmap Sheamus(":/new/images/Wrestlers/Sheamus.jpg");
    ui->label_25->setScaledContents( true );
    ui->label_25->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_25->setPixmap(Sheamus);

    QPixmap SteveAustin(":/new/images/Wrestlers/SteveAustin.jpg");
    ui->label_26->setScaledContents( true );
    ui->label_26->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_26->setPixmap(SteveAustin);

    QPixmap TheRock(":/new/images/Wrestlers/TheRock.jpg");
    ui->label_27->setScaledContents( true );
    ui->label_27->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_27->setPixmap(TheRock);

    QPixmap TripleH(":/new/images/Wrestlers/TripleH.jpg");
    ui->label_28->setScaledContents( true );
    ui->label_28->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_28->setPixmap(TripleH);

    QPixmap Undertaker(":/new/images/Wrestlers/Undertaker.jpg");
    ui->label_29->setScaledContents( true );
    ui->label_29->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_29->setPixmap(Undertaker);

    QPixmap VinceMcMahon(":/new/images/Wrestlers/VinceMcMahon.jpg");
    ui->label_30->setScaledContents( true );
    ui->label_30->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->label_30->setPixmap(VinceMcMahon);
}

/**
 * @brief MainWindow::~MainWindow
 * Default destructor. No calls to new made in my code
 */
MainWindow::~MainWindow()
{
    delete ui;
}
