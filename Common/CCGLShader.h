#ifndef CCGLSHADER_H
#define CCGLSHADER_H



#include "Common/CCGlobalDefine.h"
#include <QObject>
#include <QOpenGLShader>


class CCGLShader : public QObject
{
public:
    explicit CCGLShader(QObject *parent = nullptr);
    virtual ~CCGLShader();

    void  SetupShaderResources(const QString& vs, const QString& fs);
    QOpenGLShaderProgram* GetShaderProgram(){ return m_pShaderProgram; }
    void  Use();
    void  UnUse();

private:
    QOpenGLShaderProgram*   m_pShaderProgram;

};

#endif // CCGLSHADER_H
