#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include<QTimer>
#include"enemy.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerId1 = startTimer(100);
    timerId2 = startTimer(1600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatEnemy(Point waypoint[], int len, int x, int y,int id){
    EnemyVec.push_back(new Enemy(waypoint,len,x,y,id));//新建敌人
}
void MainWindow::CreatEnemyWave(){
    Point  Path[]={
                    Point(21*positionSIZE,11*positionSIZE),//第一个节点
                    Point(6*positionSIZE,11*positionSIZE),//第二个节点
                    Point(6*positionSIZE,34*positionSIZE),//第三个节点
                    Point(21*positionSIZE,34*positionSIZE),//第四个节点
                    Point(21*positionSIZE,44*positionSIZE),//第五个节点
                    Point(43*positionSIZE,44*positionSIZE),//第六个节点
                    Point(43*positionSIZE,34*positionSIZE),//第七个节点
                    Point(57*positionSIZE,34*positionSIZE),//8
                    Point(57*positionSIZE,20*positionSIZE),//9
                    Point(83*positionSIZE,20*positionSIZE),//10
                    Point(83*positionSIZE,8*positionSIZE),//11
                    Point(97*positionSIZE,8*positionSIZE)//终点
                   };

    Point startpoint(21*positionSIZE,0);//起点

    if(count>=0&&count<=5)
       CreatEnemy(Path,12,startpoint.x,startpoint.y,1);
    if(count>=6&&count<=12)
       CreatEnemy(Path,12,startpoint.x,startpoint.y,2);
    count++;

}
void MainWindow::DrawEnemy(QPainter& painter){
    for(auto e=EnemyVec.begin();e!=EnemyVec.end();e++)
               (*e)->Draw(painter);

    for (auto e = EnemyVec.begin(); e != EnemyVec.end(); e++)
        if((*e)->Move()) //怪物走到终点
        {
            delete *e;
            EnemyVec.erase(e);         //怪物走到终点则删除这个怪物
            break;
        }
}

void MainWindow::DrawMapArr(QPainter& painter)
{
    painter.drawPixmap(0, 0, imgSIZE*per_WIDTH, imgSIZE*per_HEIGHT,
        QPixmap(":/pics/imgs/背景.png"));
    //地图数组
    int Map[per_HEIGHT][per_WIDTH] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,1,1,1,1,0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,1,1,1,1,0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 6, 0,0,0,0,0,0,0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,
    };
    for (int j = 0; j < per_HEIGHT; j++)
        for (int i = 0; i < per_WIDTH; i++)
        {
            switch (Map[j][i])
            {
            case 1:     /*地面*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE, imgSIZE,
                    QPixmap(":/pics/imgs/地砖2.png"));
                break;
            case 2:     /*蓝色云1*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*3, imgSIZE*2,
                    QPixmap(":/pics/imgs/蓝色云1.png"));
                break;
            case 3:     /*蓝色云2*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*4, imgSIZE*2,
                    QPixmap(":/pics/imgs/蓝色云2.png"));
                break;
            case 4:     /*粉色云*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*3, imgSIZE*2,
                    QPixmap(":/pics/imgs/粉色云.png"));
                break;
            case 5:     /*热气球*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*4.5, imgSIZE*5.5,
                    QPixmap(":/pics/imgs/热气球.png"));
                break;
            case 6:     /*热气球*/
                painter.drawPixmap(i * imgSIZE, j * imgSIZE, imgSIZE*6, imgSIZE*8,
                    QPixmap(":/pics/imgs/热气球.png"));
                break;
            }
        }

    }

void MainWindow::paintEvent(QPaintEvent *)
{

    move(400,120);//窗口位置
    setFixedSize(imgSIZE*per_WIDTH, per_HEIGHT*imgSIZE);//窗口大小
    QPainter painter(this);     //创建画家类
    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿
    DrawMapArr(painter);        //画出地图
    DrawEnemy(painter);
}

void MainWindow::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();
    if (inGame) {
        if(id == timerId2){
          CreatEnemyWave();
            }
        if(id == timerId1)
         repaint();
         }
}
