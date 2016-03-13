/** @file mainwindow.cpp
  * @brief This file contains code for implementing the MainWindow class
  *
  * The functions defined in mainwindow.cpp create the playable version of Battleship enumerated by the MainWindow class. Broadly,
  * provided functionality includes construction of the board, setting player/opponent ships, differentiated types of coordinates
  * on the board, visual movement through the board and processing opponent AI turns all with checks for validity.
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent is the parent widget
 * Constructor for the MainWindow class. Have modified default behavior so that constructor creates window with QLabel title/instructions,
 * QCheckBox prompts for player to input ships and QPushButton start/quit. In addition, constructor sets storage vectors default to empty
 * and int/bool values to 0
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    main = new QWidget;
    main_layout = new QVBoxLayout;

    //This code sets up the top row
    //Let's Play Battleship         [Quit]
    title = new QLabel("Let's Play Battleship!");
    title->setStyleSheet("font:bold 24pt");

    //spacer
    blank = new QLabel;

    //quit button
    quit = new QPushButton("Quit");
    quit->setStyleSheet("font: 16pt");
    QObject::connect(quit,SIGNAL(clicked(bool)),this,SLOT(close()));

    top_row = new QHBoxLayout;
    top_row->addWidget(title);
    top_row->addWidget(blank);
    top_row->addWidget(quit);

    main_layout->addLayout(top_row);

    //This code sets up the second row
    //Move through board using arrow keys. Select location using Space
    instructions = new QLabel("Move through board using arrow keys. Select location using Space");
    instructions->setStyleSheet("font:14pt");

    //Click corresponding checkbox to set ships. If a mistake is made, Begin will erase board
    instructions_line2 = new QLabel("Click corresponding checkbox to set ships. If a mistake is made, Begin will erase board");
    instructions_line2->setStyleSheet("font:14pt");

    main_layout->addWidget(instructions);
    main_layout->addWidget(instructions_line2);

    //This code sets the bottom left column consisting of a Begin button, QLabel representations of ships and check boxes
    bottom_row = new QHBoxLayout;

    begin = new QPushButton("Begin");
    begin->setStyleSheet("font:16pt");
    QObject::connect(begin,SIGNAL(clicked(bool)),this,SLOT(start_game()));

    aircraft_carrier = new QHBoxLayout;
    battleship = new QHBoxLayout;
    submarine = new QHBoxLayout;
    cruiser = new QHBoxLayout;
    destroyer = new QHBoxLayout;

    QLabel* aircraft_carrier_1 = new QLabel;
    aircraft_carrier_1 = create_gray_box();
    QLabel* aircraft_carrier_2 = new QLabel;
    aircraft_carrier_2 = create_gray_box();
    QLabel* aircraft_carrier_3 = new QLabel;
    aircraft_carrier_3 = create_gray_box();
    QLabel* aircraft_carrier_4 = new QLabel;
    aircraft_carrier_4 = create_gray_box();
    QLabel* aircraft_carrier_5 = new QLabel;
    aircraft_carrier_5 = create_gray_box();

    aircraft_carrier->addWidget(aircraft_carrier_1);
    aircraft_carrier->addWidget(aircraft_carrier_2);
    aircraft_carrier->addWidget(aircraft_carrier_3);
    aircraft_carrier->addWidget(aircraft_carrier_4);
    aircraft_carrier->addWidget(aircraft_carrier_5);

    QLabel* battleship_1 = new QLabel;
    battleship_1 = create_gray_box();
    QLabel* battleship_2 = new QLabel;
    battleship_2 = create_gray_box();
    QLabel* battleship_3 = new QLabel;
    battleship_3 = create_gray_box();
    QLabel* battleship_4 = new QLabel;
    battleship_4 = create_gray_box();
    QLabel* battleship_5 = new QLabel;
    battleship_5 = create_white_box();

    battleship->addWidget(battleship_1);
    battleship->addWidget(battleship_2);
    battleship->addWidget(battleship_3);
    battleship->addWidget(battleship_4);
    battleship->addWidget(battleship_5);

    QLabel* submarine_1 = new QLabel;
    submarine_1 = create_gray_box();
    QLabel* submarine_2 = new QLabel;
    submarine_2 = create_gray_box();
    QLabel* submarine_3 = new QLabel;
    submarine_3 = create_gray_box();
    QLabel* submarine_4 = new QLabel;
    submarine_4 = create_white_box();
    QLabel* submarine_5 = new QLabel;
    submarine_5 = create_white_box();

    submarine->addWidget(submarine_1);
    submarine->addWidget(submarine_2);
    submarine->addWidget(submarine_3);
    submarine->addWidget(submarine_4);
    submarine->addWidget(submarine_5);

    QLabel* cruiser_1 = new QLabel;
    cruiser_1 = create_gray_box();
    QLabel* cruiser_2 = new QLabel;
    cruiser_2 = create_gray_box();
    QLabel* cruiser_3 = new QLabel;
    cruiser_3 = create_gray_box();
    QLabel* cruiser_4 = new QLabel;
    cruiser_4 = create_white_box();
    QLabel* cruiser_5 = new QLabel;
    cruiser_5 = create_white_box();

    cruiser->addWidget(cruiser_1);
    cruiser->addWidget(cruiser_2);
    cruiser->addWidget(cruiser_3);
    cruiser->addWidget(cruiser_4);
    cruiser->addWidget(cruiser_5);

    QLabel* destroyer_1 = new QLabel;
    destroyer_1 = create_gray_box();
    QLabel* destroyer_2 = new QLabel;
    destroyer_2 = create_gray_box();
    QLabel* destroyer_3 = new QLabel;
    destroyer_3 = create_white_box();
    QLabel* destroyer_4 = new QLabel;
    destroyer_4 = create_white_box();
    QLabel* destroyer_5 = new QLabel;
    destroyer_5 = create_white_box();

    destroyer->addWidget(destroyer_1);
    destroyer->addWidget(destroyer_2);
    destroyer->addWidget(destroyer_3);
    destroyer->addWidget(destroyer_4);
    destroyer->addWidget(destroyer_5);

    aircraft_carrier_check = new QCheckBox("Aircraft Carrier");
    aircraft_carrier_check->setStyleSheet("font:12pt");
    battleship_check = new QCheckBox("Battleship");
    battleship_check->setStyleSheet("font:12pt");
    submarine_check = new QCheckBox("Submarine");
    submarine_check->setStyleSheet("font:12pt");
    cruiser_check = new QCheckBox("Cruiser");
    cruiser_check->setStyleSheet("font:12pt");
    destroyer_check = new QCheckBox("Destroyer");
    destroyer_check->setStyleSheet("font:12pt");

    //connects checkboxes to set functions (indicates what type of ship is being laid)
    QObject::connect(aircraft_carrier_check,SIGNAL(stateChanged(int)),this,SLOT(set_aircraft_carrier()));
    QObject::connect(battleship_check,SIGNAL(stateChanged(int)),this,SLOT(set_battleship()));
    QObject::connect(submarine_check,SIGNAL(stateChanged(int)),this,SLOT(set_submarine()));
    QObject::connect(cruiser_check,SIGNAL(stateChanged(int)),this,SLOT(set_cruiser()));
    QObject::connect(destroyer_check,SIGNAL(stateChanged(int)),this,SLOT(set_destroyer()));

    bottom_left = new QVBoxLayout;
    bottom_left->addWidget(begin);
    bottom_left->addLayout(aircraft_carrier);
    bottom_left->addWidget(aircraft_carrier_check);
    bottom_left->addLayout(battleship);
    bottom_left->addWidget(battleship_check);
    bottom_left->addLayout(submarine);
    bottom_left->addWidget(submarine_check);
    bottom_left->addLayout(cruiser);
    bottom_left->addWidget(cruiser_check);
    bottom_left->addLayout(destroyer);
    bottom_left->addWidget(destroyer_check);

    bottom_row->addLayout(bottom_left);

    //This code sets the bottom middle which consists of the player's grid and a QLabel indicating so
    bottom_middle = new QVBoxLayout;

    player_label = new QLabel("Your board");
    player_label->setStyleSheet("font:12pt");

    player_grid = new QGridLayout;
    player_grid->setGeometry(QRect());
    player_grid->setSpacing(0);

    player = std::vector< std::vector<QLabel*> >(10,std::vector<QLabel*>(10));

    //sets grid of QLabel in bottom middle that will serve as player's board
    //for loops cylce through player vector of vectors
    //i represents y values
    for(int i=0;i<10;++i){
        //for loops cylce through player vector of vectors
        //j represents x values
        for(int j=0;j<10;++j){
            player[i][j] = new QLabel;
            player[i][j]->setMinimumSize(40,40);
            player[i][j]->setMaximumSize(40,40);
            player[i][j]->setStyleSheet("background-color:blue");
            player[i][j]->setFrameStyle(1);
            player[i][j]->setAlignment(Qt::AlignCenter);
            player_grid->addWidget(player[i][j], i ,j);
        }
    }

    bottom_middle->addWidget(player_label);
    bottom_middle->addLayout(player_grid);

    bottom_row->addLayout(bottom_middle);

    //This code sets the bottom right which consists of the opponent's grid and a QLabel indicating so
    bottom_right = new QVBoxLayout;

    opponent_label = new QLabel("Opponent board");
    opponent_label->setStyleSheet("font:12pt");

    opponent_grid = new QGridLayout;
    opponent_grid->setGeometry(QRect());
    opponent_grid->setSpacing(0);

    opponent = std::vector< std::vector<QLabel*> >(10,std::vector<QLabel*>(10));

    //sets grid of QLabel in bottom right that will serve as opponent's board
    //for loops cylce through opponent vector of vectors
    //i represents y values
    for(int i=0;i<10;++i){
        //for loops cylce through opponent vector of vectors
        //j represents x values
        for(int j=0;j<10;++j){
            opponent[i][j] = new QLabel;
            opponent[i][j]->setMinimumSize(40,40);
            opponent[i][j]->setMaximumSize(40,40);
            opponent[i][j]->setStyleSheet("background-color:blue");
            opponent[i][j]->setFrameStyle(1);
            opponent[i][j]->setAlignment(Qt::AlignCenter);
            opponent_grid->addWidget(opponent[i][j], i ,j);
        }
    }

    //0 is blue             :not yet guess or hit
    //1 is blue with an X   :guessed but no hit
    //2 is gray             :ship
    //3 is red              :guessed and hit
    player_type = std::vector< std::vector<int> >(10,std::vector<int>(10));
    opponent_type = std::vector< std::vector<int> >(10,std::vector<int>(10));
    //cycles through vector of vector of int storing type of QLabel at each position
    //sets as default blue value
    //for loops cylce through player and opponent vector of vectors
    //i represents y values
    for(int i=0;i<10;++i){
        //for loops cylce through player and opponent vector of vectors
        //j represents x values
        for(int j=0;j<10;++j){
            player_type[i][j]=0;
            opponent_type[i][j]=0;
        }
    }

    bottom_right->addWidget(opponent_label);
    bottom_right->addLayout(opponent_grid);

    bottom_row->addLayout(bottom_right);

    main_layout->addLayout(bottom_row);
    main->setLayout(main_layout);
    this->setCentralWidget(main);

    //This sets the initial values for the location of player and opponent
    location = new QPoint(0,0);
    srand(time(0));
    int x=(rand()%10+0);
    int y=(rand()%10+0);
    opponent_location=new QPoint(x,y);

    //This sets the fact that we are currently on the player board
    mode=0;

    //This sets the face that we are currently not inputting any ships
    space_type=-1;

    //Sets ship vectors default to empty
    aircraft_carrier_player_pos=std::vector<QPoint*> (0);
    battleship_player_pos=std::vector<QPoint*> (0);
    submarine_player_pos=std::vector<QPoint*> (0);
    cruiser_player_pos=std::vector<QPoint*> (0);
    destroyer_player_pos=std::vector<QPoint*> (0);

    aircraft_carrier_opponent_pos=std::vector<QPoint*> (0);
    battleship_opponent_pos=std::vector<QPoint*> (0);
    submarine_opponent_pos=std::vector<QPoint*> (0);
    cruiser_opponent_pos=std::vector<QPoint*> (0);
    destroyer_opponent_pos=std::vector<QPoint*> (0);

    //Set registered hits to empty
    player_hits=0;
    opponent_hits=0;

    //This tells set_opponent_board function to store a copy of current QPoint
    reset=1;

    //This is a running int value incremented so that seed values change when functions called recursively
    seed_change=0;
}

/**
 * @brief MainWindow::~MainWindow
 * Destructor for the MainWindow class. Qt objects automatically deal with memory management. Call delete on vectors containing pointers
 * to ensure no memory leaks
 */
