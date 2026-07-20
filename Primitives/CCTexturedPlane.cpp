/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include <GL/glew.h>
#include "CCTexturedPlane.h"

CCTexturedPlane::CCTexturedPlane(QObject *parent) : QObject(parent)
{
    m_pOpenGLShader = new CCGLShader();
    m_pOpenGLShader->SetupShaderResources(":/shaders/vertex_rgb.vert",":/shaders/fragment_rgb.frag");

    m_pOpenGLTexture = new CCGLTexture();

    QString textString = QString(":/Images/ground.jpg");
    m_texture = m_pOpenGLTexture->CreateOpenGLTexture(textString);

    CCVertex planVertices[] =
    {
        { -1.0f, -1.0f, 1.0f,  0,  0 },
        {  -1.0f,1.0f, 1.0f,   0,  1 },
        {  1.0f,-1.0f, 1.0f,   1,  0 },
        {  1.0f, 1.0f, 1.0f,   1,  1 },
    };

    short planeIndexs[] ={
        0, 1, 2,
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
CCTexturedPlane::~CCTexturedPlane()
{

    CCGLSafePtrDelete(m_pOpenGLShader);
    CCGLSafePtrDelete(m_pOpenGLTexture);

    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);

    glDeleteTextures(1,&m_texture);

}
void CCTexturedPlane::Render(CCGLCamera* pCamera, float deltaTime)
{
    Q_UNUSED(deltaTime)

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
    QMatrix4x4 planeMatScale;
    QMatrix4x4 planeMatRot;
    planeMat.setToIdentity();
    planeMatTrans.translate(0,0,0);

    planeMatRot.setToIdentity();
    planeMatRot.rotate(90,1,0,0);

    planeMatScale.setToIdentity();
    planeMatScale.scale(5,5,1);

    planeMat =  planeMatRot* planeMatScale * planeMatTrans ;

    planeMat =  pCamera->projectionMatrix * pCamera->viewMatrix * planeMat ;

    shaderProgram->setUniformValue("uni_mat",planeMat);


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
}
