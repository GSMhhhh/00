/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCTEXTUREDCUBE_H
#define CCTEXTUREDCUBE_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"

class CCTexturedCube : public QObject
{
public:
    explicit CCTexturedCube(QObject *parent = nullptr);
    virtual ~CCTexturedCube();

    void  Render(CCGLCamera* camera, float deltaTime);


private:

    GLuint            m_texture[6];
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;


    float             m_angle = 0.0;
};

#endif // CCTEXTUREDCUBE_H
