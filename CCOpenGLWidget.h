/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCOPENGLWIDGET_H
#define CCOPENGLWIDGET_H

#include <GL/glew.h>

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

#include <QTimer>
#include <QMouseEvent>
#include <QMatrix4x4>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

#include "CCGLScene.h"
#include "videorecorderinterface.h"


class CCOpenGLWidget:  public QOpenGLWidget
{
    Q_OBJECT
public:
    CCOpenGLWidget(QWidget *parent = 0);
    ~CCOpenGLWidget();
    void StartRecordVideo();
    void StopRecordVideo();

protected:
    void initializeGL() ;
    void resizeGL(int w, int h) ;
    void paintGL();
    void mousePressEvent(QMouseEvent *event);

private:
    void saveImage();
    void renderFBORenderTexture();
    void processPBOReadPixels();
    void initFrameBufferObject();

private slots:
    void onRenderTimerUpdate();

private:

    CCGLScene*          m_pRenderScene = NULL;
    QTimer*             m_pRenderTimer;

    CCGLShader*       m_pOpenGLShader;
    QOpenGLFramebufferObject*   m_pFBO;

    int                         m_DMA =0;
    int                         m_READ =1;
    GLuint                      m_pbo[2];

    QOpenGLBuffer*              m_pPBOfst;
    QOpenGLBuffer*              m_pPBOsnd;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

    double            m_pixelRatio;



    GLuint      m_fboId;
    GLuint      m_renderId;
    GLuint      m_renderTexture;

    bool        m_bRecording = false;


};

#endif // CCOPENGLWIDGET_H
