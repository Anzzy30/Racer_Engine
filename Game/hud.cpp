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

    fontColor.setRgbF(0.1, 0.598, 0.655);
    font = QFont("Arial");

    font.setBold(true);
    this->resize(this->parentWidget()->width(),this->parentWidget()->height()); //
}

void HUD::updateHUDInfo()
{
    this->resize(this->parentWidget()->width(),this->parentWidget()->height()); //
    VehicleComponent *carComponent = scene->getCar()->getComponent<VehicleComponent>();
    info.speed = carComponent->getSpeed();
    info.boostCD = carComponent->getBoostCD();
    info.maxBoostCD = carComponent->getMaxBoostCD();
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
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath speedPath;
    font.setStyleStrategy(QFont::ForceIntegerMetrics);
    painter.setPen(QColor(0,0,0));
    font.setPointSize((this->width()*0.03+this->height()*0.03));

    speedPath.addText(this->width()*0.05,this->height()*0.95, font,QString::number((int)info.speed));

    painter.fillPath(speedPath,QColor(10, 110, 155));

    painter.drawPath(speedPath);

    QPainterPath nosBar;
    font.setStyleStrategy(QFont::ForceIntegerMetrics);
    painter.setPen(QColor(0,0,0));
    font.setPointSize((this->width()*0.03+this->height()*0.03));

    nosBar.addRoundRect(this->width()*0.06,this->height()*0.80 - this->height()*0.15*(info.maxBoostCD-info.boostCD)/info.maxBoostCD,
                        this->width()*0.015,this->height()*0.15*(info.maxBoostCD-info.boostCD)/info.maxBoostCD,2,2);
    nosBar = nosBar.toReversed();
    painter.fillPath(nosBar,QColor(0, 220, 10));

    painter.drawPath(nosBar);

    nosBar.addRoundRect(this->width()*0.06,this->height()*0.65,this->width()*0.015,this->height()*0.15,2,2);
    painter.fillPath(nosBar,QColor(220, 0, 10));

    painter.drawPath(nosBar);


    //QRectF speedRect(QPointF(this->width()*0.4,this->height()),QPointF(this->width()*0.6,this->height()*0.9));
    //painter.drawText(speedRect,QString::number((int)info.speed),QTextOption((Qt::AlignVCenter | Qt::AlignHCenter)));
    painter.end();
}
