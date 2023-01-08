#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    illu = new Illustrate;
    Level = new ChooseLevel;

    //设置固定大小
    setFixedSize(660,880);
    QSound *startSound = new QSound(":/music/LevelWinSound.wav");
    //设置图标
    setWindowIcon(QIcon(":/image/logo.jpg"));
    startSound->play();
    //设置标题
    setWindowTitle("记忆翻牌");
    connect(ui->actiontquit,&QAction::triggered,[=](){
            this->close();
    });
    connect(ui->actionshuoming,&QAction::triggered,[=](){
        this->hide();
        illu->show();

        connect(Level,&ChooseLevel::backSignal,[=](){
            Level->hide();
            this->show();
        });
    });
    connect(ui->Start,&QPushButton::clicked,[=](){
        this->hide();
        Level->show();
        connect(Level,&ChooseLevel::backSignal,this,[=](){
            Level->hide();
            this->show();
        });
    });
    connect(ui->illustrate,&QPushButton::clicked,[=](){
        this->hide();
        illu->show();
        connect(illu,&Illustrate::backSignal,this,[=](){
            illu->hide();
            this->show();
        });
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}
