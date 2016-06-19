#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);;
    // Enable the event Filter
    qApp->installEventFilter(this);//安裝事件過濾器在this
    exi = new QPushButton(this);
    exi->setStyleSheet("border-image:url(:/image/exit.png);}");
    exi->setGeometry(QRect(QPoint(850,0),QSize(75,75)));
    connect(exi,SIGNAL(released()),this,SLOT(QUIT()));
    restart = new QPushButton(this);
    restart->setStyleSheet("border-image:url(:/image/restart.png);}");
    restart->setGeometry(QRect(QPoint(850,75),QSize(75,75)));
    score = 0;
    text = new QTextEdit(this);
    text->setPlainText(QString("Score :"+QString::number(score)));
    text->setFont(QFont("Arial",10));
    text->cursorForPosition(QPoint(0,0));
    connect(restart,SIGNAL(released()),this,SLOT(NEW()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    timecheck1 = 0;
    timerclose = 0;
    laugh = 0;
    timecheck = 0;
    test = 0;
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    //lis = new con();
    //world->SetContactListener(lis);
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());//將QTsize和box2d的size傳到setglobalsize
    // Create ground (You can edit here)
    itemList.push_back(new bg(16,9,32,18,QPixmap(":/image/PIGLANTIS_SKY.png").scaled(width(),height()),world,scene));
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width()/32*32,height()/18*3),world,scene));
    itemList.push_back(new Land(16,18,32,0.1,QPixmap(":/ground.png").scaled(0,0),world,scene));
    // Create bird (You can edit here)
    shoot = new building(5.5f,5.0f,3.0f,5.0f,&timer,QPixmap("://image/shooter.png").scaled(width()/32*3.0,height()/18*5.0),world,scene,5000);
    build = new building(18.0f,4.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,120.0);
    build1 = new building(18.0f,7.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,120.0);
    build2 = new building(28.0f,4.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,120.0);
    build3 = new building(28.0f,7.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,1000.0);
    build4 = new building(23.0f,9.5f,13.0f,1.0f,&timer,QPixmap(":/image/BLOCK_ROCK_10X1_1.png").scaled(width()/32*13.0,height()/18*1.0),world,scene,25.0);
    ba = new bad(23.0f,4.0f,2.0f,&timer,QPixmap(":/image/7363e3ae596cecf19d16b41b3bc9a317.png").scaled(width()/32*4,height()/18*4),world,scene,180);
    /*birdie1 = new Bird(4.1f,3.0f,0.5f,&timer,QPixmap(":/image/red.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird1 = new superbird(2.8f,3.0f,0.5f,&timer,QPixmap(":/image/dd7722fb6953a171183c01f26d0b37a0.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird2 = new superbird1(1.5f,3.0f,0.5f,&timer,QPixmap(":/image/blue.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird4 = new superbird2(0.2f,3.0f,0.5f,&timer,QPixmap(":/image/fire.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);*/
    //sco = new score();
    birdie = new Bird(5.5f,8.0f,1.0f,&timer,QPixmap(":/image/red.png").scaled(width()/32*2,height()/18*2),world,scene,50);
    subird = new superbird(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    subird3 = new superbird1(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    subird5 = new superbird2(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    ti = new QTimer(this);
    biti = new QTimer(this);
    biti1 = new QTimer(this);
    biti2 = new QTimer(this);
    biti3 = new QTimer(this);
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(test == 1)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            orix = e->globalX();
            oriy = e->globalY();
            test = 2;
        }
        if(test == 3)
        {
            test = 4;
        }
        if(test == 5)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            orix = e->globalX();
            oriy = e->globalY();
            test = 6;
        }
        if(test == 7)
        {
            subird->supergo();
            delete biti1;
            biti1 = new QTimer(this);
            connect(biti1,SIGNAL(timeout()),this,SLOT(checkbird1()));
            biti1->start(1000);
            test = 8;
        }
        if(test == 10)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            orix = e->globalX();
            oriy = e->globalY();
            test = 11;
        }
        if(test == 12)
        {
            subird3->supergo();
            delete biti2;
            biti2 = new QTimer(this);
            connect(biti2,SIGNAL(timeout()),this,SLOT(checkbird2()));
            biti2->start(1000);
            test = 13;
        }
        if(test == 15)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            orix = e->globalX();
            oriy = e->globalY();
            test = 16;
        }
        if(test == 17)
        {
            subird5->supergo();
            delete biti3;
            biti3 = new QTimer(this);
            connect(biti3,SIGNAL(timeout()),this,SLOT(checkbird3()));
            biti3->start(1000);
            test = 18;
        }
    }

    if(event->type() == QEvent::MouseMove)
    {
        if(test == 1)
        {
        }
    }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(test == 0)
        {
            ha = new bg(16,9,32,18,QPixmap(":/image/hqdefault.jpg").scaled(0,0),world,scene);
            //delete birdie1;

            test = 1;
        }
        if(test == 2)
        {
            timerclose = 0;
            delete ti;
            ti = new QTimer(this);
            connect(ti , SIGNAL(timeout()) , this , SLOT(advance()));
            ti->start(1000);
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            rex = e->globalX();
            rey = e->globalY();
            vx = (orix - rex)/20;
            vy = (-oriy + rey)/20;
            birdie->setLinearVelocity(b2Vec2(vx,vy));
            itemList.push_back(birdie);
            delete biti;
            biti = new QTimer(this);
            connect(biti,SIGNAL(timeout()),this,SLOT(checkbird()));
            biti->start(1000);
            test = 3;
        }
        if(test == 4)
        {
            delete subird;
            subird = new superbird(5.5f,8.0f,1.0f,&timer,QPixmap(":/image/dd7722fb6953a171183c01f26d0b37a0.png").scaled(width()/32*2,height()/18*2),world,scene,50);
            test = 5;
        }
        if(test == 6)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            rex = e->globalX();
            rey = e->globalY();
            vx = (orix - rex)/20;
            vy = (-oriy + rey)/20;
            subird->setLinearVelocity(b2Vec2(vx,vy));
            itemList.push_back(subird);
            test = 7;
        }
        if(test == 8)
        {
            test = 9;
        }
        if(test == 9)
        {
            delete subird3;
            subird3 = new superbird1(5.5f,8.0f,1.0f,&timer,QPixmap(":/image/blue.png").scaled(width()/32*2,height()/18*2),world,scene,50);
            test = 10;
        }
        if(test == 11)
        {
                QMouseEvent *e = static_cast<QMouseEvent *>(event);
                rex = e->globalX();
                rey = e->globalY();
                vx = (orix - rex)/20;
                vy = (-oriy + rey)/20;
                subird3->setLinearVelocity(b2Vec2(vx,vy));
                itemList.push_back(subird3);
                test = 12;
        }
        if(test == 13)
        {
            test = 14;
        }
        if(test == 14)
        {
            delete subird5;
            subird5 = new superbird2(5.5f,8.0f,1.0f,&timer,QPixmap(":/image/fire.png").scaled(width()/32*2,height()/18*2),world,scene,50);
            test = 15;
        }
        if(test == 16)
        {
                QMouseEvent *e = static_cast<QMouseEvent *>(event);
                rex = e->globalX();
                rey = e->globalY();
                vx = (orix - rex)/20;
                vy = (-oriy + rey)/20;
                subird5->setLinearVelocity(b2Vec2(vx,vy));
                itemList.push_back(subird5);
                test = 17;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    std::cout << "Quit Game Signal receive !" << std::endl;
    exit(0);
}
void MainWindow::QUIT()
{
    emit quitGame();
}

