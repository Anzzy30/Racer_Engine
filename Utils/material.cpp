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
