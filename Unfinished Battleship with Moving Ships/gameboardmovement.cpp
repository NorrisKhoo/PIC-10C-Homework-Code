#include "gameboardmovement.h"
#include "ui_gameboardmovement.h"

unsigned int seed_movement=std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator_movement(seed_movement);

GameboardMovement::GameboardMovement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameboardMovement)
{
    ui->setupUi(this);

    main_layout = new QVBoxLayout;

    //This code sets up the top row
    //Battleship Single Player              [Quit]
    title = new QLabel("Battleship Single Player");

    title->setStyleSheet("font:bold 24pt");

    //spacer
    blank = new QLabel;

    //quit button
    quit = new QPushButton("Quit");
    quit->setStyleSheet("font: 16pt");
    QObject::connect(quit,SIGNAL(clicked(bool)),this,SLOT(end_game()));

    top_row = new QHBoxLayout;
    top_row->addWidget(title);
    top_row->addWidget(blank);
    top_row->addWidget(quit);

    main_layout->addLayout(top_row);

    //This code sets up the second row
    //Move through board using arrow keys. Select location using Space
    instructions = new QLabel("Move through board using arrow keys. Select location using Space");
    instructions->setStyleSheet("font:14pt");

    //Click corresponding checkbox to set ships. If a mistake is made, Begin will reset board
    instructions_line2 = new QLabel("Click corresponding checkbox to set ships. If a mistake is made, Begin will reset board");
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

    QLabel* aircraft_carrier_1 = create_gray_box();
    QLabel* aircraft_carrier_2 = create_gray_box();
    QLabel* aircraft_carrier_3 = create_gray_box();
    QLabel* aircraft_carrier_4 = create_gray_box();
    QLabel* aircraft_carrier_5 = create_gray_box();

    aircraft_carrier->addWidget(aircraft_carrier_1);
    aircraft_carrier->addWidget(aircraft_carrier_2);
    aircraft_carrier->addWidget(aircraft_carrier_3);
    aircraft_carrier->addWidget(aircraft_carrier_4);
    aircraft_carrier->addWidget(aircraft_carrier_5);

    QLabel* battleship_1 = create_gray_box();
    QLabel* battleship_2 = create_gray_box();
    QLabel* battleship_3 = create_gray_box();
    QLabel* battleship_4 = create_gray_box();
    QLabel* battleship_5 = create_white_box();

    battleship->addWidget(battleship_1);
    battleship->addWidget(battleship_2);
    battleship->addWidget(battleship_3);
    battleship->addWidget(battleship_4);
    battleship->addWidget(battleship_5);

    QLabel* submarine_1 = create_gray_box();
    QLabel* submarine_2 = create_gray_box();
    QLabel* submarine_3 = create_gray_box();
    QLabel* submarine_4 = create_white_box();
    QLabel* submarine_5 = create_white_box();

    submarine->addWidget(submarine_1);
    submarine->addWidget(submarine_2);
    submarine->addWidget(submarine_3);
    submarine->addWidget(submarine_4);
    submarine->addWidget(submarine_5);

    QLabel* cruiser_1 = create_gray_box();
    QLabel* cruiser_2 = create_gray_box();
    QLabel* cruiser_3 = create_gray_box();
    QLabel* cruiser_4 = create_white_box();
    QLabel* cruiser_5 = create_white_box();

    cruiser->addWidget(cruiser_1);
    cruiser->addWidget(cruiser_2);
    cruiser->addWidget(cruiser_3);
    cruiser->addWidget(cruiser_4);
    cruiser->addWidget(cruiser_5);

    QLabel* destroyer_1 = create_gray_box();
    QLabel* destroyer_2 = create_gray_box();
    QLabel* destroyer_3 = create_white_box();
    QLabel* destroyer_4 = create_white_box();
    QLabel* destroyer_5 = create_white_box();

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
    this->setLayout(main_layout);

    //This sets the initial values for the location of player and opponent
    location = new QPoint(0,0);
    std::uniform_int_distribution<int> unif_x(0,9);
    std::uniform_int_distribution<int> unif_y(0,9);
    int x=unif_x(generator_movement);
    int y=unif_y(generator_movement);
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
    //player_hits=0;
    //opponent_hits=0;

    //This tells set_opponent_board function to store a copy of current QPoint
    reset=1;
}

