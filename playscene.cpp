#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int index)
{
    this->levelIndex = index;

    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/image/res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/image/res/BackButton.png",":/image/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());

    //返回按钮功能实现
    connect(closeBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
             }
        );
    });

    //当前关卡标题
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    label->setFont(font);
    QString str = QString("Leavel: %1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30, this->height() - 50,120, 50)); //设置大小和位置

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/image/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //金币对象
            QString img;
            if(gameArray[i][j] == 1)
            {
              img = ":/image/res/Coin0001.png";
            }
            else
            {
              img = ":/image/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag =gameArray[i][j]; //记录正反标志

            connect(coin,&MyCoin::clicked,[=](){
                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
            });


        }
    }



}

void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/image/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap( 10, 30, pix.width(), pix.height(), pix);

}
