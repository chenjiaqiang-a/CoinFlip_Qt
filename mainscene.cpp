#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/image/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币");

    //点击退出，退出程序
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);

    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(":/image/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    QSound * startSound = new QSound(":/sound/res/TapButtonSound.wav", this);

    connect(startBtn, &MyPushButton::clicked, [=](){
        startSound->play();
        startBtn->jump_down();
        startBtn->jump_up();

        QTimer::singleShot(500, this, [=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/image/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/image/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}

