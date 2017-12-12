#include "hud.h"




HUD::HUD(QWidget *parent):
    QWidget(parent)
{
    initialize();
}
void HUD::initialize()
{
    int msec = 1000/60;

    timer.start(msec, this);

    fontColor.setRgbF(0.698, 0.133, 0.133);
    font.setPointSize(30);
    font.setBold(true);
    this->resize(this->parentWidget()->width(),this->parentWidget()->height()); //
}

void HUD::updateHUDInfo()
{
    this->resize(this->parentWidget()->width(),this->parentWidget()->height()); //
    info.speed = scene->getCar()->getComponent<VehicleComponent>()->getSpeed();
}


void HUD::setScene(const Scene *scene)
{
    this->scene = scene;
}
void HUD::timerEvent(QTimerEvent *)
{
    update();

}

void HUD::resizeEvent(QResizeEvent *event)
{
    this->resize(this->parentWidget()->width(),this->parentWidget()->height()); //
}

void HUD::paintEvent(QPaintEvent *event)
{
    updateHUDInfo();

    QPainter painter(this);
    painter.setFont(font);
    painter.setPen(fontColor);
    QRectF speedRect(QPointF(this->width()*0.4,this->height()),QPointF(this->width()*0.6,this->height()*0.9));
    painter.drawText(speedRect,QString::number((int)info.speed),QTextOption((Qt::AlignVCenter | Qt::AlignHCenter)));
    painter.end();
}
