#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>


class GameObject
{
public:
    GameObject();

    QVector3D getPosition() const;

    QVector3D getRotation() const;

    QVector3D getScale() const;

    void setPosition(const QVector3D &value);

    void setRotation(const QVector3D &value);

    void setScale(const QVector3D &value);

protected:
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
};

#endif // GAMEOBJECT_H
