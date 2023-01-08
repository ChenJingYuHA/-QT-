#ifndef GAMEPLAY_H
#define GAMEPLAY_H

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
#include <QLCDNumber>
//行数和列数
const int ROW_COUNT=8;
const int COLUMN_COUNT=8;
//图片高度和宽度
const int IMAGE_WIDHT=54;
const int IMAGE_HEIGHT=77;
class GamePlay : public QWidget
{
    Q_OBJECT
public:
    explicit GamePlay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent *ev);//鼠标点击
    void mouseReleaseEvent(QMouseEvent *e);
    bool Contrl(QPoint p1,QPoint p2);
    bool isWin();
    void initDate();


signals:
     void backSignal();
     void hasWin();
private slots:
     void slot_timeout();
     void on_pushButton_clicked();
private:
    void rightbox();
    QString game1(int k);

    QPushButton * start;
    QPushButton * back;
    QPushButton * quit;

//    QPushButton * restart;

    int count=0;
    bool flag=false;
    QTimer * timer;
    QLabel * label2;
    void time_show();
    void time_start();
    void time_stop();

    bool showGameArea;
    int PixmapData[ROW_COUNT][COLUMN_COUNT]; //存放图片
    QVector<QVector<bool>>* isEmpty;
    int clickCount;
    int firstClickX;
    int firstClickY;
};

#endif // GAMEPLAY_H
