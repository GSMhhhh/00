/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include <GL/glew.h>

#include "CCMesh.h"

CCMesh::CCMesh()
{

}

CCMesh::~CCMesh()
{
    CCGLSafePtrDelete(m_pOpenGLShader);

    CCGLSafePtrDelete(m_vertexBuffer);
    CCGLSafePtrDelete(m_indexBuffer);

    CCGLSafePtrDelete(m_pDiffuseTexture);
    CCGLSafePtrDelete(m_pNormalTexture);
    CCGLSafePtrDelete(m_pSpecularTexture);


    glDeleteTextures(1,&m_diffuseId);
    glDeleteTextures(1,&m_normalId);
    glDeleteTextures(1,&m_specularId);

}

CCMesh::CCMesh(const QVector<CCVertexData> &vertData, const QVector<GLuint> &indexes)
{

    init(vertData, indexes);
}

void CCMesh::init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes)
{
    m_pOpenGLShader = new CCGLShader();
    m_pOpenGLShader->SetupShaderResources(":/res/shaders/objloader.vert",":/res/shaders/objloader.frag");

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(vertData.size() * sizeof (VertexData));
    m_vertexBuffer->write(0, vertData.constData(), vertData.size() * sizeof (VertexData));
    m_vertexBuffer->release();


    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->bind();
    m_indexBuffer->allocate(indexes.size() * sizeof (GLuint));
    m_indexBuffer->write(0, indexes.constData(), indexes.size() * sizeof (GLuint));
    m_indexBuffer->release();

    QString diffuseString = QString(":/res/Models/monkey_diffuse.png");
    QString normalString = QString(":/res/Models/monkey_normal.png");
    QString specularString = QString(":/res/Models/monkey_specular.png");


    m_pDiffuseTexture = new CCGLTexture();
    m_pNormalTexture = new CCGLTexture();
    m_pSpecularTexture = new CCGLTexture();

    m_diffuseId = m_pDiffuseTexture->CreateOpenGLTexture(diffuseString);
    m_normalId = m_pDiffuseTexture->CreateOpenGLTexture(normalString);
    m_specularId = m_pDiffuseTexture->CreateOpenGLTexture(specularString);

}



void CCMesh::Render(CCGLCamera* pCamera, float deltaTime)
{
    Q_UNUSED(deltaTime)
    if (!m_vertexBuffer->isCreated() || !m_indexBuffer->isCreated()){
        return;
    }

    m_pOpenGLShader->Use();

    QOpenGLShaderProgram* shaderProgram = m_pOpenGLShader->GetShaderProgram();

    if(shaderProgram == NULL){
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    shaderProgram->setUniformValue("texture_diffuse", 0);
    glBindTexture(GL_TEXTURE_2D,m_diffuseId);


    glActiveTexture(GL_TEXTURE1);
    shaderProgram->setUniformValue("texture_normal", 1);
    glBindTexture(GL_TEXTURE_2D,m_normalId);


     glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,m_specularId);
    shaderProgram->setUniformValue("texture_specular", 2);

    shaderProgram->setUniformValue("m_shiness", 32.0f);
    shaderProgram->setUniformValue("u_viewPos", pCamera->GetEyePosition());

    shaderProgram->setUniformValue("myLight.m_ambient", QVector3D(0.5,0.5,0.5));
    shaderProgram->setUniformValue("myLight.m_diffuse", QVector3D(0.8,0.8,0.8));
    shaderProgram->setUniformValue("myLight.m_specular", QVector3D(0.9,0.9,0.9));

    shaderProgram->setUniformValue("myLight.m_pos", QVector3D(5,5,5));
    shaderProgram->setUniformValue("myLight.m_c", 1.0f);
    shaderProgram->setUniformValue("myLight.m_l", 0.09f);
    shaderProgram->setUniformValue("myLight.m_q", 0.032f);


    QMatrix4x4 modelMatrix;

    QMatrix4x4 modelMatrixTrans;
    modelMatrixTrans.translate(m_Objx,m_Objy,-3);

    QMatrix4x4 modelMatrixRot;
    modelMatrixRot.rotate(0,QVector3D(0,0,0));

    QMatrix4x4 modelMatrixScale;
    modelMatrixScale.scale(0.33 * m_ObjScale ,0.33 *4/3 * m_ObjScale ,0.33);

    modelMatrix =    modelMatrixTrans * modelMatrixRot * modelMatrixScale;


    shaderProgram->setUniformValue("u_modelMatrix", modelMatrix);
    shaderProgram->setUniformValue("u_viewMatrix", pCamera->viewMatrix);
    shaderProgram->setUniformValue("u_projectionMatrix", pCamera->projectionMatrix);

    m_vertexBuffer->bind();

    int offset = 0;

    int vertLoc = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertLoc);
    shaderProgram->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof (QVector3D);

    int textLoc = shaderProgram->attributeLocation("a_texturCoord");
    shaderProgram->enableAttributeArray(textLoc);
    shaderProgram->setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof (QVector2D);

    int normalLoc = shaderProgram->attributeLocation("a_normal");
    shaderProgram->enableAttributeArray(normalLoc);
    shaderProgram->setAttributeBuffer(normalLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset += sizeof (QVector3D);

    int tangentLoc = shaderProgram->attributeLocation("a_tangent");
    shaderProgram->enableAttributeArray(tangentLoc);
    shaderProgram->setAttributeBuffer(tangentLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset += sizeof (QVector3D);

    int bitangentLoc = shaderProgram->attributeLocation("a_bitangent");
    shaderProgram->enableAttributeArray(bitangentLoc);
    shaderProgram->setAttributeBuffer(bitangentLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    m_indexBuffer->bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer->size(), GL_UNSIGNED_INT, nullptr);

    m_vertexBuffer->release();
    m_indexBuffer->release();

    glBindTexture(GL_TEXTURE_2D,0);

}

void CCMesh::UpdateModelPosition(QPointF pos,float scale)
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


