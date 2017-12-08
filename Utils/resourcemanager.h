#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include<vector>
#include<QString>
#include<map>
#include "external\bullet3-2.87\src\BulletCollision\CollisionShapes\btCollisionShape.h"

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    int storeMesh(QString name, Mesh * meshPointer);
    int storeShape(QString name, btCollisionShape * shapePointer);
    Mesh * retrieveMesh(int);
    btCollisionShape * retrieveShape(int);
    Mesh * retrieveMesh(QString);
    btCollisionShape * retrieveShape(QString);
private:
    std::vector<Mesh *>meshBatch;
    std::vector<btCollisionShape*>shapeBatch;
    std::map<QString,int> meshMap;
    std::map<QString,int> shapeMap;
};

#endif // RESOURCEMANAGER_H