MainWindow::~MainWindow()
{
    delete ui;

    //for loop cycles through player and opponent vector of vectors to call delete
    //i represent y values
    for(size_t i=0;i<10;++i){
        //for loop cycles through player and opponent vector of vectors to call delete
        //j represent x values
        for(size_t j=0;j<10;++j){
            delete player[i][j];
            delete opponent[i][j];
        }
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:aircraft_carrier_player_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:aircraft_carrier_opponent_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:battleship_player_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:battleship_opponent_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:submarine_player_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:submarine_opponent_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:cruiser_player_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:cruiser_opponent_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:destroyer_player_pos){
        delete x;
    }

    //for loop cycles through ship vector to call delete on QPoint objects
    for(auto& x:destroyer_opponent_pos){
        delete x;
    }
}

/**
 * @brief pointCompare
 * @param left reference to a QPoint pointer to be compared
 * @param right reference to a QPoint pointer to be compared
 * Custom compare function orders QPoint objects by size of x value. Utilized to sort vectors of QPoint pointers (compare was not defined)
 * @return bool stating whether left<right
 */
bool pointCompare(QPoint*& left, QPoint*& right){
    return (left->rx())<(right->rx());
}

/**
 * @brief MainWindow::updateLocation
 * @param px is x coordinate user is originally on
 * @param py is y coordinate user is originally on
 * @param nx is x coordinate user will be switching to
 * @param ny is y coordinate user will be switching to
 * @param grid is vector of vector of QLabel* denoting grid that user is moving accross
 * @param grid_type is vector of vector of int denoting types of QLabel* at each coordinate in the grid
 * When called, updates the location of user and corresponding appearance of the board. Used in conjunction with keyPressEvent and
 * paintEvent to show movement accross board
 */
