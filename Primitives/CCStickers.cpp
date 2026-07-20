/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include <GL/glew.h>
#include "CCStickers.h"
#include <QApplication>
#include <QScreen>


CCStickers::CCStickers(QObject *parent) : QObject(parent)
{
    m_pOpenGLShader = new CCGLShader();
    m_pOpenGLShader->SetupShaderResources(":/res/shaders/vertex_rgb.vert",":/res/shaders/fragment_rgb.frag");

    m_pOpenGLTexture = new CCGLTexture();

    QString textString = QString(":/res/stickers/item_stickerrabit.png");
    m_texture = m_pOpenGLTexture->CreateOpenGLTexture(textString);

    CCVertex planVertices[] =
    {
        { -1.0f, 1.0f, 1.0f,  0,  0 },
        {  -1.0f,-1.0f, 1.0f,   0,  1 },
        {  1.0f,-1.0f, 1.0f,   1,  1 },
        {  1.0f, 1.0f, 1.0f,   1,  0 },
    };

    short planeIndexs[] ={
        0, 1, 3,
        1, 3, 2
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
}
CCStickers::~CCStickers()
{
    CCGLSafePtrDelete(m_pOpenGLShader);
    CCGLSafePtrDelete(m_pOpenGLTexture);

    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);

    glDeleteTextures(1,&m_texture);
}

void CCStickers::Render(CCGLCamera* pCamera, float deltaTime)
{
    Q_UNUSED(deltaTime)
    m_pCamera = pCamera;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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

    QMatrix4x4 planeMat;

    QMatrix4x4 planeMatTrans;
    planeMatTrans.translate(m_Objx,m_Objy+0.2,-3);

    QMatrix4x4 planeMatScale;
    planeMatScale.scale(0.5 * m_ObjScale ,0.5*4/3 * m_ObjScale ,1);

    planeMat =    planeMatTrans * planeMatScale;

    planeMat =  pCamera->projectionMatrix * pCamera->viewMatrix * planeMat ;

    shaderProgram->setUniformValue("uni_mat",planeMat);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER ,0.9);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texture);

    const short* indices =(const short *) 0;
    glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);

    glBindTexture(GL_TEXTURE_2D,0);

    shaderProgram->disableAttributeArray("attr_position");
    shaderProgram->disableAttributeArray("attr_uv");

    m_vertexBuffer->release();
    m_indexBuffer->release();


    m_pOpenGLShader->UnUse();

    glDisable(GL_ALPHA_TEST);
}
void CCStickers::UpdateMouseEvent(QPointF pos,float scale)
{
    m_Objx = pos.rx();
    m_Objy = pos.ry();

    m_ObjScale = scale;

    int viewport[4]= {0,0,640,480};
    double modelview[16], projection[16];

    float x = pos.rx();
    float y = pos.ry();

    GLfloat  z = 0;

    //glGetIntegerv( GL_VIEWPORT, viewport );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );

    glReadBuffer(GL_FRONT);
    glReadPixels( x, viewport[3]-y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &m_Objz );

    gluUnProject( x, viewport[3]-y, z, modelview, projection, viewport, &m_Objx, &m_Objy, &m_Objz );
    //qDebug()<<"00"<<"posX"<<m_Objx<<"posY"<<m_Objy<<"posZ"<<m_Objz;
}