void MainWindow::NEW()
{
    timerclose = 1;
    std::cout<<"12t3"<<std::endl;
    delete build;
    delete build1;
    delete build2;
    delete build3;
    std::cout<<"12t3"<<std::endl;
    delete build4;
    delete ba;
    std::cout<<"12t3"<<std::endl;
    delete birdie;
    delete subird;
    delete subird3;
    std::cout<<"12t3"<<std::endl;
    delete subird5;
    if(laugh == 0)
    {
        delete ha;
    }

    std::cout<<"12t3"<<std::endl;
    delete ti;
    delete biti;
    delete biti1;
    delete biti2;
    delete biti3;
    delete shoot;
    laugh = 0;
    test = 0;
    timecheck = 0;
    timecheck1 = 0;
    build = new building(18.0f,4.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,12.0);
    build1 = new building(18.0f,7.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,12.0);
    build2 = new building(28.0f,4.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,12.0);
    build3 = new building(28.0f,7.5f,2.0f,3.0f,&timer,QPixmap(":/image/wood.png").scaled(width()/32*2.0,height()/18*3.0),world,scene,12.0);
    build4 = new building(23.0f,9.5f,13.0f,1.0f,&timer,QPixmap(":/image/BLOCK_ROCK_10X1_1.png").scaled(width()/32*13.0,height()/18*1.0),world,scene,25.0);
    ba = new bad(23.0f,3.0f,2.0f,&timer,QPixmap(":/image/7363e3ae596cecf19d16b41b3bc9a317.png").scaled(width()/32*4,height()/18*4),world,scene,180);
    birdie = new Bird(5.5f,8.0f,1.0f,&timer,QPixmap(":/image/red.png").scaled(width()/32*2,height()/18*2),world,scene,50);
    subird = new superbird(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    subird3 = new superbird1(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    subird5 = new superbird2(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    /*birdie1 = new Bird(4.1f,3.0f,0.5f,&timer,QPixmap(":/image/red.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird1 = new superbird(2.8f,3.0f,0.5f,&timer,QPixmap(":/image/dd7722fb6953a171183c01f26d0b37a0.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird2 = new superbird1(1.5f,3.0f,0.5f,&timer,QPixmap(":/image/blue.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);
    subird4 = new superbird2(0.2f,3.0f,0.5f,&timer,QPixmap(":/image/fire.png").scaled(width()/32*1.0,height()/18*1.0),world,scene,500);*/
    shoot = new building(5.5f,5.0f,3.0f,5.0f,&timer,QPixmap("://image/shooter.png").scaled(width()/32*3.0,height()/18*5.0),world,scene,5000);
    ti = new QTimer(this);
    biti = new QTimer(this);
    biti1 = new QTimer(this);
    biti2 = new QTimer(this);
    biti3 = new QTimer(this);
    score = 0;
    text->setPlainText(QString("Score :"+QString::number(score)));
}

void MainWindow::advance()
{
    timecheck++;
    if(timecheck >= 3)
    {
        if(ba->getvelocity())
        {
            laugh = 1;
            delete ba;
            ba = new bad(25.0f,4.0f,0.0f,&timer,QPixmap(":/image/7363e3ae596cecf19d16b41b3bc9a317.png").scaled(0,0),world,scene,180);
            score = 100;
            text->setPlainText(QString("Score :"+QString::number(score)));
        }
    }
}
void MainWindow::checkbird()
{
    if(birdie->disapp())
    {
        delete birdie;
        birdie = new Bird(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    }
}
void MainWindow::checkbird1()
{
    if(subird->disapp())
    {
        delete subird;
        subird = new superbird(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    }
}
void MainWindow::checkbird2()
{
    if(subird3->disapp())
    {
        delete subird3;
        subird3 = new superbird1(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    }
}
void MainWindow::checkbird3()
{
    timecheck1++;
    if(subird5->disapp())
    {
        if(laugh == 0&&timecheck1 > 2)
        {
            delete ha;
            ha = new bg(16,9,32,18,QPixmap(":/image/hqdefault.jpg").scaled(width(),height()),world,scene);
        }
        delete subird5;
        subird5 = new superbird2(5.5f,8.0f,0.0f,&timer,QPixmap(":/image/red.png").scaled(0,0),world,scene,100);
    }
}
