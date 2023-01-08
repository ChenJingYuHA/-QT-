#ifndef ILLUSTRATE_H
#define ILLUSTRATE_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
class Illustrate : public QMainWindow
{
    Q_OBJECT
public:
    explicit Illustrate(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent*);
signals:
     void backSignal();
private:
    QPushButton *back;
    QTextEdit * rule;
};

#endif // ILLUSTRATE_H
