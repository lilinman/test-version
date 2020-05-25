#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>     //画家
#include <QMouseEvent>  //鼠标事件
#include <Qtimer>       //定时器
#include <QLabel>
#include<vector>
#include<QString>
#include<iostream>
using namespace std;
#include"enemy.h"
const int positionSIZE=10;
const int imgSIZE=30; //图片缩放比例
const int per_WIDTH=35;//35*30画面宽
const int per_HEIGHT=20;//20*30画面高



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVector<Enemy*> EnemyVec;           //怪物数组
    bool inGame;
    int a=10;
    int count = 0;    //敌人计数器
    int timerId1; //第1个时间控制器，可以控制页面的响应操作
    int timerId2;
    int DELAY=100;
protected:
    void CreatEnemyWave();
    void timerEvent(QTimerEvent *e);
    void DrawEnemy(QPainter&);            //画出怪物
    void paintEvent(QPaintEvent *);
    void DrawMapArr(QPainter&);             //用于画出地图函数
    void CreatEnemy(Point waypoint[],int len,int x,int y,int id);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;//计时器？

};



#endif // MAINWINDOW_H
