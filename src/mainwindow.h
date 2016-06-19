#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QTextEdit>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <superbird.h>
#include <superbird1.h>
#include <superbird2.h>
#include <QPushButton>
#include <QApplication>
#include <bg.h>
#include <building.h>
#include <bad.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

        Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);//過濾條件判斷event是否會被執行
    void closeEvent(QCloseEvent *);//對關閉窗口消息進行攔截
    /*void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);*/
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void QUIT();
    void NEW();
    void advance();
    void checkbird();
    void checkbird1();
    void checkbird2();
    void checkbird3();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Bird *birdie;
    Bird *birdie1;
    bad *ba;
    superbird *subird;
    superbird *subird1;
    superbird1 *subird2;
    superbird1 *subird3;
    superbird2 *subird4;
    superbird2 *subird5;
    QPushButton *restart;
    QPushButton *exi;
    QTextEdit *text;
    building *shoot;
    building *build;
    building *build1;
    building *build2;
    building *build3;
    building *build4;
    bg *ha;
    QTimer *ti;
    QTimer *biti;
    QTimer *biti1;
    QTimer *biti2;
    QTimer *biti3;
    int timecheck;
    int timecheck1;
    int orix;
    int oriy;
    int rex;
    int rey;
    int mx;
    int my;
    int vx;
    int vy;
    int test;
    int test1;
    int laugh;
    int timerclose;
    int score;
};

#endif // MAINWINDOW_H