GameboardMovement::~GameboardMovement()
{
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

    delete ui;
}

void GameboardMovement::updateLocation(int px, int py, int nx, int ny, std::vector<std::vector<QLabel*>>& grid, std::vector<std::vector<int>>& grid_type){
    grid[py][px]->clear();
    //if type grid denotes 0 set corresponding location to blue (not hit nor guessed)
    if(grid_type[py][px]==0){
        grid[py][px]->setStyleSheet("background-color:blue");
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

void GameboardMovement::set_location(){
    //if space type is 0 construct aircraft carrier
    if (space_type==0){
        int x=location->rx();
        int y=location->ry();
        //if player type denotes 0 location is empty and therefore valid
        if(player_type[y][x]==0 || player_type[y][x]==2){
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
        if(player_type[y][x]==0 || player_type[y][x]==2){
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
        if(player_type[y][x]==0 || player_type[y][x]==2){
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
        if(player_type[y][x]==0 || player_type[y][x]==2){
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
        if(player_type[y][x]==0 || player_type[y][x]==2){
            player_type[y][x]=2;
            player[y][x]->setStyleSheet("background-color:gray");
            destroyer_player_pos.push_back(new QPoint(x,y));
        }
    }
}

void GameboardMovement::paintEvent(QPaintEvent *event){
    //if mode is 0 player is moving through their own board
    if(mode==0){
        int x=location->rx();
        int y=location->ry();

        //if space type is 0 add black border to blue QLabel
        if(player_type[y][x]==0){
            player[y][x]->setStyleSheet("background-color:blue; border: 6px solid");
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

void GameboardMovement::keyPressEvent(QKeyEvent *event){
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

void GameboardMovement::showEvent(QShowEvent *event) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(event);
}

bool GameboardMovement::isValid_aircraft_carrier(){
    std::sort(aircraft_carrier_player_pos.begin(),aircraft_carrier_player_pos.end(),PointCompare());
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

bool GameboardMovement::isValid_battleship(){
    std::sort(battleship_player_pos.begin(),battleship_player_pos.end(),PointCompare());
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

bool GameboardMovement::isValid_submarine(){
    std::sort(submarine_player_pos.begin(),submarine_player_pos.end(),PointCompare());
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

bool GameboardMovement::isValid_cruiser(){
    std::sort(cruiser_player_pos.begin(),cruiser_player_pos.end(),PointCompare());
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

bool GameboardMovement::isValid_destroyer(){
    std::sort(destroyer_player_pos.begin(),destroyer_player_pos.end(),PointCompare());
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

bool GameboardMovement::set_opponent_aircraft_carrier(){
    //ensures that aircraft carrier vector is empty to begin with
    if(aircraft_carrier_opponent_pos.size()!=0){
        //returns to positions in aircraft carrier container and sets their type to empty
        for(size_t i=0;i<aircraft_carrier_opponent_pos.size();++i){
            int x=aircraft_carrier_opponent_pos[i]->rx();
            int y=aircraft_carrier_opponent_pos[i]->ry();
            opponent[y][x]->setStyleSheet("background-color:blue");
            opponent_type[y][x]=0;
        }
    }
    aircraft_carrier_opponent_pos=std::vector<QPoint*>(0);

    std::uniform_int_distribution<int> unif_orientation(0,1);
    int orientation=unif_orientation(generator_movement);

    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        std::uniform_int_distribution<int> unif_x(4,5);
        std::uniform_int_distribution<int> unif_y(0,9);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        std::uniform_int_distribution<int> unif_x(0,9);
        std::uniform_int_distribution<int> unif_y(4,5);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through aircraft carrier length set position
            for(size_t i=0;i<5;++i){
                aircraft_carrier_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

bool GameboardMovement::set_opponent_battleship(){
    //ensures that battleship vector is empty to begin with
    if(battleship_opponent_pos.size()!=0){
        //returns to positions in battleship container and sets their type to empty
        for(size_t i=0;i<battleship_opponent_pos.size();++i){
            int x=battleship_opponent_pos[i]->rx();
            int y=battleship_opponent_pos[i]->ry();
            opponent[y][x]->setStyleSheet("background-color:blue");
            opponent_type[y][x]=0;
        }
    }
    battleship_opponent_pos=std::vector<QPoint*>(0);

    std::uniform_int_distribution<int> unif_orientation(0,1);
    int orientation=unif_orientation(generator_movement);

    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        std::uniform_int_distribution<int> unif_x(3,6);
        std::uniform_int_distribution<int> unif_y(0,9);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        std::uniform_int_distribution<int> unif_x(0,9);
        std::uniform_int_distribution<int> unif_y(3,6);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through battleship length set position
            for(size_t i=0;i<4;++i){
                battleship_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

bool GameboardMovement::set_opponent_submarine(){
    //ensures that submarine vector is empty to begin with
    if(submarine_opponent_pos.size()!=0){
        //returns to positions in submarine vector and sets their type to empty
        for(size_t i=0;i<submarine_opponent_pos.size();++i){
            int x=submarine_opponent_pos[i]->rx();
            int y=submarine_opponent_pos[i]->ry();
            opponent[y][x]->setStyleSheet("background-color:blue");
            opponent_type[y][x]=0;
        }
    }
    submarine_opponent_pos=std::vector<QPoint*>(0);

    std::uniform_int_distribution<int> unif_orientation(0,1);
    int orientation=unif_orientation(generator_movement);

    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        std::uniform_int_distribution<int> unif_x(2,7);
        std::uniform_int_distribution<int> unif_y(0,9);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        std::uniform_int_distribution<int> unif_x(0,9);
        std::uniform_int_distribution<int> unif_y(2,7);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through submarine length set position
            for(size_t i=0;i<3;++i){
                submarine_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

bool GameboardMovement::set_opponent_cruiser(){
    //ensures that cruiser vector is empty to begin with
    if(cruiser_opponent_pos.size()!=0){
        //returns to positions in cruiser vector and sets their type to empty
        for(size_t i=0;i<cruiser_opponent_pos.size();++i){
            int x=cruiser_opponent_pos[i]->rx();
            int y=cruiser_opponent_pos[i]->ry();
            opponent[y][x]->setStyleSheet("background-color:blue");
            opponent_type[y][x]=0;
        }
    }
    cruiser_opponent_pos=std::vector<QPoint*>(0);

    std::uniform_int_distribution<int> unif_orientation(0,1);
    int orientation=unif_orientation(generator_movement);

    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        std::uniform_int_distribution<int> unif_x(2,7);
        std::uniform_int_distribution<int> unif_y(0,9);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        std::uniform_int_distribution<int> unif_x(0,9);
        std::uniform_int_distribution<int> unif_y(2,7);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through cruiser length set position
            for(size_t i=0;i<3;++i){
                cruiser_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

bool GameboardMovement::set_opponent_destroyer(){
    //ensures that destroyer vector is empty to begin with
    if(destroyer_opponent_pos.size()!=0){
        //returns to positions in destroyer vector and sets their types to empty
        for(size_t i=0;i<destroyer_opponent_pos.size();++i){
            int x=destroyer_opponent_pos[i]->rx();
            int y=destroyer_opponent_pos[i]->ry();
            opponent[y][x]->setStyleSheet("background-color:blue");
            opponent_type[y][x]=0;
        }
    }
    destroyer_opponent_pos=std::vector<QPoint*>(0);

    std::uniform_int_distribution<int> unif_orientation(0,1);
    int orientation=unif_orientation(generator_movement);

    //if orientation is 0 proceed horizontal from coordinates
    if(orientation==0){
        std::uniform_int_distribution<int> unif_x(1,8);
        std::uniform_int_distribution<int> unif_y(0,9);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed to right of coordinates
        if(above_below==0){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++x;
            }
        }
        //if above_below is 1 proceed to left of coordinates
        else if(above_below==1){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --x;
            }
        }
    }
    //1 is vertical
    else if(orientation==1){
        std::uniform_int_distribution<int> unif_x(0,9);
        std::uniform_int_distribution<int> unif_y(1,8);
        std::uniform_int_distribution<int> unif_above_below(0,1);

        int x=unif_x(generator_movement);
        int y=unif_y(generator_movement);
        int above_below=unif_above_below(generator_movement);

        //if above_below is 0 proceed upwards of coordinates
        if(above_below==0){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                ++y;
            }
        }
        //if above_below is 1 proceed downwards of coordinates
        else if(above_below==1){
            //iterates through destroyer length set position
            for(size_t i=0;i<2;++i){
                destroyer_opponent_pos.push_back(new QPoint(x,y));
                opponent[y][x]->setStyleSheet("background-color:gray");
                opponent_type[y][x]=2;
                --y;
            }
        }
    }
    return true;
}

void GameboardMovement::set_aircraft_carrier(){
    space_type = 0;
    this->setFocus();
}

void GameboardMovement::set_battleship(){
    space_type = 1;
    this->setFocus();
}

void GameboardMovement::set_submarine(){
    space_type = 2;
    this->setFocus();
}

void GameboardMovement::set_cruiser(){
    space_type = 3;
    this->setFocus();
}

void GameboardMovement::set_destroyer(){
    space_type = 4;
    this->setFocus();
}

void GameboardMovement::start_game(){
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
        //if player type is 2 set to gray
        if(player_type[y][x]==2){
            player[y][x]->setStyleSheet("background-color:gray");
        }
        //if player type is 3 set to red
        if(player_type[y][x]==3){
            player[y][x]->setStyleSheet("background-color:red");
        }

        set_direction(aircraft_carrier_player_pos,direction_movement_aircraft_carrier);
        set_direction(aircraft_carrier_opponent_pos,direction_movement_aircraft_carrier_opponent);
        set_direction(battleship_player_pos,direction_movement_battleship);
        set_direction(battleship_opponent_pos,direction_movement_battleship_opponent);
        set_direction(submarine_player_pos,direction_movement_submarine);
        set_direction(submarine_opponent_pos,direction_movement_submarine_opponent);
        set_direction(cruiser_player_pos,direction_movement_cruiser);
        set_direction(cruiser_opponent_pos,direction_movement_cruiser_opponent);
        set_direction(destroyer_player_pos,direction_movement_destroyer);
        set_direction(destroyer_opponent_pos,direction_movement_destroyer_opponent);

        aircraft_carrier_player_hit=std::vector<bool>(5,false);
        aircraft_carrier_opponent_hit=std::vector<bool>(5,false);
        battleship_player_hit=std::vector<bool>(4,false);
        battleship_opponent_hit=std::vector<bool>(4,false);
        submarine_player_hit=std::vector<bool>(3,false);
        submarine_opponent_hit=std::vector<bool>(3,false);
        cruiser_player_hit=std::vector<bool>(3,false);
        cruiser_opponent_hit=std::vector<bool>(3,false);
        destroyer_player_hit=std::vector<bool>(2,false);
        destroyer_opponent_hit=std::vector<bool>(2,false);

        std::sort(aircraft_carrier_opponent_pos.begin(),aircraft_carrier_opponent_pos.end(),PointCompare());
        std::sort(battleship_opponent_pos.begin(),battleship_opponent_pos.end(),PointCompare());
        std::sort(submarine_opponent_pos.begin(),submarine_opponent_pos.end(),PointCompare());
        std::sort(cruiser_opponent_pos.begin(),cruiser_opponent_pos.end(),PointCompare());
        std::sort(destroyer_opponent_pos.begin(),destroyer_opponent_pos.end(),PointCompare());
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
        error_message = new QLabel("Invalid placement of ships. Please try again");
        error_message->setStyleSheet("font: bold 28px");
        error_message->show();

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

void GameboardMovement::set_opponent_board(){
    clear_opponent_board();
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

void GameboardMovement::clear_opponent_board(){
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
    aircraft_carrier_opponent_pos=std::vector<QPoint*>(0);
    battleship_opponent_pos=std::vector<QPoint*>(0);
    submarine_opponent_pos=std::vector<QPoint*>(0);
    cruiser_opponent_pos=std::vector<QPoint*>(0);
    destroyer_opponent_pos=std::vector<QPoint*>(0);
}

QLabel* GameboardMovement::create_gray_box(){
    QLabel* gray_box = new QLabel;
    gray_box->setMinimumSize(20,20);
    gray_box->setMaximumSize(20,20);
    gray_box->setStyleSheet("background-color:gray");
    gray_box->setAlignment(Qt::AlignCenter);
    return gray_box;
}

QLabel* GameboardMovement::create_white_box(){
    QLabel* white_box = new QLabel;
    white_box->setMinimumSize(20,20);
    white_box->setMaximumSize(20,20);
    white_box->setStyleSheet("background-color:white");
    white_box->setAlignment(Qt::AlignCenter);
    return white_box;
}

void GameboardMovement::guess_location(){
    int x=location->rx();
    int y=location->ry();

    //if mode is 2 ship is in location and registers a hit
    //increments tally of ships player has hit
    if(opponent_type[y][x]==2){
        opponent_type[y][x]=3;
        opponent[y][x]->setStyleSheet("background-color:red");
        for(size_t i=0; i<5; ++i){
            int x_ship=aircraft_carrier_opponent_pos[i]->rx();
            int y_ship=aircraft_carrier_opponent_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                aircraft_carrier_opponent_hit[i]=true;
                //++player_hits;
            }
        }
        for(size_t i=0; i<4; ++i){
            int x_ship=battleship_opponent_pos[i]->rx();
            int y_ship=battleship_opponent_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                battleship_opponent_hit[i]=true;
                //++player_hits;
            }
        }
        for(size_t i=0; i<3; ++i){
            int x_ship=submarine_opponent_pos[i]->rx();
            int y_ship=submarine_opponent_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                submarine_opponent_hit[i]=true;
                //++player_hits;
            }
        }
        for(size_t i=0; i<3; ++i){
            int x_ship=cruiser_opponent_pos[i]->rx();
            int y_ship=cruiser_opponent_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                cruiser_opponent_hit[i]=true;
                //++player_hits;
            }
        }
        for(size_t i=0; i<2; ++i){
            int x_ship=destroyer_opponent_pos[i]->rx();
            int y_ship=destroyer_opponent_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                destroyer_opponent_hit[i]=true;
                //++player_hits;
            }
        }
    }
    opponent_turn();
    victor();

    increment_ship(aircraft_carrier_player_pos,player_type,direction_movement_aircraft_carrier);
    increment_ship(battleship_player_pos,player_type,direction_movement_battleship);
    increment_ship(submarine_player_pos, player_type,direction_movement_submarine);
    increment_ship(cruiser_player_pos,player_type,direction_movement_cruiser);
    increment_ship(destroyer_player_pos,player_type,direction_movement_destroyer);

    increment_ship(aircraft_carrier_opponent_pos,opponent_type, direction_movement_aircraft_carrier_opponent);
    increment_ship(battleship_opponent_pos,opponent_type,direction_movement_battleship_opponent);
    increment_ship(submarine_opponent_pos,opponent_type,direction_movement_submarine_opponent);
    increment_ship(cruiser_opponent_pos,opponent_type,direction_movement_cruiser_opponent);
    increment_ship(destroyer_opponent_pos,opponent_type,direction_movement_destroyer_opponent);

    update_board();

    this->setFocus();
}

void GameboardMovement::opponent_turn(){
    std::uniform_int_distribution<int> unif_x(0,9);
    std::uniform_int_distribution<int> unif_y(0,9);

    int x=opponent_location->rx();
    int y=opponent_location->ry();

    //if ship has been iterated through completely reset is true and QPoint is set as current coordinates
    if(reset){
        opponent_location_storage=new QPoint(x,y);
    }

    //if type is 2 registers a hit (increments opponent_hit) and begins educated guess algorithm
    if(player_type[y][x]==2){
        reset=0;
        player[y][x]->setStyleSheet("background-color:red");
        player_type[y][x]=3;
        for(size_t i=0; i<5; ++i){
            int x_ship=aircraft_carrier_player_pos[i]->rx();
            int y_ship=aircraft_carrier_player_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                aircraft_carrier_player_hit[i]=true;
                //++opponent_hits;
            }
        }
        for(size_t i=0; i<4; ++i){
            int x_ship=battleship_player_pos[i]->rx();
            int y_ship=battleship_player_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                battleship_player_hit[i]=true;
                //++opponent_hits;
            }
        }
        for(size_t i=0; i<3; ++i){
            int x_ship=submarine_player_pos[i]->rx();
            int y_ship=submarine_player_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                submarine_player_hit[i]=true;
                //++opponent_hits;
            }
        }
        for(size_t i=0; i<3; ++i){
            int x_ship=cruiser_player_pos[i]->rx();
            int y_ship=cruiser_player_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                cruiser_player_hit[i]=true;
                //++opponent_hits;
            }
        }
        for(size_t i=0; i<2; ++i){
            int x_ship=destroyer_player_pos[i]->rx();
            int y_ship=destroyer_player_pos[i]->ry();
            if(x==x_ship && y==y_ship){
                destroyer_player_hit[i]=true;
                //++opponent_hits;
            }
        }
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
                        x=unif_x(generator_movement);
                        y=unif_y(generator_movement);
                        opponent_location=new QPoint(x,y);
                    }
                }
            }
        }
    }
    //if type is 0 registers a miss and sets coordinates to new random value
    //sets reset to 1 so that opponent location storage may be set to new value
    else if(player_type[y][x]==0){
        x=unif_x(generator_movement);
        y=unif_y(generator_movement);
        reset=1;
        opponent_location=new QPoint(x,y);
    }
}

bool GameboardMovement::opponent_guess_up(){
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

bool GameboardMovement::opponent_guess_down(){
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

bool GameboardMovement::opponent_guess_left(){
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

bool GameboardMovement::opponent_guess_right(){
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

void GameboardMovement::victor(){
    bool player_victory;
    bool opponent_victory;
    std::vector<bool> player_container (0);
    player_container.insert(player_container.end(),aircraft_carrier_opponent_hit.begin(), aircraft_carrier_opponent_hit.end());
    player_container.insert(player_container.end(),battleship_opponent_hit.begin(), battleship_opponent_hit.end());
    player_container.insert(player_container.end(),submarine_opponent_hit.begin(), submarine_opponent_hit.end());
    player_container.insert(player_container.end(),cruiser_opponent_hit.begin(), cruiser_opponent_hit.end());
    player_container.insert(player_container.end(),destroyer_opponent_hit.begin(), destroyer_opponent_hit.end());
    for(size_t i=0; i<17; ++i){
        player_victory=player_container[i];
        if(player_victory==false){
            break;
        }
    }
    //if player hits is 17 then the player has sunk all of the opponent's ships
    //prompts victory banner
    if(player_victory){
        victory=new QLabel("Congrats! You are the winner");
        victory->setStyleSheet("font:bold 32px");
        victory->show();
        return;
    }
    std::vector<bool> opponent_container (0);
    opponent_container.insert(opponent_container.end(),aircraft_carrier_player_hit.begin(), aircraft_carrier_player_hit.end());
    opponent_container.insert(opponent_container.end(),battleship_player_hit.begin(), battleship_player_hit.end());
    opponent_container.insert(opponent_container.end(),submarine_player_hit.begin(), submarine_player_hit.end());
    opponent_container.insert(opponent_container.end(),cruiser_player_hit.begin(), cruiser_player_hit.end());
    opponent_container.insert(opponent_container.end(),destroyer_player_hit.begin(), destroyer_player_hit.end());
    for(size_t i=0; i<17; ++i){
        opponent_victory=opponent_container[i];
        if(opponent_victory==false){
            break;
        }
    }
    //if opponent hits is 17 then the opponent has sunk all of the player's ships
    //prompts defeat banner
    if(opponent_victory){
        victory=new QLabel("The computer has won");
        victory->setStyleSheet("font:bold 32px");
        victory->show();
    }
}

void GameboardMovement::end_game(){
    parentWidget()->close();
}

void GameboardMovement::increment_ship(std::vector<QPoint*>& ship, std::vector< std::vector<int> >& owner_type, int& direction){
    int x = ship[ship.size()-1]->rx();
    int y = ship[ship.size()-1]->ry();
    //going left
    if(ship[0]->rx()==ship[1]->rx()-1 && direction==0){
        if(ship[0]->rx()==0){
            direction=1;
            increment_ship(ship, owner_type, direction);
        }
        for(size_t i=0; i<ship.size();++i){
            x=ship[i]->rx();
            y=ship[i]->ry();
            ship[i]=new QPoint(x-1, y);
            owner_type[y][x-1]=2;
        }
    }
    //going right
    else if(ship[0]->rx()==ship[1]->rx()-1 && direction==1){
        if(ship[ship.size()-1]->rx()==9){
            direction=0;
            increment_ship(ship, owner_type, direction);
        }
        for(size_t i=0; i<ship.size();++i){
            x=ship[i]->rx();
            y=ship[i]->ry();
            ship[i]=new QPoint(x+1, y);
            owner_type[y][x+1]=2;
        }
    }
    //going down
    else if(ship[0]->ry()==ship[1]->ry()-1 && direction==2){
        if(ship[ship.size()-1]->ry()==9){
            direction=3;
            increment_ship(ship, owner_type, direction);
        }
        for(size_t i=0; i<ship.size();++i){
            x=ship[i]->rx();
            y=ship[i]->ry();
            ship[i]=new QPoint(x, y+1);
            owner_type[y+1][x]=2;
        }
    }
    //going up
    else if(ship[0]->ry()==ship[1]->ry()-1 && direction==3){
        if(ship[0]->ry()==0){
            direction=2;
            increment_ship(ship, owner_type, direction);
        }
        for(size_t i=0; i<ship.size();++i){
            x=ship[i]->rx();
            y=ship[i]->ry();
            ship[i]=new QPoint(x, y-1);
            owner_type[y-1][x]=2;
        }
    }
}

void GameboardMovement::set_direction(std::vector<QPoint*>& ship, int& direction){
    int x_min = ship[0]->rx();
    int x_max = ship[ship.size()-1]->rx();
    int y_min = ship[0]->ry();
    int y_max = ship[ship.size()-1]->ry();

    if(ship[0]->rx()==ship[1]->rx()-1 && x_min==0){
        direction=1;
        return;
    }
    if(ship[0]->rx()==ship[1]->rx()-1 && x_max==9){
        direction=0;
        return;
    }
    if(ship[0]->rx()==ship[1]->rx()-1){
        direction=0;
        return;
    }

    if(ship[0]->ry()==ship[1]->ry()-1 && y_min==0){
        direction=2;
        return;
    }
    if(ship[0]->ry()==ship[1]->ry()-1 && y_max==9){
        direction=3;
        return;
    }
    if(ship[0]->ry()==ship[1]->ry()-1){
        direction=2;
        return;
    }
}

void GameboardMovement::update_board(){
    for(size_t i=0; i<10; ++i){
        for(size_t j=0; j<10; ++j){
            player[j][i]->clear();
            opponent[j][i]->clear();
            player[j][i]->setStyleSheet("background-color:blue");
            opponent[j][i]->setStyleSheet("background-color:blue");
        }
    }
    update_ship(aircraft_carrier_player_pos,aircraft_carrier_player_hit,player,player_type);
    update_ship(battleship_player_pos,battleship_player_hit,player,player_type);
    update_ship(submarine_player_pos,submarine_player_hit,player,player_type);
    update_ship(cruiser_player_pos,cruiser_player_hit,player,player_type);
    update_ship(destroyer_player_pos,destroyer_player_hit,player,player_type);

    update_ship_opponent_board(aircraft_carrier_opponent_pos,aircraft_carrier_opponent_hit,opponent,opponent_type);
    update_ship_opponent_board(battleship_opponent_pos,battleship_opponent_hit,opponent,opponent_type);
    update_ship_opponent_board(submarine_opponent_pos,submarine_opponent_hit,opponent,opponent_type);
    update_ship_opponent_board(cruiser_opponent_pos,cruiser_opponent_hit,opponent,opponent_type);
    update_ship_opponent_board(destroyer_opponent_pos,destroyer_opponent_hit,opponent,opponent_type);
}

void GameboardMovement::update_ship(std::vector<QPoint*>& ship, std::vector<bool>& ship_hit, std::vector< std::vector<QLabel*> >& owner, std::vector< std::vector<int> >& owner_type){
    for(size_t i=0; i<ship_hit.size(); ++i){
        if(ship_hit[i]){
            int x=ship[i]->rx();
            int y=ship[i]->ry();
            owner[y][x]->setStyleSheet("background-color:red");
            owner_type[y][x]=3;
        }
        if(!ship_hit[i]){
            int x=ship[i]->rx();
            int y=ship[i]->ry();
            owner[y][x]->setStyleSheet("background-color:gray");
            owner_type[y][x]=2;
        }
    }
}

void GameboardMovement::update_ship_opponent_board(std::vector<QPoint*>& ship, std::vector<bool>& ship_hit, std::vector< std::vector<QLabel*> >& owner, std::vector< std::vector<int> >& owner_type){
    for(size_t i=0; i<ship_hit.size(); ++i){
        if(ship_hit[i]){
            int x=ship[i]->rx();
            int y=ship[i]->ry();
            owner[y][x]->setStyleSheet("background-color:red");
            owner_type[y][x]=3;
        }
        if(!ship_hit[i]){
            int x=ship[i]->rx();
            int y=ship[i]->ry();
            owner[y][x]->setStyleSheet("background-color:gray");
            owner_type[y][x]=2;
        }
    }
}

