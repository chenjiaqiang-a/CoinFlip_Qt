#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QEasingCurve>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent){}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
     //成员变量normalImgPath保存正常显示图片路径
     normalImgPath = normalImg;
     //成员变量pressedImgPath保存按下后显示的图片
     pressedImgPath = pressImg;
     //创建QPixmap对象
     QPixmap pixmap;
     //判断是否能够加载正常显示的图片，若不能提示加载失败
     bool ret = pixmap.load(normalImgPath);
     if(!ret)
     {
         qDebug() << normalImg << "加载图片失败!";
     }
     //设置图片的固定尺寸
     this->setFixedSize( pixmap.width(), pixmap.height() );
     //设置不规则图片的样式表
     this->setStyleSheet("QPushButton{border:0px;}");
     //设置图标
     this->setIcon(pixmap);
     //设置图标大小
     this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::jump_down()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);         //设置时间间隔
    //创建起始/结束位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

void MyPushButton::jump_up()
{

    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}
