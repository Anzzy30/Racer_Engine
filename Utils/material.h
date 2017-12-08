#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QOpenGLTexture>
#include <QString>
#include <QFile>
#include <QStringList>

#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif

class Material
{

public:
    Material();
    Material(QString name, QVector3D Ka, QVector3D Kd, QVector3D Ks, float Ns, float Ni, float d, int illum);
    ~Material();

    QString getName() const;

    void setName(const QString &value);

    QVector3D getKa() const;

    void setKa(const QVector3D &value);

    QVector3D getKd() const;

    void setKd(const QVector3D &value);

    QVector3D getKs() const;

    void setKs(const QVector3D &value);

    float getNs() const;

    void setNs(float value);

    float getNi() const;

    void setNi(float value);

    float getD() const;

    void setD(float value);

    int getIllum() const;

    void setIllum(int value);

    QOpenGLTexture *getMap_Kd() const;

    void setMap_Kd(QOpenGLTexture *value);

    void loadMap_Kd(QString path);
private:

    QString name;
    QVector3D Ka;
    QVector3D Kd;
    QVector3D Ks;
    float Ns;
    float Ni;
    float d;
    int illum;

    QOpenGLTexture *  map_Kd;
};

#endif // MATERIAL_H
