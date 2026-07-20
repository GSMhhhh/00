/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include "CCOpenGLWidget.h"
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QDateTime>

CCOpenGLWidget::CCOpenGLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    m_DMA    =   0;
    m_READ   =   1;
    m_bRecording = false;

    m_pRenderScene = new CCGLScene(width(),height());

    QScreen *screen = QApplication::screens().at(0);
    m_pixelRatio = screen->devicePixelRatio();

    m_pRenderTimer = new QTimer();
    connect(m_pRenderTimer,SIGNAL(timeout()),SLOT(onRenderTimerUpdate()));
    m_pRenderTimer->start(30);
    update();
}

CCOpenGLWidget::~CCOpenGLWidget()
{
    CCGLSafePtrDelete(m_pRenderScene);
    CCGLSafePtrDelete(m_pRenderTimer);


    CCGLSafePtrDelete(m_pOpenGLShader);
    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);

    //CCGLSafePtrDelete(m_pPBOfst);
    //CCGLSafePtrDelete(m_pPBOsnd);

    CCGLSafePtrDelete(m_pFBO);

    glDeleteBuffers(2,m_pbo);
}

void CCOpenGLWidget::StartRecordVideo()
{
    int     w   =   width()*m_pixelRatio;
    int     h   =   height()*m_pixelRatio;

    QDateTime dateTime = QDateTime::currentDateTime();
#if defined(Q_OS_WIN32)
    QString pathStr = qApp->applicationDirPath() +"/"+ dateTime.toString("yyyyMMddhhmmss") + ".mp4";
#else
     QString pathStr = "/Users/chenchao/Desktop/" + dateTime.toString("yyyyMMddhhmmss") + ".mp4";
#endif

    AVRecorderAPI_setupInputResolution(w,h);
    AVRecorderAPI_setupOutputResolution(w,h);
    AVRecorderAPI_startRecordVideoWithPath(pathStr.toUtf8().data(),"");

    m_bRecording = true;

}
void CCOpenGLWidget::StopRecordVideo()
{
    m_bRecording = false;
    AVRecorderAPI_stopRecordReleaseAllResources();
}
void CCOpenGLWidget::initializeGL()
{

    GLenum err = glewInit();
    if (GLEW_OK != err){
        qDebug()<< glewGetErrorString(err);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    glClearColor(0.0,0.0,0.0,1.0);


    m_pRenderScene->SetupSceneResources();


    m_pOpenGLShader = new CCGLShader();
    m_pOpenGLShader->SetupShaderResources(":/res/shaders/vertex_rgb.vert",":/res/shaders/fragment_rgb.frag");


//    CCVertex planVertices[] =
//    {
//        { -1.0f, 1.0f, -1.0f,  0,  0 },
//        {  -1.0f,-1.0f, -1.0f,   0,  1 },
//        {  1.0f,-1.0f, -1.0f,   1,  1 },
//        {  1.0f, 1.0f, -1.0f,   1,  0 },
//    };

//    short planeIndexs[] ={
//        0, 1, 3,
//        1, 3, 2
//    };


    CCVertex planVertices[] =
    {
        { -1.0f, -1.0f, -1.0f,  0,  0 },
        {  -1.0f, 1.0f, -1.0f,  0,  1 },
        {  1.0f, -1.0f, -1.0f,   1,  0 },
        {  1.0f, 1.0f, -1.0f,   1,  1 },
    };

    short planeIndexs[] ={
        0, 1, 2,
        1, 2, 3
    };

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(sizeof(planVertices));
    m_vertexBuffer->write(0, planVertices, sizeof(planVertices));
    m_vertexBuffer->release();


    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->bind();
    m_indexBuffer->allocate(sizeof(planeIndexs));
    m_indexBuffer->write(0, planeIndexs, sizeof(planeIndexs));
    m_indexBuffer->release();

    //initFrameBufferObject();

    int viewport[4]= {0,0,0,0};
    glGetIntegerv( GL_VIEWPORT, viewport );
    qDebug()<<"ViewPort:"<<viewport[2]<<viewport[3]<<width()<<height()<<m_pixelRatio;

    QSize fboSize(width()*m_pixelRatio, height()*m_pixelRatio);
    m_pFBO = new QOpenGLFramebufferObject(fboSize, QOpenGLFramebufferObject::Depth);
    bool  bValid = m_pFBO->isValid();
    qDebug()<<"FBO Valid:"<<bValid;


//    m_pPBOfst = new QOpenGLBuffer(QOpenGLBuffer::PixelPackBuffer);
//    m_pPBOfst->create();
//    m_pPBOfst->bind();
//    m_pPBOfst->allocate(fboSize.width() * fboSize.height() * 4);
//    m_pPBOfst->release();

//    m_pPBOsnd = new QOpenGLBuffer(QOpenGLBuffer::PixelPackBuffer);
//    m_pPBOsnd->create();
//    m_pPBOsnd->bind();
//    m_pPBOsnd->allocate(fboSize.width() * fboSize.height() * 4);
//    m_pPBOsnd->release();

    glGenBuffers(2,m_pbo);
    glBindBuffer(GL_PIXEL_PACK_BUFFER,m_pbo[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER,width()*m_pixelRatio*height()*m_pixelRatio*4,0,GL_STREAM_READ);

    glBindBuffer(GL_PIXEL_PACK_BUFFER,m_pbo[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER,width()*m_pixelRatio*height()*m_pixelRatio*4,0,GL_STREAM_READ);

    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);

    return;

}


void CCOpenGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(0.0,0.0,0.0,1.0);

    m_pFBO->bind();
    //glBindFramebuffer(GL_FRAMEBUFFER,m_fboId);

    m_pRenderScene->Render(m_pRenderTimer->interval());

    if(m_bRecording == true){
        processPBOReadPixels();
    }

    m_pFBO->release();
    //glBindFramebuffer(GL_FRAMEBUFFER,0);

    renderFBORenderTexture();


}
void CCOpenGLWidget::processPBOReadPixels()
{
    int     w   =   width()*m_pixelRatio;
    int     h   =   height()*m_pixelRatio;

    glReadBuffer(GL_FRONT);

    // DMA
    glBindBuffer(GL_PIXEL_PACK_BUFFER,m_pbo[m_DMA]);
    glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,0);
    // READ
    glBindBuffer(GL_PIXEL_PACK_BUFFER,m_pbo[m_READ]);

    void* data=glMapBuffer(GL_PIXEL_PACK_BUFFER,GL_READ_ONLY);
    if(data){

          AVRecorderAPI_writeVideoData((unsigned char*)data, w*3);
     }

    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    std::swap(m_DMA,m_READ);

    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);



}
//void CCOpenGLWidget::processPBOReadPixels()
//{
//    int     w   =   width()*m_pixelRatio;
//    int     h   =   height()*m_pixelRatio;

