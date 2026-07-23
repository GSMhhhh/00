#include "CCGLShader.h"

CCGLShader::CCGLShader(QObject *parent) : QObject(parent)
{
    m_pShaderProgram = NULL;
}

CCGLShader::~CCGLShader()
{
    CCGLSafePtrDelete(m_pShaderProgram);
}

void  CCGLShader::SetupShaderResources(const QString& vs, const QString& fs)
{
    QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex,this);
    bool bCompileVS = vertexShader->compileSourceFile(vs);
    if(bCompileVS == false){
        qDebug()<<"VS Compile ERROR:"<<vertexShader->log();
    }

    QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment,this);
    bool bCompileFS = fragmentShader->compileSourceFile(fs);
    if(bCompileFS == false){
        qDebug()<<"FS Compile ERROR:"<<fragmentShader->log();
    }

    m_pShaderProgram = new QOpenGLShaderProgram();
    m_pShaderProgram->addShader(vertexShader);
    m_pShaderProgram->addShader(fragmentShader);

    bool linkStatus = m_pShaderProgram->link();
    if(linkStatus == false){
        qDebug()<<"LINK ERROR:"<<m_pShaderProgram->log();
    }

    if(vertexShader != NULL){
        delete vertexShader;
        vertexShader = NULL;
    }

    if(fragmentShader != NULL){
        delete fragmentShader;
        fragmentShader = NULL;
    }
}

void  CCGLShader::Use()
{
    if(m_pShaderProgram){
        m_pShaderProgram->bind();
    }
}
void  CCGLShader::UnUse()
{
    if(m_pShaderProgram){
        m_pShaderProgram->release();
    }
}