void MainWindow::updateLocation(int px, int py, int nx, int ny, std::vector<std::vector<QLabel*>>& grid, std::vector<std::vector<int>>& grid_type){
    grid[py][px]->clear();
    //if type grid denotes 0 set corresponding location to blue (not hit nor guessed)
    if(grid_type[py][px]==0){
        grid[py][px]->setStyleSheet("background-color:blue");
    }
    //if type grid denotes 1 set corresponding location to blue with an X (not hit but guessed)
    if(grid_type[py][px]==1){
        grid[py][px]->setText("X");
        grid[py][px]->setStyleSheet("background-color:blue; font:16px");
    }
    //if type grid denotes 2 and currently on player board set location to gray (ship)
    if(grid_type[py][px]==2 && mode==0){
        grid[py][px]->setStyleSheet("background-color:gray");
    }
    //if type grid denotes 2 and currently on opponent board do nothing
    if(grid_type[py][px]==2 && mode==1){
        grid[py][px]->setStyleSheet("background-color:blue");
    }
    //if type grid currently on 3 set corresponding location to red (hit and guessed)
    if(grid_type[py][px]==3){
        grid[py][px]->setStyleSheet("background-color:red");
    }
    location->setX(nx);
    location->setY(ny);
}

/**
 * @brief MainWindow::set_location
 * Activated by keyPressEvent, allows user to set the position of their ships on their board. space_type is determined by QCheckBox
 * pressed and denotes type of ship
 */
void MainWindow::set_location(){
    //if space type is 0 construct aircraft carrier
    if (space_type==0){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            aircraft_carrier_player_pos.push_back(new QPoint(x,y));
        }
    }
    //if space type is 1 construct battleship
    if(space_type==1){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            battleship_player_pos.push_back(new QPoint(x,y));
        }
    }
    //if space type is 2 construct submarine
    if(space_type==2){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            submarine_player_pos.push_back(new QPoint(x,y));
        }
    }
    //if space type is 3 construct cruiser
    if(space_type==3){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            cruiser_player_pos.push_back(new QPoint(x,y));
        }
    }
    //if space type is 4 construct destroyer
    if(space_type==4){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            destroyer_player_pos.push_back(new QPoint(x,y));
        }
    }
}

/**
 * @brief MainWindow::keyPressEvent
 * @param event is a pointer to the QKeyEvent activated by keyboard
 * Sets location of player based on keyboard commands and calls repaint() to update appearance of screen
 */
