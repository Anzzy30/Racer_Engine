#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>

class GameObject
{
public:
    GameObject();
    GameObject(QVector3D position,QVector3D rotation,QVector3D scale);

    virtual void draw();

    QVector3D getPosition() const;
    QVector3D getRotation() const;
    QVector3D getScale() const;
    QMatrix4x4 getModelMatrix();

    void setPosition(const QVector3D &value);
    void setRotation(const QVector3D &value);
    void setScale(const QVector3D &value);

protected:
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;

    QMatrix4x4 model;

};

#endif // GAMEOBJECT_H
