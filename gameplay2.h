#ifndef GAMEPLAY2_H
#define GAMEPLAY2_H

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
const int ROW_COUNT2=10;
const int COLUMN_COUNT2=10;
//图片高度和宽度
const int IMAGE_WIDHT2=45;
const int IMAGE_HEIGHT2=63;
class GamePlay2 : public QWidget
{
    Q_OBJECT
public:
    explicit GamePlay2(QWidget *parent = nullptr);
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
    int PixmapData[ROW_COUNT2][COLUMN_COUNT2]; //存放图片
    QVector<QVector<bool>>* isEmpty;
    int clickCount;
    int firstClickX;
    int firstClickY;
};

#endif // GAMEPLAY2_H
