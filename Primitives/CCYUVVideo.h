/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCYUVVIDEO_H
#define CCYUVVIDEO_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "CCYUVDataDefine.h"

class CCYUVVideo : public QObject
{
    Q_OBJECT
public:
    explicit CCYUVVideo(QObject *parent = nullptr);
    virtual ~CCYUVVideo();
     void  Render(CCGLCamera* camera, CCYUV_Buffer* yuvBuffer);

private:
    GLuint            m_textures[3];
    CCGLShader*       m_pOpenGLShader;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;


};

#endif // CCYUVVIDEO_H
