#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<time.h>
#include<QLabel>
#include<QPushButton>
#include<QGridLayout>
#include<QWidget>
#include<QTimer>
#include<QEvent>
#include<QGestureEvent>
#include<QHBoxLayout>
#include<QDesktopWidget>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings("settings.conf", QSettings::IniFormat);
    settings->beginGroup("record");
    int x = settings->value("best",0).toInt();
    settings->endGroup();

    sc = new QLabel("Score\n 0");
    begin = new QPushButton(" New\n Game");
    best = new QLabel("Best\n "+QString::number(x));
    sc->setStyleSheet("QLabel { background-color: #FFFFFF;border-radius: 5px;border:1px solid;}");
    best->setStyleSheet("QLabel { background-color: #FFFFFF;border-radius: 5px;border:1px solid;}");
    begin->setStyleSheet("QPushButton{background-color: #f00001;color : white; border-radius: 5px;text-align: left;}");
    for(int i=0;i<lenb;i++){
        for(int j=0;j<5;j++){
            buttons[i][j] = new QPushButton("");
            buttons[i][j]->setMaximumSize(QSize(1000,1000));
            set_default(i,j);
            set_enabled(i,j,false);
        }
    }
    sc->setMaximumSize(QSize(1000,1000));
    best->setMaximumSize(QSize(1000,1000));
    begin->setMaximumSize(QSize(1000,1000));

    labels=new QGridLayout;
    labels->addWidget(sc,0,3,1,1);
    labels->addWidget(best,0,6,1,1);
    labels->addWidget(begin,0,0,1,1);
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addSpacerItem(new QSpacerItem(0,50));
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addSpacerItem(new QSpacerItem(0,50));
    for(int i =0;i<lenb;i++){
        layouts[i] = new QGridLayout;
        for(int j=0;j<5;j++){
            layouts[i]->addWidget(buttons[i][j],i,j);
        }
    }
    QGridLayout *mam = new QGridLayout;
    mam->addLayout(labels,0,0);
    for(int i=0;i<lenb;i++){
        mam->addLayout(layouts[i],i+1,0);
    }
    mam->addLayout(layout2,8,0);
    widget = new QWidget;
    widget->setLayout(mam);
    widget->setStyleSheet("background-color:#f8f8f8;");
    setCentralWidget(widget);
    srand(time(0));

    QFont f;
    f.setPointSize(30);
    f.setBold(true);
    begin->setFont(f);
    sc->setFont(f);
    best->setFont(f);


    timer = new QTimer();
    tim = new QTimer();
    connect(begin,SIGNAL(pressed()),this,SLOT(begin_new_game()));
    connect(timer, SIGNAL(timeout()), this, SLOT(pr()));
    connect(tim, SIGNAL(timeout()), this, SLOT(ch()));

    connect(buttons[0][0],SIGNAL(pressed()),this,SLOT(x1_click()));
    connect(buttons[0][1],SIGNAL(pressed()),this,SLOT(x2_click()));
    connect(buttons[0][2],SIGNAL(pressed()),this,SLOT(x3_click()));
    connect(buttons[0][3],SIGNAL(pressed()),this,SLOT(x4_click()));
    connect(buttons[0][4],SIGNAL(pressed()),this,SLOT(x5_click()));
    connect(buttons[1][0],SIGNAL(pressed()),this,SLOT(x6_click()));
    connect(buttons[1][1],SIGNAL(pressed()),this,SLOT(x7_click()));
    connect(buttons[1][2],SIGNAL(pressed()),this,SLOT(x8_click()));
    connect(buttons[1][3],SIGNAL(pressed()),this,SLOT(x9_click()));
    connect(buttons[1][4],SIGNAL(pressed()),this,SLOT(x10_click()));
    connect(buttons[2][0],SIGNAL(pressed()),this,SLOT(x11_click()));
    connect(buttons[2][1],SIGNAL(pressed()),this,SLOT(x12_click()));
    connect(buttons[2][2],SIGNAL(pressed()),this,SLOT(x13_click()));
    connect(buttons[2][3],SIGNAL(pressed()),this,SLOT(x14_click()));
    connect(buttons[2][4],SIGNAL(pressed()),this,SLOT(x15_click()));
    connect(buttons[3][0],SIGNAL(pressed()),this,SLOT(x16_click()));
    connect(buttons[3][1],SIGNAL(pressed()),this,SLOT(x17_click()));
    connect(buttons[3][2],SIGNAL(pressed()),this,SLOT(x18_click()));
    connect(buttons[3][3],SIGNAL(pressed()),this,SLOT(x19_click()));
    connect(buttons[3][4],SIGNAL(pressed()),this,SLOT(x20_click()));
    connect(buttons[4][0],SIGNAL(pressed()),this,SLOT(x21_click()));
    connect(buttons[4][1],SIGNAL(pressed()),this,SLOT(x22_click()));
    connect(buttons[4][2],SIGNAL(pressed()),this,SLOT(x23_click()));
    connect(buttons[4][3],SIGNAL(pressed()),this,SLOT(x24_click()));
    connect(buttons[4][4],SIGNAL(pressed()),this,SLOT(x25_click()));
    connect(buttons[5][0],SIGNAL(pressed()),this,SLOT(x26_click()));
    connect(buttons[5][1],SIGNAL(pressed()),this,SLOT(x27_click()));
    connect(buttons[5][2],SIGNAL(pressed()),this,SLOT(x28_click()));
    connect(buttons[5][3],SIGNAL(pressed()),this,SLOT(x29_click()));
    connect(buttons[5][4],SIGNAL(pressed()),this,SLOT(x30_click()));
    connect(buttons[6][0],SIGNAL(pressed()),this,SLOT(x31_click()));
    connect(buttons[6][1],SIGNAL(pressed()),this,SLOT(x32_click()));
    connect(buttons[6][2],SIGNAL(pressed()),this,SLOT(x33_click()));
    connect(buttons[6][3],SIGNAL(pressed()),this,SLOT(x34_click()));
    connect(buttons[6][4],SIGNAL(pressed()),this,SLOT(x35_click()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


