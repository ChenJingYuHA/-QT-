#include "illustrate.h"
#include <QPainter>
#include <QtDebug>
#include <QFont>
Illustrate::Illustrate(QWidget *parent) : QMainWindow(parent)
{
    //设置图标
    setWindowIcon(QIcon(":/image/logo.jpg"));

    //设置标题
    setWindowTitle("游戏说明");
    //设置大小
    setFixedSize(660,880);

    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    QMenu * starttMenu = bar->addMenu("开始");
    QAction * quit = starttMenu->addAction("退出");
    connect(quit,SIGNAL(triggered()),this,SLOT(close()));
    //字体设置
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);
    font.setPointSize(15);

    //游戏规则
    rule = new QTextEdit(this);
    rule->setGeometry(100,200,500,400);
    rule->setFont(font);
    rule->setText("  记忆翻牌是一款锻炼瞬间反应力的小游戏。""\r\n"
                  "  开始游戏之前，玩家可以选择游戏难度和查看游戏规则。游戏总共分为三个难度，初级是8x8的布局，共有64个麻将，中级是10x10的布局，"
                  "共有100个麻将，高级是12x12的布局，共有144个麻将。""\r\n"

                  "  游戏中，玩家通过点击相同的麻将，即刻进行消除，"
                  "否则花色就会不变，看看你能用多长时间获得获得游戏胜利。");

    //返回按钮
    rule->setCursorWidth(0);//设置光标属性 为false
    back = new QPushButton(this);
    back->setText(tr("返回"));
    back->resize(200,100);
    back->setGeometry(this->width()-back->width()-30,this->height()-back->height()-30,200,100);
    connect(back,&QPushButton::clicked,[=](){
//        qDebug()<<"点击返回功能";
        emit this->backSignal();
    });
}
void Illustrate::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/image/background.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
