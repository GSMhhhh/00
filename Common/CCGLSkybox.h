/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCGLSKYBOX_H
#define CCGLSKYBOX_H

#include <GL/glew.h>
#include <QObject>
#include "CCGLShader.h"
#include "CCGLTexture.h"

class CCGLSkybox : public QObject
{
public:
    explicit CCGLSkybox(QObject *parent = nullptr);
    virtual ~CCGLSkybox();

    void  Render(CCGLCamera* camera, float deltaTime);


private:

    GLuint            m_texture[6];
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

};

#endif // CCGLSKYBOX_H
