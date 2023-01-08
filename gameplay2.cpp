#include "gameplay2.h"
#include <QFont>
#include <QDebug>
#include <cmath>
GamePlay2::GamePlay2(QWidget *parent) : QWidget(parent)
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
    label2->setGeometry(480,360,140,80);

    QFont font;
    font.setBold(true);
    font.setPointSize(18);
    label2->setFont(font);

    rightbox();
    initDate();
    showGameArea=true;
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&GamePlay2::slot_timeout);
}

void GamePlay2::slot_timeout()
{
    count++;
    time_show();
}
void GamePlay2::on_pushButton_clicked()
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

void GamePlay2::time_start()
{
    timer->start(10);
    flag=true;
}

void GamePlay2::time_stop()
{
    timer->stop();
    flag=false;
}

void GamePlay2::time_show()
{
    QString str=QString("%1:%2.%3")
            .arg(count/6000%60,2,10,QLatin1Char('0'))
            .arg(count/100%60,2,10,QLatin1Char('0'))
            .arg(count%100,2,10,QLatin1Char('0'));
    label2->setText(str);
}

void GamePlay2::rightbox()
{
    back = new QPushButton(tr("返回"));
    start = new QPushButton(this);
    start->setText(tr("开始"));
    quit = new QPushButton(tr("退出"));
    restart = new QPushButton(tr("重新开始"));
    back->setParent(this);
    //restart->setParent(this);
    quit->setParent(this);

    //restart->setGeometry(440,440,90,70);
    start->setGeometry(480,510,90,70);
    quit->setGeometry(480,590,90,70);
    back->setGeometry(480,670,90,70);
    connect(start,&QPushButton::clicked,this,&GamePlay2::on_pushButton_clicked);
    connect(back,&QPushButton::clicked,[=](){
        this->hide();
        emit backSignal();
    });
    connect(quit,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(restart,&QPushButton::clicked,[=](){
        count=0;
        timer->stop();
        label2->setText("计时");
    });
}
void GamePlay2::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/image/background.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    if(showGameArea)
    {
        for(int i=0;i<ROW_COUNT2;++i)
        {
            for(int j=0;j<COLUMN_COUNT2;++j)
            {
                if(!(*isEmpty)[i][j])
                {
                    painter.drawPixmap(j*IMAGE_WIDHT2,i*IMAGE_HEIGHT2,IMAGE_WIDHT2,IMAGE_HEIGHT2,QPixmap(QString(":/image/image/%1.png").arg(PixmapData[i][j])));

                }
                else
                {
                    painter.drawPixmap(j*IMAGE_WIDHT2,i*IMAGE_HEIGHT2,IMAGE_WIDHT2,IMAGE_HEIGHT2,QPixmap(QString(":/image/image/majiang.png")));
                }
            }
        }
    }
}
void GamePlay2::initDate()
{
    showGameArea=false;
    QVector<int>*hasExist = new QVector<int>(ROW_COUNT2/2*COLUMN_COUNT2+1,0);
    for(int i=0;i<ROW_COUNT2/2;++i)
    {
        for(int j=0;j<COLUMN_COUNT2;++j)
        {
            int type = QRandomGenerator::global()->generate()%27;
            PixmapData[i][j]=type;
            while(true)
            {
                int tempIndex = QRandomGenerator::global()->generate()%(ROW_COUNT2/2*COLUMN_COUNT2)+ROW_COUNT2/2*COLUMN_COUNT2;
                if((*hasExist)[tempIndex-ROW_COUNT2/2*COLUMN_COUNT2]==0)
                {
                    PixmapData[tempIndex/ROW_COUNT2][tempIndex%ROW_COUNT2]=type;

                    (*hasExist)[tempIndex-ROW_COUNT2/2*COLUMN_COUNT2]=1;
                    break;
                }
            }
        }
    }
    isEmpty=new QVector<QVector<bool>>(ROW_COUNT2,QVector<bool>(COLUMN_COUNT2,false));
    clickCount=0;
    firstClickX=-1;
    firstClickY=-1;
}
void GamePlay2::mousePressEvent(QMouseEvent *e)
{
    QSound *sound = new QSound(":/music/BackButtonSound.wav");
    int currentX=e->x()/IMAGE_WIDHT2;
    int currentY=e->y()/IMAGE_HEIGHT2;
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
//            sound->stop();
        }
    }
}
bool GamePlay2::isWin()
{
    for(int i=0;i<ROW_COUNT2;++i)
        for(int j=0;j<COLUMN_COUNT2;++j)
        {   //不为空 则返回false
            if(!(*isEmpty)[i][j])
                return false;
        }
    return true;
}
void GamePlay2::mouseReleaseEvent(QMouseEvent *e)
{
    bool youWin=isWin();
    if(youWin)
    {
        //赢了之后，得先暂停计时器
        //emit hasWin();
        timer->stop();
        //询问是否继续游戏
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
