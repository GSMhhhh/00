/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

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