//    glReadBuffer(GL_FRONT);

//    m_pPBOfst->bind();
//    glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,0);


//    void* readBuff = m_pPBOfst->map(QOpenGLBuffer::ReadOnly);
//    if(readBuff)
//    {

//        QString tempPath="/Users/chenchao/Desktop/test.png";

//        QImage image = QImage((unsigned char*)readBuff, w, h, QImage::Format_RGB32);
//        if (image.isNull())
//        {
//            qDebug()<<"Receive frame error, width:%d, height:%d."<<w<<h;

//            return;
//        }
//        image= image.rgbSwapped();
//        image.save(tempPath,"PNG",100);

//        m_pPBOfst->unmap();
//    }

//    m_pPBOfst->release();
//}

void CCOpenGLWidget::onRenderTimerUpdate()
{
    update();
}


void CCOpenGLWidget::resizeGL(int w, int h)
{
   Q_UNUSED(w)
   Q_UNUSED(h)

}

void CCOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    update();
    if(event->button() == Qt::LeftButton)
    {
        float x = event->pos().rx();
        float y = event->pos().ry();
        m_pRenderScene->UpdateMouseEvent(QPointF(x,y));
    }


    update();
}

void CCOpenGLWidget::renderFBORenderTexture()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QOpenGLShaderProgram* shaderProgram = m_pOpenGLShader->GetShaderProgram();

    if(shaderProgram == NULL){
        return;
    }


    m_pOpenGLShader->Use();

    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    shaderProgram->enableAttributeArray("attr_position");
    shaderProgram->setAttributeBuffer("attr_position",GL_FLOAT, 0, 3, sizeof(CCVertex));//tupleSize 元组大小

    shaderProgram->enableAttributeArray("attr_uv");
    shaderProgram->setAttributeBuffer("attr_uv",GL_FLOAT,3*sizeof(float), 2, sizeof(CCVertex));

    QMatrix4x4 matrix;
    QMatrix4x4 planeMatTrans;
    matrix.setToIdentity();
    planeMatTrans.setToIdentity();
    planeMatTrans.translate(0,0,-3);
    matrix.ortho(-1,1,-1,1,0.1,1000);

    shaderProgram->setUniformValue("uni_mat",matrix);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_pFBO->texture());
    //glBindTexture(GL_TEXTURE_2D,m_renderTexture);

    const short* indices =(const short *) 0;
    glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);


    shaderProgram->disableAttributeArray("attr_position");
    shaderProgram->disableAttributeArray("attr_uv");

    glBindTexture(GL_TEXTURE_2D,0);

    m_vertexBuffer->release();
    m_indexBuffer->release();


    m_pOpenGLShader->UnUse();

}

void CCOpenGLWidget::saveImage()
{

    int     w   =   width()*m_pixelRatio;
    int     h   =   height()*m_pixelRatio;
    int size = w *h * 4;
    unsigned char*   data=   new unsigned char[size];
    memset(data,0,w * h * 4);
    glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,data);

    QString tempPath="/Users/chenchao/Desktop/test.png";

    QImage image = QImage(data, w, h, QImage::Format_RGB32);
    if (image.isNull())
    {
        qDebug()<<"Receive frame error, width:%d, height:%d."<<w<<h;

        return;
    }
    image= image.rgbSwapped();
    image.save(tempPath,"PNG",100);
}

void CCOpenGLWidget::initFrameBufferObject()
{
    int     w   =   width()*m_pixelRatio;
    int     h   =   height()*m_pixelRatio;

    glGenTextures(1,&m_renderTexture);
    glBindTexture(GL_TEXTURE_2D, m_renderTexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,w,h,0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D,0);

    glGenRenderbuffers(1, &m_renderId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w,h);
    glBindRenderbuffer(GL_RENDERBUFFER,0);


    glGenFramebuffers(1, &m_fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_renderTexture,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderId);

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER);

    switch( status )
    {
    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:

        qDebug("GL_FRAMEBUFFER_UNSUPPORTED_EXT!");
        break;
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}
