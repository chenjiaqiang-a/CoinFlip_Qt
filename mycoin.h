#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);

    MyCoin(QString);

    void changeFlag();  //改变标志，执行翻转效果
    QTimer *timer1;     //正翻反定时器
    QTimer *timer2;     //反翻正定时器
    int min = 1;
    int max = 8;
    bool isAnimation = false;

    void mousePressEvent(QMouseEvent *);

    int  posX;
    int  posY;
    bool flag;

signals:

};

#endif // MYCOIN_H
