#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<random>
#include<iostream>
#include<time.h>
#include<QLabel>
#include<QPushButton>
#include<QGridLayout>
#include<QWidget>
#include<QThread>
#include<QTimer>
#include<QMessageBox>
#include<QDebug>
#include<QGestureEvent>
#include<QSpacerItem>
#include<QtMultimedia/QSound>
#include<QSettings>



using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QLabel *sc;
    QWidget *widget;
    QPushButton *begin;
    int lenb=7;
    QPushButton *buttons[7][5];
    QGridLayout *layouts[7];
    int comp = 3;
    int downposition;
    QString colors[5];
    QString colors_base[5];
    int flag=0;
    QTimer *timer;
    QTimer *tim;
    int tt=300;
    int ttt=1;
    int rr = 0;
    QGridLayout *labels;
    QLabel *best;
    QSettings *settings;



    vector<int> generate(int what){
        int how = rand()%what;
        if(how==0)
            how=1;
        if(how>=4)
            how=3;
        vector<int>a;
        for(int i=0;i<=how;i++){
            a.push_back(rand()%what);
        }
        return a;
    }


    void set_default(int a, int b){
        buttons[a][b]->setStyleSheet("QPushButton { background-color: #FFFFFF; color: black; font:20pt; font-weight:400;border-radius: 5px;border:1px solid}");
    }

    void set_enabled(int a,int b, bool ka = true){
        buttons[a][b]->setEnabled(ka);
    }

    void set_black(int a,int b){
        buttons[a][b]->setStyleSheet("QPushButton { background-color: #000000; color: black; font:20pt; font-weight:400;border-radius: 5px;border:1px solid}");//#1C1C1C
    }

    void set_white(int a,int b){
        buttons[a][b]->setStyleSheet("QPushButton { background-color: #FFFFFF; color: white; font:20pt; font-weight:400;border-radius: 5px;border:1px solid;}");//#F8F8FF
    }

    void set_grey(int a,int b){
        buttons[a][b]->setStyleSheet("QPushButton { background-color: #e0e0e0; color: grey; font:20pt; font-weight:400;border-radius: 5px;border:1px solid}");
    }

    void set_red(int a,int b){
        buttons[a][b]->setStyleSheet("QPushButton { background-color: #EE2C2C;color: red;  font:20pt; font-weight:400; border-radius: 5px;border:1px solid}");
    }

    void swap(int a, int b){//swap colors of buttons
        if(colors[b]=="white")
            set_white(a+1,b);
        else if(colors[b]=="black")
            set_black(a+1,b);
        else{}
        set_default(a,b);
    }

    void create(){//create new squares on up
        if(get_score()>=10&&comp==3){//открываем 5ую плитку
            comp++;
            set_enabled(lenb-1,4);
            set_white(lenb-1,4);
            colors_base[4]="white";
        }else if(get_score()>=30&&comp==4){//открываем первую плитку
            comp++;
            set_enabled(lenb-1,0);
            set_white(lenb-1,0);
            colors_base[0]="white";
        }
        vector<int>n = generate(comp);
        int b=0;
        if(comp==3||comp==4)
            b=1;
        for(int i=b;i<b+comp;i++){
            set_white(downposition,i);
            colors[i]="white";
            set_white(lenb-1,i);
            colors_base[i]="white";
        }
        for(int i=0;i<(signed)n.size();i++){
            set_black(downposition,n[i]+b);
            colors[n[i]+b]="black";
        }
        for(int i=0;i<5;i++){
            if(i<b||i>=b+comp)
                colors[i]="default";
        }
        flag=downposition;
    }

    void swap_row(int a){
        for(int i=0;i<5;i++){
            swap(a,i);
        }
    }

    void do_down(){//make down all squares
        int b=0;
        if(comp==3||comp==4)
            b=1;
        for(int i=b;i<b+comp;i++){
            if(colors[i]!=colors_base[i]){
                play_bad_connect();
                for(int i=0;i<5;i++){
                    set_grey(downposition,i);
                }
                for(int i=0;i<5;i++){
                    set_default(lenb-2,i);
                }
                downposition++;
                tt+=40;
                return;
            }
        }
        for(int i=0;i<5;i++){
            set_default(lenb-2,i);
        }
        play_good_connect();
        if(tt>200)
            tt-=10;
        sc->setText("Score\n "+QString::number(get_score()+comp));
    }

    int get_score(){
        QString score = sc->text();
        QString tmp;
        for(int i=7;i<score.size();i++)
            tmp+=score[i];
        return tmp.toInt();
    }

    int get_best(){
        QString b = best->text();
        QString tmp;
        for(int i=5;i<b.size();i++)
            tmp+=b[i];
        return tmp.toInt();
    }

    void create_base(){//creat base squares at the beginning of game
        for(int i=0;i<lenb-1;i++){
            for(int j=0;j<5;j++){
                set_enabled(i,j,false);
            }
        }
        for(int i=0;i<5;i++){
            set_enabled(lenb-1,i);
        }
        set_grey(lenb-1,0);
        set_enabled(lenb-1,0,false);
        colors_base[0]="grey";
        set_grey(lenb-1,4);
        set_enabled(lenb-1,4,false);
        colors_base[4]="grey";
        for(int i=1;i<4;i++){
                set_white(lenb-1,i);
                colors_base[i]="white";
        }

    }

    void change(int a, int b){
        QString c = buttons[a][b]->styleSheet();
        QString u="";
        for(int i=48;i<53;i++){
            u+=c[i];
        }
        if(u=="white"){
            set_black(a,b);
            colors_base[b]="black";
        }else if(u=="black"){
            set_white(a,b);
            colors_base[b]="white";
        }
    }



