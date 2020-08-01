#include "chooselevelscene.h"
#include "mypushbutton.h"

#include <QPixmap>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include <QLabel>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/image/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * exitAction = startMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    //返回按钮
    MyPushButton * returnBtn = new MyPushButton(":/image/res/BackButton.png",":/image/res/BackButtonSelected.png");
    returnBtn->setParent(this);
    returnBtn->move(this->width()-returnBtn->width(),this->height()-returnBtn->height());

    connect(returnBtn, &MyPushButton::clicked, [=](){
        QTimer::singleShot(500, this, [=](){
            this->hide();
            emit this->chooseSceneBack();
        });
    });

    //创建关卡按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/image/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i%4)*70, 130 + (i/4)*70);

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //设置居中
        label->move(25 + (i%4)*70, 130 + (i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);  //鼠标事件穿透

        connect(menuBtn, &MyPushButton::clicked, [=](){
            if(pScene == nullptr)
            {
                this->hide();
                pScene = new PlayScene(i+1);
                pScene->show();

                connect(pScene,&PlayScene::chooseSceneBack,[=](){
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });
            }
        });
    }



}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/image/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
