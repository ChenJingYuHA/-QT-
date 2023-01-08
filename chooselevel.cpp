#include "chooselevel.h"

ChooseLevel::ChooseLevel(QWidget *parent) : QWidget(parent)
{
    //设置图标
    setWindowIcon(QIcon(":/image/logo.jpg"));
    //设置标题
    setWindowTitle("难度选择");
    //设置大小
    setFixedSize(660,880);
    level1 = new QPushButton();
    level1->setText(tr("初级"));
    level1->setMaximumSize(200,100);
    level1->setMinimumSize(200,100);
    level2 = new QPushButton();
    level2->setText(tr("中级"));
    level2->setMaximumSize(200,100);
    level2->setMinimumSize(200,100);

    level3 = new QPushButton();
    level3->setText(tr("高级"));
    level3->setMaximumSize(200,100);
    level3->setMinimumSize(200,100);


    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->setMaximumSize(150,80);
    back->setMinimumSize(150,80);
    back->setGeometry(this->width()-back->width()-30,this->height()-back->height()-30,200,100);
    connect(back,&QPushButton::clicked,[=](){
        emit this->backSignal();
    });
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(level1,0,0);
    mainLayout->addWidget(level2,1,0);
    mainLayout->addWidget(level3,2,0);
    mainLayout->addWidget(back,3,1);
    mainLayout->setSpacing(10);

    gameplay = new GamePlay;
    gameplay2 = new GamePlay2;
    gameplay3 = new GamePlay3;
    connect(level1,&QPushButton::clicked,[=](){
        this->hide();
        gameplay->show();
        connect(gameplay,&GamePlay::backSignal,this,[=](){
            this->show();
        });

    });

    connect(level2,&QPushButton::clicked,[=](){
        this->hide();
        gameplay2->show();
        connect(gameplay2,&GamePlay2::backSignal,this,[=](){
            this->show();
        });

    });
    connect(level3,&QPushButton::clicked,[=](){
        this->hide();
        gameplay3->show();
        connect(gameplay3,&GamePlay3::backSignal,this,[=](){
            this->show();
        });

    });
}
void ChooseLevel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/image/background.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
