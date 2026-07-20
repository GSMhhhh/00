/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include <GL/glew.h>
#include "CCGLSkybox.h"


CCGLSkybox::CCGLSkybox(QObject *parent) : QObject(parent)
{
    m_pOpenGLShader = new CCGLShader();
    m_pOpenGLShader->SetupShaderResources(":/res/shaders/skybox.vert",":/res/shaders/skybox.frag");

    m_pOpenGLTexture = new CCGLTexture();

    QStringList fileList;
    fileList.append(":/res/Images/sky_px.jpg");
    fileList.append(":/res/Images/sky_py.jpg");
    fileList.append(":/res/Images/sky_pz.jpg");
    fileList.append(":/res/Images/sky_nx.jpg");
    fileList.append(":/res/Images/sky_ny.jpg");
    fileList.append(":/res/Images/sky_nz.jpg");


    for(int i=0; i<fileList.count(); i++)
    {
        QString textString= fileList.at(i);
        m_texture[i] = m_pOpenGLTexture->CreateOpenGLSkyBoxTexture(textString);
    }

    const CCVertex cubeVertexs[]  = {
            {  1, 1, -1,  0, 1 },
            {  1, -1, -1, 0, 0 },
            {  1, -1, 1,  1, 0 },
            {  1, 1, 1,   1, 1 },

            {  -1, 1, 1,  1, 0 },
            {  -1, 1, -1, 1, 1 },
            {  1, 1, -1,  0, 1 },
            {  1, 1, 1,   0, 0  },

            {  -1, 1, -1, 0, 1 },
            {  -1, -1, -1, 0, 0 },
            {  1, -1, -1,  1, 0 },
            {  1, 1, -1,  1, 1 },

            {  -1, 1, 1,  0, 1 },
            {  -1, -1, 1, 0, 0 },
            {  -1, -1, -1,1, 0 },
            {  -1, 1, -1, 1, 1 },

            {  -1, -1, -1, 1, 0 },
            {  -1, -1, 1,  1, 1  },
            {  1, -1, 1,   0, 1 },
            {  1, -1, -1,  0, 0},

            {  1, 1, 1,   0, 1 },
            {  1, -1, 1,  0, 0 },
            {  -1, -1, 1, 1, 0 },
            {  -1, 1, 1,  1, 1 }
     };


    const short cubeIndex[]=  {
       0, 1, 2,  0, 2, 3,
       4, 5, 6,  4, 6, 7,
       8, 9, 10,  8, 10, 11,
       12, 13, 14,  12, 14, 15,
       16, 17, 18, 16, 18, 19,
       20, 21, 22,  20, 22, 23
    };

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(sizeof(cubeVertexs));
    m_vertexBuffer->write(0, cubeVertexs, sizeof(cubeVertexs));
    m_vertexBuffer->release();


    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->bind();
    m_indexBuffer->allocate(sizeof(cubeIndex));
    m_indexBuffer->write(0, cubeIndex, sizeof(cubeIndex));
    m_indexBuffer->release();
}
CCGLSkybox::~CCGLSkybox()
{

    CCGLSafePtrDelete(m_pOpenGLShader);
    CCGLSafePtrDelete(m_pOpenGLTexture);

    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);


    glDeleteTextures(6,m_texture);
}

void CCGLSkybox::Render(CCGLCamera* rCamera, float deltaTime)
{
    Q_UNUSED(deltaTime)

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_pOpenGLShader->Use();

    QOpenGLShaderProgram* shaderProgram = m_pOpenGLShader->GetShaderProgram();

    if(shaderProgram == NULL){
        return;
    }

    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    shaderProgram->enableAttributeArray("attr_position");
    shaderProgram->setAttributeBuffer("attr_position",GL_FLOAT, 0, 3, sizeof(CCVertex));//tupleSize 元组大小

    shaderProgram->enableAttributeArray("attr_uv");
    shaderProgram->setAttributeBuffer("attr_uv",GL_FLOAT,3*sizeof(float), 2, sizeof(CCVertex));


    QMatrix4x4 cubeMat;
    cubeMat.setToIdentity();

    QMatrix4x4 cubeMatRot;
    cubeMatRot.setToIdentity();
    cubeMatRot.scale(50,50,50);
    cubeMat = rCamera->projectionMatrix * rCamera->viewMatrix * cubeMatRot;

    shaderProgram->setUniformValue("uni_mat",cubeMat);



    for(int i=0; i< 6; i++)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_texture[i]);

        const short* indices =(const short *) (i*6*sizeof(short));
        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);

        glBindTexture(GL_TEXTURE_2D,0);

    }

    shaderProgram->disableAttributeArray("attr_position");
    shaderProgram->disableAttributeArray("attr_uv");

    m_vertexBuffer->release();
    m_indexBuffer->release();

    m_pOpenGLShader->UnUse();
}
