#ifndef GAMEPLAY3_H
#define GAMEPLAY3_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QTimer>
#include <QLabel>
#include <QVector>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSound>

//行数和列数
const int ROW_COUNT3=12;
const int COLUMN_COUNT3=12;
//图片高度和宽度
const int IMAGE_WIDHT3=40;
const int IMAGE_HEIGHT3=56;

class GamePlay3 : public QWidget
{
    Q_OBJECT
public:
    explicit GamePlay3(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent *ev);//鼠标点击
    void mouseReleaseEvent(QMouseEvent *e);
    bool Contrl(QPoint p1,QPoint p2);
    bool isWin();
    void initDate();
signals:
     void backSignal();
private slots:
     void slot_timeout();
     void on_pushButton_clicked();
private:
    void rightbox();
    QString game1(int k);

    QPushButton * start;
    QPushButton * back;
    QPushButton * quit;
    QPushButton * restart;

    int count=0;
    bool flag=false;
    QTimer * timer;
    QLabel * label2;
    void time_show();
    void time_start();
    void time_stop();

    bool showGameArea;
    int PixmapData[ROW_COUNT3][COLUMN_COUNT3]; //存放图片
    QVector<QVector<bool>>* isEmpty;
    int clickCount;
    int firstClickX;
    int firstClickY;
signals:

};

#endif // GAMEPLAY3_H
