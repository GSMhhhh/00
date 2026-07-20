/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include <GL/glew.h>
#include "CCYUVVideo.h"
#include <QDebug>

CCYUVVideo::CCYUVVideo(QObject *parent) : QObject(parent)
{

   glGenTextures(3, m_textures);

   m_pOpenGLShader = new CCGLShader();
   m_pOpenGLShader->SetupShaderResources(":/res/shaders/vertex_yuv.vert",":/res/shaders/fragment_yuv.frag");

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


CCYUVVideo::~CCYUVVideo()
{
    CCGLSafePtrDelete(m_pOpenGLShader);

    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);

    glDeleteTextures(3,m_textures);

}

void CCYUVVideo::Render(CCGLCamera* pCamera, CCYUV_Buffer* yuvBuffer)
{
    if(yuvBuffer == NULL || yuvBuffer->width <=0 || yuvBuffer->height <= 0){
        return;
    }


    QOpenGLShaderProgram* shaderProgram = m_pOpenGLShader->GetShaderProgram();

    if(shaderProgram == NULL){
        return;
    }

    m_pOpenGLShader->Use();

    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    shaderProgram->bind();


    shaderProgram->enableAttributeArray("attr_position");
    shaderProgram->setAttributeBuffer("attr_position",GL_FLOAT, 0, 3, sizeof(CCVertex));//tupleSize 元组大小

    shaderProgram->enableAttributeArray("attr_uv");
    shaderProgram->setAttributeBuffer("attr_uv",GL_FLOAT,3*sizeof(float), 2, sizeof(CCVertex));

    QMatrix4x4 planeMat;
    QMatrix4x4 planeMatTrans;
    planeMat.setToIdentity();
    planeMat.translate(0,0,-5);

    planeMat =  pCamera->projectionMatrix * pCamera->viewMatrix * planeMat ;

    shaderProgram->setUniformValue("uni_mat",planeMat);


    shaderProgram->setUniformValue("uni_textureY",0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, yuvBuffer->width, yuvBuffer->height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, yuvBuffer->buffer);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    shaderProgram->setUniformValue("uni_textureU",1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[1]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE,yuvBuffer->width/2, yuvBuffer->height/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (char*)(yuvBuffer->buffer+yuvBuffer->ylength));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    shaderProgram->setUniformValue("uni_textureV",2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_textures[2]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, yuvBuffer->width/2, yuvBuffer->height/2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (char*)(yuvBuffer->buffer+yuvBuffer->ylength+yuvBuffer->ulength));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const short* indices =(const short *) 0;
    glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);


    m_vertexBuffer->release();
    m_indexBuffer->release();


    m_pOpenGLShader->UnUse();


}
