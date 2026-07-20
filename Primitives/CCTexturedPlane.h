/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCTEXTUREDPLANE_H
#define CCTEXTUREDPLANE_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"


class CCTexturedPlane : public QObject
{
public:
    explicit CCTexturedPlane(QObject *parent = nullptr);
    virtual ~CCTexturedPlane();
    void  Render(CCGLCamera* camera, float deltaTime);

private:
    GLuint            m_texture;
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

};

#endif // CCTEXTUREDPLANE_H
