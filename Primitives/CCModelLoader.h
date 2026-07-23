#ifndef CCMODELLOADER_H
#define CCMODELLOADER_H

#include <QObject>
#include "Common/CCGlobalDefine.h"
#include "Common/CCGLShader.h"
#include "CCMesh.h"

class CCModelLoader : public QObject
{

public:
    explicit CCModelLoader(QObject *parent = nullptr);
    virtual ~CCModelLoader();
    void    LoadModelFromFile(const QString &file);
    CCMesh* GetMesh();
    void    Render(CCGLCamera* camera, float deltaTime);
    void    UpdateMouseEvent(QPointF pos,float scale);
private:
    void    calculateTBN(QVector<CCVertexData> &vertData);


private:
    CCMesh* m_pMesh;


};

#endif // CCMODELLOADER_H
