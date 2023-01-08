// 作者：陈婧瑜
// 完成时间： 2022.12.19-2022.12.21
#include "mainwindow.h"
#include <QFont>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("AR PL KaitiM GB",18);
    a.setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
