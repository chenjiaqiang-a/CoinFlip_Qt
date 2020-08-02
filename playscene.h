#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int);

    void paintEvent(QPaintEvent *);

    int levelIndex;
    int gameArray[4][4];
    MyCoin * coinBtn[4][4];
    bool isWin = true;//是否胜利

signals:
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
