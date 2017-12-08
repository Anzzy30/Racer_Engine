#include "material.h"

Material::Material()
{
    name;
    Ns = 0.0f;
    Ni = 0.0f;
    d = 0.0f;
    illum = 0;
}

Material::Material(QString name, QVector3D Ka, QVector3D Kd, QVector3D Ks, float Ns, float Ni, float d, int illum):
    name(name),Ka(Ka),Kd(Kd),Ks(Ks),Ns(Ns),Ni(Ni),d(d),illum(illum)
{

}

Material::~Material()
{
    if(map_Kd == NULL) delete map_Kd;

}

void Material::setName(const QString &value)
{
    name = value;
}

QString Material::getName() const
{
    return name;
}

QVector3D Material::getKa() const
{
    return Ka;
}

void Material::setKa(const QVector3D &value)
{
    Ka = value;
}

QVector3D Material::getKd() const
{
    return Kd;
}

void Material::setKd(const QVector3D &value)
{
    Kd = value;
}

QVector3D Material::getKs() const
{
    return Ks;
}

void Material::setKs(const QVector3D &value)
{
    Ks = value;
}

float Material::getNs() const
{
    return Ns;
}

void Material::setNs(float value)
{
    Ns = value;
}

float Material::getNi() const
{
    return Ni;
}

void Material::setNi(float value)
{
    Ni = value;
}

float Material::getD() const
{
    return d;
}

void Material::setD(float value)
{
    d = value;
}

int Material::getIllum() const
{
    return illum;
}

void Material::setIllum(int value)
{
    illum = value;
}

QOpenGLTexture *Material::getMap_Kd() const
{
    return map_Kd;
}

void Material::setMap_Kd(QOpenGLTexture *value)
{
    map_Kd = value;
}

void Material::loadMap_Kd(QString path)
{
    qDebug() <<path;

    map_Kd = new QOpenGLTexture(QImage(path).mirrored());

    map_Kd->setMinificationFilter(QOpenGLTexture::Nearest);

    map_Kd->setMagnificationFilter(QOpenGLTexture::Linear);

    map_Kd->setWrapMode(QOpenGLTexture::Repeat);
}
