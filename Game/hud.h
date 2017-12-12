#ifndef HUD_H
#define HUD_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QBasicTimer>
#include <QFont>
#include "Game/scene.h"
#include "GameObject/gameobject.h"
/*Racer HUD*/


struct HUDInfo{
    float speed = 0;
};

class HUD: public QWidget
{
    Q_OBJECT
public:

    explicit HUD(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void initialize();

    void updateHUDInfo();
    void setScene(const Scene *value);

private:

    const Scene* scene;
    QBasicTimer timer;
    HUDInfo info;
    QFont font;
    QColor fontColor;
};

#endif // HUD_H
