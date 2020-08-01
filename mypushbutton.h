#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径

    //按下按钮的特效
    void jump_down();
    void jump_up();


signals:

};

#endif // MYPUSHBUTTON_H