private slots:

    void begin_new_game(){
        flag=0;
        tt=300;
        comp=3;
        play_begin_game();
        sc->setText("Score\n 0");
        for(int i=0;i<lenb;i++){
            for(int j=0;j<5;j++){
                set_default(i,j);
            }
        }
        downposition=0;
        create_base();
        create();
        timer->start(tt);
        tim->start(ttt);

    }

    void pr(){//paint every tt time by the help of timer
        timer->stop();
        timer->start(tt);
        if(downposition==lenb-2){
            timer->stop();
            play_end_game();
            if(get_score()>get_best()){
                best->setText("Best\n "+QString::number(get_score()));
                settings->beginGroup("record");
                settings->setValue("best",get_score());
                settings->endGroup();
            }
            QMessageBox *msg = new QMessageBox;
            msg->setText("You lose! Your score is "+QString::number(get_score()));
            msg->setWindowTitle("LOSE");
            msg->exec();
            return;
        }
        if(flag==lenb-2){
            do_down();
            create();
        }
        else{
            swap_row(flag);
            flag++;
        }
    }

    void ch(){
        tim->stop();
        tim->start(ttt);
    }

    void play_begin_game(){
        QSound::play(":/new/sounds/musc/begin_game.wav");
    }

    void play_end_game(){
        QSound::play(":/new/sounds/musc/end_game.wav");
    }

    void play_good_connect(){
        QSound::play(":/new/sounds/musc/good_connect.wav");
    }
    void play_bad_connect(){
        QSound::play(":/new/sounds/musc/bad_connect.wav");
    }




    void x1_click(){
        change(0,0);
    }

    void x2_click(){
        change(0,1);
    }

    void x3_click(){
        change(0,2);
    }

    void x4_click(){
        change(0,3);
    }

    void x5_click(){
        change(0,4);
    }
    void x6_click(){
        change(1,0);
    }

    void x7_click(){
        change(1,1);
    }

    void x8_click(){
        change(1,2);
    }

    void x9_click(){
        change(1,3);
    }

    void x10_click(){
        change(1,4);
    }
    void x11_click(){
        change(2,0);
    }

    void x12_click(){
        change(2,1);
    }

    void x13_click(){
        change(2,2);
    }

    void x14_click(){
        change(2,3);
    }

    void x15_click(){
        change(2,4);
    }
    void x16_click(){
        change(3,0);
    }

    void x17_click(){
        change(3,1);
    }

    void x18_click(){
        change(3,2);
    }

    void x19_click(){
        change(3,3);
    }

    void x20_click(){
        change(3,4);
    }
    void x21_click(){
        change(4,0);
    }

    void x22_click(){
        change(4,1);
    }

    void x23_click(){
        change(4,2);
    }

    void x24_click(){
        change(4,3);
    }

    void x25_click(){
        change(4,4);
    }
    void x26_click(){
        change(5,0);
    }

    void x27_click(){
        change(5,1);
    }

    void x28_click(){
        change(5,2);
    }

    void x29_click(){
        change(5,3);
    }

    void x30_click(){
        change(5,4);
    }
    void x31_click(){
        change(6,0);
    }

    void x32_click(){
        change(6,1);
    }

    void x33_click(){
        change(6,2);
    }

    void x34_click(){
        change(6,3);
    }

    void x35_click(){
        change(6,4);
    }

};

#endif // MAINWINDOW_H
