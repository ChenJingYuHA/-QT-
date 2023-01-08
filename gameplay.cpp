#include "gameplay.h"
#include <QFont>
#include <QDebug>
#include <cmath>
GamePlay::GamePlay(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    //设置图标
    setWindowIcon(QIcon(":/image/logo.jpg"));
    //设置标题
    setWindowTitle("开始");
    //设置大小
    setFixedSize(660,880);
    label2 = new QLabel(this);
    label2->setText(QString("%1%2:%3%4.%5%6").arg(0).arg(0).arg(0).arg(0).arg(0).arg(0));
    label2->setGeometry(440,360,140,80);

    QFont font;
    font.setBold(true);
    font.setPointSize(18);
    label2->setFont(font);

    rightbox();
    initDate();
    showGameArea=true;
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&GamePlay::slot_timeout);//时间

}

void GamePlay::slot_timeout()
{
    count++;
    time_show();
}
void GamePlay::on_pushButton_clicked()
{
    //false->定时器暂停状态 true->定时器正在运行
    if(flag==false)
    {
        time_start();
    }
    else
    {
        time_stop();
    }
}

void GamePlay::time_start()
{
    timer->start(10);
    flag=true;
}

void GamePlay::time_stop()
{
    timer->stop();
    flag=false;
}

void GamePlay::time_show()
{
    QString str=QString("%1:%2.%3")
            .arg(count/6000%60,2,10,QLatin1Char('0'))
            .arg(count/100%60,2,10,QLatin1Char('0'))
            .arg(count%100,2,10,QLatin1Char('0'));
    label2->setText(str);
}

void GamePlay::rightbox()
{
    back = new QPushButton(tr("返回"));
    start = new QPushButton(this);
    start->setText(tr("开始"));
    quit = new QPushButton(tr("退出"));
    back->setParent(this);
    quit->setParent(this);

    start->setGeometry(440,510,90,70);
    quit->setGeometry(440,590,90,70);
    back->setGeometry(440,670,90,70);
    connect(start,&QPushButton::clicked,this,&GamePlay::on_pushButton_clicked);
    connect(back,&QPushButton::clicked,[=](){
        this->hide();
        emit backSignal();
    });
    connect(quit,&QPushButton::clicked,[=](){
        this->close();
    });
}
void GamePlay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/image/background.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    if(showGameArea)
    {
        for(int i=0;i<ROW_COUNT;++i)
        {
            for(int j=0;j<COLUMN_COUNT;++j)
            {
                if(!(*isEmpty)[i][j])
                {
                    painter.drawPixmap(j*IMAGE_WIDHT,i*IMAGE_HEIGHT,IMAGE_WIDHT,IMAGE_HEIGHT,QPixmap(QString(":/image/image/%1.png").arg(PixmapData[i][j])));
                }
                else
                {
                    painter.drawPixmap(j*IMAGE_WIDHT,i*IMAGE_HEIGHT,IMAGE_WIDHT,IMAGE_HEIGHT,QPixmap(QString(":/image/image/majiang.png")));
                }
            }
        }
    }
}
void GamePlay::initDate()
{
    showGameArea=false;
    QVector<int>*hasExist = new QVector<int>(ROW_COUNT/2*COLUMN_COUNT+1,0);
    for(int i=0;i<ROW_COUNT/2;++i)
    {
        for(int j=0;j<COLUMN_COUNT;++j)
        {
            int type = QRandomGenerator::global()->generate()%27;
            PixmapData[i][j]=type;
            while(true)
            {
                int tempIndex = QRandomGenerator::global()->generate()%(ROW_COUNT/2*COLUMN_COUNT)+ROW_COUNT/2*COLUMN_COUNT;
                if((*hasExist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]==0)
                {
                    PixmapData[tempIndex/ROW_COUNT][tempIndex%ROW_COUNT]=type;

                    (*hasExist)[tempIndex-ROW_COUNT/2*COLUMN_COUNT]=1;
                    break;
                }
            }
        }
    }
    isEmpty=new QVector<QVector<bool>>(ROW_COUNT,QVector<bool>(COLUMN_COUNT,false)); //判断是否为空的数组
    clickCount=0;
    firstClickX=-1;
    firstClickY=-1;
}
void GamePlay::mousePressEvent(QMouseEvent *e)
{
    QSound *sound = new QSound(":/music/BackButtonSound.wav");
    int currentX=e->x()/IMAGE_WIDHT;
    int currentY=e->y()/IMAGE_HEIGHT;
    //如果点击的图片是空，那就直接返回
    if((*isEmpty)[currentY][currentX])
        return ;
    ++clickCount;
    //第一次点击
    if(clickCount%2!=0)
    {
        sound->play();
        firstClickX=currentX;
        firstClickY=currentY;
        qDebug()<<"第一次点击"<<firstClickY<<","<<firstClickX<<"图片类型是"<<PixmapData[currentY][currentX];
    }
    else if(clickCount%2==0){
        sound->play();
        qDebug()<<"第二次点击"<<currentY<<" ,"<<currentX<<"图片类型是"<<PixmapData[currentY][currentX];
        //若图片类型不同或者点击位置相同直接return
        if(PixmapData[firstClickY][firstClickX]!=PixmapData[currentY][currentX]||(currentY==firstClickY&&currentX==firstClickX))
            return ;


        //图片类型相同 位置不同
        if(PixmapData[firstClickY][firstClickX]==PixmapData[currentY][currentX]&&(currentY!=firstClickY||currentX!=firstClickX))
        {
            sound->play();

            qDebug()<<"修改数组";
            (*isEmpty)[firstClickY][firstClickX]=true;
            (*isEmpty)[currentY][currentX]=true;

            update();
        }
    }
}
bool GamePlay::isWin()
{
    for(int i=0;i<ROW_COUNT;++i)
        for(int j=0;j<COLUMN_COUNT;++j)
        {   //不为空 则返回false
            if(!(*isEmpty)[i][j])
                return false;
        }
    return true;
}
void GamePlay::mouseReleaseEvent(QMouseEvent *e)
{
    bool youWin=isWin();
    if(youWin)
    {
        //赢了之后，得先暂停计时器
        //emit hasWin();
        timer->stop();
        if(QMessageBox::Ok==QMessageBox::question(this,"你赢了","真厉害",
                                                  QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel))
        {
            //emit restart();
        }
        else{
            this->close();
        }
    }
}
