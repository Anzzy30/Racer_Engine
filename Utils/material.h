#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QString>


class Material
{
public:
    Material();
    Material(QString name,QVector3D Ka, QVector3D Kd, QVector3D Ks, float Ns, float Ni, float d, int illum);

private:

    QString name;
    QVector3D Ka;
    QVector3D Kd;
    QVector3D Ks;
    float Ns;
    float Ni;
    float d;
    int illum;
};

#endif // MATERIAL_H