void MainWindow::keyPressEvent(QKeyEvent *event){
    //if mode is 0 player is moving through their own board
    if(mode==0){
        int x=location->rx();
        int y=location->ry();
        switch(event->key()){
        case Qt::Key_Left:
            //ensures do not go off board
            if(location->rx() != 0)
                updateLocation(x,y,x-1,y,player,player_type);
            break;
        case Qt::Key_Right:
            //ensures do not go off board
            if(location->rx() != 9)
                updateLocation(x,y,x+1,y,player,player_type);
            break;
        case Qt::Key_Up:
            //ensures do not go off board
            if(location->ry() != 0)
                updateLocation(x,y,x,y-1,player,player_type);
            break;
        case Qt::Key_Down:
            //ensures do not go off board
            if(location->ry() != 9)
                updateLocation(x,y,x,y+1,player,player_type);
            break;
        case Qt::Key_Space:
            //when on player board space is utilized to set player ships
            set_location();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
        QCoreApplication::processEvents();
        repaint();
    }
    //if mode is 1 player is moving through opponent board
    if(mode==1){
        int x=location->rx();
        int y=location->ry();
        switch(event->key()){
        case Qt::Key_Left:
            //ensures do not go off board
            if(location->rx() != 0)
                updateLocation(x,y,x-1,y,opponent,opponent_type);
            break;
        case Qt::Key_Right:
            //ensures do not go off board
            if(location->rx() != 9)
                updateLocation(x,y,x+1,y,opponent,opponent_type);
            break;
        case Qt::Key_Up:
            //ensures do not go off board
            if(location->ry() != 0)
                updateLocation(x,y,x,y-1,opponent,opponent_type);
            break;
        case Qt::Key_Down:
            //ensures do not go off board
            if(location->ry() != 9)
                updateLocation(x,y,x,y+1,opponent,opponent_type);
            break;
        case Qt::Key_Space:
            //when on opponent board space is utilized to guess location of ships
            guess_location();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
        QCoreApplication::processEvents();
        repaint();
    }
}

/**
 * @brief MainWindow::paintEvent
 * @param event is a pointer to the QPaintEvent that updates the appearance of screen
 * In addition to painting existing portions of the board when called, paintEvent creates black border around current location of
 * user
 */
void MainWindow::paintEvent(QPaintEvent *event){
    //if mode is 0 player is moving through their own board
    if(mode==0){
        int x=location->rx();
        int y=location->ry();

        //if space type is 0 add black border to blue QLabel
        if(player_type[y][x]==0){
            player[y][x]->setStyleSheet("background-color:blue; border: 6px solid");
        }
        //if space type is 1 add black border to blue QLabel with an X
        if(player_type[y][x]==1){
            player[y][x]->setText("X");
            player[y][x]->setStyleSheet("background-color:blue; font:16px; border: 6px solid");
        }
        //if space type is 2 add black border to gray QLabel
        if(player_type[y][x]==2){
            player[y][x]->setStyleSheet("background-color:gray; border: 6px solid");
        }
        //if space type is 3 add black border to red QLabel
        if(player_type[y][x]==3){
            player[y][x]->setStyleSheet("background-color:red; border: 6px solid");
        }
    }
    //if mode is 1 player is moving through opponent board
    if(mode==1){
        int x=location->rx();
        int y=location->ry();

        //if space type is 0 add black border to blue QLabel
        if(opponent_type[y][x]==0){
            opponent[y][x]->setStyleSheet("background-color:blue; border: 6px solid");
        }
        //if space type is 1 add black border to blue QLabel with an X
        if(opponent_type[y][x]==1){
            opponent[y][x]->setText("X");
            opponent[y][x]->setStyleSheet("background-color:blue; font:16px; border: 6px solid");
        }
        //if space type is 2 add black border to blue QLabel
        if(opponent_type[y][x]==2){
            opponent[y][x]->setStyleSheet("background-color:blue; border: 6px solid");
        }
        //if space type is 3 add black border to red QLabel
        if(opponent_type[y][x]==3){
            opponent[y][x]->setStyleSheet("background-color:red; border: 6px solid");
        }
    }
}

/**
 * @brief MainWindow::showEvent
 * @param event is a pointer to the QShowEvent that displays the MainWindow object to the screen
 * showEvent function displays window created by MainWindow object to screen. setFocus ensures that keyboard can be used (QPushButton/
 * QCheckBox are not the focus)
 */
void MainWindow::showEvent(QShowEvent *event) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(event);
}

/**
 * @brief MainWindow::isValid_aircraft_carrier
 * @return bool value indicating whether aircraft carrier has been set in valid location
 * Iterates through the player aircraft carrier QPoint* vector and ensures that points are in a continuous line of requisite length.
 * Return true is position is valid
 */
bool MainWindow::isValid_aircraft_carrier(){
    std::sort(aircraft_carrier_player_pos.begin(),aircraft_carrier_player_pos.end(),pointCompare);
    //checks if aircraft carrier is requisite length returns false otherwise
    if(aircraft_carrier_player_pos.size()!=5){
        return false;
    }
    int x0=aircraft_carrier_player_pos[0]->rx();
    int y0=aircraft_carrier_player_pos[0]->ry();
    int x=aircraft_carrier_player_pos[1]->rx();
    int y=aircraft_carrier_player_pos[1]->ry();
    //for first two points checks if they are adjacent in the x direction
    if(((x0==x+1)||(x0==x-1))&&(y0==y)){
        x0=x;
        y0=y;
        //iterates through aircraft carrier vector to ensure that points are adjacent in the x direction
        for(size_t i=2;i<5;++i){
            x=aircraft_carrier_player_pos[i]->rx();
            y=aircraft_carrier_player_pos[i]->ry();
            //if points are adjacent in the x direction set original points to current position
            if(((x0==x+1)||(x0==x-1))&&(y0==y)){
                x0=x;
                y0=y;
            }
            //if points are not adjacent in the x direction return false
            else{
                return false;
            }
        }
    }
    //for first two points checks if they are adjacent in the y direction
    else if(((y0==y+1)||(y0==y-1))&&(x0==x)){
        x0=x;
        y0=y;
        //iterates through aircraft carrier vector to ensure that points are adjacent in the y direction
        for(size_t i=2;i<5;++i){
            x=aircraft_carrier_player_pos[i]->rx();
            y=aircraft_carrier_player_pos[i]->ry();
            //if points are adjacent in the y direction set original points to current position
            if(((y0==y+1)||(y0==y-1))&&(x0==x)){
                x0=x;
                y0=y;
            }
            //if points are not adjacent in the y direction return false
            else{
                return false;
            }
        }
    }
    //if not adjacent in either x or y direction return false
    else{
        return false;
    }
    return true;
}

/**
 * @brief MainWindow::isValid_battleship
 * @return bool value indicating whether battleship has been set in valid location
 * Iterates through the player battleship QPoint* vector and ensures that points are in a continuous line of requisite length.
 * Return true is position is valid
 */
bool MainWindow::isValid_battleship(){
    std::sort(battleship_player_pos.begin(),battleship_player_pos.end(),pointCompare);
    //checks if battleship is requisite length returns false otherwise
    if(battleship_player_pos.size()!=4){
        return false;
    }
    int x0=battleship_player_pos[0]->rx();
    int y0=battleship_player_pos[0]->ry();
    int x=battleship_player_pos[1]->rx();
    int y=battleship_player_pos[1]->ry();
    //for first two points checks if they are adjacent in the x direction
    if(((x0==x+1)||(x0==x-1))&&(y0==y)){
        x0=x;
        y0=y;
        //iterates through battleship vector to ensure that points are adjacent in the x direction
        for(size_t i=2;i<4;++i){
            x=battleship_player_pos[i]->rx();
            y=battleship_player_pos[i]->ry();
            //if points are adjacent in the x direction set original points to current position
            if(((x0==x+1)||(x0==x-1))&&(y0==y)){
                x0=x;
                y0=y;
            }
            //if points are not adjacent in the x direction return false
            else{
                return false;
            }
        }
    }
    //for first two points checks if they are adjacent in the y direction
    else if(((y0==y+1)||(y0==y-1))&&(x0==x)){
        x0=x;
        y0=y;
        //iterates through battleship vector to ensure that points are adjacent in the y direction
        for(size_t i=2;i<4;++i){
            x=battleship_player_pos[i]->rx();
            y=battleship_player_pos[i]->ry();
            //if points are adjacent in the y direction set original points to current position
            if(((y0==y+1)||(y0==y-1))&&(x0==x)){
                x0=x;
                y0=y;
            }
            //if points are not adjacent in the y direction return false
            else{
                return false;
            }
        }
    }
    //if not adjacent in either x or y direction return false
    else{
        return false;
    }
    return true;
}

/**
 * @brief MainWindow::isValid_submarine
 * @return bool value indicating whether submarine has been set in valid location
 * Iterates through the player submarine QPoint* vector and ensures that points are in a continuous line of requisite length.
 * Return true is position is valid
 */
bool MainWindow::isValid_submarine(){
    std::sort(submarine_player_pos.begin(),submarine_player_pos.end(),pointCompare);
    //checks if submarine is requisite length returns false otherwise
    if(submarine_player_pos.size()!=3){
        return false;
    }
    int x0=submarine_player_pos[0]->rx();
    int y0=submarine_player_pos[0]->ry();
    int x=submarine_player_pos[1]->rx();
    int y=submarine_player_pos[1]->ry();
    //for first two points checks if they are adjacent in the x direction
    if(((x0==x+1)||(x0==x-1))&&(y0==y)){
        x0=x;
        y0=y;
        x=submarine_player_pos[2]->rx();
        y=submarine_player_pos[2]->ry();
        //if points are adjacent in the x direction return true
        if(((x0==x+1)||(x0==x-1))&&(y0==y)){
            return true;
        }
        //if points are not adjacent in the x direction return false
        else{
            return false;
        }
    }
    //for first two points checks if they are adjacent in the y direction
    else if(((y0==y+1)||(y0==y-1))&&(x0==x)){
        x0=x;
        y0=y;
        x=submarine_player_pos[2]->rx();
        y=submarine_player_pos[2]->ry();
        //if points are adjacent in the y direction return true
        if(((y0==y+1)||(y0==y-1))&&(x0==x)){
            return true;
        }
        //if points are not adjacent in the y direction return false
        else{
            return false;
        }
    }
    //if not adjacent in either x or y direction return false
    else{
        return false;
    }
}

/**
 * @brief MainWindow::isValid_cruiser
 * @return bool value indicating whether cruiser has been set in valid location
 * Iterates through the player cruiser QPoint* vector and ensures that points are in a continuous line of requisite length.
 * Return true is position is valid
 */
bool MainWindow::isValid_cruiser(){
    std::sort(cruiser_player_pos.begin(),cruiser_player_pos.end(),pointCompare);
    //checks if cruiser is requisite length returns false otherwise
    if(cruiser_player_pos.size()!=3){
        return false;
    }
    int x0=cruiser_player_pos[0]->rx();
    int y0=cruiser_player_pos[0]->ry();
    int x=cruiser_player_pos[1]->rx();
    int y=cruiser_player_pos[1]->ry();
    //for first two points checks if they are adjacent in the x direction
    if(((x0==x+1)||(x0==x-1))&&(y0==y)){
        x0=x;
        y0=y;
        x=cruiser_player_pos[2]->rx();
        y=cruiser_player_pos[2]->ry();
        //if points are adjacent in the x direction return true
        if(((x0==x+1)||(x0==x-1))&&(y0==y)){
            return true;
        }
        //if points are not adjacent in the x direction return false
        else{
            return false;
        }
    }
    //for first two points checks if they are adjacent in the y direction
    else if(((y0==y+1)||(y0==y-1))&&(x0==x)){
        x0=x;
        y0=y;
        x=cruiser_player_pos[2]->rx();
        y=cruiser_player_pos[2]->ry();
        //if points are adjacent in the y direction return true
        if(((y0==y+1)||(y0==y-1))&&(x0==x)){
            return true;
        }
        //if points are not adjacent in the y direction return false
        else{
            return false;
        }
    }
    //if not adjacent in either x or y direction return false
    else{
        return false;
    }
}

/**
 * @brief MainWindow::isValid_destroyer
 * @return bool value indicating whether destroyer has been set in valid location
 * Iterates through the player destroyer QPoint* vector and ensures that points are in a continuous line of requisite length.
 * Return true is position is valid
 */
bool MainWindow::isValid_destroyer(){
    std::sort(destroyer_player_pos.begin(),destroyer_player_pos.end(),pointCompare);
    //checks if destroyer is requisite length returns false otherwise
    if(destroyer_player_pos.size()!=2){
        return false;
    }
    int x0=destroyer_player_pos[0]->rx();
    int y0=destroyer_player_pos[0]->ry();
    int x=destroyer_player_pos[1]->rx();
    int y=destroyer_player_pos[1]->ry();
    //for the two points checks if they are adjacent in the x direction if so return true
    if(((x0==x+1)||(x0==x-1))&&(y0==y)){
        return true;
    }
    //for the two points checks if they are adjacent in the y direction if so return true
    else if(((y0==y+1)||(y0==y-1))&&(x0==x)){
        return true;
    }
    //if not adjacent in either x or y direction return false
    else{
        return false;
    }
}

/**
 * @brief MainWindow::set_opponent_aircraft_carrier
 * @return bool value indicating whether opponent aircraft carrier has been set in valid location
 * Sets opponent aircraft carrier by generating random coordinates and iterating through the opponent grid in a line. Because aircraft
 * carrier is first ship created, will always return true
 */
bool MainWindow::set_opponent_aircraft_carrier(){
    //ensures that aircraft carrier vector is empty to begin with
    if(aircraft_carrier_opponent_pos.size()!=0){
        aircraft_carrier_opponent_pos=std::vector<QPoint*>(0);
    }
    srand(time(0));
    int orientation=(rand()%(2)+0);
    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        int x=(rand()%(2)+4);
        int y=(rand()%(10)+0);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        int x=(rand()%(10)+0);
        int y=(rand()%(2)+4);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

/**
 * @brief MainWindow::set_opponent_battleship
 * @return bool value indicating whether opponent battleship has been set in valid location
 * Sets opponent battleship by generating random coordinates and iterating through the opponent grid in a line. Afterwards,
 * compares each element of battleship vector with each element of aircraft carrier vector to ensure no overlap. Return true
 * if valid location
 */
bool MainWindow::set_opponent_battleship(){
    //ensures that battleship vector is empty to begin with
    if(battleship_opponent_pos.size()!=0){
        battleship_opponent_pos=std::vector<QPoint*>(0);
    }
    srand(time(0)+1);
    int orientation=(rand()%(2)+0);
    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        int x=(rand()%(4)+3);
        int y=(rand()%(10)+0);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        int x=(rand()%(10)+0);
        int y=(rand()%(4)+3);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }

    //iterates through battleship vector to compare elements
    for(size_t i=0;i<4;++i){
        //iterates through aircraft carrier vector to compare elements
        for(size_t j=0;j<5;++j){
            //if two points overlap return false
            if((*battleship_opponent_pos[i])==(*aircraft_carrier_opponent_pos[j])){
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief MainWindow::set_opponent_submarine
 * @return bool value indicating whether opponent submarine has been set in valid location
 * Sets opponent submarine by generating random coordinates and iterating through the opponent grid in a line. Afterwards,
 * compares each element of submarine vector with each element of aircraft carrier and battleship vectors to ensure no overlap.
 * Return true if valid location
 */
bool MainWindow::set_opponent_submarine(){
    //ensures that submarine vector is empty to begin with
    if(submarine_opponent_pos.size()!=0){
        submarine_opponent_pos=std::vector<QPoint*>(0);
    }
    srand(time(0)+2);
    int orientation=(rand()%(2)+0);
    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        int x=(rand()%(6)+2);
        int y=(rand()%(10)+0);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        int x=(rand()%(10)+0);
        int y=(rand()%(6)+2);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }

    //iterates through submarine vector to compare elements
    for(size_t i=0;i<3;++i){
        //iterates through aircraft carier vector to compare elements
        for(size_t j=0;j<5;++j){
            //if two points overlap return false
            if((*submarine_opponent_pos[i])==(*aircraft_carrier_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through submarine vector to compare elements
    for(size_t i=0;i<3;++i){
        //iterates through battleship vector to compare elements
        for(size_t j=0;j<4;++j){
            //if two points overlap return false
            if((*submarine_opponent_pos[i])==(*battleship_opponent_pos[j])){
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief MainWindow::set_opponent_cruiser
 * @return bool value indicating whether opponent cruiser has been set in valid location
 * Sets opponent cruiser by generating random coordinates and iterating through the opponent grid in a line. Afterwards,
 * compares each element of cruiser vector with each element of aircraft carrier, battleship and submarine vectors to ensure no overlap.
 * Return true if valid location
 */
bool MainWindow::set_opponent_cruiser(){
    //ensures that cruiser vector is empty to begin with
    if(cruiser_opponent_pos.size()!=0){
        cruiser_opponent_pos=std::vector<QPoint*>(0);
    }
    srand(time(0)+3);
    int orientation=(rand()%(2)+0);
    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        int x=(rand()%(6)+2);
        int y=(rand()%(10)+0);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        int x=(rand()%(10)+0);
        int y=(rand()%(6)+2);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }

    //iterates through cruiser vector to compare elements
    for(size_t i=0;i<3;++i){
        //iterates through aircraft carrier vector to compare elements
        for(size_t j=0;j<5;++j){
            //if two points overlap return false
            if((*cruiser_opponent_pos[i])==(*aircraft_carrier_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through cruiser vector to compare elements
    for(size_t i=0;i<3;++i){
        //iterates through battleship vector to compare elements
        for(size_t j=0;j<4;++j){
            //if two points overlap return false
            if((*cruiser_opponent_pos[i])==(*battleship_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through cruiser vector to compare elements
    for(size_t i=0;i<3;++i){
        //iterates through submarine vector to compare elements
        for(size_t j=0;j<3;++j){
            //if two points overlap return false
            if((*cruiser_opponent_pos[i])==(*submarine_opponent_pos[j])){
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief MainWindow::set_opponent_destroyer
 * @return bool value indicating whether opponent destroyer has been set in valid location
 * Sets opponent destroyer by generating random coordinates and iterating through the opponent grid in a line. Afterwards,
 * compares each element of destroyer vector with each element of aircraft carrier, battleship, submarine and cruiser
 * vectors to ensure no overlap. Return true if valid location
 */
bool MainWindow::set_opponent_destroyer(){
    //ensures that destroyer vector is empty to begin with
    if(destroyer_opponent_pos.size()!=0){
        destroyer_opponent_pos=std::vector<QPoint*>(0);
    }
    srand(time(0)+4);
    int orientation=(rand()%(2)+0);
    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        int x=(rand()%(8)+1);
        int y=(rand()%(10)+0);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        int x=(rand()%(10)+0);
        int y=(rand()%(8)+1);
        int above_below=(rand()%(2)+0);
        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:blue");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }

    //iterates through destroyer vector to compare elements
    for(size_t i=0;i<2;++i){
        //iterates through aircraft carrier vector to compare elements
        for(size_t j=0;j<5;++j){
            //if two points overlap return false
            if((*destroyer_opponent_pos[i])==(*aircraft_carrier_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through destroyer vector to compare elements
    for(size_t i=0;i<2;++i){
        //iterates through battleship vector to compare elements
        for(size_t j=0;j<4;++j){
            //if two points overlap return false
            if((*destroyer_opponent_pos[i])==(*battleship_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through destroyer vector to compare elements
    for(size_t i=0;i<2;++i){
        //iterates through submarine vector to compare elements
        for(size_t j=0;j<3;++j){
            //if two points overlap return false
            if((*destroyer_opponent_pos[i])==(*submarine_opponent_pos[j])){
                return false;
            }
        }
    }

    //iterates through destroyer vector to compare elements
    for(size_t i=0;i<2;++i){
        //iterates through cruiser vector to compare elements
        for(size_t j=0;j<3;++j){
            //if two points overlap return false
            if((*destroyer_opponent_pos[i])==(*cruiser_opponent_pos[j])){
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief MainWindow::set_aircraft_carrier
 * Sets space type to 0 so that spacebar sets aircraft carrier position
 */
void MainWindow::set_aircraft_carrier(){
    space_type = 0;
    this->setFocus();
}

/**
 * @brief MainWindow::set_battleship
 * Sets space type to 1 so that spacebar sets battleship location
 */
void MainWindow::set_battleship(){
    space_type = 1;
    this->setFocus();
}

/**
 * @brief MainWindow::set_submarine
 * Sets space type to 2 so that spacebar sets submarine location
 */
void MainWindow::set_submarine(){
    space_type = 2;
    this->setFocus();
}

/**
 * @brief MainWindow::set_cruiser
 * Sets space type to 3 so that spacebar sets cruiser location
 */
void MainWindow::set_cruiser(){
    space_type = 3;
    this->setFocus();
}

/**
 * @brief MainWindow::set_destroyer
 * Sets space type to 4 so that spacebar sets destroyer location
 */
void MainWindow::set_destroyer(){
    space_type = 4;
    this->setFocus();
}

/**
 * @brief MainWindow::start_game
 * Ensures that all player ships are in valid location. If so, starts game by setting mode to 1 so that player guesses on opponent's board.
 * If player ships are not in valid location, resets game by setting entire board to type 0/blue, unchecking QCheckbox objects and
 * emptying player ship vectors
 */
void MainWindow::start_game(){
    std::vector<bool> track_storage (0);
    track_storage.push_back(isValid_aircraft_carrier());
    track_storage.push_back(isValid_battleship());
    track_storage.push_back(isValid_submarine());
    track_storage.push_back(isValid_cruiser());
    track_storage.push_back(isValid_destroyer());
    bool track_final=1;
    //iterates through vector of bool storing whether each player ship is valid
    for(size_t i=0; i<5; ++i){
        //if ship is in invalid location set track_final to false indicating game not ready to be played
        if(track_storage[i]==0){
            track_final=0;
            break;
        }
    }
    //if track_final is true game is ready to play
    //sets mode to 1 so that player appears on opponent board to guess locations
    //sets last position on player board to version without black border
    if(track_final){
        mode=1;
        set_opponent_board();
        this->setFocus();
        int x=location->rx();
        int y=location->ry();
        //if player type is 0 set to blue
        if(player_type[y][x]==0){
            player[y][x]->setStyleSheet("background-color:blue");
        }
        //if player type is 1 set to blue with an X
        if(player_type[y][x]==1){
            player[y][x]->setText("X");
            player[y][x]->setStyleSheet("background-color:blue; font:16px");
        }
        //if player type is 2 set to gray
        if(player_type[y][x]==2){
            player[y][x]->setStyleSheet("background-color:gray");
        }
        //if player type is 3 set to red
        if(player_type[y][x]==3){
            player[y][x]->setStyleSheet("background-color:red");
        }
    }
    //if track_final is false game is not ready to play and must be reset
    else{
        //for loop cycles through player and player_type vectors of vectors to set to blue/0
        //i represent y values
        for(size_t i=0;i<10;++i){
            //for loop cycles through player and player_type vectors of vectors to set to blue/0
            //j represent x values
            for(size_t j=0;j<10;++j){
                player[i][j]->setStyleSheet("background-color:blue");
                player_type[i][j]=0;
            }
        }
        aircraft_carrier_player_pos=std::vector<QPoint*> (0);
        battleship_player_pos=std::vector<QPoint*> (0);
        submarine_player_pos=std::vector<QPoint*> (0);
        cruiser_player_pos=std::vector<QPoint*> (0);
        destroyer_player_pos=std::vector<QPoint*> (0);

        aircraft_carrier_check->setCheckState(Qt::Unchecked);
        battleship_check->setCheckState(Qt::Unchecked);
        submarine_check->setCheckState(Qt::Unchecked);
        cruiser_check->setCheckState(Qt::Unchecked);
        destroyer_check->setCheckState(Qt::Unchecked);

        this->setFocus();
    }
}

/**
 * @brief MainWindow::set_opponent_board
 * Calls set_opponent_ship functions to create opponent board. Stores whether they return false and if so, calls set_opponent_board
 * function recursively to restart process until valid locations are reached for all ships. Clears board before doing so
 */
void MainWindow::set_opponent_board(){
    bool track=1;
    track=set_opponent_aircraft_carrier();
    //if opponent aircraft carrier is not in valid position call function recursively to restart
    //clears opponent board for new values to be set
    if(!track){
        clear_opponent_board();
        set_opponent_board();
    }
    track=set_opponent_battleship();
    //if opponent battleship is not in valid position call function recursively to restart
    //clears opponent board for new values to be set
    if(!track){
        clear_opponent_board();
        set_opponent_board();
    }
    track=set_opponent_submarine();
    //if opponent submarine is not in valid position call function recursively to restart
    //clears opponent board for new values to be set
    if(!track){
        clear_opponent_board();
        set_opponent_board();
    }
    track=set_opponent_cruiser();
    //if opponent cruiser is not in valid position call function recursively to restart
    //clears opponent board for new values to be set
    if(!track){
        clear_opponent_board();
        set_opponent_board();
    }
    track=set_opponent_destroyer();
    //if opponent destroyer is not in valid position call function recursively to restart
    //clears opponent board for new values to be set
    if(!track){
        clear_opponent_board();
        set_opponent_board();
    }
    this->setFocus();
}

/**
 * @brief MainWindow::clear_opponent_board
 * Iterates through opponent and opponent_type vectors of vectors to set to blue/0
 */
void MainWindow::clear_opponent_board(){
    //for loop cycles through opponent and opponent_type vectors of vectors to set to blue/0
    //i represent y values
    for(size_t i=0;i<10;++i){
        //for loop cycles through opponent and opponent_type vectors of vectors to set to blue/0
        //j represent x values
        for(size_t j=0;j<10;++j){
            opponent[i][j]->setStyleSheet("background-color:blue");
            opponent_type[i][j]=0;
        }
    }
}

/**
 * @brief MainWindow::create_gray_box
 * @return a pointer to the gray QLabel object created
 * Creates in the heap a square gray QLabel for use in depicting the ships on the bottom left
 */
QLabel* MainWindow::create_gray_box(){
    QLabel* gray_box = new QLabel;
    gray_box->setMinimumSize(20,20);
    gray_box->setMaximumSize(20,20);
    gray_box->setStyleSheet("background-color:gray");
    gray_box->setAlignment(Qt::AlignCenter);
    return gray_box;
}

/**
 * @brief MainWindow::create_white_box
 * @return a pointer to the white QLabel object created
 * Creates in the heap a square white QLabel for use in depicting the ships on the bottom left
 */
QLabel* MainWindow::create_white_box(){
    QLabel* white_box = new QLabel;
    white_box->setMinimumSize(20,20);
    white_box->setMaximumSize(20,20);
    white_box->setStyleSheet("background-color:white");
    white_box->setAlignment(Qt::AlignCenter);
    return white_box;
}

/**
 * @brief MainWindow::guess_location
 * Activated by keyPressEvent, allows player to guess location of ship on opponent's board. If wrong registers a miss and if correct
 * registers a hit. Afterwards, runs opponent's turn and then victor function to determine whether either play has won yet
 */
void MainWindow::guess_location(){
    int x=location->rx();
    int y=location->ry();
    //if mode is 0 ship is not in location and registers a miss
    if(opponent_type[y][x]==0){
        opponent_type[y][x]=1;
        opponent[y][x]->setText("X");
        opponent[y][x]->setStyleSheet("background-color:blue; font:16px");
    }
    //if mode is 2 ship is in location and registers a hit
    //increments tally of ships player has hit
    if(opponent_type[y][x]==2){
        opponent_type[y][x]=3;
        opponent[y][x]->setStyleSheet("background-color:red");
        ++player_hits;
    }
    opponent_turn();
    victor();
    this->setFocus();
}

/**
 * @brief MainWindow::opponent_turn
 * opponent_turn allows the computer to guess a location on the grid. The AI makes an educated guess (starting with an initial random
 * coordinate) by first choosing random coordinates until a hit has been made. It records the hit coordinates on a storage point and
 * proceeds to test points one away from the hit to the top, bottom left and right. When another hit is registered, the AI continues
 * guessing in the said direction with x and y being incrementally updated. The storage point is used to allow the AI to revisit the
 * original point and travel the opposite direction to ensure that all of the ship has been targeted. Once the ship has been sunk (points
 * on either side both register misses), the coordinates are set to random values again. The function ensures that no repeat guessing of points
 * occurs by setting new random coordinates and running the function recursively if location type is 1 or 3. I artifically made the AI
 * worse by introducing a 1 in 12 possibility that coordinates are set to random values which would disrupt the methodical iteration
 * through player ships (else AI may be too powerful). AI algorithm subject to improvements.
 */
void MainWindow::opponent_turn(){
    srand(time(0)+seed_change);
    ++seed_change;
    int x =opponent_location->rx();
    int y=opponent_location->ry();

    /*
    int chance=(rand()%12+0);
    //for 1 in 12 chance set coordinates to random values thus disrupting the algorithm
    if(chance==2){
        x=(rand()%10+0);
        y=(rand()%10+0);
    }*/

    //if ship has been iterated through completely reset is true and QPoint is set as current coordinates
    if(reset){
        opponent_location_storage=new QPoint(x,y);
    }
    //if type is 1 (guessed and miss) or 3 (guessed and hit) calls function recursively with new position
    if((player_type[y][x]==1)||(player_type[y][x]==3)){
        x=(rand()%10+0);
        y=(rand()%10+0);
        opponent_location=new QPoint(x,y);
        opponent_turn();
    }
    //if type is 2 registers a hit (increments opponent_hit) and begins educated guess algorithm
    else if(player_type[y][x]==2){
        reset=0;
        player[y][x]->setStyleSheet("background-color:red");
        player_type[y][x]=3;
        bool up=opponent_guess_up();
        //if there is not point above current location try below
        if(!up){
            bool down=opponent_guess_down();
            //if there is no point below current location try to the left
            if(!down){
                bool left=opponent_guess_left();
                //if there is no point to the left of current location try to the right
                if(!left){
                    bool right=opponent_guess_right();
                    //if there is no point to the right of current location set opponent location to new random values
                    //educated guesses have been exhausted
                    if(!right){
                        x=(rand()%10+0);
                        y=(rand()%10+0);
                        opponent_location=new QPoint(x,y);
                    }
                }
            }
        }
        ++opponent_hits;
    }
    //if type is 0 registers a miss and sets coordinates to new random value
    //sets reset to 1 so that opponent location storage may be set to new value
    else if(player_type[y][x]==0){
        player_type[y][x]=1;
        player[y][x]->setText("X");
        player[y][x]->setStyleSheet("background-color:blue; font:16px");
        x=(rand()%10+0);
        y=(rand()%10+0);
        reset=1;
        opponent_location=new QPoint(x,y);
    }
}

/**
 * @brief MainWindow::opponent_guess_up
 * @return bool value true if there is a ship point one above current location
 * Provided that y is at least 1, guesses one above and returns true if ship in location. Further sets opponent location to incremented
 * position so that guesses may continue in direction
 */
bool MainWindow::opponent_guess_up(){
    int x=opponent_location->rx();
    int y=opponent_location->ry();
    --y;
    //decremented y must be at least 0 to stay in vector range
    if(y>=0){
        //if ship is in location sets opponent location to current position and return true
        if(player_type[y][x]==2){
            opponent_location=new QPoint(x,y);
            return true;
        }
    }
    return false;
}

/**
 * @brief MainWindow::opponent_guess_down
 * @return bool value true if there is a ship point one below current location
 * Provided that y is at least 8, guesses one below and returns true if ship in location. Further sets opponent location to incremented
 * position and updates storage so that guesses may continue in direction
 */
bool MainWindow::opponent_guess_down(){
    int x=opponent_location_storage->rx();
    int y=opponent_location_storage->ry();
    ++y;
    //incremented y must be less than 9 to say in vector range
    if(y<=9){
        //if ship is in location sets opponent location to current position and return true
        //updates storage
        if(player_type[y][x]==2){
            opponent_location_storage->setY(y);
            opponent_location=new QPoint(x,y);
            return true;
        }
    }
    return false;
}

/**
 * @brief MainWindow::opponent_guess_left
 * @return bool value true if there is a ship point one to the left of current location
 * Provided that x is at least 1, guesses one to the left and returns true if ship in location. Further sets opponent location to
 * incremented position and updates storage so that guesses may continue in direction
 */
bool MainWindow::opponent_guess_left(){
    int x=opponent_location->rx();
    int y=opponent_location->ry();
    --x;
    //decremented y must be at least 0 to stay in vector range
    if(x>=0){
        //if ship is in location sets opponent location to current position and return true
        if(player_type[y][x]==2){
            opponent_location=new QPoint(x,y);
            return true;
        }
    }
    return false;
}

/**
 * @brief MainWindow::opponent_guess_right
 * @return bool value true if there is a ship point one to the right of current location
 * Provided that x is at least 8, guesses one to the right and returns true if ship in location. Further sets opponent location to
 * incremented position and updates storage so that guesses may continue in direction
 */
bool MainWindow::opponent_guess_right(){
    int x=opponent_location_storage->rx();
    int y=opponent_location_storage->ry();
    ++x;
    //incremented x must be less than 9 to say in vector range
    if(x<=9){
        //if ship is in location sets opponent location to current position and return true
        //updates storage
        if(player_type[y][x]==2){
            opponent_location_storage->setX(x);
            opponent_location=new QPoint(x,y);
            return true;
        }
    }
    return false;
}

/**
 * @brief MainWindow::victor
 * Checks hit integer values and if either play reches 17 declares them the victor
 */
void MainWindow::victor(){
    //if player hits is 17 then the player has sunk all of the opponent's ships
    //prompts victory banner
    if(player_hits==17){
        victory=new QLabel("Congrats! You are the winner");
        victory->setStyleSheet("font:bold 32px");
        victory->show();
    }
    //if opponent hits is 17 then the opponent has sunk all of the player's ships
    //prompts defeat banner
    else if(opponent_hits==17){
        victory=new QLabel("The computer has won");
        victory->setStyleSheet("font:bold 32px");
        victory->show();
    }
}
