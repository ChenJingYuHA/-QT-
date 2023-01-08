#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGridLayout>
#include <QPushButton>
#include<QPainter>
#include "gameplay.h"
#include "gameplay2.h"
#include "gameplay3.h"

class ChooseLevel : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
signals:
     void backSignal();
     void level1Signal();

private:
    QGridLayout *mainLayout;
    QPushButton *level1;
    QPushButton *level2;
    QPushButton *level3;
    QPushButton *back;

    GamePlay * gameplay;
    GamePlay2 * gameplay2;
    GamePlay3 *gameplay3;


};

#endif // CHOOSELEVEL_H
